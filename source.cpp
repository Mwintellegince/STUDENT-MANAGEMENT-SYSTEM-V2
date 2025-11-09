#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <cctype>
#include <cmath>
#include <map>
#include <unordered_map>
#include <set>
#include <random>
#include <regex>
#include <filesystem>
#include <ctime>

#if defined(_WIN32)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

using namespace std;
namespace fs = std::filesystem;

// Advanced Color System
const string COL_RESET = "\x1B[0m";
const string COL_Header = "\x1B[1;36m";
const string COL_Menu = "\x1B[1;33m";
const string COL_Prompt = "\x1B[1;32m";
const string COL_Error = "\x1B[1;31m";
const string COL_Info = "\x1B[1;35m";
const string COL_Success = "\x1B[1;32m";
const string COL_Warning = "\x1B[1;93m";
const string COL_Accent = "\x1B[1;34m";
const string COL_Data = "\x1B[37m";
const string COL_Critical = "\x1B[5;31m";

// Advanced Student Structure with Metadata
struct Student {
    string id;
    string name;
    int age;
    double gpa;
    string major;
    string email;
    string phone;
    string address;
    string enrollmentDate;
    string lastModified;
    vector<string> courses;
    map<string, double> courseGrades;
    string academicStatus; // Active, Probation, Honor Roll, Graduated
    double totalCredits;
    string advisor;
    string notes;
    
    // Advanced calculated fields
    double getWeightedGPA() const {
        if (courseGrades.empty()) return gpa;
        double sum = 0, credits = 0;
        for (const auto& grade : courseGrades) {
            sum += grade.second * 3.0; // Assume 3 credits per course
            credits += 3.0;
        }
        return credits > 0 ? sum / credits : gpa;
    }
    
    string getDisplayStatus() const {
        if (gpa >= 3.8) return "Honor Roll";
        else if (gpa < 2.0) return "Academic Probation";
        else if (gpa >= 3.5) return "Dean's List";
        else return academicStatus;
    }
};

// Advanced System Configuration
struct SystemConfig {
    bool enableAutoBackup = true;
    int maxBackupFiles = 10;
    bool enableLogging = true;
    bool enableDataValidation = true;
    bool enableAdvancedSearch = true;
    string defaultExportFormat = "CSV";
    int maxStudents = 10000;
    bool enableEncryption = false;
};

SystemConfig config;

// Advanced Utility Functions
void enableConsoleVT() {
#if defined(_WIN32)
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string getCurrentTimestamp() {
    auto now = chrono::system_clock::now();
    auto time_t = chrono::system_clock::to_time_t(now);
    stringstream ss;
    ss << put_time(localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

string generateSecureID(const string& name) {
    string baseID = name;
    baseID.erase(remove_if(baseID.begin(), baseID.end(), [](char c) { 
        return !isalnum(c); 
    }), baseID.end());
    transform(baseID.begin(), baseID.end(), baseID.begin(), ::tolower);
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1000, 9999);
    
    return baseID + to_string(dis(gen));
}

bool validateEmail(const string& email) {
    regex emailPattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return regex_match(email, emailPattern);
}

bool validatePhone(const string& phone) {
    regex phonePattern(R"(\+?[1-9]\d{1,14})");
    return regex_match(phone, phonePattern);
}

string toLower(const string& s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}
qw
string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

void logActivity(const string& activity) {
    if (!config.enableLogging) return;
    ofstream log("system.log", ios::app);
    if (log.is_open()) {
        log << "[" << getCurrentTimestamp() << "] " << activity << "\n";
        log.close();
    }
}

void createBackup(const vector<Student>& db) {
    if (!config.enableAutoBackup) return;
    
    string timestamp = getCurrentTimestamp();
    replace(timestamp.begin(), timestamp.end(), ':', '-');
    replace(timestamp.begin(), timestamp.end(), ' ', '_');
    
    string backupFile = "backup_" + timestamp + ".csv";
    
    ofstream out(backupFile);
    if (out.is_open()) {
        out << "id,name,age,gpa,major,email,phone,address,enrollmentDate,totalCredits,advisor,status,notes\n";
        for (const auto& s : db) {
            out << s.id << ",\"" << s.name << "\"," << s.age << "," 
                << fixed << setprecision(2) << s.gpa << ",\"" << s.major 
                << "\",\"" << s.email << "\",\"" << s.phone << "\",\"" 
                << s.address << "\",\"" << s.enrollmentDate << "\"," 
                << s.totalCredits << ",\"" << s.advisor << "\",\"" 
                << s.academicStatus << "\",\"" << s.notes << "\"\n";
        }
        out.close();
        logActivity("Backup created: " + backupFile);
    }
}

// Advanced Animation and UI
void typewriterEffect(const string& text, int delayMs = 30) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delayMs));
    }
}

void progressBar(const string& task, int steps = 20) {
    cout << COL_Info << task << " [";
    for (int i = 0; i <= steps; ++i) {
        cout << "\r" << COL_Info << task << " [";
        for (int j = 0; j < i; ++j) cout << "#";
        for (int j = i; j < steps; ++j) cout << ".";
        cout << "] " << (i * 100 / steps) << "%" << flush;
        this_thread::sleep_for(chrono::milliseconds(30));
    }
    cout << "\r" << COL_Info << task << " [";
    for (int j = 0; j < steps; ++j) cout << "#";
    cout << "] 100% " << COL_Success << "Complete!" << COL_RESET << "\n";
}

void drawAdvancedHeader() {
    cout << COL_Header;
    cout << "\n\n";
    cout << "============================================================\n";
    cout << "          MWINTELLIGENCE STUDENT MANAGEMENT SYSTEM\n";
    cout << "                    ENTERPRISE EDITION v3.0\n";
    cout << "============================================================\n";
    cout << COL_RESET;
    
    cout << COL_Accent << "\n    [*] Professional Academic Database Management\n";
    cout << COL_Info << "    [*] Build 2025.10.24 | Advanced Analytics Engine\n" << COL_RESET;
    cout << "\n";
}

