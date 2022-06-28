#include "MCP23017.h"

MCP23017::MCP23017(uint8_t address, TwoWire& bus) {
	_deviceAddr = address;
	_bus = &bus;
}

MCP23017::MCP23017(TwoWire& bus) {
	_deviceAddr = MCP23017_I2C_ADDRESS;
	_bus = &bus;
}

MCP23017::~MCP23017() {}

bool MCP23017::init()
{
	//BANK = 	0 : sequential register addresses
	//MIRROR = 	0 : use configureInterrupt 
	//SEQOP = 	1 : sequential operation disabled, address pointer does not increment
	//DISSLW = 	0 : slew rate enabled
	//HAEN = 	0 : hardware address pin is always enabled on 23017
	//ODR = 	0 : active driver output (INTPOL bit sets the polarity.)

	//INTPOL = 	0 : interrupt active low
	//UNIMPLMENTED 	0 : unimplemented: Read as ‘0’

	bool retval = writeRegister(MCP23017Register::IOCON, 0b00100000);

	//enable all pull up resistors (will be effective for input pins only)
	retval &= writeRegister(MCP23017Register::GPPU_A, 0xFF, 0xFF);

	return retval;
}

bool MCP23017::begin()
{
	return init();
}

bool MCP23017::begin(uint8_t address)
{
	_deviceAddr = address;
	return begin();
}

bool MCP23017::portMode(MCP23017Port port, uint8_t directions, uint8_t pullups, uint8_t inverted)
{
	bool retVal = writeRegister(MCP23017Register::IODIR_A + port, directions);
	retVal &= writeRegister(MCP23017Register::GPPU_A + port, pullups);
	retVal &= writeRegister(MCP23017Register::IPOL_A + port, inverted);
	return retVal;
}

bool MCP23017::pinMode(uint8_t pin, uint8_t mode, bool inverted)
{
	MCP23017Register iodirreg = MCP23017Register::IODIR_A;
	MCP23017Register pullupreg = MCP23017Register::GPPU_A;
	MCP23017Register polreg = MCP23017Register::IPOL_A;
	uint8_t iodir, pol, pull;

	if(pin > 7)
	{
		iodirreg = MCP23017Register::IODIR_B;
		pullupreg = MCP23017Register::GPPU_B;
		polreg = MCP23017Register::IPOL_B;
		pin -= 8;
	}

	iodir = readRegister(iodirreg);
	if(mode == INPUT || mode == INPUT_PULLUP) bitSet(iodir, pin);
	else bitClear(iodir, pin);

	pull = readRegister(pullupreg);
	if(mode == INPUT_PULLUP) bitSet(pull, pin);
	else bitClear(pull, pin);

	pol = readRegister(polreg);
	if(inverted) bitSet(pol, pin);
	else bitClear(pol, pin);

	bool retVal = writeRegister(iodirreg, iodir);
	retVal &= writeRegister(pullupreg, pull);
	retVal &= writeRegister(polreg, pol);
	return retVal;
}

bool MCP23017::digitalWrite(uint8_t pin, uint8_t state)
{
	MCP23017Register gpioreg = MCP23017Register::GPIO_A;
	uint8_t gpio;
	if(pin > 7)
	{
		gpioreg = MCP23017Register::GPIO_B;
		pin -= 8;
	}

	gpio = readRegister(gpioreg);
	if(state == HIGH) bitSet(gpio, pin);
	else bitClear(gpio, pin);

	return writeRegister(gpioreg, gpio);
}

uint8_t MCP23017::digitalRead(uint8_t pin)
{
	MCP23017Register gpioreg = MCP23017Register::GPIO_A;
	uint8_t gpio;
	if(pin > 7)
	{
		gpioreg = MCP23017Register::GPIO_B;
		pin -=8;
	}

	gpio = readRegister(gpioreg);
	if(bitRead(gpio, pin)) return HIGH;
	return LOW;
}

bool MCP23017::writePort(MCP23017Port port, uint8_t value)
{
	return writeRegister(MCP23017Register::GPIO_A + port, value);
}

