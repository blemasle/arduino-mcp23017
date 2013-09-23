#ifndef _MCP23017_h
#define _MCP23017_h

#define _MCP23017_INTERRUPT_SUPPORT_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <Wire.h>

enum MCP23017_INTMODE
{
	SEPARATED = 0,
	OR = 0b01000000
};

//register for BANK = 0
enum MCP23017_REGISTER
{
	IODIRA		= 0x00,
	IODIRB		= 0x01,
	IPOLA		= 0x02,
	IPOLB		= 0x03,
	GPINTENA	= 0x04,
	GPINTENB	= 0x05,
	DEFVALA		= 0x06,
	DEFVALB		= 0x07,
	INTCONA		= 0x08,
	INTCONB		= 0x09,
	IOCON		= 0x0A,
	//IOCONB		= 0x0B,
	GPPUA		= 0x0C,
	GPPUB		= 0x0D,
	INTFA		= 0x0E,
	INTFB		= 0x0F,
	INTCAPA		= 0x10,
	INTCAPB		= 0x11,
	GPIOA		= 0x12,
	GPIOB		= 0x13,
	OLATA		= 0x14,
	OLATB		= 0x15,
};

inline MCP23017_REGISTER operator+(MCP23017_REGISTER a, byte b) {
	return static_cast<MCP23017_REGISTER>(static_cast<int>(a) + b);
};

class MCP23017
{
private:
public:
	MCP23017(byte addr);
	~MCP23017();
	void init();
	void portMode(byte port, byte value);
	void pinMode(byte pin, byte mode);

	void digitalWrite(byte pin, byte state);
	byte digitalRead(byte pin);

	void writePort(byte port, byte value);
	void write(short value);

	byte readPort(byte port);
	short read();

	void writeRegister(MCP23017_REGISTER reg, byte value);
	void writeRegister(MCP23017_REGISTER reg, byte portA, byte portB);
	byte readRegister(MCP23017_REGISTER reg);
	void readRegister(MCP23017_REGISTER reg, byte* portA, byte* portB);

#ifdef _MCP23017_INTERRUPT_SUPPORT_
	void interruptMode(MCP23017_INTMODE intMode);
	void interrupt(byte port, byte mode);
	void disableInterrupt(byte port);
	void interruptedBy(byte* portA, byte* portB);
	void clearInterrupts();
	void clearInterrupts(byte* portA, byte* portB);
#endif
};

#endif