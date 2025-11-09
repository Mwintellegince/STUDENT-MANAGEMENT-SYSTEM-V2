# 🎓 Student Management System V2# 🎓 Student Management System V2MWINTELLIGENCE Student Management System v3.0



<div align="center">==============================================

  

![Student Management System](https://readme-typing-svg.herokuapp.com?font=Fira+Code&size=30&duration=3000&pause=1000&color=F70000&center=true&vCenter=true&random=false&width=500&lines=Student+Management+System;Powered+by+C%2B%2B;Modern+and+Efficient)<div align="center">



<p align="center">  **Now Available in Two Editions:**

  <img src="https://img.shields.io/badge/C%2B%2B-17-blue?style=for-the-badge&logo=c%2B%2B" alt="C++17"/>

  <img src="https://img.shields.io/badge/Platform-Windows-blue?style=for-the-badge&logo=windows" alt="Windows"/>![Student Management System](https://readme-typing-svg.herokuapp.com?font=Fira+Code&size=30&duration=3000&pause=1000&color=F70000&center=true&vCenter=true&random=false&width=500&lines=Student+Management+System;Powered+by+C%2B%2B;Modern+and+Efficient)- 🖥️ **GUI Edition** - Modern desktop application with Dear ImGui (NEW!)

  <img src="https://img.shields.io/badge/GUI-Dear%20ImGui-orange?style=for-the-badge" alt="Dear ImGui"/>

  <img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge" alt="License"/>- 💻 **Console Edition** - Professional command-line interface

</p>

</div>

</div>

Quick Start - GUI Edition (Recommended)

## 📑 Table of Contents

- [Features](#-features)## 🌟 Features----------------------------------------

- [Installation](#-installation)

- [Usage](#-usage)1. **Setup**: `.\start_gui.bat` (downloads libraries and builds)

- [Technical Details](#-technical-details)

- [Troubleshooting](#-troubleshooting)- 🎯 **Dual Interface**: Choose between GUI and CLI versions2. **Run**: `.\student_manager_gui.exe`

- [Support](#-support-the-project)

- 📊 **Student Data Management**: Add, edit, delete student records

## 🌟 Features

- 🔍 **Advanced Search**: Find students by various criteriaSee [README_GUI.md](README_GUI.md) for complete GUI documentation.

### Core Functionality

| Feature | Description |- 💾 **Auto Backup**: Automatic CSV backup system

|---------|-------------|

| **Student Management** | Add, edit, delete students with auto-generated IDs |- 📈 **Performance**: Built with optimized C++ code---

| **Data Organization** | Sort by name, age, GPA with multiple criteria |

| **Search & Filter** | Advanced search with case-insensitive matching |- 🎨 **Modern UI**: ImGui-based graphical interface

| **Backup System** | Automatic CSV backups with timestamps |

| **Data Analysis** | GPA statistics, distribution analysis |Student GPA Manager v3.0 - Console Edition

| **Export Options** | CSV and RTF report generation |

## 🚀 Quick Start===========================================

### Interface Options

- 🎨 **Modern GUI Version**

  - ImGui-based graphical interface

  - Intuitive controls and layouts### Prerequisites**Build & Run on Windows (MSYS2 / MinGW-w64 g++)**

  - Real-time updates and filtering

  - Windows OS

- 💻 **Classic CLI Version**

  - Fast keyboard-driven interface- MinGW-w64 with C++17 supportQuick Start

  - ANSI color support

  - ASCII art visualizations- GLFW and ImGui for GUI version-----------



## 🚀 Installation1. **Build**: Terminal → Run Task → `Build (g++)`



### Prerequisites### 🔧 Installation2. **Run**: `.\\student_manager.exe` in integrated terminal

```bash

# 1. Install MSYS2 from https://www.msys2.org/3. **Build & Run**: Terminal → Run Task → `Build & Run (g++)`



# 2. Install required packages1. **Clone the Repository**

pacman -S mingw-w64-x86_64-gcc

pacman -S mingw-w64-x86_64-glfw```bashFeatures (14 Operations)

```

git clone https://github.com/Mwintellegince/STUDENT-MANAGEMENT-SYSTEM-V2.git------------------------

### Quick Setup

```bashcd STUDENT-MANAGEMENT-SYSTEM-V2| # | Feature | Description |

# 1. Clone the repository

git clone https://github.com/Mwintellegince/STUDENT-MANAGEMENT-SYSTEM-V2.git```|---|---------|-------------|

cd STUDENT-MANAGEMENT-SYSTEM-V2

| 1 | Add Student | Create new student with auto-generated unique ID, age, GPA, major |

# 2. Run setup script

./setup_gui.ps1  # For GUI version2. **Setup Environment**| 2 | List Students | Display all students in formatted table (ID, Name, Age, GPA, Major) |

# No setup needed for CLI version

   - For GUI Version:| 3 | Search | Find by name or student ID (case-insensitive substring match) |

# 3. Build the project

./build_gui.bat  # For GUI version     ```powershell| 4 | Edit | Modify name, age, GPA, or major of existing student |

./build.bat      # For CLI version

```     # Run the setup script| 5 | Delete | Remove student by ID (with confirmation) |



## 💫 Usage     ./setup_gui.ps1| 6 | Sort | By name (A-Z), age, GPA ascending, or GPA descending |



### GUI Version     ```| 7 | Statistics | Show count, average GPA, median GPA, GPA/age ranges |

![GUI Screenshot](https://via.placeholder.com/800x400?text=GUI+Screenshot)

   - For CLI Version:| 8 | Filter by GPA | Range query (min/max GPA with validation) |

1. Launch: `./start_gui.bat`

2. Use the navigation bar at the top     ```powershell| 9 | Save CSV | Export all students to comma-separated file |

3. Add/Edit students using forms

4. View real-time updates in the main table     # No additional setup needed| 10 | Load CSV | Import students from CSV with error recovery |



### CLI Version     ```| 11 | Export RTF | Generate Word-compatible rich text format report |

```bash

./student_manager.exe| 12 | Clear All | Bulk delete with "DELETE" confirmation |

```

3. **Build the Project**| 13 | Duplicate Check | Find duplicate names (case-insensitive) with counts |

#### Available Commands

| Key | Action |   - GUI Version:| 14 | GPA Analysis | Visual distribution histogram (ASCII asterisks) |

|-----|--------|

| 1-9 | Menu navigation |     ```powershell

| F1 | Help |

| Ctrl+S | Save |     ./build_gui.batEnhanced Code Features

| Esc | Exit current menu |

     ```----------------------

## 🛠️ Technical Details

   - CLI Version:- **Unique IDs**: Auto-generated from student name (e.g., "john", "john1", "john2")

### System Architecture

```mermaid     ```powershell- **Input Validation**: Age 5-120, GPA 0.0-4.0, non-empty names

graph TD

    A[User Interface] --> B[Core Logic]     ./build.bat- **Robust I/O**: CSV parsing with quoted fields, UTF-8 support

    B --> C[Data Layer]

    C --> D[File System]     ```- **Sorting**: Multiple criteria (name, age, GPA asc/desc)

    C --> E[Memory Cache]

```- **Color Output**: ANSI codes for Windows 10+ (cyan, yellow, green, red, magenta)



### File Structure4. **Run the Application**- **Case-Insensitive Search**: Works with name and ID fields

```

📦 STUDENT-MANAGEMENT-SYSTEM-V2   - GUI Version:- **Error Handling**: Try-catch for file I/O and CSV parsing

 ┣ 📜 source.cpp         # CLI version

 ┣ 📜 source_gui.cpp     # GUI version     ```powershell

 ┣ 📜 students.csv       # Data storage

 ┣ 📂 backup/           # Auto backups     ./start_gui.batBuild Instructions

 ┣ 📂 libs/             # Dependencies

 ┗ 📜 README.md         # Documentation     ```-------------------

```

   - CLI Version:- **Compiler**: g++ (MSYS2 mingw64, v15.2.0+)

## ⚠️ Troubleshooting

     ```powershell- **Standard**: C++17

<details>

<summary>Common Issues</summary>     ./student_manager.exe- **Command**: 



| Problem | Solution |     ```  ```bash

|---------|----------|

| Build fails | Update MinGW-w64 |  g++ -std=c++17 -O2 -pipe source.cpp -o student_manager.exe

| Missing GLFW | Run setup_gui.ps1 |

| Startup crash | Check students.csv |## 💫 Usage  ```



</details>



## ❤️ Support the Project### GUI VersionRunning the Program



If you find this project helpful, consider buying me a coffee!<details>-------------------



<a href="https://www.buymeacoffee.com/mwintelligence" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-red.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a><summary>Click to expand!</summary>**In VS Code Integrated Terminal:**



---```powershell



<div align="center">1. 🖱️ Launch the application using `start_gui.bat`cd "C:\Users\<YourName>\Documents\New folder"



Made with ❤️ by [Mwintellegince](https://github.com/Mwintellegince)2. 📝 Use the top menu to navigate between features.\student_manager.exe



![Visitors](https://api.visitorbadge.io/api/visitors?path=https%3A%2F%2Fgithub.com%2FMwintellegince%2FSTUDENT-MANAGEMENT-SYSTEM-V2&countColor=%23263759)3. ➕ Add students using the "Add Student" form```



</div>4. 🔍 Search using the search bar

5. 📊 View all records in the main table**Or use the Build & Run Task (Ctrl+Shift+P):**

6. 💾 Data is automatically saved- Tasks: Run Task → "Build & Run (g++)"



</details>Troubleshooting

---------------

### CLI Version| Issue | Solution |

<details>|-------|----------|

<summary>Click to expand!</summary>| `g++` not found | Ensure `C:\msys64\mingw64\bin` is in PATH; restart VS Code |

| Program appears frozen | It's waiting for input — use a real terminal, not Debug Console |

1. 🖥️ Launch using `student_manager.exe`| Code Runner doesn't work | Enable: Settings → search "Code Runner: Run In Terminal" → set to true |

2. 📋 Follow the on-screen menu options| CSV import fails | Check file format: `id,name,age,gpa,major` with quoted fields |

3. ⌨️ Use number keys to select options

4. 💾 Save changes when promptedFile Locations

--------------

</details>- **Source**: `source.cpp`

- **Executable**: `student_manager.exe`

## 🛠️ Technical Details- **Tasks config**: `.vscode/tasks.json`

- **Launch config**: `.vscode/launch.json`

- **Language**: C++17- **Data files**: `students.csv`, `students.rtf` (created when you export/save)

- **GUI Framework**: Dear ImGui with GLFW# Student Management System

- **Build System**: MinGW-w64

- **Data Storage**: CSV formatA C++ console application for managing student records with GPA calculation, CSV import/export, and RTF report generation.

- **Backup System**: Automated with timestamps

## Features

## 📄 File Structure

```- Add, list, and search students

📦 STUDENT-MANAGEMENT-SYSTEM-V2- Calculate GPA statistics

 ┣ 📜 source.cpp            # CLI version source- Save/load data to CSV files

 ┣ 📜 source_gui.cpp        # GUI version source- Export formatted reports to RTF (Word)

 ┣ 📜 students.csv          # Data storage- Colored console interface

 ┣ 📂 backup               # Backup files- Settings persistence

 ┣ 📂 imgui                # ImGui library- Animated startup sequence

 ┗ 📂 glfw                 # GLFW library- Unicode box-drawing menu

```

## Building from Source

## ⚠️ Common Issues and Solutions

### Prerequisites

<details>

<summary>Build Errors</summary>1. Install MSYS2:

   - Download the installer from https://www.msys2.org/

- **Issue**: Missing GLFW   - Run the installer and follow the prompts

  - 🔧 Run `setup_gui.ps1` again   - After installation, open "MSYS2 MinGW 64-bit" from the Start menu

- **Issue**: Compilation fails

  - 🔧 Ensure MinGW-w64 is in PATH2. Update MSYS2 and install development tools:

  - 🔧 Update your compiler   ```bash

   # Update package database and core system packages

</details>   pacman -Syu

   # Close MSYS2 when prompted, then reopen and run:

<details>   pacman -Su

<summary>Runtime Errors</summary>   # Install development toolchain

   pacman -S --needed base-devel mingw-w64-x86_64-toolchain

- **Issue**: Can't open CSV file   ```

  - 🔧 Check file permissions

  - 🔧 Ensure `students.csv` exists3. Add MSYS2's MinGW64 bin directory to your system PATH:

- **Issue**: GUI not responding   - Open Windows Settings → System → About → Advanced System Settings

  - 🔧 Update graphics drivers   - Click "Environment Variables"

  - 🔧 Check system resources   - Under "User variables", select "Path" and click "Edit"

   - Click "New" and add: `C:\msys64\mingw64\bin`

</details>   - Click "OK" on all windows

   - Restart any open terminals/PowerShell windows

## 🤝 Contributing

### Building

1. Fork the repo

2. Create feature branch1. Regular build (with DLL dependencies):

3. Commit changes   ```powershell

4. Push to branch   .\build.bat

5. Open pull request   ```



## ❤️ Support the Project2. Static build (standalone exe, larger but no DLLs needed):

   ```powershell

If you find this project helpful, consider buying me a coffee!   .\build.bat --static

   ```

<a href="https://www.buymeacoffee.com/mwintelligence" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-red.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>

Notes on colors and Unicode

## 📝 License--------------------------

- The program enables Windows Virtual Terminal processing to allow ANSI color sequences on modern Windows 10+ consoles. If your console is old and doesn't support ANSI, output will still be readable but may include escape sequences.

This project is licensed under the MIT License - see the LICENSE file for details.- `chcp 65001` is used in the build script to set UTF-8 code page so Unicode box characters look better.



---Files added/edited

------------------

<div align="center">- `source.cpp` — main program (enhanced with stats, settings persistence, boxed menu, ANSI enable on Windows)

- `build.bat` — simple Windows build script using g++

Made with ❤️ by [Mwintellegince](https://github.com/Mwintellegince)- `README.md` — this file



![Visitors](https://api.visitorbadge.io/api/visitors?path=https%3A%2F%2Fgithub.com%2FMwintellegince%2FSTUDENT-MANAGEMENT-SYSTEM-V2&countColor=%23263759)Next steps / Suggested improvements

----------------------------------

</div>- Add unit tests for CSV parsing and RTF generation.
- Provide a GUI front-end using a lightweight framework (Dear ImGui + SDL2, or a simple Win32 GUI) for a richer UI.
- Add more robust CSV parsing (use a library) and UTF-8 handling for RTF.

If you'd like, I can:
- Try to compile the program here and run a smoke test (will attempt if you want me to), or
- Convert the program to a small GUI using Dear ImGui + GLFW/SDL,
- Or create an installer or a packaged .exe using tools like Inno Setup.

#