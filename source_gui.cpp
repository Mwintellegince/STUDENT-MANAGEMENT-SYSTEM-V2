// MWINTELLIGENCE Student Management System - GUI Edition
// Using Dear ImGui + GLFW for modern graphical interface

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#ifdef _WIN32
#include <windows.h>
#include <GL/gl.h>
// Hide console window on Windows
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <random>
#include <regex>

using namespace std;

// Student structure
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
    string academicStatus;
    double totalCredits;
    string advisor;
    string notes;
    
    double getWeightedGPA() const {
        if (courseGrades.empty()) return gpa;
        double sum = 0, credits = 0;
        for (const auto& pair : courseGrades) {
            sum += pair.second * 3.0;
            credits += 3.0;
        }
        return credits > 0 ? sum / credits : gpa;
    }
    
    string getDisplayStatus() const {
        if (gpa >= 3.8) return "Honor Roll";
        if (gpa >= 3.5) return "Dean's List";
        if (gpa < 2.0) return "Academic Probation";
        return academicStatus;
    }
};

// System configuration
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

// Global data
vector<Student> database;
SystemConfig config;
bool show_add_window = false;
bool show_list_window = false;
bool show_search_window = false;
bool show_edit_window = false;
bool show_stats_window = false;
bool show_export_window = false;
bool show_settings_window = false;
bool show_about_window = false;

// GUI state for forms
char input_name[128] = "";
int input_age = 18;
float input_gpa = 3.0f;
char input_major[128] = "Undeclared";
char input_email[128] = "";
char input_phone[64] = "";
char input_address[256] = "";
char input_advisor[128] = "";
char input_notes[512] = "";
int selected_student_idx = -1;
char search_query[128] = "";
vector<const Student*> search_results;

