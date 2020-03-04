<div id="top">

<div id="titlearea">

<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr class="odd">
<td><div id="projectname">

</div>
<div id="projectbrief">
MCP23017 16-Bit I/O Expander with Serial Interface
</div></td>
</tr>
</tbody>
</table>

</div>

<div id="main-nav">

</div>

<div id="MSearchSelectWindow" onmouseover="return searchBox.OnSearchSelectShow()" onmouseout="return searchBox.OnSearchSelectHide()" onkeydown="return searchBox.OnSearchSelectKey(event)">

</div>

<div id="MSearchResultsWindow">

</div>

</div>

<div class="header">

</div>

</div>

<div class="contents">

## <span id="pub-methods"></span> Public Member Functions

</div>

#### [MCP23017](#mcp23017) (uint8\_t address, TwoWire \&bus=Wire)
#### void [init](#init)()
#### void [begin](#BEGIN)(uint8\_t pullup\_a=0x00, uint8\_t pullup\_b=0x00)
#### void [portMode](#400)(MCP23017\_PORT port, uint8\_t modes, uint8\_t pullups=0xff, uint8\_t inverteds=0x00)
#### void [pinMode](#500)(uint8\_t pin, uint8\_t mode, bool inverted=false)
#### void [digitalWrite](#600)(uint8\_t pin, uint8\_t state)
#### uint8\_t [digitalRead](#700)(uint8\_t pin)
#### void [writePort](#800)(MCP23017\_PORT port, uint8\_t values)
#### void [write](#900)(uint16\_t values)
#### uint8\_t [readPort](#1000)(MCP23017\_PORT port)
#### uint16\_t [read](#1100)()
#### void [writeRegister](#1200)(MCP23017\_REGISTER reg, uint8\_t value)
#### void [writeRegister](#1300)(MCP23017\_REGISTER reg, uint8\_t portA, uint8\_t portB)
#### uint8\_t [readRegister](#1400)(MCP23017\_REGISTER reg)
#### void [readRegister](#1500)(MCP23017\_REGISTER reg, uint8\_t \&portA, uint8\_t \&portB)
#### void [interruptMode](#1600)(MCP23017\_INTMODE intMode)
#### void [interrupt](#1700)(MCP23017\_PORT port, uint8\_t mode)
#### void [disableInterrupt](#1800)(MCP23017\_PORT port)
#### void [interruptedBy](#1900)(uint8\_t \&portA, uint8\_t \&portB)
#### void [clearInterrupts](#2000)()
#### void [clearInterrupts](#2100)(uint8\_t \&portA, uint8\_t \&portB)

## Constructor & Destructor Documentation

## <span class="permalink">[◆ ](#TOC)</span>MCP23017()

<div class="memitem">

<div class="memproto">

|                    |   |           |                |
| ------------------ | - | --------- | -------------- |
| MCP23017::MCP23017 | ( | uint8\_t  | *address*,     |
|                    |   | TwoWire & | *bus* = `Wire` |
|                    | ) |           |                |

</div>

<div class="memdoc">

Instantiates a new instance to interact with a MCP23017 at the specified
address.

  - Parameters
    
    |         |                                        |
    | ------- | -------------------------------------- |
    | address | bus address of MCP23017 (0x20 \~ 0x27) |
    | bus     | refence to i2c bus object              |
    

</div>

</div>

## Member Function Documentation

## <span class="permalink">[◆ ](#TOC)</span>begin()

<div class="memitem">

<div class="memproto">

|                      |   |          |                       |
| -------------------- | - | -------- | --------------------- |
| void MCP23017::begin | ( | uint8\_t | *pullup\_a* = `0x00`, |
|                      |   | uint8\_t | *pullup\_b* = `0x00`  |
|                      | ) |          |                       |

</div>

<div class="memdoc">

Initializes the chip with the default configuration. Enables Byte mode
(IOCON.BANK = 0 and IOCON.SEQOP = 1). Enables pull-up resistors for all
pins by default. This will only be effective for input pins.

  - Note  
    See: "3.2.1 Byte mode and Sequential mode"

<!-- end list -->

  - Parameters
    
    |           |                                                               |
    | --------- | ------------------------------------------------------------- |
    | pullup\_a | bitmask for port A                                            |
    | pullup\_b | bitmask for port B See "3.2.1 Byte mode and Sequential mode". |
    

</div>

</div>

<span id="a47e31859ed3fdd709d60dee11239042f"></span>

## <span class="permalink">[◆ ](#TOC)</span>clearInterrupts() <span class="overload">\[1/2\]</span>

<div class="memitem">

<div class="memdoc">

Clears interrupts on both ports.

  - Note  
    See: "3.5.9 INTERRUPT CAPTURED REGISTER"

