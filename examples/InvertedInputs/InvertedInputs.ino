#include <Arduino.h>
#include <MCP23017.h>

/**
 * Please connect:
 *    A5  => SCL   (ON UNO R3)
 *    A4  => SDA   (ON UNO R3)
 *    A3  => RST   (ON UNO R3)
 *    A0  =>  B0
 *    A1  =>  B1
 *    A2  =>  B2
 *    A3  =>  B3
 *    A4  =>  B4
 *    A5  =>  B5
 *    A6  =>  B6
 *    A7  =>  B7
 */

#define MCP23017_ADDR 0x20
  
MCP23017 mcp = MCP23017(MCP23017_ADDR);

void setup() {
  
    Serial.begin(115200);
    delay(200);
    //Serial.write(27); Serial.print("[2J"); // CLRSCR
    //Serial.write(27); Serial.print("[H");  // HOME

    pinMode( A3, OUTPUT );
    
    digitalWrite( A3, LOW );
    delay(50);
    digitalWrite( A3, HIGH );
    delay(50);
    
    Wire.begin();
    mcp.init();

    bool error = false;
  
	  mcp.portMode( MCP23017_PORT::A, INPUT, 0xFF ); // PORT A is input inverted
	  mcp.portMode( MCP23017_PORT::B, OUTPUT );      // PORT B is output
    mcp.writePort (MCP23017_PORT::B, 0xFF);
  
    Serial.println("##### Checking setting port mode #####\n" );
	  for ( uint8_t i=0; i<8 ; i++ ){
      
    error |= ( mcp.digitalRead(i) != mcp.digitalRead(i+8) );
		if ( mcp.digitalRead(i) != HIGH ){
			Serial.print( "Your connection ");
      Serial.print( i );
			Serial.print(" was wrong, please check it: " );
      Serial.print("IN: " );
      Serial.print( mcp.digitalRead(i) ? "HIGH" : "LOW" );
      Serial.print(", OUT: " );
      Serial.println( mcp.digitalRead(i+8) ? "HIGH" : "LOW" );
		}
	}
	
  if ( error )
  Serial.println("--------- FAILED (see above) ----------");
  else
  Serial.println("------------- SUCCEEDED --------------");
  
  error = false;
    digitalWrite( A3, LOW );
    delay(50);
    digitalWrite( A3, HIGH );
 delay(50);
 
  Serial.println("\n##### Checking setting pin mode #####\n" );
  
	for ( uint8_t i=0; i<16; i++ ){
		if ( i< 8 )
      mcp.pinMode( i, OUTPUT ); // PORT A is output
		else
      mcp.pinMode( i, INPUT, true );  // PORT B is input inverted
	}

   mcp.writePort (MCP23017_PORT::A, 0xFF);
      Serial.print( mcp.readPort(MCP23017_PORT::B) );
  
	for ( uint8_t i=0; i<8 ; i++ ){
    error |= ( mcp.digitalRead(i+8) != mcp.digitalRead(i) );
//    if ( mcp.digitalRead(i+8) == HIGH ){
    if ( true ){
      Serial.print( "Your connection " );
      Serial.print( i );
      Serial.print(" was wrong, please check it: " );
      Serial.print("IN: " );
      Serial.print( mcp.digitalRead(i+8) ? "HIGH" : "LOW" );
      Serial.print(", OUT: " );
      Serial.println( mcp.digitalRead(i) ? "HIGH" : "LOW" );
		}
	}

  if ( error )
  Serial.println("--------- FAILED (see above) ----------");
  else
  Serial.println("------------- SUCCEEDED --------------");

}

void loop() {}