// Utility functions
string getCurrentTimestamp() {
    time_t now = time(nullptr);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << put_time(ltm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

bool idExists(const vector<Student>& db, const string& id) {
    return any_of(db.begin(), db.end(), [&id](const Student& s) { return s.id == id; });
}

string generateSecureID(const string& name) {
    string base;
    for (char c : name) {
        if (isalnum(c)) base += tolower(c);
    }
    if (base.empty()) base = "student";
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1000, 9999);
    
    string id = base + to_string(dis(gen));
    int attempt = 0;
    while (idExists(database, id) && attempt++ < 100) {
        id = base + to_string(dis(gen));
    }
    return id;
}

bool validateEmail(const string& email) {
    if (email.empty()) return true;
    regex emailPattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return regex_match(email, emailPattern);
}

bool validatePhone(const string& phone) {
    if (phone.empty()) return true;
    regex phonePattern(R"(\+?[1-9]\d{1,14})");
    return regex_match(phone, phonePattern);
}

void logActivity(const string& msg) {
    if (!config.enableLogging) return;
    ofstream log("system.log", ios::app);
    if (log) {
        log << "[" << getCurrentTimestamp() << "] " << msg << "\n";
    }
}

void createBackup(const vector<Student>& db) {
    if (!config.enableAutoBackup) return;
    
    string timestamp = getCurrentTimestamp();
    for (char& c : timestamp) {
        if (c == ' ' || c == ':') c = '-';
    }
    
    string filename = "backup_" + timestamp + ".csv";
    ofstream out(filename);
    if (!out) return;
    
    out << "ID,Name,Age,GPA,Major,Email,Phone,Address,EnrollmentDate,LastModified,Status,Credits,Advisor,Notes\n";
    for (const auto& s : db) {
        out << s.id << ",\"" << s.name << "\"," << s.age << "," << fixed << setprecision(2) 
            << s.gpa << ",\"" << s.major << "\",\"" << s.email << "\",\"" << s.phone 
            << "\",\"" << s.address << "\",\"" << s.enrollmentDate << "\",\"" << s.lastModified 
            << "\",\"" << s.academicStatus << "\"," << s.totalCredits << ",\"" << s.advisor 
            << "\",\"" << s.notes << "\"\n";
    }
}

void saveToCSV(const vector<Student>& db, const string& filename) {
    ofstream out(filename);
    if (!out) return;
    
    out << "ID,Name,Age,GPA,Major,Email,Phone,Address,EnrollmentDate,LastModified,Status,Credits,Advisor,Notes\n";
    for (const auto& s : db) {
        out << s.id << ",\"" << s.name << "\"," << s.age << "," << fixed << setprecision(2) 
            << s.gpa << ",\"" << s.major << "\",\"" << s.email << "\",\"" << s.phone 
            << "\",\"" << s.address << "\",\"" << s.enrollmentDate << "\",\"" << s.lastModified 
            << "\",\"" << s.academicStatus << "\"," << s.totalCredits << ",\"" << s.advisor 
            << "\",\"" << s.notes << "\"\n";
    }
}

void loadFromCSV(vector<Student>& db, const string& filename) {
    ifstream in(filename);
    if (!in) return;
    
    string line;
    getline(in, line); // Skip header
    
    while (getline(in, line)) {
        if (line.empty()) continue;
        
        try {
            stringstream ss(line);
            string id, name, ageStr, gpaStr, major;
            
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
        } catch (...) {}
    }
}

// GUI rendering functions
void RenderMainMenu() {
    ImGui::Begin("MWINTELLIGENCE - Student Management System", nullptr, ImGuiWindowFlags_MenuBar);
    
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Import CSV")) {
                loadFromCSV(database, "students.csv");
            }
            if (ImGui::MenuItem("Export", nullptr, &show_export_window)) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Exit")) {
                saveToCSV(database, "students.csv");
                exit(0);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Students")) {
            if (ImGui::MenuItem("Add Student", nullptr, &show_add_window)) {}
            if (ImGui::MenuItem("List All", nullptr, &show_list_window)) {}
            if (ImGui::MenuItem("Search", nullptr, &show_search_window)) {}
            if (ImGui::MenuItem("Edit", nullptr, &show_edit_window)) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Analytics")) {
            if (ImGui::MenuItem("Statistics", nullptr, &show_stats_window)) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Settings")) {
            if (ImGui::MenuItem("Preferences", nullptr, &show_settings_window)) {}
            if (ImGui::MenuItem("About", nullptr, &show_about_window)) {}
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    
    ImGui::SetCursorPosY(60);
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.2f, 0.8f, 0.8f, 1.0f));
    ImGui::Text("   MWINTELLIGENCE ADVANCED STUDENT MANAGEMENT SYSTEM");
    ImGui::PopStyleColor();
    ImGui::Spacing();
    ImGui::Text("   Enterprise Edition v3.0 | Professional Academic Database");
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    
    // Dashboard statistics
    ImGui::Text("   Database Overview");
    ImGui::Spacing();
    ImGui::Indent(20);
    ImGui::Text("Total Students: %zu", database.size());
    
    if (!database.empty()) {
        double avgGPA = 0;
        int honors = 0;
        for (const auto& s : database) {
            avgGPA += s.gpa;
            if (s.gpa >= 3.8) honors++;
        }
        avgGPA /= database.size();
        
        ImGui::Text("Average GPA: %.2f", avgGPA);
        ImGui::Text("Honor Roll Students: %d (%.1f%%)", honors, (honors * 100.0) / database.size());
    }
    ImGui::Unindent(20);
    
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Text("   Quick Actions");
    ImGui::Spacing();
    ImGui::Indent(20);
    
    if (ImGui::Button("Add New Student", ImVec2(250, 45))) {
        show_add_window = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("View All Students", ImVec2(250, 45))) {
        show_list_window = true;
    }
    
    if (ImGui::Button("Search Students", ImVec2(250, 45))) {
        show_search_window = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("View Statistics", ImVec2(250, 45))) {
        show_stats_window = true;
    }
    
    ImGui::Unindent(20);
    
    ImGui::End();
}

