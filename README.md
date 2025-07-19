[mcp]: https://github.com/autowp/arduino-mcp2515
[u8g2]: https://github.com/olikraus/u8g2

## Overview
Arduino program to read CAN messages from OF Gear Transmission Control Unit and MaxxECU Engine Control Unit, and display relevant data to an OLED display.

Can messages are read using the MCP2515 CAN Bus module and [arduino library][mcp].

Data is drawn on the display using the U8G2 [arduino library][u8g2].

## Wiring




## TCU Data
### Messages
| Message ID | Data |
| :--------- | :--- |
| 0x00000603 | Gear, Mode, Oil Temperature |

### Possible values and explanation
Gear: 0 = Neutral/Reverse, 1-5 = Actual gear

Mode: 1 = Automatic, 2 = Manual

Temperature: 0-255 Celsius

## ECU Data (TODO)
