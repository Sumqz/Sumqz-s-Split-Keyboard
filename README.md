
# Sumqz-s-Split-Keyboard

Hey everyone this is my Split Keyboard. I always felt that traditional Keyboard were functional but boring so i decided to build my own split keyboard. It can attach to the other half with magnets and work completely wirelessly. It includes a nrf52840. It's hotswappable and easy to make it at home. To use it you just need to flash the .ino file on the nrf52840 and connect it to the PC. It can be made into a full 75% Keyboard within seconds just by putting the two side together with the magnets. 

I wanted something more fun than a normal keyboard, so I made one that can:
- work as two separate halves
- snap together with magnets
- become a full 75% style board quickly

It is hot-swappable, uses nRF52840 boards, and is made to be buildable at home.

## Short Description

A DIY wireless split keyboard with magnetic attachment, hot-swap switches, and easy firmware flashing.

## Pictures
=======
## Short Description

DIY wireless split keyboard with magnetic attachment and hot-swap sockets.

Here are some pictures:
>>>>>>> Stashed changes

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

<<<<<<< Updated upstream
| Part | Qty | Notes |
|---|---:|---|
| nRF52840 (XIAO nRF52840) | 2 | One per side |
| Buzzer 12x8.5 | 2 | One per side | https://it.aliexpress.com/item/1005002576043967.html?spm=a2g0o.productlist.main.16.4313nghjnghjWD&aem_p4p_detail=202603311041497352129250057200001461119&algo_pvid=d92a82d0-7910-4042-bfa4-55e98ba7c152&algo_exp_id=d92a82d0-7910-4042-bfa4-55e98ba7c152-15&pdp_ext_f=%7B%22order%22%3A%2267%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21EUR%211.69%211.69%21%21%211.89%211.89%21%40211b617b17749789096072619e3bbb%2112000021227023571%21sea%21IT%217741602446%21ABX%211%210%21n_tag%3A-29910%3Bd%3A7766218f%3Bm03_new_user%3A-29895&curPageLogUid=pQgxmelRyi34&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005002576043967%7C_p_origin_prod%3A&search_p4p_id=202603311041497352129250057200001461119_4 |
| Switches (Holy Panda) | 87 | Total keys | https://it.aliexpress.com/item/1005004388563696.html?spm=a2g0o.productlist.main.1.4a85xkx2xkx2Ny&algo_pvid=f43e91a3-0339-49d6-946e-d4aab90c1666&algo_exp_id=f43e91a3-0339-49d6-946e-d4aab90c1666-0&pdp_ext_f=%7B%22order%22%3A%22889%22%2C%22spu_best_type%22%3A%22price%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21EUR%215.11%214.23%21%21%215.73%214.74%21%402103834817749794439556267e94b8%2112000029005363921%21sea%21IT%217741602446%21ABX%211%210%21n_tag%3A-29910%3Bd%3A7766218f%3Bm03_new_user%3A-29895%3BpisId%3A5000000203171050&curPageLogUid=xMDT4E0ebd1j&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005004388563696%7C_p_origin_prod%3A |
| Keycaps (generic) | 87 | Match your layout |
| MCP23017 GPIO Expander DIP | 2 | MCP23017_SP |
| LiPo 1200mAh | 2 | One per side | https://it.aliexpress.com/item/1005011550469394.html?spm=a2g0o.productlist.main.5.47cahFrPhFrPyH&algo_pvid=31524ca6-3e65-4e7b-b68b-552d57e3a3ed&algo_exp_id=31524ca6-3e65-4e7b-b68b-552d57e3a3ed-4&pdp_ext_f=%7B%22order%22%3A%2251%22%2C%22spu_best_type%22%3A%22price%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21EUR%2112.11%219.69%21%21%2193.73%2175.00%21%4021038df617749795769426625e8c6c%2112000055891309696%21sea%21IT%217741602446%21ABX%211%210%21n_tag%3A-29910%3Bd%3A7766218f%3Bm03_new_user%3A-29895&curPageLogUid=uhpoMLkrdQiL&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005011550469394%7C_p_origin_prod%3A |
| Diodes | 87 | 1N4148W (SOD-123) |
| Resistor 4.7k | 4 | R1, R2, R5, R6 |
| Resistor 806k | 2 | R3, R7 |
| Resistor 2M | 2 | R4, R8 |

## Firmware

Flash the `.ino` firmware to each nRF52840 board, connect to PC, and use.



=======
| Part | Qty | Notes | Link |
|---|---:|---|---|
| nRF52840 (XIAO nRF52840) | 2 | One per side | [Buy](https://it.aliexpress.com/item/1005006988954136.html) |
| MCP23017 GPIO Expander | 2 | MCP23017_SP, DIP-28 package required | [Buy](https://it.aliexpress.com/item/1005009603989894.html) |
| LiPo 1200mAh | 2 | One per side | [Buy](https://it.aliexpress.com/item/1005011550469394.html) |
| Buzzer 12x9.5 / RM7.6 | 2 | Match PCB footprint pin spacing | [Buy](https://it.aliexpress.com/item/1005002576043967.html) |
| Switches (Holy Panda) | 87 | Total keys | [Buy](https://it.aliexpress.com/item/1005004388563696.html) |
| Keycaps (generic) | 87 | Match your layout | [Buy](https://it.aliexpress.com/item/1005011879391386.html) |
| Diodes 1N4148W (SOD-123) | 87 | One per switch | [Buy](https://it.aliexpress.com/item/1005003194674618.html) |
| Resistor 4.7k (0805) | 4 | R1, R2, R5, R6 | [Buy](https://it.aliexpress.com/item/1005011649990763.html) |
| Resistor 806k (0805) | 2 | R3, R7 | [Buy](https://it.aliexpress.com/item/1005011649990763.html) |
| Resistor 2M (0805) | 2 | R4, R8 | [Buy](https://it.aliexpress.com/item/1005011649990763.html) |

Resistor note: it is usually cheaper to buy one full resistor set (0805 assortment) instead of buying each value separately.

## Quick Compatibility Check

- MCU: looks correct if the listing is really XIAO nRF52840.
- Diodes: good if they are really SOD-123 1N4148W.
- Resistors: must be 0805 values 4.7k, 806k, 2M.
- Buzzer: PCB footprint is 12x9.5 with 7.6 mm pin spacing, so verify that before buying.
- MCP: your PCB uses a DIP-28 MCP23017 chip, not a pre-built module board.
- Important: your PCB switch footprints are Choc (`SW_choc_v1...`). Most Holy Panda switches are MX-style, so they may NOT fit. Use Choc-compatible switches unless you redesign footprints.
>>>>>>> Stashed changes
