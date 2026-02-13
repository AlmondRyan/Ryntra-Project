java -jar C:\ANTLR\antlr-4.13.2-complete.jar -Dlanguage=Cpp -visitor -package Ryntra::antlr -o .\antlr\antlr-generated .\antlr\Ryntra.g4

if ($LASTEXITCODE -ne 0) {
    Write-Error "Error occurred during generate ANTLR Sources."
    exit $LASTEXITCODE
} else {
    Write-Output "Done."
}
