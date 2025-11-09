# MWINTELLIGENCE GUI Setup Script
# Downloads and sets up Dear ImGui and GLFW

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "MWINTELLIGENCE GUI Setup" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

$currentDir = Get-Location

# Setup Dear ImGui
if (-not (Test-Path "imgui")) {
    Write-Host "[*] Downloading Dear ImGui..." -ForegroundColor Yellow
    
    $imguiUrl = "https://github.com/ocornut/imgui/archive/refs/heads/docking.zip"
    $imguiZip = "imgui.zip"
    
    try {
        Invoke-WebRequest -Uri $imguiUrl -OutFile $imguiZip
        Write-Host "[+] Downloaded ImGui" -ForegroundColor Green
        
        Write-Host "[*] Extracting ImGui..." -ForegroundColor Yellow
        Expand-Archive -Path $imguiZip -DestinationPath "." -Force
        Rename-Item -Path "imgui-docking" -NewName "imgui"
        Remove-Item $imguiZip
        
        Write-Host "[+] ImGui setup complete" -ForegroundColor Green
    } catch {
        Write-Host "[!] Failed to download ImGui automatically" -ForegroundColor Red
        Write-Host "Please download manually from: https://github.com/ocornut/imgui" -ForegroundColor Yellow
        Write-Host "Extract to: $currentDir\imgui" -ForegroundColor Yellow
    }
} else {
    Write-Host "[+] ImGui already installed" -ForegroundColor Green
}

# Setup GLFW
if (-not (Test-Path "glfw")) {
    Write-Host ""
    Write-Host "[*] Downloading GLFW..." -ForegroundColor Yellow
    
    $glfwUrl = "https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.bin.WIN64.zip"
    $glfwZip = "glfw.zip"
    
    try {
        Invoke-WebRequest -Uri $glfwUrl -OutFile $glfwZip
        Write-Host "[+] Downloaded GLFW" -ForegroundColor Green
        
        Write-Host "[*] Extracting GLFW..." -ForegroundColor Yellow
        Expand-Archive -Path $glfwZip -DestinationPath "." -Force
        Rename-Item -Path "glfw-3.4.bin.WIN64" -NewName "glfw"
        Remove-Item $glfwZip
        
        Write-Host "[+] GLFW setup complete" -ForegroundColor Green
    } catch {
        Write-Host "[!] Failed to download GLFW automatically" -ForegroundColor Red
        Write-Host "Please download manually from: https://www.glfw.org/download.html" -ForegroundColor Yellow
        Write-Host "Get: Windows pre-compiled binaries (64-bit)" -ForegroundColor Yellow
        Write-Host "Extract to: $currentDir\glfw" -ForegroundColor Yellow
    }
} else {
    Write-Host "[+] GLFW already installed" -ForegroundColor Green
}

Write-Host ""
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Setup Complete!" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "Next steps:" -ForegroundColor Yellow
Write-Host "1. Run: .\build_gui.bat" -ForegroundColor White
Write-Host "2. Launch: .\student_manager_gui.exe" -ForegroundColor White
Write-Host ""
