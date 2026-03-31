param(
  [string]$Fqbn = "Seeeduino:mbed:xiaonRF52840"
)

$ErrorActionPreference = "Stop"

$repoRoot = Split-Path -Parent $PSScriptRoot
$arduinoCli = "C:\Program Files\Arduino CLI\arduino-cli.exe"
$uf2Conv = "C:\Users\elias\AppData\Local\Arduino15\packages\adafruit\hardware\nrf52\1.7.0\tools\uf2conv\uf2conv.py"
$sketchDir = Join-Path $PSScriptRoot "SplitKeyboard"
$buildRoot = Join-Path $PSScriptRoot "build"
$leftBuild = Join-Path $buildRoot "left"
$rightBuild = Join-Path $buildRoot "right"
$prodDir = Join-Path $repoRoot "Production\UF2"

New-Item -ItemType Directory -Force -Path $leftBuild | Out-Null
New-Item -ItemType Directory -Force -Path $rightBuild | Out-Null
New-Item -ItemType Directory -Force -Path $prodDir | Out-Null

& $arduinoCli lib install "Adafruit MCP23017 Arduino Library" | Out-Null

Write-Host "Compiling LEFT..."
& $arduinoCli compile `
  --fqbn $Fqbn `
  --build-property "build.extra_flags=-DHALF_LEFT" `
  --output-dir $leftBuild `
  $sketchDir

Write-Host "Compiling RIGHT..."
& $arduinoCli compile `
  --fqbn $Fqbn `
  --build-property "build.extra_flags=-DHALF_RIGHT" `
  --output-dir $rightBuild `
  $sketchDir

$leftHex = Join-Path $leftBuild "SplitKeyboard.ino.hex"
$rightHex = Join-Path $rightBuild "SplitKeyboard.ino.hex"
$leftUf2Out = Join-Path $leftBuild "SplitKeyboard-left.uf2"
$rightUf2Out = Join-Path $rightBuild "SplitKeyboard-right.uf2"

if (-not (Test-Path $leftHex) -or -not (Test-Path $rightHex)) {
  throw "Expected HEX output not found. Check compile logs and FQBN."
}

if (-not (Test-Path $uf2Conv)) {
  throw "uf2conv.py not found at $uf2Conv"
}

Write-Host "Converting LEFT HEX to UF2..."
python $uf2Conv -c -f 0xADA52840 -o $leftUf2Out $leftHex | Out-Null

Write-Host "Converting RIGHT HEX to UF2..."
python $uf2Conv -c -f 0xADA52840 -o $rightUf2Out $rightHex | Out-Null

Copy-Item $leftUf2Out (Join-Path $prodDir "SplitKeyboard-left.uf2") -Force
Copy-Item $rightUf2Out (Join-Path $prodDir "SplitKeyboard-right.uf2") -Force

Write-Host ""
Write-Host "Done."
Write-Host "LEFT : $leftUf2Out"
Write-Host "RIGHT: $rightUf2Out"
Write-Host "Copied to: $prodDir"
