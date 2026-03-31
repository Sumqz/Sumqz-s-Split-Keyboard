Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

function Run-Git {
  param([string[]]$GitArgs)
  & git @GitArgs
  if ($LASTEXITCODE -ne 0) {
    throw "git $($GitArgs -join ' ') failed with exit code $LASTEXITCODE"
  }
}

$repoRoot = "C:\Users\elias\OneDrive\Splitkeeboard"
Set-Location $repoRoot
$env:GIT_TERMINAL_PROMPT = "0"
$env:GCM_INTERACTIVE = "Never"

Run-Git -GitArgs @("rev-parse", "--is-inside-work-tree")
Run-Git -GitArgs @("pull", "--rebase", "--autostash", "origin", "main")

$changes = git status --porcelain
if (-not $changes) {
  exit 0
}

Run-Git -GitArgs @("add", "-A")

$timestamp = Get-Date -Format "yyyy-MM-dd HH:mm:ss"
Run-Git -GitArgs @("commit", "-m", "auto sync $timestamp")
Run-Git -GitArgs @("push", "origin", "main")