void drawMainMenu() {
    cout << "\n" << COL_Menu;
    cout << "============================================================\n";
    cout << "                  [*] MAIN CONTROL PANEL\n";
    cout << "============================================================\n\n";
    
    cout << COL_Accent << "  [*] STUDENT MANAGEMENT\n" << COL_RESET;
    cout << "      [1] Add Student              [2] List All Students\n";
    cout << "      [3] Advanced Search          [4] Edit Student Profile\n";
    cout << "      [5] Delete Student           [6] Bulk Operations\n\n";
    
    cout << COL_Accent << "  [*] ANALYTICS & REPORTS\n" << COL_RESET;
    cout << "      [7] Academic Statistics      [8] GPA Analysis & Trends\n";
    cout << "      [9] Grade Distribution       [10] Performance Reports\n\n";
    
    cout << COL_Accent << "  [*] DATA MANAGEMENT\n" << COL_RESET;
    cout << "      [11] Export Manager          [12] Import Data\n";
    cout << "      [13] Backup & Restore        [14] Data Validation\n\n";
    
    cout << COL_Accent << "  [*] ADVANCED TOOLS\n" << COL_RESET;
    cout << "      [15] Course Management       [16] Academic Advisor Tools\n";
    cout << "      [17] System Settings         [18] Data Integrity Check\n\n";
    
    cout << COL_Error << "      [0] Exit System\n" << COL_RESET;
    cout << COL_Menu << "============================================================\n";
    cout << COL_RESET;
}

// Advanced Input Functions
string promptLine(const string& label, bool allowEmpty = false, const string& defaultValue = "") {
    while (true) {
        cout << COL_Prompt << label;
        if (!defaultValue.empty()) cout << " [" << defaultValue << "]";
        cout << ": " << COL_RESET;
        
        string input;
        getline(cin, input);
        input = trim(input);
        
        if (input.empty() && !defaultValue.empty()) return defaultValue;
        if (!input.empty() || allowEmpty) return input;
        
        cout << COL_Error << " This field cannot be empty. Please try again.\n" << COL_RESET;
    }
}

int promptInt(const string& label, int minVal = INT_MIN, int maxVal = INT_MAX, int defaultValue = 0) {
    while (true) {
        cout << COL_Prompt << label;
        if (defaultValue != 0) cout << " [" << defaultValue << "]";
        cout << " (" << minVal << "-" << maxVal << "): " << COL_RESET;
        
        string input;
        getline(cin, input);
        input = trim(input);
        
        if (input.empty() && defaultValue != 0) return defaultValue;
        
        try {
            int value = stoi(input);
            if (value >= minVal && value <= maxVal) return value;
            cout << COL_Error << " Value must be between " << minVal << " and " << maxVal << "\n" << COL_RESET;
        } catch (...) {
            cout << COL_Error << " Please enter a valid number.\n" << COL_RESET;
        }
    }
}

double promptDouble(const string& label, double minVal = 0.0, double maxVal = 4.0, double defaultValue = 0.0) {
    while (true) {
        cout << COL_Prompt << label;
        if (defaultValue != 0.0) cout << " [" << fixed << setprecision(2) << defaultValue << "]";
        cout << " (" << minVal << "-" << maxVal << "): " << COL_RESET;
        
        string input;
        getline(cin, input);
        input = trim(input);
        
        if (input.empty() && defaultValue != 0.0) return defaultValue;
        
        try {
            double value = stod(input);
            if (value >= minVal && value <= maxVal) return value;
            cout << COL_Error << " Value must be between " << minVal << " and " << maxVal << "\n" << COL_RESET;
        } catch (...) {
            cout << COL_Error << " Please enter a valid number.\n" << COL_RESET;
        }
    }
}

// Advanced Student Management Functions
void addAdvancedStudent(vector<Student>& db) {
    cout << "\n" << COL_Header;
    cout << "============================================================\n";
    cout << "                   ADD NEW STUDENT\n";
    cout << "============================================================\n\n" << COL_RESET;
    
    if (db.size() >= config.maxStudents) {
        cout << COL_Error << "    [!] Maximum student limit reached (" << config.maxStudents << ")\n\n" << COL_RESET;
        return;
    }
    
    Student s;
    
    cout << COL_Info << "  [*] PERSONAL INFORMATION\n" << COL_RESET;
    s.name = promptLine("      Full Name");
    s.id = generateSecureID(s.name);
    s.age = promptInt("      Age", 16, 120);
    
    cout << "\n" << COL_Info << "  [*] ACADEMIC INFORMATION\n" << COL_RESET;
    s.gpa = promptDouble("      Current GPA", 0.0, 4.0);
    s.major = promptLine("      Major/Program", false, "Undeclared");
    s.totalCredits = promptDouble("      Total Credits", 0.0, 200.0, 0.0);
    s.enrollmentDate = promptLine("      Enrollment Date (YYYY-MM-DD)", false, getCurrentTimestamp().substr(0, 10));
    s.advisor = promptLine("      Academic Advisor", true);
    
    cout << "\n" << COL_Info << "  [*] CONTACT INFORMATION\n" << COL_RESET;
    while (true) {
        s.email = promptLine("      Email Address", true);
        if (s.email.empty() || validateEmail(s.email)) break;
        cout << COL_Error << "      [!] Invalid email format. Please try again.\n" << COL_RESET;
    }
    
    while (true) {
        s.phone = promptLine("      Phone Number", true);
        if (s.phone.empty() || validatePhone(s.phone)) break;
        cout << COL_Error << "      [!] Invalid phone format. Please try again.\n" << COL_RESET;
    }
    
    s.address = promptLine("      Address", true);
    
    cout << "\n" << COL_Info << "  [*] ADDITIONAL NOTES\n" << COL_RESET;
    s.notes = promptLine("      Notes", true);
    
    s.academicStatus = "Active";
    s.lastModified = getCurrentTimestamp();
    
    db.push_back(s);
    createBackup(db);
    logActivity("Added student: " + s.name + " (ID: " + s.id + ")");
    
    cout << "\n" << COL_Success << "  [+] STUDENT SUCCESSFULLY ADDED!\n" << COL_RESET;
    cout << COL_Menu << "  ============================================================\n";
    cout << COL_Info << "    Generated ID: " << COL_Accent << s.id << COL_RESET << "\n";
    cout << COL_Info << "    Name: " << s.name << "\n";
    cout << COL_Info << "    Email: " << s.email << "\n";
    cout << COL_Info << "    Phone: " << s.phone << "\n";
    cout << COL_Menu << "  ============================================================\n\n" << COL_RESET;
}

