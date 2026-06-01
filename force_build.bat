@echo off
setlocal
title X-INSPECT Build Tool

:: Compiler Path
set PATH=C:\Program Files (x86)\Embarcadero\Dev-Cpp\TDM-GCC-64\bin;%PATH%

echo [1/3] Baking Icon into Resources...
windres resources.rc -o resources.o

echo [2/3] Compiling X-INSPECT Core...
g++ main.cpp resources.o -o X-INSPECT.exe -lcomctl32 -lgdi32 -lshell32 -mwindows

if %ERRORLEVEL% EQU 0 (
    echo [3/3] [SUCCESS] X-INSPECT is Ready.
    start X-INSPECT.exe
) else (
    echo [ERROR] Build Failed.
    pause
)