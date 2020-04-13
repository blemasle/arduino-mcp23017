/**
 * When a pin on port B is falling, the same pin on port A is switched.
 * Connect a range of switches to port B and leds on port A to see it happening.
 */
#include <Wire.h>
#include <MCP23017.h>

#define MCP23017_ADDR 0x20
MCP23017 mcp = MCP23017(MCP23017_ADDR);

volatile bool interrupted = false;

void userInput() {
    interrupted = true;
}

void setup() {
    Wire.begin();
    Serial.begin(115200);
    
    mcp.init();
    mcp.portMode(MCP23017_PORT::A, 0);          //Port A as output
    mcp.portMode(MCP23017_PORT::B, 0b11111111); //Port B as input

    mcp.interruptMode(MCP23017_INTMODE::SEPARATED);      
    mcp.interrupt(MCP23017_PORT::B, FALLING);

    mcp.writeRegister(MCP23017_REGISTER::GPIOA, 0x00);
    mcp.writeRegister(MCP23017_REGISTER::GPIOB, 0x00);

    mcp.clearInterrupts();
    attachInterrupt(1, userInput, FALLING);
}

void loop() {
    uint8_t conf, a, b;
    uint8_t captureA, captureB;
    uint8_t currentA, currentB;

    if(!interrupted) 
    {
        // just to be sure that arduino and mcp are in the "same state"
        // regarding interrupts
        mcp.clearInterrupts();
        return;
    }

    //debouncing
    delay(100);
    interrupted = false;
    
    mcp.interruptedBy(a, b);
    mcp.clearInterrupts(captureA, captureB);
    currentB = mcp.readPort(MCP23017_PORT::B);

    if((b & ~currentB) == (b & ~captureB)) {
        uint8_t currentA = mcp.readPort(MCP23017_PORT::A);
        mcp.writeRegister(MCP23017_REGISTER::GPIOA, currentA ^ b);
    }
}