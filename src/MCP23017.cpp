#include "MCP23017.h"

MCP23017::MCP23017(byte addr) {
	_deviceAddr = addr;
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

#ifdef _DEBUG
void MCP23017::debug()
{
	Serial.begin(115200);
	byte conf = readRegister(IODIRA);
	Serial.print("IODIRA : ");
	Serial.print(conf, BIN);
	Serial.println();
	
	conf = readRegister(IODIRB);
	Serial.print("IODIRB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = readRegister(IPOLA);
	Serial.print("IPOLA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = readRegister(IPOLB);
	Serial.print("IPOLB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = readRegister(GPINTENA);
	Serial.print("GPINTENA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = readRegister(GPINTENB);
	Serial.print("GPINTENB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = readRegister(DEFVALA);
	Serial.print("DEFVALA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = readRegister(DEFVALB);
	Serial.print("DEFVALB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = readRegister(INTCONA);
	Serial.print("INTCONA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = readRegister(INTCONB);
	Serial.print("INTCONB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = readRegister(IOCON);
	Serial.print("IOCON : ");
	Serial.print(conf, BIN);
	Serial.println();

	//conf = readRegister(IOCONB);
	//Serial.print("IOCONB : ");
	//Serial.print(conf, BIN);
	//Serial.println();

	conf = readRegister(GPPUA);
	Serial.print("GPPUA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = readRegister(GPPUB);
	Serial.print("GPPUB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = readRegister(INTFA);
	Serial.print("INTFA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = readRegister(INTFB);
	Serial.print("INTFB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = readRegister(INTCAPA);
	Serial.print("INTCAPA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = readRegister(INTCAPB);
	Serial.print("INTCAPB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = readRegister(GPIOA);
	Serial.print("GPIOA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = readRegister(GPIOB);
	Serial.print("GPIOB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = readRegister(OLATA);
	Serial.print("OLATA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = readRegister(OLATB);
	Serial.print("OLATB : ");
	Serial.print(conf, BIN);
	Serial.println();
	Serial.end();
}
#endif

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
	Wire.beginTransmission(_deviceAddr);
	Wire.write(reg);
	Wire.write(value);
	Wire.endTransmission();
}

void MCP23017::writeRegister(MCP23017_REGISTER reg, byte portA, byte portB)
{
	Wire.beginTransmission(_deviceAddr);
	Wire.write(reg);
	Wire.write(portA);
	Wire.write(portB);
	Wire.endTransmission();
}


byte MCP23017::readRegister(MCP23017_REGISTER reg)
{
	Wire.beginTransmission(_deviceAddr);
	Wire.write(reg);
	Wire.endTransmission();
	Wire.requestFrom(_deviceAddr, (byte)1);
	return Wire.read();
}

void MCP23017::readRegister(MCP23017_REGISTER reg, byte& portA, byte& portB)
{
	Wire.beginTransmission(_deviceAddr);
	Wire.write(reg);
	Wire.endTransmission();
	Wire.requestFrom(_deviceAddr, (byte)2);
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
	clearInterrupts(a, b);
}

void MCP23017::clearInterrupts(byte& portA, byte& portB)
{
	readRegister(INTCAPA, portA, portB);
}

#endif