void RenderAddWindow() {
    if (!show_add_window) return;
    
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x * 0.4f, io.DisplaySize.y * 0.85f), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.3f, io.DisplaySize.y * 0.05f), ImGuiCond_FirstUseEver);
    ImGui::Begin("Add New Student", &show_add_window);
    
    ImGui::SeparatorText("Personal Information");
    ImGui::InputText("Full Name", input_name, IM_ARRAYSIZE(input_name));
    ImGui::InputInt("Age", &input_age);
    if (input_age < 16) input_age = 16;
    if (input_age > 120) input_age = 120;
    
    ImGui::SeparatorText("Academic Information");
    ImGui::SliderFloat("Current GPA", &input_gpa, 0.0f, 4.0f, "%.2f");
    ImGui::InputText("Major/Program", input_major, IM_ARRAYSIZE(input_major));
    
    ImGui::SeparatorText("Contact Information");
    ImGui::InputText("Email Address", input_email, IM_ARRAYSIZE(input_email));
    if (strlen(input_email) > 0 && !validateEmail(input_email)) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "Invalid email format");
    }
    
    ImGui::InputText("Phone Number", input_phone, IM_ARRAYSIZE(input_phone));
    if (strlen(input_phone) > 0 && !validatePhone(input_phone)) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "Invalid phone format");
    }
    
    ImGui::InputText("Address", input_address, IM_ARRAYSIZE(input_address));
    
    ImGui::SeparatorText("Additional Information");
    ImGui::InputText("Academic Advisor", input_advisor, IM_ARRAYSIZE(input_advisor));
    ImGui::InputTextMultiline("Notes", input_notes, IM_ARRAYSIZE(input_notes), ImVec2(-1, 100));
    
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    
    if (ImGui::Button("Add Student", ImVec2(200, 40))) {
        if (strlen(input_name) > 0) {
            Student s;
            s.name = input_name;
            s.id = generateSecureID(s.name);
            s.age = input_age;
            s.gpa = input_gpa;
            s.major = input_major;
            s.email = input_email;
            s.phone = input_phone;
            s.address = input_address;
            s.advisor = input_advisor;
            s.notes = input_notes;
            s.academicStatus = "Active";
            s.enrollmentDate = getCurrentTimestamp().substr(0, 10);
            s.lastModified = getCurrentTimestamp();
            s.totalCredits = 0;
            
            database.push_back(s);
            createBackup(database);
            logActivity("Added student: " + s.name + " (ID: " + s.id + ")");
            
            // Clear form
            memset(input_name, 0, sizeof(input_name));
            input_age = 18;
            input_gpa = 3.0f;
            strcpy(input_major, "Undeclared");
            memset(input_email, 0, sizeof(input_email));
            memset(input_phone, 0, sizeof(input_phone));
            memset(input_address, 0, sizeof(input_address));
            memset(input_advisor, 0, sizeof(input_advisor));
            memset(input_notes, 0, sizeof(input_notes));
            
            show_add_window = false;
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("Cancel", ImVec2(200, 40))) {
        show_add_window = false;
    }
    
    ImGui::End();
}

void RenderListWindow() {
    if (!show_list_window) return;
    
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x * 0.85f, io.DisplaySize.y * 0.8f), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.075f, io.DisplaySize.y * 0.1f), ImGuiCond_FirstUseEver);
    ImGui::Begin("Student Registry", &show_list_window);
    
    ImGui::Text("Total Students: %zu", database.size());
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    
    if (database.empty()) {
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "No students in database.");
    } else {
        if (ImGui::BeginTable("Students", 8, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY)) {
            ImGui::TableSetupColumn("ID");
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Age");
            ImGui::TableSetupColumn("GPA");
            ImGui::TableSetupColumn("Major");
            ImGui::TableSetupColumn("Email");
            ImGui::TableSetupColumn("Phone");
            ImGui::TableSetupColumn("Status");
            ImGui::TableHeadersRow();
            
            for (size_t i = 0; i < database.size(); i++) {
                const auto& s = database[i];
                ImGui::TableNextRow();
                
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%s", s.id.c_str());
                
                ImGui::TableSetColumnIndex(1);
                if (ImGui::Selectable(s.name.c_str(), selected_student_idx == (int)i, ImGuiSelectableFlags_SpanAllColumns)) {
                    selected_student_idx = i;
                }
                
                ImGui::TableSetColumnIndex(2);
                ImGui::Text("%d", s.age);
                
                ImGui::TableSetColumnIndex(3);
                ImGui::Text("%.2f", s.gpa);
                
                ImGui::TableSetColumnIndex(4);
                ImGui::Text("%s", s.major.c_str());
                
                ImGui::TableSetColumnIndex(5);
                ImGui::Text("%s", s.email.c_str());
                
                ImGui::TableSetColumnIndex(6);
                ImGui::Text("%s", s.phone.c_str());
                
                ImGui::TableSetColumnIndex(7);
                string status = s.getDisplayStatus();
                if (status == "Honor Roll") {
                    ImGui::TextColored(ImVec4(0, 1, 0, 1), "%s", status.c_str());
                } else if (status == "Academic Probation") {
                    ImGui::TextColored(ImVec4(1, 0, 0, 1), "%s", status.c_str());
                } else {
                    ImGui::Text("%s", status.c_str());
                }
            }
            
            ImGui::EndTable();
        }
    }
    
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    
    if (selected_student_idx >= 0 && selected_student_idx < (int)database.size()) {
        if (ImGui::Button("Edit Selected", ImVec2(180, 35))) {
            show_edit_window = true;
        }
        ImGui::SameLine();
        if (ImGui::Button("Delete Selected", ImVec2(180, 35))) {
            database.erase(database.begin() + selected_student_idx);
            createBackup(database);
            selected_student_idx = -1;
        }
    }
    
    ImGui::End();
}

