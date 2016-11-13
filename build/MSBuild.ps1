param(
    [Parameter(Mandatory = $True)]
    [string]$Configuration,

    [Parameter(Mandatory = $True)]
    [string]$Platform
)

switch ($Platform)
{
    'x86' { $EnvPlatform = 'x86' }
    'x64' { $EnvPlatform = 'amd64' }
    default { throw "Platform $Platform is not supported." }
}

$Solutions = @(
    "$PSScriptRoot\..\Switcher.sln",
    "$PSScriptRoot\..\Engines\Component Object Model\Component Object Model.sln",
    "$PSScriptRoot\..\Switches\Windows Service\Windows Service.sln"
)

foreach ($Solution in $Solutions)
{
    cmd /c "`"$env:VS_ENV_SETTER`" $EnvPlatform & MSBuild `"$Solution`" /t:Rebuild /p:Configuration=`"$Configuration`" /p:Platform=`"$Platform`""
    if ($LASTEXITCODE -ne 0)
    {
        throw "Failed to build $Solution."
    }

    Write-Host "`n"
}