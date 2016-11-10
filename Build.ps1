param(
    [Parameter(Mandatory = $True)]
    [string]$Configuration,

    [Parameter(Mandatory = $True)]
    [string]$Platform
)

$Solutions = @(
    'Switcher.sln',
    'Engines\Component Object Model\Component Object Model.sln'
)

foreach ($Solution in $Solutions)
{
    MSBuild "$Solution" /t:Rebuild /p:Configuration=$Configuration /p:Platform=$Platform
    if ($LASTEXITCODE -ne 0)
    {
        throw "Failed to build $Solution."
    }
}