</div>

</div>

<span id="aed02c9fef408d86f1369254e17cd6c2b"></span>

## <span class="permalink">[◆ ](#TOC)</span>clearInterrupts() <span class="overload">\[2/2\]</span>

<div class="memitem">

<div class="memproto">

|                                |   |            |          |
| ------------------------------ | - | ---------- | -------- |
| void MCP23017::clearInterrupts | ( | uint8\_t & | *portA*, |
|                                |   | uint8\_t & | *portB*  |
|                                | ) |            |          |

</div>

<div class="memdoc">

Clear interrupts on both ports. Returns port values at the time the
interrupt occured.

  - Note  
    See: "3.5.9 INTERRUPT CAPTURED REGISTER"

<!-- end list -->

  - Parameters
    
    |       |                                                           |
    | ----- | --------------------------------------------------------- |
    | portA | reference to port A value; returns the value by reference |
    | portB | reference to port B value; returns the value by reference |
    

</div>

</div>

<span id="a47eb64469c2dc6d1b9e0ba7637f0bebd"></span>

## <span class="permalink">[◆ ](#TOC)</span>digitalRead()

<div class="memitem">

<div class="memdoc">

Reads a single pin state.

  - Note  
    See: "3.5.10 Port register"

<!-- end list -->

  - Parameters
    
    |        |                                                                  |
    | ------ | ---------------------------------------------------------------- |
    | pin    | Pin 0-7 for port A, 8-15 for port B.                             |
    | return | HIGH or 0x01, LOW or 0x00 depending the hardwarestate of the pin |
    

</div>

</div>

<span id="a148aa7b0464c6bee4d50ab591636605b"></span>

## <span class="permalink">[◆ ](#TOC)</span>digitalWrite()

<div class="memitem">

<div class="memproto">

|                             |   |          |         |
| --------------------------- | - | -------- | ------- |
| void MCP23017::digitalWrite | ( | uint8\_t | *pin*,  |
|                             |   | uint8\_t | *state* |
|                             | ) |          |         |

</div>

<div class="memdoc">

Writes a single pin state.

  - Note  
    See: "3.5.10 Port register"

<!-- end list -->

  - Parameters
    
    |       |                                      |
    | ----- | ------------------------------------ |
    | pin   | Pin 0-7 for port A, 8-15 for port B. |
    | state | HIGH or 0x01 LOW or 0x00             |
    

</div>

</div>

<span id="af8b8a5ee7578effe78be5cfc4c31319b"></span>

## <span class="permalink">[◆ ](#TOC)</span>disableInterrupt()

<div class="memitem">

<div class="memproto">

|                                 |   |                |        |   |
| ------------------------------- | - | -------------- | ------ | - |
| void MCP23017::disableInterrupt | ( | MCP23017\_PORT | *port* | ) |

</div>

<div class="memdoc">

Disables interrupts for the specified port.

  - Note  
    See: "3.5.3 INTERRUPT-ON-CHANGE CONTROL REGISTER"

<!-- end list -->

  - Parameters
    
    |      |                      |
    | ---- | -------------------- |
    | port | MCP23017 port A or B |
    

</div>

</div>

<span id="adb0e51e254e2af89455a155f313e8ce8"></span>

## <span class="permalink">[◆ ](#TOC)</span>interrupt()

<div class="memitem">

<div class="memproto">

|                          |   |                |         |
| ------------------------ | - | -------------- | ------- |
| void MCP23017::interrupt | ( | MCP23017\_PORT | *port*, |
|                          |   | uint8\_t       | *mode*  |
|                          | ) |                |         |

</div>

<div class="memdoc">

Configures interrupt registers using an Arduino-like API-mode .

  - Note  
    See: "3.5.3 INTERRUPT-ON-CHANGE CONTROL REGISTER"

<!-- end list -->

  - Parameters
    
    |      |                                         |
    | ---- | --------------------------------------- |
    | port | MCP23017 port A or B                    |
    | mode | Can be one of CHANGE, FALLING or RISING |
    

</div>

</div>

<span id="a821758bb3e5197e817ad43b61c898a92"></span>

## <span class="permalink">[◆ ](#TOC)</span>interruptedBy()

<div class="memitem">

<div class="memproto">

|                              |   |            |          |
| ---------------------------- | - | ---------- | -------- |
| void MCP23017::interruptedBy | ( | uint8\_t & | *portA*, |
|                              |   | uint8\_t & | *portB*  |
|                              | ) |            |          |

</div>

<div class="memdoc">

Reads which pin caused the interrupt.

  - Note  
    See: "3.5.9 GPINTEN: INTERRUPT CAPTURED REGISTER"

