param(
    [Parameter(Mandatory = $True)]
    [string]$Configuration,

    [Parameter(Mandatory = $True)]
    [string]$Platform
)

$BuildScripts = @(
    '.\build\MSBuild.ps1'
)

foreach ($BuildScript in $BuildScripts)
{
    & $BuildScript $Configuration $Platform
    if ($LASTEXITCODE -ne 0)
    {
        throw "Failed to execute $BuildScript."
    }
}