void listAdvancedStudents(const vector<Student>& db) {
    cout << "\n" << COL_Header;
    cout << "============================================================\n";
    cout << "                    STUDENT REGISTRY\n";
    cout << "============================================================\n\n" << COL_RESET;
    
    if (db.empty()) {
        cout << COL_Info << "    [!] No students in database.\n\n" << COL_RESET;
        return;
    }
    
    cout << COL_Menu;
    cout << left << setw(15) << "  ID" << setw(28) << "Name" << setw(6) << "Age" 
         << setw(8) << "GPA" << setw(22) << "Major" << setw(28) << "Email" 
         << setw(18) << "Phone" << "Status" << '\n';
    cout << "  " << string(140, '-') << "\n" << COL_RESET;
    
    for (const auto& s : db) {
        string status = s.getDisplayStatus();
        string statusColor = (status == "Honor Roll") ? COL_Success : 
                           (status == "Academic Probation") ? COL_Error : COL_Info;
        
        cout << COL_Data << "  " << left << setw(15) << s.id << setw(28) << s.name.substr(0, 27) 
             << setw(6) << s.age << fixed << setprecision(2) << setw(8) << s.gpa 
             << setw(22) << s.major.substr(0, 21) << setw(28) << s.email.substr(0, 27)
             << setw(18) << s.phone.substr(0, 17);
        cout << statusColor << status << COL_RESET << '\n';
    }
    
    cout << "\n" << COL_Menu << "  " << string(140, '-') << "\n";
    cout << COL_Info << "  [*] Total Students: " << db.size() 
         << "  |  Database Size: " << (db.size() * sizeof(Student) / 1024) << " KB\n";
    cout << COL_Menu << "============================================================\n\n" << COL_RESET;
}

void editStudent(vector<Student>& db) {
    cout << COL_Menu << "\n[*] EDIT STUDENT PROFILE\n" << COL_RESET;
    
    if (db.empty()) {
        cout << COL_Info << "[!] No students in database.\n" << COL_RESET;
        return;
    }
    
    string id = promptLine("[>] Student ID");
    
    for (auto& s : db) {
        if (s.id == id) {
            cout << "\n[*] Current Data:\n";
            cout << "  Name: " << s.name << "\n";
            cout << "  Age: " << s.age << "\n";
            cout << "  GPA: " << fixed << setprecision(2) << s.gpa << "\n";
            cout << "  Major: " << s.major << "\n";
            cout << "  Email: " << s.email << "\n";
            cout << "  Phone: " << s.phone << "\n\n";
            
            cout << COL_Menu << "[1] Name  [2] Age  [3] GPA  [4] Major  [5] Email  [6] Phone  [0] Cancel\n" << COL_RESET;
            string choice = promptLine("[>] Select field to edit");
            
            if (choice == "1") s.name = promptLine("[>] New name");
            else if (choice == "2") s.age = promptInt("[>] New age", 16, 120);
            else if (choice == "3") s.gpa = promptDouble("[>] New GPA", 0.0, 4.0);
            else if (choice == "4") s.major = promptLine("[>] New major");
            else if (choice == "5") {
                while (true) {
                    s.email = promptLine("[>] New email", true);
                    if (s.email.empty() || validateEmail(s.email)) break;
                    cout << COL_Error << "[!] Invalid email format.\n" << COL_RESET;
                }
            }
            else if (choice == "6") {
                while (true) {
                    s.phone = promptLine("[>] New phone", true);
                    if (s.phone.empty() || validatePhone(s.phone)) break;
                    cout << COL_Error << "[!] Invalid phone format.\n" << COL_RESET;
                }
            }
            else if (choice == "0") {
                cout << COL_Info << "[!] Edit canceled.\n" << COL_RESET;
                return;
            }
            
            s.lastModified = getCurrentTimestamp();
            createBackup(db);
            logActivity("Edited student: " + s.name + " (ID: " + s.id + ")");
            cout << COL_Success << "[+] Student updated successfully!\n" << COL_RESET;
            return;
        }
    }
    cout << COL_Error << "[!] Student ID not found.\n" << COL_RESET;
}

void deleteStudent(vector<Student>& db) {
    cout << COL_Menu << "\n[*] DELETE STUDENT\n" << COL_RESET;
    
    if (db.empty()) {
        cout << COL_Info << "[!] No students in database.\n" << COL_RESET;
        return;
    }
    
    string id = promptLine("[>] Student ID to delete");
    
    for (size_t i = 0; i < db.size(); ++i) {
        if (db[i].id == id) {
            cout << "\n[*] Student Found:\n";
            cout << "  Name: " << db[i].name << "\n";
            cout << "  Age: " << db[i].age << "\n";
            cout << "  GPA: " << fixed << setprecision(2) << db[i].gpa << "\n\n";
            
            string confirm = promptLine("[!] Type 'DELETE' to confirm");
            if (confirm == "DELETE") {
                string name = db[i].name;
                db.erase(db.begin() + i);
                createBackup(db);
                logActivity("Deleted student: " + name + " (ID: " + id + ")");
                cout << COL_Success << "[+] Student deleted successfully!\n" << COL_RESET;
            } else {
                cout << COL_Info << "[!] Deletion canceled.\n" << COL_RESET;
            }
            return;
        }
    }
    cout << COL_Error << "[!] Student ID not found.\n" << COL_RESET;
}

void bulkOperations(vector<Student>& db) {
    cout << COL_Menu << "\n[*] BULK OPERATIONS\n" << COL_RESET;
    cout << "[1] Sort by Name   [2] Sort by GPA   [3] Sort by Age\n";
    cout << "[4] Delete by GPA Range   [5] Update Major for All\n";
    cout << "[0] Cancel\n";
    
    string choice = promptLine("[>] Select operation");
    
    if (choice == "1") {
        sort(db.begin(), db.end(), [](const Student& a, const Student& b) {
            return toLower(a.name) < toLower(b.name);
        });
        cout << COL_Success << "[+] Sorted by name (A-Z).\n" << COL_RESET;
    }
    else if (choice == "2") {
        sort(db.begin(), db.end(), [](const Student& a, const Student& b) {
            return a.gpa > b.gpa;
        });
        cout << COL_Success << "[+] Sorted by GPA (highest first).\n" << COL_RESET;
    }
    else if (choice == "3") {
        sort(db.begin(), db.end(), [](const Student& a, const Student& b) {
            return a.age < b.age;
        });
        cout << COL_Success << "[+] Sorted by age (youngest first).\n" << COL_RESET;
    }
    else if (choice == "4") {
        double minGPA = promptDouble("[>] Minimum GPA", 0.0, 4.0);
        double maxGPA = promptDouble("[>] Maximum GPA", minGPA, 4.0);
        
        auto it = remove_if(db.begin(), db.end(), [minGPA, maxGPA](const Student& s) {
            return s.gpa >= minGPA && s.gpa <= maxGPA;
        });
        
        int count = distance(it, db.end());
        if (count > 0) {
            string confirm = promptLine("[!] Delete " + to_string(count) + " student(s)? Type 'YES'");
            if (confirm == "YES") {
                db.erase(it, db.end());
                createBackup(db);
                cout << COL_Success << "[+] Deleted " << count << " student(s).\n" << COL_RESET;
            } else {
                cout << COL_Info << "[!] Operation canceled.\n" << COL_RESET;
            }
        } else {
            cout << COL_Info << "[!] No students in that GPA range.\n" << COL_RESET;
        }
    }
    else if (choice == "5") {
        string newMajor = promptLine("[>] New major for all students");
        for (auto& s : db) {
            s.major = newMajor;
            s.lastModified = getCurrentTimestamp();
        }
        createBackup(db);
        cout << COL_Success << "[+] Updated major for " << db.size() << " student(s).\n" << COL_RESET;
    }
}

