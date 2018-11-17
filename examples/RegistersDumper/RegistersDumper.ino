#include <Arduino.h>
#include <MCP23017.h>

MCP23017 mcp = MCP23017(0x24);

void setup() {
    Wire.begin();
    mcp.init();

    Serial.begin(115200);
	byte conf = mcp.readRegister(IODIRA);
	Serial.print("IODIRA : ");
	Serial.print(conf, BIN);
	Serial.println();
	
	conf = mcp.readRegister(IODIRB);
	Serial.print("IODIRB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(IPOLA);
	Serial.print("IPOLA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(IPOLB);
	Serial.print("IPOLB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(GPINTENA);
	Serial.print("GPINTENA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(GPINTENB);
	Serial.print("GPINTENB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(DEFVALA);
	Serial.print("DEFVALA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(DEFVALB);
	Serial.print("DEFVALB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(INTCONA);
	Serial.print("INTCONA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(INTCONB);
	Serial.print("INTCONB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(IOCON);
	Serial.print("IOCON : ");
	Serial.print(conf, BIN);
	Serial.println();

	//conf = mcp.readRegister(IOCONB);
	//Serial.print("IOCONB : ");
	//Serial.print(conf, BIN);
	//Serial.println();

	conf = mcp.readRegister(GPPUA);
	Serial.print("GPPUA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(GPPUB);
	Serial.print("GPPUB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(INTFA);
	Serial.print("INTFA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(INTFB);
	Serial.print("INTFB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(INTCAPA);
	Serial.print("INTCAPA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(INTCAPB);
	Serial.print("INTCAPB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(GPIOA);
	Serial.print("GPIOA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(GPIOB);
	Serial.print("GPIOB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(OLATA);
	Serial.print("OLATA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(OLATB);
	Serial.print("OLATB : ");
	Serial.print(conf, BIN);
	Serial.println();
	Serial.end();
}

void loop() {}