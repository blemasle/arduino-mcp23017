#pragma once

#include <Arduino.h>
#include <Wire.h>

#define _MCP23017_INTERRUPT_SUPPORT_  ///< Enables support for MCP23017 interrupts.

enum class MCP23017_PORT : uint8_t
{
	A = 0,
	B = 1
};

/**
 * Controls if the two interrupt pins mirror each other.
 * <See "3.6 Interrupt Logic".>
 */
enum class MCP23017_INTMODE : uint8_t
{
	SEPARATED = 0,	///< Interrupt pins are kept independent
	OR = 0b01000000	///< Interrupt pins are mirrored
};

/**
 * Registers addresses.
 * The library use addresses for IOCON.BANK = 0.
 * <See "3.2.1 Byte mode and Sequential mode".>
 */
enum class MCP23017_REGISTER : uint8_t
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

/// @brief operator for adding a B-offset to the A-register
inline MCP23017_REGISTER operator+(MCP23017_REGISTER a, MCP23017_PORT b) {
	return static_cast<MCP23017_REGISTER>(static_cast<uint8_t>(a) + static_cast<uint8_t>(b));
};

class MCP23017
{
private:
	TwoWire* _bus;
	uint8_t _deviceAddr;
public:
	/**
	 * Instantiates a new instance to interact with a MCP23017 at the specified address.
	 * @param address: bus address of MCP23017 (0x20 ~ 0x27)
	 * @param bus: refence to i2c bus object
	 */
	MCP23017(uint8_t address, TwoWire& bus = Wire);
	~MCP23017();
#ifdef _DEBUG
	void debug();
#endif

	/**
	 * @brief deprecated, for backward compability only
	 * 
	 */
	inline void init(){
		begin();
	}

	/**
	 * Initializes the chip with the default configuration.
	 * Enables Byte mode (IOCON.BANK = 0 and IOCON.SEQOP = 1).
	 * Enables pull-up resistors for all pins by default. 
	 * This will only be effective for input pins.
	 * <See "3.2.1 Byte mode and Sequential mode".>
	 * 
	 * @param pullup_a: bitmask for port A
	 * @param pullup_b: bitmask for port B
	 * See "3.2.1 Byte mode and Sequential mode".
	 */
	void begin(uint8_t pullup_a=0x00, uint8_t pullup_b=0x00);

	/**
	 * Controls the pins direction on a whole port at once.
	 * <See "3.5.1 I/O IODIR I/O DIRECTION REGISTER <0x00>", 
	 *      "3.5.2 I NPUT POLARITY REGISTER <0x01>",
	 *      "3.5.7 PULL-UP RESISTOR CONFIGURATION REGISTER <0x06>">
	 * @param port:      MCP23017 port A or B
	 * @param modes:     direction of whole port
	 * 		       INPUT or 0x0
	 *             OUTPUT or0x01
	 * @param pullup:    bitmask for internal 100k pullup resistors
	 * @param inverteds: bitmask for inverted mode
	 * 
	 */
	void portMode(MCP23017_PORT port, uint8_t modes, uint8_t pullups=0xff, uint8_t inverteds=0x00);

	/**
	 * Sets a single pins' direction. When the pin is an input pin
	 * a pullup and/or an inverted option can be specified
	 * <See "3.5.1 I/O IODIR I/O DIRECTION REGISTER <0x00>", 
	 *      "3.5.2 I NPUT POLARITY REGISTER <0x01>",
	 *      "3.5.7 PULL-UP RESISTOR CONFIGURATION REGISTER <0x06>">
	 * @param pin: Controls a single pin direction. 
	 *       Pin 0-7 for port A, 8-15 fo port B.
	 * @param mode: 
	 *             INPUT or 0x00
	 *             INPUT_PULLUP or 0x02
	 *             OUTPUT or 0x01
	 */
	void pinMode(uint8_t pin, uint8_t mode, bool inverted=false);

	/**
	 * Writes a single pin state.
	 * <See "3.5.10 Port register <0x09>".>
	 * @param pin:   Pin 0-7 for port A, 8-15 for port B.
	 * @param state: HIGH or 0x01
	 *         LOW  or 0x00
	 */
	void digitalWrite(uint8_t pin, uint8_t state);

	/**
	 * Reads a single pin state.
	 * <See "3.5.10 Port register <0x09>".>
	 * @param pin:   Pin 0-7 for port A, 8-15 for port B.
	 * @param return HIGH or 0x01, LOW or 0x00 
	 *         depending the hardwarestate of the pin
	 */ 
	uint8_t digitalRead(uint8_t pin);