void academicStatistics(const vector<Student>& db) {
    cout << COL_Menu << "\n[*] ACADEMIC STATISTICS\n" << COL_RESET;
    
    if (db.empty()) {
        cout << COL_Info << "[!] No students in database.\n" << COL_RESET;
        return;
    }
    
    double sumGPA = 0, minGPA = 4.0, maxGPA = 0.0;
    int minAge = 120, maxAge = 0;
    map<string, int> majorCount;
    int honors = 0, probation = 0;
    
    for (const auto& s : db) {
        sumGPA += s.gpa;
        minGPA = min(minGPA, s.gpa);
        maxGPA = max(maxGPA, s.gpa);
        minAge = min(minAge, s.age);
        maxAge = max(maxAge, s.age);
        majorCount[s.major]++;
        
        if (s.gpa >= 3.8) honors++;
        else if (s.gpa < 2.0) probation++;
    }
    
    double avgGPA = sumGPA / db.size();
    
    cout << "\n" << COL_Info << "[*] OVERALL STATISTICS:\n" << COL_RESET;
    cout << "  Total Students: " << db.size() << "\n";
    cout << "  Average GPA: " << fixed << setprecision(3) << avgGPA << "\n";
    cout << "  GPA Range: " << setprecision(2) << minGPA << " - " << maxGPA << "\n";
    cout << "  Age Range: " << minAge << " - " << maxAge << " years\n";
    cout << "  Honor Roll (GPA >= 3.8): " << honors << " (" << (honors*100/db.size()) << "%)\n";
    cout << "  Academic Probation (GPA < 2.0): " << probation << " (" << (probation*100/db.size()) << "%)\n";
    
    cout << "\n" << COL_Info << "[*] STUDENTS BY MAJOR:\n" << COL_RESET;
    for (const auto& pair : majorCount) {
        cout << "  " << pair.first << ": " << pair.second << " student(s)\n";
    }
}

void gpaAnalysisTrends(const vector<Student>& db) {
    cout << COL_Menu << "\n[*] GPA ANALYSIS & TRENDS\n" << COL_RESET;
    
    if (db.empty()) {
        cout << COL_Info << "[!] No students in database.\n" << COL_RESET;
        return;
    }
    
    map<string, int> distribution;
    distribution["4.0 (Perfect)"] = 0;
    distribution["3.5-3.9 (Excellent)"] = 0;
    distribution["3.0-3.4 (Good)"] = 0;
    distribution["2.5-2.9 (Satisfactory)"] = 0;
    distribution["2.0-2.4 (Below Average)"] = 0;
    distribution["<2.0 (Failing)"] = 0;
    
    for (const auto& s : db) {
        if (s.gpa == 4.0) distribution["4.0 (Perfect)"]++;
        else if (s.gpa >= 3.5) distribution["3.5-3.9 (Excellent)"]++;
        else if (s.gpa >= 3.0) distribution["3.0-3.4 (Good)"]++;
        else if (s.gpa >= 2.5) distribution["2.5-2.9 (Satisfactory)"]++;
        else if (s.gpa >= 2.0) distribution["2.0-2.4 (Below Average)"]++;
        else distribution["<2.0 (Failing)"]++;
    }
    
    cout << "\n" << COL_Info << "[*] GPA DISTRIBUTION:\n" << COL_RESET;
    for (const auto& pair : distribution) {
        if (pair.second > 0) {
            int percentage = (pair.second * 100) / db.size();
            cout << "  " << left << setw(25) << pair.first << ": " 
                 << string(pair.second, '#') << " " << pair.second 
                 << " (" << percentage << "%)\n";
        }
    }
    
    // Top performers
    vector<Student> sorted = db;
    sort(sorted.begin(), sorted.end(), [](const Student& a, const Student& b) {
        return a.gpa > b.gpa;
    });
    
    cout << "\n" << COL_Success << "[*] TOP 5 PERFORMERS:\n" << COL_RESET;
    for (size_t i = 0; i < min(size_t(5), sorted.size()); ++i) {
        cout << "  " << (i+1) << ". " << sorted[i].name << " - GPA: " 
             << fixed << setprecision(2) << sorted[i].gpa << "\n";
    }
}

void gradeDistribution(const vector<Student>& db) {
    cout << COL_Menu << "\n[*] GRADE DISTRIBUTION\n" << COL_RESET;
    
    if (db.empty()) {
        cout << COL_Info << "[!] No students in database.\n" << COL_RESET;
        return;
    }
    
    map<string, vector<const Student*>> grades;
    grades["A (3.7-4.0)"] = {};
    grades["B (2.7-3.6)"] = {};
    grades["C (1.7-2.6)"] = {};
    grades["D (1.0-1.6)"] = {};
    grades["F (<1.0)"] = {};
    
    for (const auto& s : db) {
        if (s.gpa >= 3.7) grades["A (3.7-4.0)"].push_back(&s);
        else if (s.gpa >= 2.7) grades["B (2.7-3.6)"].push_back(&s);
        else if (s.gpa >= 1.7) grades["C (1.7-2.6)"].push_back(&s);
        else if (s.gpa >= 1.0) grades["D (1.0-1.6)"].push_back(&s);
        else grades["F (<1.0)"].push_back(&s);
    }
    
    cout << "\n" << COL_Info << "[*] LETTER GRADE DISTRIBUTION:\n" << COL_RESET;
    for (const auto& pair : grades) {
        int count = pair.second.size();
        if (count > 0) {
            int percentage = (count * 100) / db.size();
            cout << "\n  " << COL_Menu << pair.first << COL_RESET << ": " << count 
                 << " student(s) (" << percentage << "%)\n";
            for (const auto* sp : pair.second) {
                cout << "    - " << sp->name << " (GPA: " << fixed << setprecision(2) 
                     << sp->gpa << ")\n";
            }
        }
    }
}

