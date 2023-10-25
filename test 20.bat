@echo off
setlocal enabledelayedexpansion

REM --- Compile the code ---
g++ -std=c++14 -Werror -Wuninitialized -o build\test_io src\main.cpp src\AVLTree.cpp
if errorlevel 1 (
    echo Compilation failed!
    exit /b 1
)

REM --- Running all tests ---

REM Creating or clearing the results file
echo Results: > test-io\output-files\results.txt

FOR /L %%i IN (20,1,20) DO (
    echo Running test case %%i...
    build\test_io < test-io\input-files\%%i.txt > test-io\output-files\%%i.txt
    echo Test case %%i: >> test-io\output-files\results.txt
    FC /W test-io\expected-output-files\%%i.txt test-io\output-files\%%i.txt >> test-io\output-files\results.txt
    echo. >> test-io\output-files\results.txt
    echo Test case %%i completed.
)

echo Results saved to test-io\output-files\results.txt