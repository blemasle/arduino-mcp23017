#include "MCP23017.h"

void writeBoth(MCP2307_REGISTER reg, byte value);
void write(MCP2307_REGISTER reg, byte portA, byte portB);

byte _addr;

MCP23017::MCP23017(byte addr) {
	_addr = addr;
}

MCP23017::~MCP23017() {}

void MCP23017::init(MCP23017_INTMODE interruptMode)
{
	//BANK = 0 : sequential register addresses
	//MIRROR = interruptMode, 
	//SEQOP = 1 : sequential operation disabled, address pointer does not increment
	//DISSLW = 0 : slew rate enabled
	//HAEN = 1 : hardware address pin enabled
	//ODR = 0 : open drain output
	//INTPOL = 0 : active low
	writeBoth(IOCON, 0b00101000 | interruptMode);

	//enable all pull up resistors (will be effective for input pins only)
	writeBoth(GPPUA, 0xFF);
}

void MCP23017::setIODir(byte portA, byte portB)
{
	write(IODIRA, portA, portB);
}


/* ============================================= */
/* ============== utility methods ============== */
/* ============================================= */
void writeBoth(MCP2307_REGISTER reg, byte value)
{
	write(reg, value, value);
}


void write(MCP2307_REGISTER reg, byte portA, byte portB)
{
	Wire.beginTransmission(_addr);
	Wire.write(reg);
	Wire.write(portA); //port A
	Wire.write(portB); //port B
	Wire.endTransmission();
}