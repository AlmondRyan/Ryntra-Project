Set-Location Scripts/GenAllNodesVisitor
python GenAllNodesVisitor.py ../../cmake-build-debug/Compiler/GeneratedHeader/AllNodesVisitor.h

if ($LASTEXITCODE -ne 0) {
    Write-Error "Error occurred during generate All Nodes Visitor."
    exit $LASTEXITCODE
} else {
    Write-Output "Done."
}