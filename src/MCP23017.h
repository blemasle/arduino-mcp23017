#pragma once

#include <Arduino.h>
#include <Wire.h>

#define _MCP23017_INTERRUPT_SUPPORT_ ///< Enables support for MCP23017 interrupts.

/**
 * Controls if the two interrupt pins mirror each other.
 * See "3.6 Interrupt Logic".
 */
enum MCP23017_INTMODE
{
	SEPARATED = 0,	///< Interrupt pins are kept independent
	OR = 0b01000000	///< Interrupt pins are mirrored
};

/**
 * Registers addresses.
 * The library use addresses for IOCON.BANK = 0.
 * See "3.2.1 Byte mode and Sequential mode".
 */
enum MCP23017_REGISTER
{
	IODIRA		= 0x00, 		///< Controls the direction of the data I/O for port A.
	IODIRB		= 0x01,			///< Controls the direction of the data I/O for port B.
	IPOLA		= 0x02,			///< Configures the polarity on the corresponding GPIO port bits for port A.
	IPOLB		= 0x03,			///< Configures the polarity on the corresponding GPIO port bits for port B.
	GPINTENA	= 0x04,			///< Controls the interrupt-on-change for each pin of port A.
	GPINTENB	= 0x05,			///< Controls the interrupt-on-change for each pin of port B.
	DEFVALA		= 0x06,			///< Controls the default comparaison value for interrupt-on-change for port A.
	DEFVALB		= 0x07,			///< Controls the default comparaison value for interrupt-on-change for port B.
	INTCONA		= 0x08,			///< Controls how the associated pin value is compared for the interrupt-on-change for port A.
	INTCONB		= 0x09,			///< Controls how the associated pin value is compared for the interrupt-on-change for port B.
	IOCON		= 0x0A,			///< Controls the device.
	GPPUA		= 0x0C,			///< Controls the pull-up resistors for the port A pins.
	GPPUB		= 0x0D,			///< Controls the pull-up resistors for the port B pins.
	INTFA		= 0x0E,			///< Reflects the interrupt condition on the port A pins.
	INTFB		= 0x0F,			///< Reflects the interrupt condition on the port B pins.
	INTCAPA		= 0x10,			///< Captures the port A value at the time the interrupt occured.
	INTCAPB		= 0x11,			///< Captures the port B value at the time the interrupt occured.
	GPIOA		= 0x12,			///< Reflects the value on the port A.
	GPIOB		= 0x13,			///< Reflects the value on the port B.
	OLATA		= 0x14,			///< Provides access to the port A output latches.
	OLATB		= 0x15,			///< Provides access to the port B output latches.
};

inline MCP23017_REGISTER operator+(MCP23017_REGISTER a, byte b) {
	return static_cast<MCP23017_REGISTER>(static_cast<int>(a) + b);
};

class MCP23017
{
private:
	byte _deviceAddr;
public:
	/**
	 * Instantiates a new instance to interact with a MCP23017 at the specified address.
	 */
	MCP23017(byte addr);
	~MCP23017();
#ifdef _DEBUG
	void debug();
#endif
	/**
	 * Initializes the chip with the default configuration.
	 * Enables Byte mode (IOCON.BANK = 0 and IOCON.SEQOP = 1).
	 * Enables pull-up resistors for all pins. This will only be effective for input pins.
	 * 
	 * See "3.2.1 Byte mode and Sequential mode".
	 */
	void init();
	/**
	 * Controls the pins direction on a whole port at once.
	 * 
	 * 1 = Pin is configured as an input.
	 * 0 = Pin is configured as an output.
	 * 
	 * See "3.5.1 I/O Direction register".
	 */
	void portMode(byte port, byte value);
	/**
	 * Controls a single pin direction. 
	 * Pin 0-7 for port A, 8-15 fo port B.
	 * 
	 * 1 = Pin is configured as an input.
	 * 0 = Pin is configured as an output.
	 *
	 * See "3.5.1 I/O Direction register".
	 */
	void pinMode(byte pin, byte mode);

	/**
	 * Writes a single pin state.
	 * Pin 0-7 for port A, 8-15 for port B.
	 * 
	 * 1 = Logic-high
	 * 0 = Logic-low
	 * 
	 * See "3.5.10 Port register".
	 */
	void digitalWrite(byte pin, byte state);
	/**
	 * Reads a single pin state.
	 * Pin 0-7 for port A, 8-15 for port B.
	 * 
	 * 1 = Logic-high
	 * 0 = Logic-low
	 * 
	 * See "3.5.10 Port register".
	 */ 
	byte digitalRead(byte pin);

	/**
	 * Writes pins state to a whole port.
	 * 
	 * 1 = Logic-high
	 * 0 = Logic-low
	 * 
	 * See "3.5.10 Port register".
	 */
	void writePort(byte port, byte value);
	/**
	 * Writes pins state to both ports.
	 * 
	 * 1 = Logic-high
	 * 0 = Logic-low
	 * 
	 * See "3.5.10 Port register".
	 */
	void write(short value);

	/**
	 * Reads pins state for a whole port.
	 * 
	 * 1 = Logic-high
	 * 0 = Logic-low
	 * 
	 * See "3.5.10 Port register".
	 */
	byte readPort(byte port);
	/**
	 * Reads pins state for both ports. 
	 * 
	 * 1 = Logic-high
	 * 0 = Logic-low
	 * 
	 * See "3.5.10 Port register".
	 */
	short read();

	/**
	 * Writes a single register value.
	 */
	void writeRegister(MCP23017_REGISTER reg, byte value);
	/**
	 * Writes values to a register pair.
	 * 
	 * For portA and portB variable to effectively match the desired port,
	 * you have to supply a portA register address to reg. Otherwise, values
	 * will be reversed due to the way the MCP23017 works in Byte mode.
	 */
	void writeRegister(MCP23017_REGISTER reg, byte portA, byte portB);
	/**
	 * Reads a single register value.
	 */
	byte readRegister(MCP23017_REGISTER reg);
	/**
	 * Reads the values from a register pair.
	 * 
	 * For portA and portB variable to effectively match the desired port,
	 * you have to supply a portA register address to reg. Otherwise, values
	 * will be reversed due to the way the MCP23017 works in Byte mode.
	 */
	void readRegister(MCP23017_REGISTER reg, byte& portA, byte& portB);

#ifdef _MCP23017_INTERRUPT_SUPPORT_

	/**
	 * Controls how the interrupt pins act with each other.
	 * If intMode is SEPARATED, interrupt conditions on a port will cause its respective INT pin to active.
	 * If intMode is OR, interrupt pins are OR'ed so an interrupt on one of the port will cause both pints to active.
	 * 
	 * Controls the IOCON.MIRROR bit. 
	 * See "3.5.6 Configuration register".
	 */
	void interruptMode(MCP23017_INTMODE intMode);
	/**
	 * Configures interrupt registers using an Arduino-like API.
	 * mode can be one of CHANGE, FALLING or RISING.
	 */
	void interrupt(byte port, byte mode);
	/**
	 * Disable interrupts for the specified port.
	 */
	void disableInterrupt(byte port);
	/**
	 * Reads which pin caused the interrupt.
	 */
	void interruptedBy(byte& portA, byte& portB);
	/**
	 * Clears interrupts on both ports.
	 */
	void clearInterrupts();
	/**
	 * Clear interrupts on both ports. Returns port values at the time the interrupt occured.
	 */
	void clearInterrupts(byte& portA, byte& portB);

#endif
};