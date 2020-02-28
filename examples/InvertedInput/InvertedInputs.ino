#include <Arduino.h>
#include <MCP23017.h>

/**
 * Please connect:
 * 
 *    A0  =>  B0
 *    A1  =>  B1
 *    A2  =>  B2
 *    A3  =>  B3
 *    A4  =>  B4
 *    A5  =>  B5
 *    A6  =>  B6
 *    A7  =>  B7
 */
  
MCP23017 mcp = MCP23017();

void setup() {
    Wire.begin();
    mcp.init();

    Serial.begin(115200);

	// All pins on Port A are inverted inputs
	mp.portMode( MCP23017_PORT::A, INPUT, 0b11111111 );
	mp.portMode( MCP23017_PORT::B, OUTPUT );

	for ( int i=8; i<16 ;i++ ){
		mp.digitalWrite( i, HIGH );
		if ( mp.digitalRead(i) == mp.digitalRead(i-8) ){
			Serial.writeln( "Your connections are wrong, please check for it." );
		}
	}

	for ( int i=0; i<16; i++ ){

		if ( i< 8 )
			mp.pinMode( i, INPUT, true );
		else
			mp.pinMode( i, OUTPUT );
	}

	for ( int i=0; i<8 ;i++ ){
		mp.digitalWrite( i, HIGH );
		if ( mp.digitalRead(i) == mp.digitalRead(i+8) ){
			Serial.writeln( "Your connections are wrong, please check for it." );
		}
	}

}

void loop() {}