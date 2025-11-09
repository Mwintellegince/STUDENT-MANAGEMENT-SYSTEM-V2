# 🎓 Student Management System V2MWINTELLIGENCE Student Management System v3.0

==============================================

<div align="center">

  **Now Available in Two Editions:**

![Student Management System](https://readme-typing-svg.herokuapp.com?font=Fira+Code&size=30&duration=3000&pause=1000&color=F70000&center=true&vCenter=true&random=false&width=500&lines=Student+Management+System;Powered+by+C%2B%2B;Modern+and+Efficient)- 🖥️ **GUI Edition** - Modern desktop application with Dear ImGui (NEW!)

- 💻 **Console Edition** - Professional command-line interface

</div>

Quick Start - GUI Edition (Recommended)

## 🌟 Features----------------------------------------

1. **Setup**: `.\start_gui.bat` (downloads libraries and builds)

- 🎯 **Dual Interface**: Choose between GUI and CLI versions2. **Run**: `.\student_manager_gui.exe`

- 📊 **Student Data Management**: Add, edit, delete student records

- 🔍 **Advanced Search**: Find students by various criteriaSee [README_GUI.md](README_GUI.md) for complete GUI documentation.

- 💾 **Auto Backup**: Automatic CSV backup system

- 📈 **Performance**: Built with optimized C++ code---

- 🎨 **Modern UI**: ImGui-based graphical interface

Student GPA Manager v3.0 - Console Edition

## 🚀 Quick Start===========================================



### Prerequisites**Build & Run on Windows (MSYS2 / MinGW-w64 g++)**

- Windows OS

- MinGW-w64 with C++17 supportQuick Start

- GLFW and ImGui for GUI version-----------

1. **Build**: Terminal → Run Task → `Build (g++)`

### 🔧 Installation2. **Run**: `.\\student_manager.exe` in integrated terminal

3. **Build & Run**: Terminal → Run Task → `Build & Run (g++)`

1. **Clone the Repository**

```bashFeatures (14 Operations)

git clone https://github.com/Mwintellegince/STUDENT-MANAGEMENT-SYSTEM-V2.git------------------------

cd STUDENT-MANAGEMENT-SYSTEM-V2| # | Feature | Description |

```|---|---------|-------------|

| 1 | Add Student | Create new student with auto-generated unique ID, age, GPA, major |

2. **Setup Environment**| 2 | List Students | Display all students in formatted table (ID, Name, Age, GPA, Major) |

   - For GUI Version:| 3 | Search | Find by name or student ID (case-insensitive substring match) |

     ```powershell| 4 | Edit | Modify name, age, GPA, or major of existing student |

     # Run the setup script| 5 | Delete | Remove student by ID (with confirmation) |

     ./setup_gui.ps1| 6 | Sort | By name (A-Z), age, GPA ascending, or GPA descending |

     ```| 7 | Statistics | Show count, average GPA, median GPA, GPA/age ranges |

   - For CLI Version:| 8 | Filter by GPA | Range query (min/max GPA with validation) |

     ```powershell| 9 | Save CSV | Export all students to comma-separated file |

     # No additional setup needed| 10 | Load CSV | Import students from CSV with error recovery |

     ```| 11 | Export RTF | Generate Word-compatible rich text format report |

| 12 | Clear All | Bulk delete with "DELETE" confirmation |

3. **Build the Project**| 13 | Duplicate Check | Find duplicate names (case-insensitive) with counts |

   - GUI Version:| 14 | GPA Analysis | Visual distribution histogram (ASCII asterisks) |

     ```powershell

     ./build_gui.batEnhanced Code Features

     ```----------------------

   - CLI Version:- **Unique IDs**: Auto-generated from student name (e.g., "john", "john1", "john2")

     ```powershell- **Input Validation**: Age 5-120, GPA 0.0-4.0, non-empty names

     ./build.bat- **Robust I/O**: CSV parsing with quoted fields, UTF-8 support

     ```- **Sorting**: Multiple criteria (name, age, GPA asc/desc)

- **Color Output**: ANSI codes for Windows 10+ (cyan, yellow, green, red, magenta)

4. **Run the Application**- **Case-Insensitive Search**: Works with name and ID fields

   - GUI Version:- **Error Handling**: Try-catch for file I/O and CSV parsing

     ```powershell

     ./start_gui.batBuild Instructions

     ```-------------------

   - CLI Version:- **Compiler**: g++ (MSYS2 mingw64, v15.2.0+)

     ```powershell- **Standard**: C++17

     ./student_manager.exe- **Command**: 

     ```  ```bash

  g++ -std=c++17 -O2 -pipe source.cpp -o student_manager.exe

## 💫 Usage  ```



### GUI VersionRunning the Program

<details>-------------------

<summary>Click to expand!</summary>**In VS Code Integrated Terminal:**

```powershell

1. 🖱️ Launch the application using `start_gui.bat`cd "C:\Users\<YourName>\Documents\New folder"

2. 📝 Use the top menu to navigate between features.\student_manager.exe

3. ➕ Add students using the "Add Student" form```

4. 🔍 Search using the search bar

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