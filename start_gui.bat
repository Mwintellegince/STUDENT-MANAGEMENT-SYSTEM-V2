@echo off
echo ========================================
echo MWINTELLIGENCE GUI - Quick Start
echo ========================================
echo.
echo This script will help you set up the GUI version.
echo.
echo Step 1: Download Required Libraries
echo ------------------------------------
echo.
echo You need to download two libraries:
echo.
echo 1. Dear ImGui (GUI Framework)
echo    URL: https://github.com/ocornut/imgui/archive/refs/heads/docking.zip
echo    Extract to: imgui\
echo.
echo 2. GLFW (Window Management)
echo    URL: https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.bin.WIN64.zip
echo    Extract to: glfw\
echo.
echo OR run the PowerShell setup script:
echo    PowerShell -ExecutionPolicy Bypass -File setup_gui.ps1
echo.
pause
echo.

REM Check if libraries are installed
if not exist "imgui\" (
    echo [ERROR] ImGui not found in imgui\ folder
    echo Please download and extract ImGui first.
    echo.
    pause
    exit /b 1
)

if not exist "glfw\" (
    echo [ERROR] GLFW not found in glfw\ folder  
    echo Please download and extract GLFW first.
    echo.
    pause
    exit /b 1
)

echo [OK] Libraries found!
echo.
echo Step 2: Building Application
echo -----------------------------
echo.

call build_gui.bat

if exist "student_manager_gui.exe" (
    echo.
    echo ========================================
    echo BUILD SUCCESSFUL!
    echo ========================================
    echo.
    echo The GUI application is ready to use!
    echo.
    echo To run: student_manager_gui.exe
    echo.
    choice /C YN /M "Would you like to launch it now"
    if errorlevel 2 goto :end
    if errorlevel 1 (
        start student_manager_gui.exe
    )
)

:end
pause
