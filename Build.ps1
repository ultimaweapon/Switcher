param(
    [string]$Configuration,
    [string]$Platform
)

$Solutions = @(
    'Switcher.sln',
    'Engines\Component Object Model\Component Object Model.sln'
)

foreach ($Solution in $Solutions)
{
    MSBuild "$Solution" /t:Rebuild /p:Configuration=$Configuration /p:Platform=$Platform
}