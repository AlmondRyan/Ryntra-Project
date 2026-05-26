Set-Location ./Scripts/CheckTest
python CheckTest.py

if ($LASTEXITCODE -ne 0) {
    Write-Error "Error during test."
    exit $LASTEXITCODE
} else {
    Write-Output "Test done."
}