void performanceReports(const vector<Student>& db) {
    cout << COL_Menu << "\n[*] PERFORMANCE REPORTS\n" << COL_RESET;
    
    if (db.empty()) {
        cout << COL_Info << "[!] No students in database.\n" << COL_RESET;
        return;
    }
    
    cout << "[1] Individual Report   [2] Major Comparison   [3] Age Group Analysis\n";
    string choice = promptLine("[>] Select report type");
    
    if (choice == "1") {
        string id = promptLine("[>] Student ID");
        for (const auto& s : db) {
            if (s.id == id) {
                cout << "\n" << COL_Info << "========== STUDENT PERFORMANCE REPORT ==========\n" << COL_RESET;
                cout << "  ID: " << s.id << "\n";
                cout << "  Name: " << s.name << "\n";
                cout << "  Age: " << s.age << " years\n";
                cout << "  Major: " << s.major << "\n";
                cout << "  GPA: " << fixed << setprecision(2) << s.gpa << "/4.0\n";
                cout << "  Status: " << s.getDisplayStatus() << "\n";
                cout << "  Total Credits: " << s.totalCredits << "\n";
                cout << "  Advisor: " << (s.advisor.empty() ? "Not assigned" : s.advisor) << "\n";
                cout << "  Enrolled: " << s.enrollmentDate << "\n";
                cout << "  Last Modified: " << s.lastModified << "\n";
                
                // Calculate percentile
                int rank = 1;
                for (const auto& other : db) {
                    if (other.gpa > s.gpa) rank++;
                }
                int percentile = 100 - ((rank * 100) / db.size());
                cout << "  Class Rank: " << rank << " of " << db.size() 
                     << " (" << percentile << "th percentile)\n";
                
                cout << "\n  Notes: " << (s.notes.empty() ? "None" : s.notes) << "\n";
                cout << "================================================\n";
                return;
            }
        }
        cout << COL_Error << "[!] Student not found.\n" << COL_RESET;
    }
    else if (choice == "2") {
        map<string, vector<double>> majorGPAs;
        for (const auto& s : db) {
            majorGPAs[s.major].push_back(s.gpa);
        }
        
        cout << "\n" << COL_Info << "[*] PERFORMANCE BY MAJOR:\n" << COL_RESET;
        for (const auto& pair : majorGPAs) {
            double sum = 0;
            for (double gpa : pair.second) sum += gpa;
            double avg = sum / pair.second.size();
            
            cout << "  " << pair.first << ":\n";
            cout << "    Students: " << pair.second.size() << "\n";
            cout << "    Average GPA: " << fixed << setprecision(2) << avg << "\n";
        }
    }
    else if (choice == "3") {
        map<string, vector<double>> ageGroups;
        for (const auto& s : db) {
            string group;
            if (s.age < 20) group = "Under 20";
            else if (s.age < 25) group = "20-24";
            else if (s.age < 30) group = "25-29";
            else group = "30+";
            ageGroups[group].push_back(s.gpa);
        }
        
        cout << "\n" << COL_Info << "[*] PERFORMANCE BY AGE GROUP:\n" << COL_RESET;
        for (const auto& pair : ageGroups) {
            double sum = 0;
            for (double gpa : pair.second) sum += gpa;
            double avg = sum / pair.second.size();
            
            cout << "  " << pair.first << " years:\n";
            cout << "    Students: " << pair.second.size() << "\n";
            cout << "    Average GPA: " << fixed << setprecision(2) << avg << "\n";
        }
    }
}

void importData(vector<Student>& db) {
    cout << COL_Menu << "\n[*] IMPORT DATA\n" << COL_RESET;
    
    string filename = promptLine("[>] CSV filename", false, "students.csv");
    
    ifstream in(filename);
    if (!in) {
        cout << COL_Error << "[!] File not found: " << filename << "\n" << COL_RESET;
        return;
    }
    
    int imported = 0, errors = 0;
    string line;
    getline(in, line); // Skip header
    
    while (getline(in, line)) {
        if (line.empty()) continue;
        
        try {
            stringstream ss(line);
            string id, name, ageStr, gpaStr, major, email, phone, address, enrollDate;
            string credits, advisor, status, notes;
            
            getline(ss, id, ',');
            getline(ss, name, ',');
            if (!name.empty() && name[0] == '"') name = name.substr(1, name.size()-2);
            getline(ss, ageStr, ',');
            getline(ss, gpaStr, ',');
            getline(ss, major, ',');
            if (!major.empty() && major[0] == '"') major = major.substr(1, major.size()-2);
            
            Student s;
            s.id = id;
            s.name = name;
            s.age = stoi(ageStr);
            s.gpa = stod(gpaStr);
            s.major = major;
            s.academicStatus = "Active";
            s.enrollmentDate = getCurrentTimestamp().substr(0, 10);
            s.lastModified = getCurrentTimestamp();
            s.totalCredits = 0;
            
            db.push_back(s);
            imported++;
        } catch (...) {
            errors++;
        }
    }
    
    in.close();
    createBackup(db);
    logActivity("Imported " + to_string(imported) + " students from " + filename);
    
    cout << COL_Success << "[+] Import complete!\n";
    cout << "  Imported: " << imported << " student(s)\n";
    if (errors > 0) {
        cout << COL_Warning << "  Errors: " << errors << " row(s) skipped\n" << COL_RESET;
    }
}

void backupRestore(vector<Student>& db) {
    cout << COL_Menu << "\n[*] BACKUP & RESTORE\n" << COL_RESET;
    cout << "[1] Create Backup   [2] Restore from Backup   [3] List Backups\n";
    
    string choice = promptLine("[>] Select option");
    
    if (choice == "1") {
        createBackup(db);
        cout << COL_Success << "[+] Backup created successfully!\n" << COL_RESET;
    }
    else if (choice == "2") {
        string filename = promptLine("[>] Backup filename");
        
        ifstream test(filename);
        if (!test) {
            cout << COL_Error << "[!] Backup file not found.\n" << COL_RESET;
            return;
        }
        test.close();
        
        string confirm = promptLine("[!] This will replace current data. Type 'RESTORE'");
        if (confirm == "RESTORE") {
            vector<Student> temp;
            ifstream in(filename);
            string line;
            getline(in, line); // Skip header
            
            while (getline(in, line)) {
                if (line.empty()) continue;
                try {
                    stringstream ss(line);
                    string id, name, ageStr, gpaStr, major, email, phone, address;
                    
                    getline(ss, id, ',');
                    getline(ss, name, ',');
                    if (!name.empty() && name[0] == '"') name = name.substr(1, name.size()-2);
                    getline(ss, ageStr, ',');
                    getline(ss, gpaStr, ',');
                    getline(ss, major, ',');
                    if (!major.empty() && major[0] == '"') major = major.substr(1, major.size()-2);
                    
                    Student s;
                    s.id = id;
                    s.name = name;
                    s.age = stoi(ageStr);
                    s.gpa = stod(gpaStr);
                    s.major = major;
                    s.academicStatus = "Active";
                    s.enrollmentDate = getCurrentTimestamp().substr(0, 10);
                    s.lastModified = getCurrentTimestamp();
                    
                    temp.push_back(s);
                } catch (...) {}
            }
            
            db = temp;
            logActivity("Restored from backup: " + filename);
            cout << COL_Success << "[+] Restored " << db.size() << " student(s) from backup.\n" << COL_RESET;
        }
    }
    else if (choice == "3") {
        cout << "\n" << COL_Info << "[*] Available backup files:\n" << COL_RESET;
        system("dir /b backup_*.csv 2>nul");
    }
}

