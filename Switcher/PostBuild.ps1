param(
	[string]$OutputDirectory,
	[string]$ProjectDirectory
)

$SdkDir = Join-Path -Path $OutputDirectory -ChildPath 'SDK'
$SdkFiles = @('Engine.idl', 'Engine.ini', 'SDK Readme.txt')

if (-not (Test-Path $SdkDir))
{
	New-Item -ItemType Directory -Path $SdkDir | Out-Null
}

foreach ($File in $SdkFiles)
{
	$Source = Join-Path -Path $ProjectDirectory -ChildPath $File
	$Destination = Join-Path -Path $SdkDir -ChildPath $File
	Copy-Item -Path $Source -Destination $Destination
}
