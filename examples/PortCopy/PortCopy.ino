/**
 * On every loop, the state of the port B is copied to port A.
 *
 * Use active low inputs on port A. Internal pullups are configured so there is no need for external resistors.
 * Place LEDS on port B for instance. 
 * When pressing a button, the corresponding led is shut down.
 * 
 * You can also uncomment one line to invert the input (when pressing a button the corresponding led is lit)
 */
#include <Wire.h>
#include <MCP23017.h>

#define MCP23017_ADDR 0x20
MCP23017 mcp = MCP23017(MCP23017_ADDR);

void setup() {
    Wire.begin();
    Serial.begin(115200);
    
    mcp.init();
    mcp.portMode(MCP23017_PORT::A, 0);          //Port A as output
    mcp.portMode(MCP23017_PORT::B, 0b11111111); //Port B as input

    mcp.writeRegister(MCP23017_REGISTER::GPIOA, 0x00);  //Reset port A 
    mcp.writeRegister(MCP23017_REGISTER::GPIOB, 0x00);  //Reset port B
    
    mcp.writeRegister(MCP23017_REGISTER::GPPUA, 0x00);  //No pullups on port A
    mcp.writeRegister(MCP23017_REGISTER::GPPUB, 0xFF);  //Pullups on port B    

    // GPIOB reflects the same logic as the input pins state
    mcp.writeRegister(MCP23017_REGISTER::IPOLB, 0x00);
    // Uncomment this line to invert inputs (press a button to lit a led)
    //mcp.writeRegister(MCP23017_REGISTER::IPOLB, 0xFF);
}

void loop() {
    uint8_t currentB;

    currentB = mcp.readPort(MCP23017_PORT::B);
    mcp.writePort(MCP23017_PORT::A, currentB);
}