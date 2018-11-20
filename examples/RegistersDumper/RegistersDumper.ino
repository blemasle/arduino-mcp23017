#include <Arduino.h>
#include <MCP23017.h>

MCP23017 mcp = MCP23017(0x24);

void setup() {
    Wire.begin();
    mcp.init();

    Serial.begin(115200);
	uint8_t conf = mcp.readRegister(MCP23017_REGISTER::IODIRA);
	Serial.print("IODIRA : ");
	Serial.print(conf, BIN);
	Serial.println();
	
	conf = mcp.readRegister(MCP23017_REGISTER::IODIRB);
	Serial.print("IODIRB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(MCP23017_REGISTER::IPOLA);
	Serial.print("IPOLA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(MCP23017_REGISTER::IPOLB);
	Serial.print("IPOLB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(MCP23017_REGISTER::GPINTENA);
	Serial.print("GPINTENA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(MCP23017_REGISTER::GPINTENB);
	Serial.print("GPINTENB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(MCP23017_REGISTER::DEFVALA);
	Serial.print("DEFVALA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(MCP23017_REGISTER::DEFVALB);
	Serial.print("DEFVALB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(MCP23017_REGISTER::INTCONA);
	Serial.print("INTCONA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(MCP23017_REGISTER::INTCONB);
	Serial.print("INTCONB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(MCP23017_REGISTER::IOCON);
	Serial.print("IOCON : ");
	Serial.print(conf, BIN);
	Serial.println();

	//conf = mcp.readRegister(IOCONB);
	//Serial.print("IOCONB : ");
	//Serial.print(conf, BIN);
	//Serial.println();

	conf = mcp.readRegister(MCP23017_REGISTER::GPPUA);
	Serial.print("GPPUA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(MCP23017_REGISTER::GPPUB);
	Serial.print("GPPUB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(MCP23017_REGISTER::INTFA);
	Serial.print("INTFA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(MCP23017_REGISTER::INTFB);
	Serial.print("INTFB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(MCP23017_REGISTER::INTCAPA);
	Serial.print("INTCAPA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(MCP23017_REGISTER::INTCAPB);
	Serial.print("INTCAPB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(MCP23017_REGISTER::GPIOA);
	Serial.print("GPIOA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(MCP23017_REGISTER::GPIOB);
	Serial.print("GPIOB : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(MCP23017_REGISTER::OLATA);
	Serial.print("OLATA : ");
	Serial.print(conf, BIN);
	Serial.println();

	conf = mcp.readRegister(MCP23017_REGISTER::OLATB);
	Serial.print("OLATB : ");
	Serial.print(conf, BIN);
	Serial.println();
	Serial.end();
}

void loop() {}