void RenderSearchWindow() {
    if (!show_search_window) return;
    
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x * 0.7f, io.DisplaySize.y * 0.75f), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.15f, io.DisplaySize.y * 0.125f), ImGuiCond_FirstUseEver);
    ImGui::Begin("Search Students", &show_search_window);
    
    ImGui::InputText("Search by Name or ID", search_query, IM_ARRAYSIZE(search_query));
    ImGui::SameLine();
    
    if (ImGui::Button("Search", ImVec2(120, 30))) {
        search_results.clear();
        string query = search_query;
        transform(query.begin(), query.end(), query.begin(), ::tolower);
        
        for (const auto& s : database) {
            string name = s.name;
            string id = s.id;
            transform(name.begin(), name.end(), name.begin(), ::tolower);
            transform(id.begin(), id.end(), id.begin(), ::tolower);
            
            if (name.find(query) != string::npos || id.find(query) != string::npos) {
                search_results.push_back(&s);
            }
        }
    }
    
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    
    ImGui::Text("Found %zu match(es)", search_results.size());
    ImGui::Spacing();
    
    if (!search_results.empty()) {
        if (ImGui::BeginTable("SearchResults", 7, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
            ImGui::TableSetupColumn("ID");
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Age");
            ImGui::TableSetupColumn("GPA");
            ImGui::TableSetupColumn("Major");
            ImGui::TableSetupColumn("Email");
            ImGui::TableSetupColumn("Status");
            ImGui::TableHeadersRow();
            
            for (const auto* sp : search_results) {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%s", sp->id.c_str());
                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%s", sp->name.c_str());
                ImGui::TableSetColumnIndex(2);
                ImGui::Text("%d", sp->age);
                ImGui::TableSetColumnIndex(3);
                ImGui::Text("%.2f", sp->gpa);
                ImGui::TableSetColumnIndex(4);
                ImGui::Text("%s", sp->major.c_str());
                ImGui::TableSetColumnIndex(5);
                ImGui::Text("%s", sp->email.c_str());
                ImGui::TableSetColumnIndex(6);
                string status = sp->getDisplayStatus();
                if (status == "Honor Roll") {
                    ImGui::TextColored(ImVec4(0, 1, 0, 1), "%s", status.c_str());
                } else if (status == "Academic Probation") {
                    ImGui::TextColored(ImVec4(1, 0, 0, 1), "%s", status.c_str());
                } else {
                    ImGui::Text("%s", status.c_str());
                }
            }
            
            ImGui::EndTable();
        }
    }
    
    ImGui::End();
}