void dataValidation(vector<Student>& db) {
    cout << COL_Menu << "\n[*] DATA VALIDATION\n" << COL_RESET;
    
    int issues = 0;
    vector<string> errors;
    
    for (const auto& s : db) {
        if (s.name.empty()) {
            errors.push_back("Empty name for ID: " + s.id);
            issues++;
        }
        if (s.age < 16 || s.age > 120) {
            errors.push_back("Invalid age (" + to_string(s.age) + ") for: " + s.name);
            issues++;
        }
        if (s.gpa < 0.0 || s.gpa > 4.0) {
            errors.push_back("Invalid GPA (" + to_string(s.gpa) + ") for: " + s.name);
            issues++;
        }
        if (!s.email.empty() && !validateEmail(s.email)) {
            errors.push_back("Invalid email for: " + s.name);
            issues++;
        }
    }
    
    // Check for duplicate IDs
    set<string> ids;
    for (const auto& s : db) {
        if (ids.count(s.id)) {
            errors.push_back("Duplicate ID: " + s.id);
            issues++;
        }
        ids.insert(s.id);
    }
    
    if (issues == 0) {
        cout << COL_Success << "[+] All data is valid! No issues found.\n" << COL_RESET;
    } else {
        cout << COL_Warning << "[!] Found " << issues << " issue(s):\n" << COL_RESET;
        for (const auto& err : errors) {
            cout << "  - " << err << "\n";
        }
    }
}

void courseManagement(vector<Student>& db) {
    cout << COL_Menu << "\n[*] COURSE MANAGEMENT\n" << COL_RESET;
    
    string id = promptLine("[>] Student ID");
    
    for (auto& s : db) {
        if (s.id == id) {
            cout << "\n[*] Student: " << s.name << "\n";
            cout << "[1] Add Course   [2] View Courses   [3] Remove Course\n";
            
            string choice = promptLine("[>] Select option");
            
            if (choice == "1") {
                string course = promptLine("[>] Course name");
                double grade = promptDouble("[>] Course grade", 0.0, 4.0);
                s.courses.push_back(course);
                s.courseGrades[course] = grade;
                s.lastModified = getCurrentTimestamp();
                cout << COL_Success << "[+] Course added!\n" << COL_RESET;
            }
            else if (choice == "2") {
                if (s.courses.empty()) {
                    cout << COL_Info << "[!] No courses enrolled.\n" << COL_RESET;
                } else {
                    cout << "\n[*] Enrolled Courses:\n";
                    for (const auto& course : s.courses) {
                        cout << "  - " << course << ": " << fixed << setprecision(2) 
                             << s.courseGrades[course] << "\n";
                    }
                    cout << "  Weighted GPA: " << s.getWeightedGPA() << "\n";
                }
            }
            else if (choice == "3") {
                if (s.courses.empty()) {
                    cout << COL_Info << "[!] No courses to remove.\n" << COL_RESET;
                } else {
                    for (size_t i = 0; i < s.courses.size(); ++i) {
                        cout << "  [" << i << "] " << s.courses[i] << "\n";
                    }
                    int idx = promptInt("[>] Course index", 0, s.courses.size()-1);
                    string removed = s.courses[idx];
                    s.courses.erase(s.courses.begin() + idx);
                    s.courseGrades.erase(removed);
                    s.lastModified = getCurrentTimestamp();
                    cout << COL_Success << "[+] Course removed!\n" << COL_RESET;
                }
            }
            createBackup(db);
            return;
        }
    }
    cout << COL_Error << "[!] Student not found.\n" << COL_RESET;
}

void advisorTools(vector<Student>& db) {
    cout << COL_Menu << "\n[*] ACADEMIC ADVISOR TOOLS\n" << COL_RESET;
    cout << "[1] Assign Advisor   [2] View Students by Advisor   [3] At-Risk Students\n";
    
    string choice = promptLine("[>] Select option");
    
    if (choice == "1") {
        string id = promptLine("[>] Student ID");
        for (auto& s : db) {
            if (s.id == id) {
                s.advisor = promptLine("[>] Advisor name");
                s.lastModified = getCurrentTimestamp();
                createBackup(db);
                cout << COL_Success << "[+] Advisor assigned!\n" << COL_RESET;
                return;
            }
        }
        cout << COL_Error << "[!] Student not found.\n" << COL_RESET;
    }
    else if (choice == "2") {
        string advisor = promptLine("[>] Advisor name");
        cout << "\n[*] Students advised by " << advisor << ":\n";
        int count = 0;
        for (const auto& s : db) {
            if (s.advisor == advisor) {
                cout << "  - " << s.name << " (GPA: " << fixed << setprecision(2) 
                     << s.gpa << ", Status: " << s.getDisplayStatus() << ")\n";
                count++;
            }
        }
        if (count == 0) {
            cout << COL_Info << "[!] No students found for this advisor.\n" << COL_RESET;
        }
    }
    else if (choice == "3") {
        cout << "\n" << COL_Warning << "[!] AT-RISK STUDENTS (GPA < 2.0):\n" << COL_RESET;
        int count = 0;
        for (const auto& s : db) {
            if (s.gpa < 2.0) {
                cout << "  - " << s.name << " (GPA: " << fixed << setprecision(2) 
                     << s.gpa << ", Advisor: " << (s.advisor.empty() ? "None" : s.advisor) << ")\n";
                count++;
            }
        }
        if (count == 0) {
            cout << COL_Success << "[+] No at-risk students!\n" << COL_RESET;
        } else {
            cout << "\n  Total at-risk: " << count << " student(s)\n";
        }
    }
}

