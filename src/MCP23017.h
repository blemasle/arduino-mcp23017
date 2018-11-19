#pragma once

#include <Arduino.h>
#include <Wire.h>

#define _MCP23017_INTERRUPT_SUPPORT_ ///< Enable support for MCP23017 interrupts.

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
 * Registers addresses for IOCON.BANK = 0.
 * See "3.2.1 Byte mode and Sequential mode".
 */
enum MCP23017_REGISTER
{
	IODIRA		= 0x00, 		///< Controls the direction of the data I/O for port A. See "3.5.1 I/O Direction register".
	IODIRB		= 0x01,			///< Controls the direction of the data I/O for port B. See "3.5.1 I/O Direction register".
	IPOLA		= 0x02,			///< Configures the polarity on the corresponding GPIO port bits for port A. See "3.5.2 Input polarity register".
	IPOLB		= 0x03,			///< Configures the polarity on the corresponding GPIO port bits for port B. See "3.5.2 Input polarity register".
	GPINTENA	= 0x04,			///< Controls the interrupt-on-change for each pin of port A. See "3.5.3 Interrupt-on-change control register".
	GPINTENB	= 0x05,			///< Controls the interrupt-on-change for each pin of port B. See "3.5.3 Interrupt-on-change control register".
	DEFVALA		= 0x06,			///< Controls the default comparaison value for interrupt-on-change for port A. See "3.5.4 Default compare register for Intterupt-on-change".
	DEFVALB		= 0x07,			///< Controls the default comparaison value for interrupt-on-change for port B. See "3.5.4 Default compare register for Intterupt-on-change".
	INTCONA		= 0x08,			///< Controls how the associated pin value is compared for the interrupt-on-change for port A. See "3.5.5 Interrupt control register".
	INTCONB		= 0x09,			///< Controls how the associated pin value is compared for the interrupt-on-change for port B. See "3.5.5 Interrupt control register".
	IOCON		= 0x0A,			///< Controls the device. See "3.5.6 Configuration register".
	GPPUA		= 0x0C,			///< Controls the pull-up resistors for the port A pins. See "3.5.7 Pull-up resistor configuration register".
	GPPUB		= 0x0D,			///< Controls the pull-up resistors for the port B pins. See "3.5.7 Pull-up resistor configuration register".
	INTFA		= 0x0E,			///< Reflects the interrupt condition on the port A pins. See "3.5.8 Interrupt flag register".	
	INTFB		= 0x0F,			///< Reflects the interrupt condition on the port B pins. See "3.5.8 Interrupt flag register".
	INTCAPA		= 0x10,			///< Captures the port A value at the time the interrupt occured. See "3.5.9 Interrupt capture register".
	INTCAPB		= 0x11,			///< Captures the port B value at the time the interrupt occured. See "3.5.9 Interrupt capture register".
	GPIOA		= 0x12,			///< Reflects the value on the port A. See "3.5.10 Port register".
	GPIOB		= 0x13,			///< Reflects the value on the port B. See "3.5.10 Port register".
	OLATA		= 0x14,			///< Provides access to the port A output latches. See "3.5.11 Output latch register".
	OLATB		= 0x15,			///< Provides access to the port B output latches. See "3.5.11 Output latch register".
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
	 * Instantiate a new instance to interact with a MCP23017 at the specified address.
	 */
	MCP23017(byte addr);
	~MCP23017();
#ifdef _DEBUG
	void debug();
#endif
	/**
	 * Initializes the chip with the default configuration.
	 * Enable Byte mode (IOCON.BANK = 0 and IOCON.SEQOP = 1) and all pull-up resistors.
	 */
	void init();
	/**
	 * Controls the pin direction on a whole port at once.
	 */
	void portMode(byte port, byte value);
	/**
	 * Controls a single pin direction. 
	 * Pin 0-7 for port A, 8-15 fo port B.
	 */
	void pinMode(byte pin, byte mode);

	/**
	 * Writes a single pin state.
	 * Pin 0-7 for port A, 8-15 for port B.
	 */
	void digitalWrite(byte pin, byte state);
	/**
	 * Reads a single pin state.
	 * Pin 0-7 for port A, 8-15 for port B.
	 */ 
	byte digitalRead(byte pin);

	/**
	 * Writes pins state to a whole port.
	 */
	void writePort(byte port, byte value);
	/**
	 * Writes pins state to both ports.
	 */
	void write(short value);

	/**
	 * Reads pins state for a whole port.
	 */
	byte readPort(byte port);
	/**
	 * Reads pins state for both ports. 
	 */
	short read();

	/**
	 * Writes a single register value.
	 */
	void writeRegister(MCP23017_REGISTER reg, byte value);
	/**
	 * Writes values to a register pair.
	 * 
	 * Due to the way MCP23017 addressing works, portA and portB values
	 * will be reversed if you supply a portB register address to reg.
	 */
	void writeRegister(MCP23017_REGISTER reg, byte portA, byte portB);
	/**
	 * Reads a single register value.
	 */
	byte readRegister(MCP23017_REGISTER reg);
	/**
	 * Reads the values from a register pair.
	 * 
	 * Due to the way MCP23017 addressing works, portA and portB values
	 * will be reversed if you supply a portB register address to reg.
	 */
	void readRegister(MCP23017_REGISTER reg, byte& portA, byte& portB);

#ifdef _MCP23017_INTERRUPT_SUPPORT_

	/**
	 * Controls the IOCON.MIRROR bit. 
	 * 
	 * See "3.5.6 Configuration register".
	 */
	void interruptMode(MCP23017_INTMODE intMode);
	/**
	 * Use Arduino like configuration API to configure interrupts registers.
	 * 
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
	 * Clear interrupts on both ports.
	 */
	void clearInterrupts();
	/**
	 * Clear interrupts on both ports, returning their value at the time
	 * the interrupt occured.
	 */
	void clearInterrupts(byte& portA, byte& portB);

#endif
};