<!-- end list -->

  - Parameters
    
    |       |                                                           |
    | ----- | --------------------------------------------------------- |
    | portA | reference to port A value; returns the value by reference |
    | portB | reference to port B value; returns the value by reference |
    

</div>

</div>

<span id="a70f416b065a40b31f0a132fd8311d482"></span>

## <span class="permalink">[◆ ](#TOC)</span>interruptMode()

<div class="memitem">

<div class="memproto">

|                              |   |                   |           |   |
| ---------------------------- | - | ----------------- | --------- | - |
| void MCP23017::interruptMode | ( | MCP23017\_INTMODE | *intMode* | ) |

</div>

<div class="memdoc">

Controls how the interrupt pins act with each other. If intMode is
SEPARATED, interrupt conditions on a port will cause its respective INT
pin to active. If intMode is OR, interrupt pins are OR'ed so an
interrupt on one of the port will cause both pints to active.

  - Note  
    See: "3.5.6 I/O EXPANDER CONFIGURATION REGISTER"

<!-- end list -->

  - Parameters
    
    |         |                                                                                                                                                           |
    | ------- | --------------------------------------------------------------------------------------------------------------------------------------------------------- |
    | intMode | When OR, the INTn pins are functionally OR’ed so that an interrupt on either port will cause both pins to activate. Otherwise use SEPARATED as parameter. |
    

</div>

</div>

<span id="a42e5f4aafc0e7378a74b54d95285fa05"></span>

## <span class="permalink">[◆ ](#TOC)</span>pinMode()

<div class="memitem">

<div class="memproto">

|                        |   |          |                      |
| ---------------------- | - | -------- | -------------------- |
| void MCP23017::pinMode | ( | uint8\_t | *pin*,               |
|                        |   | uint8\_t | *mode*,              |
|                        |   | bool     | *inverted* = `false` |
|                        | ) |          |                      |

</div>

<div class="memdoc">

Sets a single pins' direction. When the pin is an input pin a pullup
and/or an inverted option can be specified.

  - Note  
    See: "3.5.1 I/O IODIR I/O DIRECTION REGISTER", "3.5.2 INPUT POLARITY REGISTER", "3.5.7 PULL-UP RESISTOR CONFIGURATION REGISTER"

<!-- end list -->

  - Parameters
    
    |      |                                                                      |
    | ---- | -------------------------------------------------------------------- |
    | pin  | Controls a single pin direction. Pin 0-7 for port A, 8-15 fo port B. |
    | mode | INPUT or 0x00 INPUT\_PULLUP or 0x02 OUTPUT or 0x01                   |
    

</div>

</div>

<span id="a3da348d5702bb69c3e79f8fc67331f58"></span>

## <span class="permalink">[◆ ](#TOC)</span>portMode()

<div class="memitem">

<div class="memproto">

|                         |   |                |                      |
| ----------------------- | - | -------------- | -------------------- |
| void MCP23017::portMode | ( | MCP23017\_PORT | *port*,              |
|                         |   | uint8\_t       | *modes*,             |
|                         |   | uint8\_t       | *pullups* = `0xff`,  |
|                         |   | uint8\_t       | *inverteds* = `0x00` |
|                         | ) |                |                      |

</div>

<div class="memdoc">

Controls the pins direction on a whole port at once.

  - Note  
    See: "3.5.1 I/O IODIR I/O DIRECTION REGISTER", "3.5.2 INPUT POLARITY REGISTER", "3.5.7 PULL-UP RESISTOR CONFIGURATION REGISTER

<!-- end list -->

  - Parameters
    
    |           |                                                    |
    | --------- | -------------------------------------------------- |
    | port      | MCP23017 port A or B                               |
    | modes     | direction of whole port INPUT or 0x0 OUTPUT or0x01 |
    | pullup    | bitmask for internal 100k pullup resistors         |
    | inverteds | bitmask for inverted mode                          |
    

</div>

</div>

<span id="ad9b2aa218f2eaf8e6499433bb3d6434b"></span>

## <span class="permalink">[◆ ](#TOC)</span>read()

<div class="memitem">

<div class="memdoc">

Reads pins state for both ports.

  - Note  
    See: "3.5.10 Port register"

<!-- end list -->

  - Parameters
    
    |        |                                                                  |
    | ------ | ---------------------------------------------------------------- |
    | return | HIGH or 0x01, LOW or 0x00 depending the hardwarestate of the pin |
    

</div>

</div>

<span id="a9defbd5c7ae971480f2a8b78b4f74586"></span>

## <span class="permalink">[◆ ](#TOC)</span>readPort()

<div class="memitem">

<div class="memproto">