bool MCP23017::write(uint16_t value)
{
	return writeRegister(MCP23017Register::GPIO_A, lowByte(value), highByte(value));
}

uint8_t MCP23017::readPort(MCP23017Port port)
{
	return readRegister(MCP23017Register::GPIO_A + port);
}

uint16_t MCP23017::read()
{
	uint8_t a = readPort(MCP23017Port::A);
	uint8_t b = readPort(MCP23017Port::B);

	return a | b << 8;
}

bool MCP23017::writeRegister(MCP23017Register reg, uint8_t value)
{
	_bus->beginTransmission(_deviceAddr);
	_bus->write(static_cast<uint8_t>(reg));
	_bus->write(value);
	uint8_t retval = _bus->endTransmission();
	return !retval;
}

bool MCP23017::writeRegister(MCP23017Register reg, uint8_t portA, uint8_t portB)
{
	_bus->beginTransmission(_deviceAddr);
	_bus->write(static_cast<uint8_t>(reg));
	_bus->write(portA);
	_bus->write(portB);
	uint8_t retval = _bus->endTransmission();
	return !retval;
}


uint8_t MCP23017::readRegister(MCP23017Register reg)
{
	_bus->beginTransmission(_deviceAddr);
	_bus->write(static_cast<uint8_t>(reg));
	uint8_t retval = _bus->endTransmission();
	retval &= _bus->requestFrom(_deviceAddr, (uint8_t)1);
	return _bus->read();
}

bool MCP23017::readRegister(MCP23017Register reg, uint8_t& portA, uint8_t& portB)
{
	_bus->beginTransmission(_deviceAddr);
	_bus->write(static_cast<uint8_t>(reg));
	uint8_t retval = _bus->endTransmission();
	retval &= _bus->requestFrom(_deviceAddr, (uint8_t)2);
	portA = _bus->read();
	portB = _bus->read();
	return !retval;
}

#ifdef _MCP23017_INTERRUPT_SUPPORT_

bool MCP23017::interruptMode(MCP23017InterruptMode intMode)
{
	uint8_t iocon = readRegister(MCP23017Register::IOCON);
	if(intMode == MCP23017InterruptMode::Or) iocon |= static_cast<uint8_t>(MCP23017InterruptMode::Or);
	else iocon &= ~(static_cast<uint8_t>(MCP23017InterruptMode::Or));

	return writeRegister(MCP23017Register::IOCON, iocon);
}

bool MCP23017::interrupt(MCP23017Port port, uint8_t mode)
{
	MCP23017Register defvalreg = MCP23017Register::DEFVAL_A + port;
	MCP23017Register intconreg = MCP23017Register::INTCON_A + port;

	//enable interrupt for port
	bool retVal = writeRegister(MCP23017Register::GPINTEN_A + port, 0xFF);
	switch(mode)
	{
	case CHANGE:
		//interrupt on change
		retVal &= writeRegister(intconreg, 0);
		break;
	case FALLING:
		//interrupt falling : compared against defval, 0xff
		retVal &= writeRegister(intconreg, 0xFF);
		retVal &= writeRegister(defvalreg, 0xFF);
		break;
	case RISING:
		//interrupt rising : compared against defval, 0x00
		retVal &= writeRegister(intconreg, 0xFF);
		retVal &= writeRegister(defvalreg, 0x00);
		break;
	}
	return retVal;
}

bool MCP23017::interruptedBy(uint8_t& portA, uint8_t& portB)
{
	return readRegister(MCP23017Register::INTF_A, portA, portB);
}

bool MCP23017::disableInterrupt(MCP23017Port port)
{
	return writeRegister(MCP23017Register::GPINTEN_A + port, 0x00);
}

bool MCP23017::clearInterrupts()
{
	uint8_t a, b;
	return clearInterrupts(a, b);
}

bool MCP23017::clearInterrupts(uint8_t& portA, uint8_t& portB)
{
	return readRegister(MCP23017Register::INTCAP_A, portA, portB);
}

#endif
