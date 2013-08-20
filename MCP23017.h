#ifndef _MCP23017_h
#define _MCP23017_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <Wire.h>

class MCP23017
{
private:
public:
	MCP23017(byte addr);
	~MCP23017();
};

#endif