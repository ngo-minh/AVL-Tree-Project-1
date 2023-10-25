@echo off
setlocal enabledelayedexpansion

g++ -std=c++14 -Werror -Wuninitialized -o build\test_io src\main.cpp src\AVLTree.cpp
if errorlevel 1 (
    echo Compilation failed!
    exit /b 1
)

REM Creating or clearing the results file
echo Results: > test-io\output-files\results.txt

for /L %%i in (1,1,13) do (
    echo Running test case %%i...
    build\test_io < test-io\input-files\%%i.txt > test-io\output-files\%%i.txt
    echo Test case %%i: >> test-io\output-files\results.txt
    FC /W test-io\expected-output-files\%%i.txt test-io\output-files\%%i.txt >> test-io\output-files\results.txt
    echo. >> test-io\output-files\results.txt
    echo Test case %%i completed.
)

echo Results saved to test-io\output-files\results.txt
