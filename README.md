# Sumqz-s-Split-Keyboard

Hey everyone this is my Split Keyboard. I always felt that traditional Keyboard were functional but boring so i decided to build my own split keyboard. It can attach to the other half with magnets and work completely wirelessly. It includes a nrf52840. It's hotswappable and easy to make it at home. To use it you just need to flash the .ino file on the nrf52840 and connect it to the PC. It can be made into a full 75% Keyboard within seconds just by putting the two side together with the magnets.

Here are some pictures:

![Assembled](Pictures/Assembled.jpg)
![Full](Pictures/Full.jpg)
![Inside](Pictures/Inside.jpg)
![PCB](Pictures/PCB.jpg)
![Reference](Pictures/Reference.png)
![Rendered](Pictures/Rendered.jpg)
![Schematic Left](Pictures/Sch_left.jpg)
![Schematic Right](Pictures/Sch_right.jpg)
![With PCB](Pictures/With_PCB.jpg)

## Bill of Materials

| Part | Qty | Notes |
|---|---:|---|
| nRF52840 (XIAO nRF52840) | 2 | One per side |
| Buzzer 12x8.5 | 2 | Through-hole buzzer |
| Switches (Holy Panda) | 87 | Total key count |
| Keycaps (generic) | 87 | Match your layout |
| MCP23017 GPIO Expander | 2 | MCP23017_SP |
| LiPo 1200mAh | 2 | One per side |
| Diodes | 87 | 1N4148W (SOD-123) |
| Resistor 4.7k | 4 | R1, R2, R5, R6 |
| Resistor 806k | 2 | R3, R7 |
| Resistor 2M | 2 | R4, R8 |
