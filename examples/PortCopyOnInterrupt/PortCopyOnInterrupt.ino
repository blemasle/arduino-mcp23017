/**
 * When a pin on port B is falling, the same pin on port A is switched.
 * Connect a range of switches to port B and leds on port A to see it happeing.
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
    mcp.portMode(0, 0);         //Port A as ouput
    mcp.portMode(1, 0b11111111);//Port B as input

    mcp.interruptMode(OR);      
    mcp.interrupt(1, FALLING);

    mcp.writeRegister(GPIOA, 0x00);
    mcp.writeRegister(GPIOB, 0x00);

    mcp.clearInterrupts();
    attachInterrupt(1, userInput, FALLING);
}

void loop() {
    byte conf, a, b;
    byte captureA, captureB;
    byte currentA, currentB;

    if(!interrupted) return;

    //debouncing
    delay(100);
    interrupted = false;
    
    mcp.interruptedBy(a, b);
    mcp.clearInterrupts(captureA, captureB);
    currentB = mcp.readPort(1);

    if((b & ~currentB) == (b & ~captureB)) {
        byte currentA = mcp.readPort(0);
        mcp.writeRegister(GPIOA, currentA ^ b);
    }
}