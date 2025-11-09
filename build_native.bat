@echo off
echo ========================================
echo MWINTELLIGENCE Native Windows App Build
echo ========================================
echo.

echo [*] Compiling resource file...
"C:\msys64\mingw64\bin\windres.exe" resource.rc -o resource.o

echo [*] Compiling Native Windows Application...
"C:\msys64\mingw64\bin\g++.exe" -std=c++17 -O2 -mwindows -municode -DUNICODE -D_UNICODE ^
    student_app_native.cpp resource.o ^
    -o StudentManager.exe ^
    -lcomctl32 -lgdi32 -lcomdlg32

if %errorlevel% equ 0 (
    echo.
    echo [SUCCESS] Build complete!
    echo Executable: StudentManager.exe
    echo.
    echo Run with: StudentManager.exe
) else (
    echo.
    echo [ERROR] Build failed!
)

pause
