Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

$repoRoot = "C:\Users\elias\OneDrive\Splitkeeboard"
Set-Location $repoRoot

try {
  git rev-parse --is-inside-work-tree | Out-Null
} catch {
  exit 1
}

$changes = git status --porcelain
if (-not $changes) {
  exit 0
}

git add -A

$timestamp = Get-Date -Format "yyyy-MM-dd HH:mm:ss"
git commit -m "auto sync $timestamp" | Out-Null
git push origin main | Out-Null
