#ifndef _MCP23017_h
#define _MCP23017_h

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

enum MCP2307_REGISTER
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
	//IODIRB		= 0x0B,
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

class MCP23017
{
private:
public:
	MCP23017(byte addr);
	~MCP23017();
	void init(MCP23017_INTMODE interruptMode);
	void setIODir(byte portA, byte portB);
};

#endif