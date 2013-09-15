#include "MCP23017.h"

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

void MCP23017::pinMode(byte portA, byte portB)
{
	writeRegister(IODIRA, portA, portB);
}

void MCP23017::write(short value)
{
	write(value & 0xFF, value >> 8);
}

void MCP23017::write(byte portA, byte portB)
{
	writeRegister(GPIOA, portA, portB);
}

short MCP23017::read()
{
	return readRegister(GPIOA);
}

void MCP23017::read(byte* portA, byte* portB)
{
	short value = read();
	*portA = value & 0xFF;
	*portB = value >> 8;
}

void MCP23017::digitalWrite(byte pin, byte state)
{

}

byte MCP23017::digitalRead(byte pin)
{

}

/* ============================================= */
/* ============== private methods ============== */
/* ============================================= */

void MCP23017::writeBoth(MCP2307_REGISTER reg, byte value)
{
	writeRegister(reg, value, value);
}

void MCP23017::writeRegister(MCP2307_REGISTER reg, byte portA, byte portB)
{
	Wire.beginTransmission(_addr);
	Wire.write(reg);
	Wire.write(portA); //port A
	Wire.write(portB); //port B
	Wire.endTransmission();
}

short MCP23017::readRegister(MCP2307_REGISTER reg)
{
	Wire.beginTransmission(_addr);
	Wire.write(reg);
	Wire.endTransmission();
	Wire.requestFrom(_addr, (byte)2);
	return Wire.read() & (Wire.read() << 8);
}