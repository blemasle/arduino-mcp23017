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
	//HAEN = 0 : hardware address pin always enabled on 23017
	//ODR = 0 : open drain output
	//INTPOL = 0 : active low
	writeRegister(IOCON, 0b00100000 | interruptMode);

	//enable all pull up resistors (will be effective for input pins only)
	writeBothRegister(GPPUA, 0xFF);
}

void MCP23017::pinMode(byte portA, byte portB)
{
	writeRegister(IODIRA, portA, portB);
}

void MCP23017::write(short value)
{
	writeRegister(GPIOA, value & 0xFF, value >> 8);
}

void MCP23017::write(byte portA, byte portB)
{
	writeRegister(GPIOA, portA, portB);
}

short MCP23017::read()
{
	return readBothRegister(GPIOA);
}

void MCP23017::read(byte* portA, byte* portB)
{
	short value = readBothRegister(GPIOA);
	*portA = value & 0xFF;
	*portB = value >> 8;
}

void MCP23017::digitalWrite(byte pin, byte state)
{
	MCP23017_REGISTER gpioreg;
	short gpio;

	//16 pins available
	if(pin > 15) return;

	if(pin < 8) gpioreg = GPIOA;
	else {
		gpioreg = GPIOB;
		//for further compute easibility
		pin -= 8;
	}

	//read gpio current state
	gpio = readRegister(gpioreg);
	//compute new register value
	if(state == HIGH) gpio |= 1 << pin;
	else gpio &= ~(1 << pin);
	
	//send new value
	writeRegister(gpioreg, gpio);
	
}

byte MCP23017::digitalRead(byte pin)
{
	MCP23017_REGISTER gpioreg;
	short gpio;

	//16 pins available
	if(pin > 15) return 0;

	if(pin < 8) gpioreg = GPIOA;
	else {
		gpioreg = GPIOB;
		//for further compute easibility
		pin -= 8;
	}

	//read gpio current state
	gpio = readRegister(gpioreg);
	
	return (gpio >> pin) & 1;
}

/* ============================================= */
/* ============== private methods ============== */
/* ============================================= */

void MCP23017::writeBothRegister(MCP23017_REGISTER reg, byte value)
{
	writeRegister(reg, value, value);
}

void MCP23017::writeRegister(MCP23017_REGISTER reg, byte portA, byte portB)
{
	Wire.beginTransmission(_addr);
	Wire.write(reg);
	Wire.write(portA);
	Wire.write(portB);
	Wire.endTransmission();
}

void MCP23017::writeRegister(MCP23017_REGISTER reg, byte value)
{
	Wire.beginTransmission(_addr);
	Wire.write(reg);
	Wire.write(value);
	Wire.endTransmission();
}

short MCP23017::readBothRegister(MCP23017_REGISTER reg)
{
	Wire.beginTransmission(_addr);
	Wire.write(reg);
	Wire.endTransmission();
	Wire.requestFrom(_addr, (byte)2);
	return Wire.read() | (Wire.read() << 8);
}

byte MCP23017::readRegister(MCP23017_REGISTER reg)
{
	Wire.beginTransmission(_addr);
	Wire.write(reg);
	Wire.endTransmission();
	Wire.requestFrom(_addr, (byte)1);
	return Wire.read();
}