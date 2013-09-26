#include <Wire.h>
#include <MCP23017.h>


#define MCP23017_ADDR 0x20
MCP23017 _mcp = MCP23017(MCP23017_ADDR);

short _oldinput;

volatile bool interrupted = true;
unsigned long m;

void userInput()
{
	interrupted = true;
}

void setup()
{
	Wire.begin();
	Serial.begin(115200);
	_mcp.init();

	//port A => output, portB => input
	_mcp.pinMode(0b00000000, 0b11111111);
	//interrupt on portB on both pin, defValue = HIGH
	_mcp.interruptMode(OR);
	_mcp.interrupt(1, FALLING);

	byte conf = _mcp.readRegister(IODIRA);
	Serial.print("IODIRA : ");
	Serial.print(conf, BIN);
	Serial.println();
	
	conf = _mcp.readRegister(IODIRB);
	Serial.print("IODIRB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = _mcp.readRegister(IPOLA);
	Serial.print("IPOLA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = _mcp.readRegister(IPOLB);
	Serial.print("IPOLB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = _mcp.readRegister(GPINTENA);
	Serial.print("GPINTENA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = _mcp.readRegister(GPINTENB);
	Serial.print("GPINTENB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = _mcp.readRegister(DEFVALA);
	Serial.print("DEFVALA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = _mcp.readRegister(DEFVALB);
	Serial.print("DEFVALB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = _mcp.readRegister(INTCONA);
	Serial.print("INTCONA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = _mcp.readRegister(INTCONB);
	Serial.print("INTCONB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = _mcp.readRegister(IOCON);
	Serial.print("IOCON : ");
	Serial.print(conf, BIN);
	Serial.println();

	//conf = _mcp.readRegister(IOCONB);
	//Serial.print("IOCONB : ");
	//Serial.print(conf, BIN);
	//Serial.println();

	conf = _mcp.readRegister(GPPUA);
	Serial.print("GPPUA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = _mcp.readRegister(GPPUB);
	Serial.print("GPPUB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = _mcp.readRegister(INTFA);
	Serial.print("INTFA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = _mcp.readRegister(INTFB);
	Serial.print("INTFB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = _mcp.readRegister(INTCAPA);
	Serial.print("INTCAPA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = _mcp.readRegister(INTCAPB);
	Serial.print("INTCAPB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = _mcp.readRegister(GPIOA);
	Serial.print("GPIOA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = _mcp.readRegister(GPIOB);
	Serial.print("GPIOB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = _mcp.readRegister(OLATA);
	Serial.print("OLATA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = _mcp.readRegister(OLATB);
	Serial.print("OLATB : ");
	Serial.print(conf, BIN);
	Serial.println();

	//ligthDemo();
//	attachInterrupt(0, userInput2, RISING);
	_mcp.clearInterrupts();
	attachInterrupt(1, userInput, FALLING);
}

void ligthDemo() {
	for(byte j = 0; j < 3; j++) 
	{
		for(byte i = 0; i < 8; i++)
		{
			delay(100);
			_mcp.digitalWrite(i, HIGH);
		}

		for(byte i = 0; i < 8; i++)
		{
			delay(100);
			_mcp.digitalWrite(i, LOW);
		}
	}
}

void loop()
{
	byte conf, a, b;
	if(interrupted)
	{
		//debouncing
		delay(100);
		interrupted = false;
		Serial.print("interrupt");
		_mcp.interruptedBy(a, b);
		byte captureA, captureB;
		byte currentB;
		_mcp.clearInterrupts(captureA, captureB);
		currentB = _mcp.readPort(1);

		if((b & ~currentB) == (b & ~captureB))
		{
			byte gpioa = _mcp.readPort(0);
			_mcp.writeRegister(GPIOA, gpioa ^ b);
		}
	}

	if(millis() - m > 1000)
	{
		/*m = millis();
		conf = _mcp.readRegister(INTFA);
		Serial.print("INTFA : ");
		Serial.print(conf, BIN);
		Serial.println();

		conf = _mcp.readRegister(INTFB);
		Serial.print("INTFB : ");
		Serial.print(conf, BIN);
		Serial.println();

		conf = _mcp.readRegister(INTCAPA);
		Serial.print("INTCAPA : ");
		Serial.print(conf, BIN);
		Serial.println();

		conf = _mcp.readRegister(INTCAPB);
		Serial.print("INTCAPB : ");
		Serial.print(conf, BIN);
		Serial.println();*/
	}
	//Serial.print("Interrupted : ");
	//Serial.print("a : ");
	//Serial.print(a, BIN);
	//Serial.print(", b : ");
	//Serial.print(b, BIN);
	//Serial.println();
	
	//int value = digitalRead(3);
	//Serial.print("int : ");
	//Serial.println(value);
	//delay(1000);
	//byte a;
	//byte b;
	//_mcp.read(&a, &b);
	//Serial.print("a : ");
	//Serial.print(a, BIN);
	//Serial.print(", b : ");
	//Serial.print(b, BIN);
	//Serial.println();

	//byte conf = _mcp.readRegister(GPIOA);
	//Serial.print("GPIOA : ");
	//Serial.print(conf, BIN);
	//Serial.println();

	//conf = _mcp.readRegister(GPIOB);
	//Serial.print("GPIOB : ");
	//Serial.print(conf, BIN);
	//Serial.println();

	//byte bttnValue = _mcp.digitalRead(9);
	//Serial.print("pin 9 : ");
	//Serial.print(bttnValue, BIN);
	//Serial.println();

	//short input = _mcp.read();
	//if(_oldinput != input)
	//{
	//	_oldinput = input;

	//	//copy gpio input to gpio output port
	//	_mcp.write((input >> 8) & 0xFF, (input >> 8) & 0xFF);
	//}
}
