# MCP23017
[![Build Status](https://travis-ci.org/blemasle/arduino-mcp23017.svg?branch=master)](https://travis-ci.org/blemasle/arduino-mcp23017)
[![License](https://img.shields.io/badge/license-MIT%20License-blue.svg)](http://doge.mit-license.org)

This library provides full control over the Microchip's [MCP23017](https://www.microchip.com/wwwproducts/en/MCP23017), including interrupt support.

## Features
 * Individual pins read & write
 * Ports read & write
 * Registers read & write
 * Full interrupt support

## Usage
Unlike most Arduino library, no default instance is created when the library is included. It's up to you to create one with the appropriate chip I2C address.

```cpp
#include <Arduino.h>
#include <MCP23017.h>

MCP23017 mcp = MCP23017(0x24);
```

See included examples for furher usage.