@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion

echo Building student_manager.exe from source.cpp...

:: Check if --static argument was provided
set STATIC=0
for %%a in (%*) do (
    if "%%a"=="--static" set STATIC=1
)

:: Build command
set "COMPILE_CMD=g++ -std=c++17 -O2 -Wall -Wextra"
if %STATIC%==1 (
    echo Using static linking...
    set "COMPILE_CMD=!COMPILE_CMD! -static -static-libgcc -static-libstdc++"
)
set "COMPILE_CMD=!COMPILE_CMD! -o student_manager.exe source.cpp"

:: Try to compile
%COMPILE_CMD%

if %ERRORLEVEL% neq 0 (
    echo.
    echo Build failed. Please ensure you have MSYS2 installed and its bin directory in your PATH:
    echo 1. Install MSYS2 from https://www.msys2.org
    echo 2. Open "MSYS2 MinGW 64-bit" terminal
    echo 3. Run: pacman -Syu
    echo 4. Close and reopen MSYS2, then run: pacman -Su
    echo 5. Run: pacman -S --needed base-devel mingw-w64-x86_64-toolchain
    echo 6. Add to PATH: C:\msys64\mingw64\bin
    pause
    exit /b %ERRORLEVEL%
)

echo Build succeeded.
echo Running student_manager.exe...
student_manager.exe
pause
