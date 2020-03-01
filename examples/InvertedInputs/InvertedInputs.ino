#include <Arduino.h>

#define MCP23017_INTERRUPT_SUPPORT 1
#include <MCP23017.h>

/**
 * This sketch demonstrates the pin capabilities in pin- and portmode. 
 * Each of the 16 bits can eigher  be an input which is inverted or not 
 * or having a 100k pullup resistor in same mode or just beeing an output.
 * 
 * Some Interrupt capabilites are also shown
 * 
 * Please connect:
 *    A5   => SCL   (ON UNO R3)
 *    A4   => SDA   (ON UNO R3)
 *    A3   => RST   (ON UNO R3)
 *    INTA =>  D2   (ON UNO R3)
 *    INTB =>  D3   (ON UNO R3)
 *    A0   =>  B0
 *    A1   =>  B1
 *    A2   =>  B2
 *    A3   =>  B3
 *    A4   =>  B4
 *    A5   =>  B5
 *    A6   =>  B6
 *    A7   =>  B7
 */

#define MCP23017_ADDR 0x20

MCP23017 mcp = MCP23017(MCP23017_ADDR);

void int_pinA(){
  Serial.println("\n#####   INTERRUPT PORT A FIRED   #####\n");
}

void int_pinB(){
  Serial.println("\n#####   INTERRUPT PORT B FIRED   #####\n");
}

void setup()
{
  Serial.begin(115200);
  delay(200);
  // Serial.write(27); Serial.print("[2J"); // CLRSCR
  // Serial.write(27); Serial.print("[H");  // HOME

  // reset pin
  pinMode(A3, OUTPUT);
  digitalWrite(A3, LOW);
  delay(50);
  digitalWrite(A3, HIGH);
  delay(50);

  // interrupt pins
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(2), int_pinA, RISING);
  attachInterrupt(digitalPinToInterrupt(3), int_pinB, RISING);

  Wire.begin();
  mcp.begin(0x00, 0x00);
  mcp.interruptMode(MCP23017_INTMODE::SEPARATED);
  mcp.interrupt(MCP23017_PORT::A, CHANGE);
  mcp.interrupt(MCP23017_PORT::B, CHANGE);

  bool error = false;

  // PORT A is input inverted with pullups
  mcp.portMode( MCP23017_PORT::A, INPUT, 0xFF, 0xFF); 
  mcp.clearInterrupts();

  // PORT B is output
  mcp.portMode(MCP23017_PORT::B, OUTPUT);

  // Set all output pins to HIGH
  mcp.writePort(MCP23017_PORT::B, 0xFF);

  Serial.println("##### Checking setting port mode #####\n");
  for (uint8_t i = 0; i < 8; i++)
  {

    error |= (mcp.digitalRead(i) != mcp.digitalRead(i + 8));
    if (error)
    {
      Serial.print("Your connection ");
      Serial.print(i);
      Serial.print(" was wrong, please check it: ");
      Serial.print("IN: ");
      Serial.print(mcp.digitalRead(i) ? "HIGH" : "LOW");
      Serial.print(", OUT: ");
      Serial.println(mcp.digitalRead(i + 8) ? "HIGH" : "LOW");
    }
  }

  if (error)
    Serial.println("--------- FAILED (see above) ----------");
  else
    Serial.println("------------- SUCCEEDED --------------");

  error = false;
  mcp.clearInterrupts();

  Serial.println("\n##### Checking setting pin mode #####\n");

  for (uint8_t i = 0; i < 16; i++)
  {
    if (i < 8)
    {
      // PORT A is output for now
      mcp.pinMode(i, OUTPUT); 
    }
    else
    {
      // PORT B is input for now, inverted inputs with pullups
      mcp.pinMode(i, INPUT_PULLUP, true);
    }
  }

  // Set all output pins to HIGH
  mcp.writePort(MCP23017_PORT::A, 0xFF);  

  for (uint8_t i = 0; i < 8; i++)
  {
    error |= (mcp.digitalRead(i) != mcp.digitalRead(i + 8));
    if (error)
    {
      Serial.print("Your connection ");
      Serial.print(i);
      Serial.print(" was wrong, please check it: ");
      Serial.print("IN: ");
      Serial.print(mcp.digitalRead(i + 8) ? "HIGH" : "LOW");
      Serial.print(", OUT: ");
      Serial.println(mcp.digitalRead(i) ? "HIGH" : "LOW");
    }
  }

  if (error)
    Serial.println("--------- FAILED (see above) ----------");
  else
    Serial.println("------------- SUCCEEDED --------------");
}

void loop() {}
