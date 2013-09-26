#include "MCP23017.h"

byte _addr;

MCP23017::MCP23017(byte addr) {
	_addr = addr;
}

MCP23017::~MCP23017() {}

void MCP23017::init()
{
	//BANK = 0 : sequential register addresses
	//MIRROR = 0, use configureInterrupt 
	//SEQOP = 1 : sequential operation disabled, address pointer does not increment
	//DISSLW = 0 : slew rate enabled
	//HAEN = 0 : hardware address pin always enabled on 23017
	//ODR = 0 : open drain output
	//INTPOL = 0 : interuppt active low
	writeRegister(IOCON, 0b00100000);

	//enable all pull up resistors (will be effective for input pins only)
	writeRegister(GPPUA, 0xFF, 0xFF);
}

void MCP23017::portMode(byte port, byte value)
{
	writeRegister(IODIRA + port, value);
}

void MCP23017::pinMode(byte pin, byte mode)
{
	MCP23017_REGISTER iodirreg = IODIRA;
	byte iodir;
	if(pin > 7)
	{
		iodirreg = IODIRB;
		pin -= 8;
	}

	iodir = readRegister(iodirreg);
	if(mode == OUTPUT) iodir |= _BV(pin);
	else iodir &= ~_BV(pin);

	writeRegister(iodirreg, iodir);
}

void MCP23017::digitalWrite(byte pin, byte state)
{
	MCP23017_REGISTER gpioreg = GPIOA;
	byte gpio;
	if(pin > 7)
	{
		gpioreg = GPIOB;
		pin -= 8;
	}

	gpio = readRegister(gpioreg);
	if(state == HIGH) gpio |= _BV(pin);
	else gpio &= ~_BV(pin);

	writeRegister(gpioreg, gpio);
}

byte MCP23017::digitalRead(byte pin)
{
	MCP23017_REGISTER gpioreg = GPIOA;
	byte gpio;
	if(pin > 7)
	{
		gpioreg = GPIOB;
		pin -=8;
	}

	gpio = readRegister(gpioreg);
	if(gpio & _BV(pin) == _BV(pin)) return HIGH;
	return LOW;
}

void MCP23017::writePort(byte port, byte value)
{
	writeRegister(GPIOA + port, value);
}

void MCP23017::write(short value)
{
	writeRegister(GPIOA, lowByte(value), highByte(value));
}

byte MCP23017::readPort(byte port)
{
	return readRegister(GPIOA + port);
}

short MCP23017::read()
{
	byte a = readPort(0);
	byte b = readPort(1);

	return a | b << 8;
}

void MCP23017::writeRegister(MCP23017_REGISTER reg, byte value)
{
	Wire.beginTransmission(_addr);
	Wire.write(reg);
	Wire.write(value);
	Wire.endTransmission();
}

void MCP23017::writeRegister(MCP23017_REGISTER reg, byte portA, byte portB)
{
	Wire.beginTransmission(_addr);
	Wire.write(reg);
	Wire.write(portA);
	Wire.write(portB);
	Wire.endTransmission();
}


byte MCP23017::readRegister(MCP23017_REGISTER reg)
{
	Wire.beginTransmission(_addr);
	Wire.write(reg);
	Wire.endTransmission();
	Wire.requestFrom(_addr, (byte)1);
	return Wire.read();
}

void MCP23017::readRegister(MCP23017_REGISTER reg, byte& portA, byte& portB)
{
	Wire.beginTransmission(_addr);
	Wire.write(reg);
	Wire.endTransmission();
	Wire.requestFrom(_addr, (byte)2);
	portA = Wire.read();
	portB = Wire.read();
}

#ifdef _MCP23017_INTERRUPT_SUPPORT_

void MCP23017::interruptMode(MCP23017_INTMODE intMode)
{
	byte iocon = readRegister(IOCON);
	if(intMode == OR) iocon |= OR;
	else iocon &= ~(OR);

	writeRegister(IOCON, iocon);
}

void MCP23017::interrupt(byte port, byte mode)
{
	MCP23017_REGISTER defvalreg = DEFVALA + port;
	MCP23017_REGISTER intconreg = INTCONA + port;

	//enable interrupt for port
	writeRegister(GPINTENA + port, 0xFF);
	switch(mode)
	{
	case CHANGE:
		//interrupt on change
		writeRegister(intconreg, 0);
		break;
	case FALLING:
		//interrupt falling : compared against defval, 0xff
		writeRegister(intconreg, 0xFF);
		writeRegister(defvalreg, 0xFF);
		break;
	case RISING:
		//interrupt falling : compared against defval, 0x00
		writeRegister(intconreg, 0xFF);
		writeRegister(defvalreg, 0x00);
		break;
	}
}

void MCP23017::interruptedBy(byte& portA, byte& portB)
{
	readRegister(INTFA, portA, portB);
}

void MCP23017::disableInterrupt(byte port)
{
	writeRegister(GPINTENA + port, 0x00);
}

void MCP23017::clearInterrupts()
{
	byte a, b;
	clearInterrupts(&a, &b);
}

void MCP23017::clearInterrupts(byte& portA, byte& portB)
{
	readRegister(INTCAPA, portA, portB);
}

#endif