	/**
	 * Writes pins state to a whole port.
	 * <See "3.5.10 Port register <0x09>".>
	 * @param port:      MCP23017 port A or B
	 * @param values:    bitmask to manipulate the given port as OUTPUT
	 */
	void writePort(MCP23017_PORT port, uint8_t values);

	/**
	 * Writes pins state to both ports.
	 * <See "3.5.10 Port register <0x09>".>
	 * @param values:    bitmask to manipulate all OUTPUT of the chip
	 */
	void write(uint16_t values);

	/**
	 * Reads pins state for a whole port.
	 * <See "3.5.10 Port register <0x09>".>
	 * @param port:  MCP23017 port A or B
	 * @param return HIGH or 0x01, LOW or 0x00 
	 *         depending the hardwarestate of the pin
	 */
	uint8_t readPort(MCP23017_PORT port);

	/**
	 * Reads pins state for both ports. 
	 * <See "3.5.10 Port register <0x09>".>
	 * @param return HIGH or 0x01, LOW or 0x00 
	 *         depending the hardwarestate of the pin
	 */
	uint16_t read();

	/**
	 * Writes a single register @reg with the specified value @val.
	 */
	void writeRegister(MCP23017_REGISTER reg, uint8_t value);

	/**
	 * Writes values to a register pair.
	 * 
	 * @note For portA and portB variable to effectively match the desired port,
	 * you have to supply a portA register address to reg. Otherwise, values
	 * will be reversed due to the way the MCP23017 works in Byte mode.
	 */
	void writeRegister(MCP23017_REGISTER reg, uint8_t portA, uint8_t portB);

	/**
	 * Reads a single registers value.
	 * @param reg: register to read
	 *       port A: 0x00 ~ 0A0
	 *       port B: 0x10 ~ 1A0
	 */
	uint8_t readRegister(MCP23017_REGISTER reg);

	/**
	 * Reads the values from a register pair.
	 * @param reg:   register to read
	 *               port A: 0x00 ~ 0A0
	 * @param portA: reference to port A value; returns the value by reference
	 * @param portB: reference to port B value; returns the value by reference
	 * 
	 * @note For portA and portB variable to effectively match the desired port,
	 * you have to supply a portA register address to reg. Otherwise, values
	 * will be reversed due to the way the MCP23017 works in Byte mode.
	 */
	void readRegister(MCP23017_REGISTER reg, uint8_t& portA, uint8_t& portB);

#ifdef _MCP23017_INTERRUPT_SUPPORT_

	/**
	 * @brief Controls how the interrupt pins act with each other.
	 * If intMode is SEPARATED, interrupt conditions on a port will cause its respective INT pin to active.
	 * If intMode is OR, interrupt pins are OR'ed so an interrupt on one of the port will cause both pints to active.
	 * <See "3.5.6 I/O EXPANDER CONFIGURATION REGISTER <0x05>".>
	 * 
	 * @param intMode  Controls the IOCON.MIRROR bit
	 */
	void interruptMode(MCP23017_INTMODE intMode);

	/**
	 * @brief Configures interrupt registers using an Arduino-like API-mode .
	 * <See "3.5.3 INTERRUPT-ON-CHANGE CONTROL REGISTER".>
	 * 
	 * @param port   MCP23017 port A or B
	 * @param mode   Can be one of CHANGE, FALLING or RISING
	 */
	void interrupt(MCP23017_PORT port, uint8_t mode);


	/**
	 * @brief Disables interrupts for the specified port.
	 * <See "3.5.3 INTERRUPT-ON-CHANGE CONTROL REGISTER".>
	 * 
	 * @param port MCP23017 port A or B
	 */
	void disableInterrupt(MCP23017_PORT port);

	/**
	 * @brief Reads which pin caused the interrupt.
	 * <See "3.5.9 GPINTEN: INTERRUPT CAPTURED REGISTER".>
	 * 
	 * @param portA reference to port A value; returns the value by reference
	 * @param portB reference to port B value; returns the value by reference
	 */
	void interruptedBy(uint8_t& portA, uint8_t& portB);

	/**
	 * @brief Clears interrupts on both ports.
	 * <See "3.5.9 INTERRUPT CAPTURED REGISTER".>
	 */
	void clearInterrupts();

	/**
	 * @brief Clear interrupts on both ports. Returns port values at the time the interrupt occured.
	 * <See "3.5.9 INTERRUPT CAPTURED REGISTER".>
	 * 
	 * @param portA reference to port A value; returns the value by reference
	 * @param portB reference to port B value; returns the value by reference
	 */
	void clearInterrupts(uint8_t& portA, uint8_t& portB);

#endif //  _MCP23017_INTERRUPT_SUPPORT_
};
