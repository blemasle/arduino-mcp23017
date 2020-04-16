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

Additionaly, you can specify the `Wire` instance to use as a second argument. For instance `MCP23017(0x24, Wire1)`.  
See included examples for further usage.

## Remarks
Major renames have been performed in v2.0.0 to improve compatibility with a variety of platforms. Existing code *will* break when you update from version v1.x.

| Name in v1.x          | Name in v2.x              |
|-----------------------|---------------------------|
| `MCP23017_PORT`       | `MCP23017Port`            |
| `MCP23017_REGISTER`   | `MCP23017Register`        |
| `MCP23017_INTMODE`    | `MCP23017InterruptMode`   |

In addition to this, every member of the `MCP23017Register` enum were renamed to avoid possible conflicts with macro definitions. `GPIOA` was renamed to `GPIO_A`, `INTCAPA` to `INTCAP_A` and so on...