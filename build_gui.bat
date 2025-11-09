@echo off
REM Build script for MWINTELLIGENCE GUI version
REM Using Dear ImGui + GLFW + OpenGL3

echo ========================================
echo MWINTELLIGENCE GUI Build System
echo ========================================
echo.

REM Check for ImGui (support both imgui-master and imgui folders)
set IMGUI_DIR=
if exist "imgui\" (
    set IMGUI_DIR=imgui
    echo [OK] ImGui found in imgui\
) else if exist "imgui-master\" (
    set IMGUI_DIR=imgui-master
    echo [OK] ImGui found in imgui-master\
) else (
    echo [ERROR] ImGui library not found!
    echo Please download Dear ImGui from: https://github.com/ocornut/imgui
    echo Extract to: imgui\ or imgui-master\
    pause
    exit /b 1
)

if not exist "glfw\" (
    echo [!] GLFW missing - downloading...
    echo.
    echo Downloading GLFW 3.4 binaries...
    powershell -Command "Invoke-WebRequest -Uri 'https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.bin.WIN64.zip' -OutFile 'glfw.zip'; Expand-Archive -Path 'glfw.zip' -DestinationPath '.'; Rename-Item -Path 'glfw-3.4.bin.WIN64' -NewName 'glfw'; Remove-Item 'glfw.zip'"
    
    if exist "glfw\" (
        echo [OK] GLFW downloaded successfully!
    ) else (
        echo [ERROR] Failed to download GLFW automatically
        echo Please download manually from: https://www.glfw.org/download.html
        echo Get: Windows pre-compiled binaries (64-bit)
        echo Extract to: glfw\
        pause
        exit /b 1
    )
)

echo.
echo [*] Compiling MWINTELLIGENCE GUI Edition...
echo.

REM Set compiler and paths
set COMPILER=C:\msys64\mingw64\bin\g++.exe
set INCLUDES=-I. -I%IMGUI_DIR% -I%IMGUI_DIR%\backends -Iglfw\include
set LIBS=-Lglfw\lib-mingw-w64 -lglfw3 -lopengl32 -lgdi32 -limm32
set FLAGS=-std=c++17 -O2

REM Compile ImGui sources
echo [1/3] Compiling ImGui core...
%COMPILER% -c %IMGUI_DIR%\imgui.cpp %INCLUDES% %FLAGS%
%COMPILER% -c %IMGUI_DIR%\imgui_draw.cpp %INCLUDES% %FLAGS%
%COMPILER% -c %IMGUI_DIR%\imgui_tables.cpp %INCLUDES% %FLAGS%
%COMPILER% -c %IMGUI_DIR%\imgui_widgets.cpp %INCLUDES% %FLAGS%

echo [2/3] Compiling ImGui backends...
%COMPILER% -c %IMGUI_DIR%\backends\imgui_impl_glfw.cpp %INCLUDES% %FLAGS%
%COMPILER% -c %IMGUI_DIR%\backends\imgui_impl_opengl3.cpp %INCLUDES% %FLAGS%

echo [3/3] Linking application...
%COMPILER% -o student_manager_gui.exe ^
    source_gui.cpp ^
    imgui.o imgui_draw.o imgui_tables.o imgui_widgets.o ^
    imgui_impl_glfw.o imgui_impl_opengl3.o ^
    %INCLUDES% %FLAGS% %LIBS%

if errorlevel 1 (
    echo.
    echo [ERROR] Build failed!
    pause
    exit /b 1
)

REM Clean up object files
del *.o 2>nul

echo.
echo [SUCCESS] Build complete!
echo Executable: student_manager_gui.exe
echo.
echo Run with: student_manager_gui.exe
echo.
pause