void systemSettings(SystemConfig& cfg) {
    cout << COL_Menu << "\n[*] SYSTEM SETTINGS\n" << COL_RESET;
    
    cout << "\n[*] Current Settings:\n";
    cout << "  [1] Auto Backup: " << (cfg.enableAutoBackup ? "ON" : "OFF") << "\n";
    cout << "  [2] Logging: " << (cfg.enableLogging ? "ON" : "OFF") << "\n";
    cout << "  [3] Data Validation: " << (cfg.enableDataValidation ? "ON" : "OFF") << "\n";
    cout << "  [4] Max Students: " << cfg.maxStudents << "\n";
    cout << "  [0] Back\n";
    
    string choice = promptLine("[>] Toggle setting");
    
    if (choice == "1") {
        cfg.enableAutoBackup = !cfg.enableAutoBackup;
        cout << COL_Success << "[+] Auto Backup: " << (cfg.enableAutoBackup ? "ON" : "OFF") << "\n" << COL_RESET;
    }
    else if (choice == "2") {
        cfg.enableLogging = !cfg.enableLogging;
        cout << COL_Success << "[+] Logging: " << (cfg.enableLogging ? "ON" : "OFF") << "\n" << COL_RESET;
    }
    else if (choice == "3") {
        cfg.enableDataValidation = !cfg.enableDataValidation;
        cout << COL_Success << "[+] Data Validation: " << (cfg.enableDataValidation ? "ON" : "OFF") << "\n" << COL_RESET;
    }
    else if (choice == "4") {
        cfg.maxStudents = promptInt("[>] Max students", 100, 100000);
        cout << COL_Success << "[+] Max students updated!\n" << COL_RESET;
    }
}

void dataIntegrityCheck(const vector<Student>& db) {
    cout << COL_Menu << "\n[*] DATA INTEGRITY CHECK\n" << COL_RESET;
    
    cout << "\n[*] Running comprehensive integrity check...\n\n";
    
    int total = db.size();
    int validEmails = 0, validPhones = 0, hasAdvisor = 0;
    set<string> uniqueIDs;
    
    for (const auto& s : db) {
        uniqueIDs.insert(s.id);
        if (!s.email.empty() && validateEmail(s.email)) validEmails++;
        if (!s.phone.empty() && validatePhone(s.phone)) validPhones++;
        if (!s.advisor.empty()) hasAdvisor++;
    }
    
    cout << COL_Info << "[*] INTEGRITY REPORT:\n" << COL_RESET;
    cout << "  Total Students: " << total << "\n";
    cout << "  Unique IDs: " << uniqueIDs.size() << " " 
         << (uniqueIDs.size() == total ? COL_Success + "[OK]" : COL_Error + "[DUPLICATES]") << COL_RESET << "\n";
    cout << "  Valid Emails: " << validEmails << "/" << total 
         << " (" << (total > 0 ? validEmails*100/total : 0) << "%)\n";
    cout << "  Valid Phones: " << validPhones << "/" << total 
         << " (" << (total > 0 ? validPhones*100/total : 0) << "%)\n";
    cout << "  Has Advisor: " << hasAdvisor << "/" << total 
         << " (" << (total > 0 ? hasAdvisor*100/total : 0) << "%)\n";
    
    double avgGPA = 0;
    for (const auto& s : db) avgGPA += s.gpa;
    if (total > 0) avgGPA /= total;
    
    cout << "  Average GPA: " << fixed << setprecision(2) << avgGPA << "/4.0\n";
    cout << "\n" << COL_Success << "[+] Integrity check complete!\n" << COL_RESET;
}

void advancedSearch(const vector<Student>& db) {
    cout << COL_Menu << "\n\n";
    cout << "                     ADVANCED SEARCH                        \n";
    cout << "\n" << COL_RESET;
    
    cout << COL_Accent << "\n Search Options:\n";
    cout << "[1] Name/ID Search    [2] GPA Range     [3] Major Filter\n";
    cout << "[4] Age Range         [5] Status Filter [6] Multi-criteria\n" << COL_RESET;
    
    string choice = promptLine("Select search type");
    vector<const Student*> results;
    
    if (choice == "1") {
        string query = toLower(promptLine(" Enter name or ID"));
        for (const auto& s : db) {
            if (toLower(s.name).find(query) != string::npos || 
                toLower(s.id).find(query) != string::npos) {
                results.push_back(&s);
            }
        }
    }
    else if (choice == "2") {
        double minGPA = promptDouble(" Minimum GPA", 0.0, 4.0);
        double maxGPA = promptDouble(" Maximum GPA", minGPA, 4.0);
        for (const auto& s : db) {
            if (s.gpa >= minGPA && s.gpa <= maxGPA) {
                results.push_back(&s);
            }
        }
    }
    else if (choice == "3") {
        string major = toLower(promptLine(" Major/Program"));
        for (const auto& s : db) {
            if (toLower(s.major).find(major) != string::npos) {
                results.push_back(&s);
            }
        }
    }
    
    if (results.empty()) {
        cout << COL_Warning << "\n    [!] No matches found for your search criteria.\n\n" << COL_RESET;
        return;
    }
    
    cout << "\n" << COL_Success << "  [+] FOUND " << results.size() << " MATCH(ES)\n" << COL_RESET;
    cout << COL_Menu << "  " << string(140, '-') << "\n";
    cout << left << setw(15) << "  ID" << setw(28) << "Name" << setw(8) << "GPA" 
         << setw(22) << "Major" << setw(30) << "Email" << "Status" << '\n';
    cout << "  " << string(140, '-') << "\n" << COL_RESET;
    
    for (const auto* sp : results) {
        string status = sp->getDisplayStatus();
        string statusColor = (status == "Honor Roll") ? COL_Success : 
                           (status == "Academic Probation") ? COL_Error : COL_Info;
        
        cout << COL_Data << "  " << left << setw(15) << sp->id << setw(28) << sp->name.substr(0, 27)
             << fixed << setprecision(2) << setw(8) << sp->gpa 
             << setw(22) << sp->major.substr(0, 21) << setw(30) << sp->email.substr(0, 29);
        cout << statusColor << status << COL_RESET << '\n';
    }
    cout << COL_Menu << "\n  " << string(140, '-') << "\n\n" << COL_RESET;
}