void RenderStatsWindow() {
    if (!show_stats_window) return;
    
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.7f), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.25f, io.DisplaySize.y * 0.15f), ImGuiCond_FirstUseEver);
    ImGui::Begin("Academic Statistics", &show_stats_window);
    
    if (database.empty()) {
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "No students in database.");
    } else {
        double sumGPA = 0, minGPA = 4.0, maxGPA = 0.0;
        int minAge = 120, maxAge = 0;
        map<string, int> majorCount;
        int honors = 0, probation = 0;
        
        for (const auto& s : database) {
            sumGPA += s.gpa;
            minGPA = min(minGPA, s.gpa);
            maxGPA = max(maxGPA, s.gpa);
            minAge = min(minAge, s.age);
            maxAge = max(maxAge, s.age);
            majorCount[s.major]++;
            
            if (s.gpa >= 3.8) honors++;
            else if (s.gpa < 2.0) probation++;
        }
        
        double avgGPA = sumGPA / database.size();
        
        ImGui::SeparatorText("Overall Statistics");
        ImGui::Text("Total Students: %zu", database.size());
        ImGui::Text("Average GPA: %.3f", avgGPA);
        ImGui::Text("GPA Range: %.2f - %.2f", minGPA, maxGPA);
        ImGui::Text("Age Range: %d - %d years", minAge, maxAge);
        ImGui::Text("Honor Roll (GPA >= 3.8): %d (%.1f%%)", honors, (honors * 100.0) / database.size());
        ImGui::Text("Academic Probation (GPA < 2.0): %d (%.1f%%)", probation, (probation * 100.0) / database.size());
        
        ImGui::Spacing();
        ImGui::SeparatorText("Students by Major");
        
        if (ImGui::BeginTable("MajorStats", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
            ImGui::TableSetupColumn("Major");
            ImGui::TableSetupColumn("Count");
            ImGui::TableHeadersRow();
            
            for (const auto& pair : majorCount) {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%s", pair.first.c_str());
                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%d", pair.second);
            }
            
            ImGui::EndTable();
        }
    }
    
    ImGui::End();
}

void RenderExportWindow() {
    if (!show_export_window) return;
    
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x * 0.35f, io.DisplaySize.y * 0.4f), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.325f, io.DisplaySize.y * 0.3f), ImGuiCond_FirstUseEver);
    ImGui::Begin("Export Data", &show_export_window);
    
    ImGui::Text("Export student database to file");
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    
    static char export_filename[128] = "students_export";
    ImGui::InputText("Filename (without extension)", export_filename, IM_ARRAYSIZE(export_filename));
    
    ImGui::Spacing();
    
    if (ImGui::Button("Export as CSV", ImVec2(220, 40))) {
        string filename = string(export_filename) + ".csv";
        saveToCSV(database, filename);
        logActivity("Exported " + to_string(database.size()) + " students to " + filename);
        show_export_window = false;
    }
    
    ImGui::Spacing();
    ImGui::Text("Exported files will be saved in the program directory.");
    
    ImGui::End();
}

void RenderSettingsWindow() {
    if (!show_settings_window) return;
    
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x * 0.4f, io.DisplaySize.y * 0.5f), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.3f, io.DisplaySize.y * 0.25f), ImGuiCond_FirstUseEver);
    ImGui::Begin("System Settings", &show_settings_window);
    
    ImGui::Checkbox("Enable Auto Backup", &config.enableAutoBackup);
    ImGui::Checkbox("Enable Logging", &config.enableLogging);
    ImGui::Checkbox("Enable Data Validation", &config.enableDataValidation);
    
    ImGui::Spacing();
    ImGui::SliderInt("Max Students", &config.maxStudents, 100, 100000);
    ImGui::SliderInt("Max Backup Files", &config.maxBackupFiles, 5, 50);
    
    ImGui::End();
}

void RenderAboutWindow() {
    if (!show_about_window) return;
    
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x * 0.35f, io.DisplaySize.y * 0.45f), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.325f, io.DisplaySize.y * 0.275f), ImGuiCond_FirstUseEver);
    ImGui::Begin("About", &show_about_window);
    
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.2f, 0.8f, 0.8f, 1.0f));
    ImGui::Text("MWINTELLIGENCE Student Management System");
    ImGui::PopStyleColor();
    ImGui::Text("Enterprise Edition v3.0");
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::Text("A comprehensive student database management system");
    ImGui::Text("featuring advanced analytics and reporting.");
    ImGui::Spacing();
    ImGui::Text("Build: 2025.10.24");
    ImGui::Text("GUI Framework: Dear ImGui + GLFW");
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::Text("(C) 2025 MWINTELLIGENCE. All rights reserved.");
    
    ImGui::End();
}