|                             |   |                |        |   |
| --------------------------- | - | -------------- | ------ | - |
| uint8\_t MCP23017::readPort | ( | MCP23017\_PORT | *port* | ) |

</div>

<div class="memdoc">

Reads pins state for a whole port.

  - Note  
    See: "3.5.10 Port register"

<!-- end list -->

  - Parameters
    
    |        |                                                                  |
    | ------ | ---------------------------------------------------------------- |
    | port   | MCP23017 port A or B                                             |
    | return | HIGH or 0x01, LOW or 0x00 depending the hardwarestate of the pin |
    

</div>

</div>

<span id="a6df25b3bd2488aeacd972f5afc5bf2b5"></span>

## <span class="permalink">[◆ ](#TOC)</span>readRegister() <span class="overload">\[1/2\]</span>

<div class="memitem">

<div class="memproto">

|                                 |   |                    |       |   |
| ------------------------------- | - | ------------------ | ----- | - |
| uint8\_t MCP23017::readRegister | ( | MCP23017\_REGISTER | *reg* | ) |

</div>

<div class="memdoc">

Reads a single registers value.

  - Parameters
    
    |     |                                                          |
    | --- | -------------------------------------------------------- |
    | reg | register to read port A: 0x00 \~ 0A0 port B: 0x10 \~ 1A0 |
    

</div>

</div>

<span id="ab6a8df6d72dd496d857ebce4ec2fe541"></span>

## <span class="permalink">[◆ ](#TOC)</span>readRegister() <span class="overload">\[2/2\]</span>

<div class="memitem">

<div class="memproto">

|                             |   |                    |          |
| --------------------------- | - | ------------------ | -------- |
| void MCP23017::readRegister | ( | MCP23017\_REGISTER | *reg*,   |
|                             |   | uint8\_t &         | *portA*, |
|                             |   | uint8\_t &         | *portB*  |
|                             | ) |                    |          |

</div>

<div class="memdoc">

Reads the values from a register pair.

  - Parameters
    
    |       |                                                           |
    | ----- | --------------------------------------------------------- |
    | reg   | register to read port A: 0x00 \~ 0A0                      |
    | portA | reference to port A value; returns the value by reference |
    | portB | reference to port B value; returns the value by reference |
    

<!-- end list -->

  - Note  
    For portA and portB variable to effectively match the desired port,
    you have to supply a portA register address to reg. Otherwise,
    values will be reversed due to the way the MCP23017 works in Byte
    mode.

</div>

</div>

<span id="a8f1b4232f8295f980f8326a5aa77b65b"></span>

## <span class="permalink">[◆ ](#TOC)</span>write()

<div class="memitem">

<div class="memproto">

|                      |   |           |          |   |
| -------------------- | - | --------- | -------- | - |
| void MCP23017::write | ( | uint16\_t | *values* | ) |

</div>

<div class="memdoc">

Writes pins state to both ports.

  - Note  
    See: "3.5.10 Port register"

<!-- end list -->

  - Parameters
    
    |        |                                              |
    | ------ | -------------------------------------------- |
    | values | bitmask to manipulate all OUTPUT of the chip |
    

</div>

</div>

<span id="ac6a375edfb48825d717fc578673125a4"></span>

## <span class="permalink">[◆ ](#TOC)</span>writePort()

<div class="memitem">

<div class="memproto">

|                          |   |                |          |
| ------------------------ | - | -------------- | -------- |
| void MCP23017::writePort | ( | MCP23017\_PORT | *port*,  |
|                          |   | uint8\_t       | *values* |
|                          | ) |                |          |

</div>

<div class="memdoc">

Writes pins state to a whole port.

  - Note  
    See: "3.5.10 Port register"

<!-- end list -->

  - Parameters
    
    |        |                                                |
    | ------ | ---------------------------------------------- |
    | port   | MCP23017 port A or B                           |
    | values | bitmask to manipulate the given port as OUTPUT |
    

</div>

</div>

<span id="a8b4d40141dd9646f80f35f302283a354"></span>

## <span class="permalink">[◆ ](#TOC)</span>writeRegister()

<div class="memitem">

<div class="memproto">

|                              |   |                    |          |
| ---------------------------- | - | ------------------ | -------- |
| void MCP23017::writeRegister | ( | MCP23017\_REGISTER | *reg*,   |
|                              |   | uint8\_t           | *portA*, |
|                              |   | uint8\_t           | *portB*  |
|                              | ) |                    |          |

</div>

<div class="memdoc">

Writes values to a register pair.

  - Note  
    For portA and portB variable to effectively match the desired port,
    you have to supply a portA register address to reg. Otherwise,
    values will be reversed due to the way the MCP23017 works in Byte
    mode.

</div>

</div>

-----