void exportManager(const vector<Student>& db) {
    cout << "\n" << COL_Header;
    cout << "============================================================\n";
    cout << "                    EXPORT MANAGER\n";
    cout << "============================================================\n\n" << COL_RESET;
    
    cout << COL_Accent << "  [*] AVAILABLE EXPORT FORMATS:\n" << COL_RESET;
    cout << "      [1] Enhanced CSV (Comma-Separated Values)\n";
    cout << "      [2] Professional RTF (Rich Text Format)\n";
    cout << "      [3] JSON Format (JavaScript Object Notation)\n";
    cout << "      [4] XML Export (Not yet implemented)\n";
    cout << "      [5] HTML Report (Not yet implemented)\n";
    cout << "      [6] Excel Format (Not yet implemented)\n\n" << COL_RESET;
    
    string choice = promptLine("      Select export format");
    
    if (choice == "0") return;
    
    string filename = promptLine("      Output filename (without extension)");
    
    if (choice == "1") {
        // Enhanced CSV with all fields
        ofstream out(filename + ".csv");
        out << "ID,Name,Age,GPA,Major,Email,Phone,Address,EnrollmentDate,Credits,Advisor,Status,LastModified,Notes\n";
        for (const auto& s : db) {
            out << s.id << ",\"" << s.name << "\"," << s.age << "," 
                << fixed << setprecision(2) << s.gpa << ",\"" << s.major 
                << "\",\"" << s.email << "\",\"" << s.phone << "\",\"" 
                << s.address << "\",\"" << s.enrollmentDate << "\"," 
                << s.totalCredits << ",\"" << s.advisor << "\",\"" 
                << s.getDisplayStatus() << "\",\"" << s.lastModified 
                << "\",\"" << s.notes << "\"\n";
        }
        out.close();
        cout << COL_Success << " Enhanced CSV exported successfully!\n" << COL_RESET;
    }
    else if (choice == "2") {
        // Professional RTF with advanced formatting
        ofstream out(filename + ".rtf");
        out << "{\\rtf1\\ansi\\deff0\n";
        out << "{\\fonttbl{\\f0\\froman Times New Roman;}{\\f1\\fswiss Arial;}}\n";
        out << "{\\colortbl;\\red0\\green0\\blue0;\\red128\\green0\\blue0;\\red0\\green128\\blue0;}\n";
        out << "\\f1\\fs28\\b MWINTELLIGENCE STUDENT REPORT\\b0\\par\\par\n";
        out << "\\fs20 Generated: " << getCurrentTimestamp() << "\\par\\par\n";
        
        out << "\\trowd\\trgaph108\\trleft0\n";
        out << "\\clbrdrt\\brdrs\\brdrw10\\clbrdrb\\brdrs\\brdrw10";
        out << "\\cellx1200\\cellx3500\\cellx4200\\cellx5000\\cellx7000\\cellx8500\n";
        out << "\\b\\cf2 ID\\cell Name\\cell Age\\cell GPA\\cell Major\\cell Status\\cell\\row\\b0\n";
        
        for (const auto& s : db) {
            out << "\\trowd\\trgaph108\\trleft0\n";
            out << "\\clbrdrt\\brdrs\\brdrw10\\clbrdrb\\brdrs\\brdrw10";
            out << "\\cellx1200\\cellx3500\\cellx4200\\cellx5000\\cellx7000\\cellx8500\n";
            out << s.id << "\\cell " << s.name << "\\cell " << s.age << "\\cell ";
            out << fixed << setprecision(2) << s.gpa << "\\cell " << s.major 
                << "\\cell " << s.getDisplayStatus() << "\\cell\\row\n";
        }
        out << "}\n";
        out.close();
        cout << COL_Success << " Professional RTF exported successfully!\n" << COL_RESET;
    }
    else if (choice == "3") {
        // JSON format for modern applications
        ofstream out(filename + ".json");
        out << "{\n  \"students\": [\n";
        for (size_t i = 0; i < db.size(); ++i) {
            const auto& s = db[i];
            out << "    {\n";
            out << "      \"id\": \"" << s.id << "\",\n";
            out << "      \"name\": \"" << s.name << "\",\n";
            out << "      \"age\": " << s.age << ",\n";
            out << "      \"gpa\": " << fixed << setprecision(2) << s.gpa << ",\n";
            out << "      \"major\": \"" << s.major << "\",\n";
            out << "      \"email\": \"" << s.email << "\",\n";
            out << "      \"phone\": \"" << s.phone << "\",\n";
            out << "      \"status\": \"" << s.getDisplayStatus() << "\",\n";
            out << "      \"lastModified\": \"" << s.lastModified << "\"\n";
            out << "    }" << (i < db.size() - 1 ? "," : "") << "\n";
        }
        out << "  ],\n";
        out << "  \"metadata\": {\n";
        out << "    \"totalStudents\": " << db.size() << ",\n";
        out << "    \"exportDate\": \"" << getCurrentTimestamp() << "\",\n";
        out << "    \"system\": \"MWINTELLIGENCE v3.0\"\n";
        out << "  }\n}\n";
        out.close();
        cout << COL_Success << " JSON format exported successfully!\n" << COL_RESET;
    }
    
    logActivity("Data exported: " + filename + " (Format: " + choice + ")");
}

int main() {
    enableConsoleVT();
    vector<Student> database;
    
    // Animated startup
    drawAdvancedHeader();
    
    progressBar("[*] Initializing System Components", 15);
    progressBar("[*] Loading Database Engine", 12);
    progressBar("[*] Configuring Advanced Features", 18);
    
    cout << "\n" << COL_Success << "[+] MWINTELLIGENCE v3.0 ENTERPRISE READY!\n\n" << COL_RESET;
    logActivity("System started - MWINTELLIGENCE v3.0");
    
    this_thread::sleep_for(chrono::milliseconds(800));
    
    while (true) {
        drawMainMenu();
        string choice = promptLine("\n[>] Select option");
        
        if (choice == "1") addAdvancedStudent(database);
        else if (choice == "2") listAdvancedStudents(database);
        else if (choice == "3") advancedSearch(database);
        else if (choice == "4") editStudent(database);
        else if (choice == "5") deleteStudent(database);
        else if (choice == "6") bulkOperations(database);
        else if (choice == "7") academicStatistics(database);
        else if (choice == "8") gpaAnalysisTrends(database);
        else if (choice == "9") gradeDistribution(database);
        else if (choice == "10") performanceReports(database);
        else if (choice == "11") exportManager(database);
        else if (choice == "12") importData(database);
        else if (choice == "13") backupRestore(database);
        else if (choice == "14") dataValidation(database);
        else if (choice == "15") courseManagement(database);
        else if (choice == "16") advisorTools(database);
        else if (choice == "17") systemSettings(config);
        else if (choice == "18") dataIntegrityCheck(database);
        else if (choice == "0") {
            cout << COL_Info << "\n[*] Saving and shutting down...\n";
            createBackup(database);
            logActivity("System shutdown - Clean exit");
            cout << COL_Success << "[+] Goodbye!\n" << COL_RESET;
            break;
        }
        else {
            cout << COL_Warning << "[!] Invalid option. Please try again.\n" << COL_RESET;
        }
        
        cout << COL_Prompt << "\n[Enter] Press Enter to continue..." << COL_RESET;
        cin.get();
    }
    
    return 0;
}