// Main function
int main(int, char**) {
    // Load existing data
    loadFromCSV(database, "students.csv");
    
    // Initialize GLFW
    if (!glfwInit())
        return -1;
    
    // GL 3.3 + GLSL 330
    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Create window with proper sizing
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary);
    int window_width = mode->width * 0.9f;   // 90% of screen width
    int window_height = mode->height * 0.9f; // 90% of screen height
    
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "MWINTELLIGENCE Student Management System", NULL, NULL);
    if (window == NULL)
        return -1;
    
    // Center the window
    glfwSetWindowPos(window, (mode->width - window_width) / 2, (mode->height - window_height) / 2);
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    // Note: Docking requires ImGui docking branch
    
    // Load larger default font
    ImFontConfig font_config;
    font_config.SizePixels = 18.0f;  // Larger base font
    io.Fonts->AddFontDefault(&font_config);
    
    // Setup style - Microsoft Store / Windows 11 Fluent Design
    ImGui::StyleColorsLight();  // Start with light theme
    
    // Customize style for modern appearance
    ImGuiStyle& style = ImGui::GetStyle();
    
    // Generous padding and spacing for modern touch-friendly UI
    style.WindowPadding = ImVec2(20, 20);
    style.FramePadding = ImVec2(12, 8);
    style.ItemSpacing = ImVec2(12, 10);
    style.ItemInnerSpacing = ImVec2(10, 8);
    style.IndentSpacing = 28.0f;
    style.ScrollbarSize = 18.0f;
    style.GrabMinSize = 14.0f;
    
    // Fluent Design rounded corners
    style.WindowRounding = 12.0f;
    style.ChildRounding = 8.0f;
    style.FrameRounding = 6.0f;
    style.PopupRounding = 8.0f;
    style.ScrollbarRounding = 9.0f;
    style.GrabRounding = 6.0f;
    style.TabRounding = 6.0f;
    
    // Borders - borderless windows for modern look
    style.WindowBorderSize = 0.0f;
    style.FrameBorderSize = 1.0f;
    style.PopupBorderSize = 1.0f;
    
    // Centered text for modern aesthetic
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    
    // Microsoft Store / Windows 11 Color Scheme
    ImVec4* colors = style.Colors;
    
    // Background - Light mica effect
    colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.96f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.98f, 0.98f, 0.99f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.96f, 0.96f, 0.97f, 0.98f);
    colors[ImGuiCol_Border] = ImVec4(0.82f, 0.82f, 0.85f, 0.50f);
    colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.96f, 0.96f, 0.97f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.94f, 0.94f, 0.96f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.47f, 0.84f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.47f, 0.84f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.47f, 0.84f, 0.80f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.96f, 0.96f, 0.97f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.94f, 0.94f, 0.96f, 0.50f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.70f, 0.70f, 0.72f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.60f, 0.60f, 0.62f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.50f, 0.50f, 0.52f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 0.47f, 0.84f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.47f, 0.84f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 0.40f, 0.72f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.00f, 0.47f, 0.84f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.00f, 0.42f, 0.76f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 0.37f, 0.68f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.00f, 0.47f, 0.84f, 0.20f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.47f, 0.84f, 0.35f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 0.47f, 0.84f, 0.50f);
    colors[ImGuiCol_Separator] = ImVec4(0.82f, 0.82f, 0.85f, 0.50f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.00f, 0.47f, 0.84f, 0.78f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.00f, 0.47f, 0.84f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.47f, 0.84f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.00f, 0.47f, 0.84f, 0.67f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.00f, 0.47f, 0.84f, 0.95f);
    colors[ImGuiCol_Tab] = ImVec4(0.88f, 0.88f, 0.90f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.00f, 0.47f, 0.84f, 0.80f);
    colors[ImGuiCol_TabActive] = ImVec4(0.00f, 0.47f, 0.84f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.92f, 0.92f, 0.94f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.85f, 0.85f, 0.87f, 1.00f);
    colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.47f, 0.84f, 0.35f);
    
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    
    ImVec4 clear_color = ImVec4(0.94f, 0.94f, 0.96f, 1.00f);  // Match window background
    
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        // Render our windows
        RenderMainMenu();
        RenderAddWindow();
        RenderListWindow();
        RenderSearchWindow();
        RenderStatsWindow();
        RenderExportWindow();
        RenderSettingsWindow();
        RenderAboutWindow();
        
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        glfwSwapBuffers(window);
    }
    
    // Save on exit
    saveToCSV(database, "students.csv");
    createBackup(database);
    logActivity("System shutdown - GUI application closed");
    
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}
