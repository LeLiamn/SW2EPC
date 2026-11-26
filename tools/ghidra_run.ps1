# Run a Ghidra headless script on the already analysed SW2E project.
# Works around two Ghidra problems on this machine: it needs JDK 25+ (JAVA_HOME), and its script
# module fails when its cache folder path contains a space (APPDATA / LOCALAPPDATA redirected).
#
# Usage (PowerShell):
#   tools\ghidra_run.ps1 DecompileAt.java out.c 0x001992c4 0x00102a20
param([Parameter(Mandatory = $true)][string]$Script, [Parameter(ValueFromRemainingArguments = $true)][string[]]$ScriptArgs)

$root = Split-Path -Parent $PSScriptRoot
$jdk = if ($env:SW2E_JDK) { $env:SW2E_JDK } else { 'E:\JDK' }
$userDir = if ($env:SW2E_GHIDRA_USER) { $env:SW2E_GHIDRA_USER } else { 'E:\ghidra_user' }
New-Item -ItemType Directory -Force "$userDir\Roaming", "$userDir\Local" | Out-Null
$env:APPDATA = "$userDir\Roaming"
$env:LOCALAPPDATA = "$userDir\Local"
$env:JAVA_HOME = $jdk
$env:Path = "$jdk\bin;" + $env:Path

& "$root\ghidra_12.2_PUBLIC\support\analyzeHeadless.bat" "$root\ghidra_project" SW2E `
    -process SLES_546.24 -noanalysis -readOnly `
    -scriptPath "$root\tools\ghidra" -postScript $Script @ScriptArgs 2>&1 |
    ForEach-Object { "$_" } | Where-Object { $_ -match 'ERROR|SCRIPT|REPORT' }
