# SplitKeyboard Firmware

This firmware targets your netlist design:
- MCU: Seeed XIAO nRF52840
- Matrix expander: MCP23017 at `0x20`
- Matrix wiring: `GPA0..7 = Col0..7`, `GPB0..5 = Row0..5`
- Battery sense: `BT_PIN (P0.02 / A0)` with divider `806k/2M`

## Build UF2 (both halves)

From repository root:

```powershell
.\Firmware\build-uf2.ps1
```

Output UF2 files are copied to:
- `Production\UF2\SplitKeyboard-left.uf2`
- `Production\UF2\SplitKeyboard-right.uf2`

## Flash

1. Double-press reset on the XIAO board (UF2 drive appears).
2. Copy the matching UF2:
   - Left board: `SplitKeyboard-left.uf2`
   - Right board: `SplitKeyboard-right.uf2`

## Battery Percentage

Battery status is printed every 30 seconds on USB serial at `115200`:

```text
Battery: 84% (3.98V)
```
