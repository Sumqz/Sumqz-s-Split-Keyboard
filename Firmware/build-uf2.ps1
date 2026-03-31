param(
  [string]$Fqbn = "Seeeduino:mbed:xiaonRF52840"
)

$ErrorActionPreference = "Stop"

$repoRoot = Split-Path -Parent $PSScriptRoot
$arduinoCli = "C:\Program Files\Arduino CLI\arduino-cli.exe"
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

$leftUf2 = Get-ChildItem -Path $leftBuild -Filter *.uf2 -File | Select-Object -First 1
$rightUf2 = Get-ChildItem -Path $rightBuild -Filter *.uf2 -File | Select-Object -First 1

if (-not $leftUf2 -or -not $rightUf2) {
  throw "UF2 output not found. Check compile logs and FQBN."
}

Copy-Item $leftUf2.FullName (Join-Path $prodDir "SplitKeyboard-left.uf2") -Force
Copy-Item $rightUf2.FullName (Join-Path $prodDir "SplitKeyboard-right.uf2") -Force

Write-Host ""
Write-Host "Done."
Write-Host "LEFT : $($leftUf2.FullName)"
Write-Host "RIGHT: $($rightUf2.FullName)"
Write-Host "Copied to: $prodDir"
