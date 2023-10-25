@echo off
FOR /L %%i IN (1,1,13) DO (
    g++ -std=c++14 -Werror -Wuninitialized -o build\test_io src\main.cpp src\AVLTree.cpp && build\test_io < test-io\input-files\%%i.txt > test-io\output-files\%%i.txt
)