# Usage
#   .\check.ps1 02              grade my solution
#   .\check.ps1 02 -Solution    run reference solution
#   .\check.ps1 01              run output-prediction questions
#   .\check.ps1 01 5            run only question 5
param(
    [Parameter(Mandatory = $true, Position = 0)]
    [ValidateSet('01', '02', '03', '04')]
    [string]$Num,

    [Parameter(Position = 1)]
    [string]$Question,

    [switch]$Solution
)

$names = @{
    '01' = '01_output_prediction'
    '02' = '02_bit_manipulation'
    '03' = '03_pointer_string'
    '04' = '04_embedded'
}
$name = $names[$Num]
$root = $PSScriptRoot
$build = Join-Path $root 'build'
New-Item -ItemType Directory -Force $build | Out-Null

if ($Num -eq '01') {
    if ($Solution) {
        Write-Host 'Q01 answers: solutions\01_answers.md'
        exit 0
    }
    $exe = Join-Path $build 'q01.exe'
    # compile with -w so warnings do not spoil answers
    & gcc -std=c99 -w (Join-Path $root "$name.c") -o $exe
    if ($LASTEXITCODE -ne 0) { exit 1 }
    if ($Question) { & $exe $Question } else { & $exe }
    exit $LASTEXITCODE
}

if ($Solution) {
    $src = Join-Path $root "solutions\$name.c"
    $includes = @('-I', (Join-Path $root 'solutions'), '-I', $root)
    $exe = Join-Path $build "${name}_solution.exe"
} else {
    $src = Join-Path $root "$name.c"
    $includes = @('-I', $root)
    $exe = Join-Path $build "$name.exe"
}
$test = Join-Path $root "tests\test_$Num.c"

& gcc -std=c99 -Wall @includes $src $test -o $exe
if ($LASTEXITCODE -ne 0) {
    Write-Host 'Compile failed'
    exit 1
}
& $exe
exit $LASTEXITCODE
