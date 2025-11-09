// MWINTELLIGENCE Student Management System - Native Windows Application
// Pure Win32 API - No external dependencies

#include <windows.h>
#include <commctrl.h>
#include <commdlg.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <map>

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "comdlg32.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publickeytoken='6595b64144ccf1df' language='*'\"")

using namespace std;

// Student structure with enhanced fields
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
    string graduationYear;
    string emergencyContact;
    string nationality;
    string status; // Active, Graduated, Suspended, etc.
    double tuitionFee;
    string parentGuardian;
    string bloodGroup;
    string allergies;
    string notes;
};

// Global variables
vector<Student> database;
HWND g_hMainWindow = NULL;
HWND g_hListView = NULL;
HWND g_hStatusBar = NULL;
HINSTANCE g_hInstance = NULL;

// Animation and UI enhancement variables
bool g_animationsEnabled = true;
bool g_soundsEnabled = true;
bool g_autoBackupEnabled = true;
int g_animationSpeed = 150; // milliseconds
string g_currentTheme = "Modern";
string g_backupPath = "backup/";
COLORREF g_accentColor = RGB(0, 120, 215); // Windows blue
int g_buttonHoverState[20] = {0}; // Track hover states
HBRUSH g_hBrushAccent = NULL;
HBRUSH g_hBrushHover = NULL;
HBRUSH g_hBrushNormal = NULL;

// Enhanced Control IDs
#define IDC_LISTVIEW 1001
#define IDC_BTN_ADD 1002
#define IDC_BTN_EDIT 1003
#define IDC_BTN_DELETE 1004
#define IDC_BTN_SEARCH 1005
#define IDC_BTN_EXPORT 1006
#define IDC_BTN_STATS 1007
#define IDC_BTN_REFRESH 1008
#define IDC_BTN_IMPORT 1009
#define IDC_BTN_BACKUP 1010
#define IDC_BTN_SETTINGS 1011
#define IDC_BTN_REPORTS 1012
#define IDC_BTN_BULK_EDIT 1013
#define IDC_BTN_GRADE_CALC 1014
#define IDC_STATUSBAR 1015

// Animation timer IDs
#define TIMER_BUTTON_HOVER 2001
#define TIMER_FADE_IN 2002
#define TIMER_SLIDE_IN 2003

// Enhanced Menu IDs
#define ID_FILE_NEW 2001
#define ID_FILE_OPEN 2002
#define ID_FILE_SAVE 2003
#define ID_FILE_SAVEAS 2004
#define ID_FILE_IMPORT 2005
#define ID_FILE_EXPORT_PDF 2006
#define ID_FILE_BACKUP 2007
#define ID_FILE_RESTORE 2008
#define ID_FILE_EXIT 2009
#define ID_EDIT_ADD 2010
#define ID_EDIT_MODIFY 2011
#define ID_EDIT_DELETE 2012
#define ID_EDIT_BULK_EDIT 2013
#define ID_EDIT_DUPLICATE 2014
#define ID_VIEW_REFRESH 2015
#define ID_VIEW_FILTERS 2016
#define ID_VIEW_GRID 2017
#define ID_VIEW_DETAILS 2018
#define ID_TOOLS_GRADE_CALC 2019
#define ID_TOOLS_ATTENDANCE 2020
#define ID_TOOLS_REPORTS 2021
#define ID_TOOLS_SETTINGS 2022
#define ID_HELP_ABOUT 2023
#define ID_HELP_TUTORIAL 2024

// Enhanced Dialog control IDs
#define IDC_EDIT_ID 3000
#define IDC_EDIT_NAME 3001
#define IDC_EDIT_AGE 3002
#define IDC_EDIT_GPA 3003
#define IDC_EDIT_MAJOR 3004
#define IDC_EDIT_EMAIL 3005
#define IDC_EDIT_PHONE 3006
#define IDC_EDIT_ADDRESS 3007
#define IDC_EDIT_ENROLLMENT 3008
#define IDC_EDIT_GRADUATION 3009
#define IDC_EDIT_EMERGENCY 3010
#define IDC_EDIT_NATIONALITY 3011
#define IDC_COMBO_STATUS 3012
#define IDC_EDIT_TUITION 3013
#define IDC_EDIT_PARENT 3014
#define IDC_COMBO_BLOOD 3015
#define IDC_EDIT_ALLERGIES 3016
#define IDC_EDIT_NOTES 3017
#define IDC_BTN_OK 3018
#define IDC_BTN_CANCEL 3019
#define IDC_EDIT_SEARCH 3020
#define IDC_STATIC_STATS 3021
#define IDC_TAB_CONTROL 3022

// Settings dialog IDs
#define IDC_CHECK_ANIMATIONS 3030
#define IDC_CHECK_SOUNDS 3031
#define IDC_CHECK_AUTO_BACKUP 3032
#define IDC_SLIDER_ANIMATION_SPEED 3033
#define IDC_COMBO_THEME 3034
#define IDC_EDIT_BACKUP_PATH 3035
#define IDC_BTN_BROWSE 3036

// Global variables for selected student
int g_selectedStudentIndex = -1;

// Forward declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ButtonSubclassProc(HWND, UINT, WPARAM, LPARAM, UINT_PTR, DWORD_PTR);
INT_PTR CALLBACK AddDialogProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK EditDialogProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK SearchDialogProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK StatsDialogProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK SettingsDialogProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK ReportsDialogProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK GradeCalcDialogProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK AboutDialogProc(HWND, UINT, WPARAM, LPARAM);

void InitListView(HWND hListView);
void LoadData();
void SaveData();
void SaveAsData();
void ImportData();
void ExportToPDF();
void CreateBackup();
void RestoreBackup();
void RefreshListView();
void ShowAddDialog();
void ShowEditDialog();
void ShowSearchDialog();
void ShowStatsDialog();
void ShowSettingsDialog();
void ShowReportsDialog();
void ShowGradeCalcDialog();
void ShowAboutDialog();
void DeleteSelectedStudent();
void BulkEditStudents();
void DuplicateStudent();
void ExportToCSV();
void ApplyFilters();
void InitializeAnimations();
void AnimateButton(HWND hButton, bool hover);
void SlideInWindow(HWND hWnd);
void FadeInWindow(HWND hWnd);
void PlayUISound(const string& soundType);
string GenerateID(const string& name);
string GetCurrentTimestamp();
void LoadSettings();
void SaveSettings();
void UpdateTheme();
bool ValidateStudentData(const Student& student);
void ShowNotification(const string& message, const string& type);

// wWinMain - Entry point
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    g_hInstance = hInstance;
    
    // Initialize common controls
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_LISTVIEW_CLASSES | ICC_BAR_CLASSES | ICC_TAB_CLASSES | ICC_PROGRESS_CLASS;
    InitCommonControlsEx(&icex);
    
    // Initialize animation brushes
    g_hBrushAccent = CreateSolidBrush(g_accentColor);
    g_hBrushHover = CreateSolidBrush(RGB(230, 245, 255));
    g_hBrushNormal = CreateSolidBrush(RGB(240, 240, 240));
    
    // Load settings
    LoadSettings();
    
    // Register window class
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"MWINTELLIGENCEClass";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    
    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, L"Window Registration Failed!", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    // Create main window
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int windowWidth = (int)(screenWidth * 0.8);
    int windowHeight = (int)(screenHeight * 0.8);
    int posX = (screenWidth - windowWidth) / 2;
    int posY = (screenHeight - windowHeight) / 2;
    
    g_hMainWindow = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        L"MWINTELLIGENCEClass",
        L"MWINTELLIGENCE Student Management System",
        WS_OVERLAPPEDWINDOW,
        posX, posY, windowWidth, windowHeight,
        NULL, NULL, hInstance, NULL
    );
    
    if (g_hMainWindow == NULL) {
        MessageBox(NULL, L"Window Creation Failed!", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    
    ShowWindow(g_hMainWindow, nCmdShow);
    UpdateWindow(g_hMainWindow);
    
    // Load data
    LoadData();
    
    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return (int)msg.wParam;
}

// Window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            // Create enhanced menu bar
            HMENU hMenu = CreateMenu();
            HMENU hFileMenu = CreateMenu();
            HMENU hEditMenu = CreateMenu();
            HMENU hViewMenu = CreateMenu();
            HMENU hToolsMenu = CreateMenu();
            HMENU hHelpMenu = CreateMenu();
            
            // File Menu
            AppendMenu(hFileMenu, MF_STRING, ID_FILE_NEW, L"&New Database\tCtrl+N");
            AppendMenu(hFileMenu, MF_STRING, ID_FILE_OPEN, L"&Open\tCtrl+O");
            AppendMenu(hFileMenu, MF_SEPARATOR, 0, NULL);
            AppendMenu(hFileMenu, MF_STRING, ID_FILE_SAVE, L"&Save\tCtrl+S");
            AppendMenu(hFileMenu, MF_STRING, ID_FILE_SAVEAS, L"Save &As...\tCtrl+Shift+S");
            AppendMenu(hFileMenu, MF_SEPARATOR, 0, NULL);
            AppendMenu(hFileMenu, MF_STRING, ID_FILE_IMPORT, L"&Import Data...");
            AppendMenu(hFileMenu, MF_STRING, ID_FILE_EXPORT_PDF, L"Export to &PDF...");
            AppendMenu(hFileMenu, MF_SEPARATOR, 0, NULL);
            AppendMenu(hFileMenu, MF_STRING, ID_FILE_BACKUP, L"Create &Backup...");
            AppendMenu(hFileMenu, MF_STRING, ID_FILE_RESTORE, L"&Restore Backup...");
            AppendMenu(hFileMenu, MF_SEPARATOR, 0, NULL);
            AppendMenu(hFileMenu, MF_STRING, ID_FILE_EXIT, L"E&xit\tAlt+F4");
            
            // Edit Menu
            AppendMenu(hEditMenu, MF_STRING, ID_EDIT_ADD, L"&Add Student\tCtrl+A");
            AppendMenu(hEditMenu, MF_STRING, ID_EDIT_MODIFY, L"&Edit Student\tCtrl+E");
            AppendMenu(hEditMenu, MF_STRING, ID_EDIT_DELETE, L"&Delete Student\tDel");
            AppendMenu(hEditMenu, MF_STRING, ID_EDIT_DUPLICATE, L"D&uplicate Student\tCtrl+D");
            AppendMenu(hEditMenu, MF_SEPARATOR, 0, NULL);
            AppendMenu(hEditMenu, MF_STRING, ID_EDIT_BULK_EDIT, L"&Bulk Edit...");
            
            // View Menu
            AppendMenu(hViewMenu, MF_STRING, ID_VIEW_REFRESH, L"&Refresh\tF5");
            AppendMenu(hViewMenu, MF_STRING, ID_VIEW_FILTERS, L"&Filters...\tCtrl+F");
            AppendMenu(hViewMenu, MF_SEPARATOR, 0, NULL);
            AppendMenu(hViewMenu, MF_STRING, ID_VIEW_GRID, L"&Grid View");
            AppendMenu(hViewMenu, MF_STRING, ID_VIEW_DETAILS, L"&Details View");
            
            // Tools Menu
            AppendMenu(hToolsMenu, MF_STRING, ID_TOOLS_GRADE_CALC, L"&Grade Calculator...");
            AppendMenu(hToolsMenu, MF_STRING, ID_TOOLS_ATTENDANCE, L"&Attendance Tracker...");
            AppendMenu(hToolsMenu, MF_STRING, ID_TOOLS_REPORTS, L"&Generate Reports...");
            AppendMenu(hToolsMenu, MF_SEPARATOR, 0, NULL);
            AppendMenu(hToolsMenu, MF_STRING, ID_TOOLS_SETTINGS, L"&Settings...\tCtrl+,");
            
            // Help Menu
            AppendMenu(hHelpMenu, MF_STRING, ID_HELP_TUTORIAL, L"&Tutorial...");
            AppendMenu(hHelpMenu, MF_STRING, ID_HELP_ABOUT, L"&About");
            
            AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"&File");
            AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hEditMenu, L"&Edit");
            AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hViewMenu, L"&View");
            AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hToolsMenu, L"&Tools");
            AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, L"&Help");
            
            SetMenu(hwnd, hMenu);
            
            // Create advanced toolbar with gradient background
            int btnY = 15;
            int btnX = 15;
            int btnWidth = 120;
            int btnHeight = 45;
            int btnSpacing = 8;
            
            // Get client rect for toolbar
            RECT rcClient;
            GetClientRect(hwnd, &rcClient);
            
            // Create toolbar background with modern styling
            HWND hToolbar = CreateWindow(L"STATIC", L"",
                WS_CHILD | WS_VISIBLE | SS_ETCHEDFRAME,
                5, 5, rcClient.right - 10, 155,
                hwnd, NULL, g_hInstance, NULL);
            
            // Row 1 - Primary Actions
            CreateWindow(L"BUTTON", L"➕ Add",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_FLAT,
                btnX, btnY, btnWidth, btnHeight,
                hwnd, (HMENU)IDC_BTN_ADD, g_hInstance, NULL);
            
            btnX += btnWidth + btnSpacing;
            CreateWindow(L"BUTTON", L"✏️ Edit",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_FLAT,
                btnX, btnY, btnWidth, btnHeight,
                hwnd, (HMENU)IDC_BTN_EDIT, g_hInstance, NULL);
            
            btnX += btnWidth + btnSpacing;
            CreateWindow(L"BUTTON", L"🗑️ Delete",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_FLAT,
                btnX, btnY, btnWidth, btnHeight,
                hwnd, (HMENU)IDC_BTN_DELETE, g_hInstance, NULL);
            
            btnX += btnWidth + btnSpacing;
            CreateWindow(L"BUTTON", L"🔍 Search",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_FLAT,
                btnX, btnY, btnWidth, btnHeight,
                hwnd, (HMENU)IDC_BTN_SEARCH, g_hInstance, NULL);
            
            btnX += btnWidth + btnSpacing;
            CreateWindow(L"BUTTON", L"📊 Stats",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_FLAT,
                btnX, btnY, btnWidth, btnHeight,
                hwnd, (HMENU)IDC_BTN_STATS, g_hInstance, NULL);
            
            btnX += btnWidth + btnSpacing;
            CreateWindow(L"BUTTON", L"🔄 Refresh",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_FLAT,
                btnX, btnY, btnWidth, btnHeight,
                hwnd, (HMENU)IDC_BTN_REFRESH, g_hInstance, NULL);
            
            // Row 2 - Secondary Actions
            btnX = 15;
            btnY = 70;
            
            CreateWindow(L"BUTTON", L"� Import",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_FLAT,
                btnX, btnY, btnWidth, btnHeight,
                hwnd, (HMENU)IDC_BTN_IMPORT, g_hInstance, NULL);
            
            btnX += btnWidth + btnSpacing;
            CreateWindow(L"BUTTON", L"💾 Export",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_FLAT,
                btnX, btnY, btnWidth, btnHeight,
                hwnd, (HMENU)IDC_BTN_EXPORT, g_hInstance, NULL);
            
            btnX += btnWidth + btnSpacing;
            CreateWindow(L"BUTTON", L"🔧 Bulk Edit",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_FLAT,
                btnX, btnY, btnWidth, btnHeight,
                hwnd, (HMENU)IDC_BTN_BULK_EDIT, g_hInstance, NULL);
            
            btnX += btnWidth + btnSpacing;
            CreateWindow(L"BUTTON", L"🧮 Calculator",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_FLAT,
                btnX, btnY, btnWidth, btnHeight,
                hwnd, (HMENU)IDC_BTN_GRADE_CALC, g_hInstance, NULL);
            
            btnX += btnWidth + btnSpacing;
            CreateWindow(L"BUTTON", L"� Reports",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_FLAT,
                btnX, btnY, btnWidth, btnHeight,
                hwnd, (HMENU)IDC_BTN_REPORTS, g_hInstance, NULL);
            
            btnX += btnWidth + btnSpacing;
            CreateWindow(L"BUTTON", L"⚙️ Settings",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_FLAT,
                btnX, btnY, btnWidth, btnHeight,
                hwnd, (HMENU)IDC_BTN_SETTINGS, g_hInstance, NULL);
            
            // Create enhanced ListView with updated positioning
            g_hListView = CreateWindowEx(
                WS_EX_CLIENTEDGE, WC_LISTVIEW, L"",
                WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS,
                10, 165,
                rcClient.right - 20,
                rcClient.bottom - 215,
                hwnd, (HMENU)IDC_LISTVIEW, g_hInstance, NULL
            );
            
            ListView_SetExtendedListViewStyle(g_hListView, 
                LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER | LVS_EX_INFOTIP);
            InitListView(g_hListView);
            
            // Initialize animations if enabled
            if (g_animationsEnabled) {
                SlideInWindow(hwnd);
                SetTimer(hwnd, TIMER_FADE_IN, 50, NULL);
            }
            
            // Create status bar
            g_hStatusBar = CreateWindowEx(
                0, STATUSCLASSNAME, NULL,
                WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
                0, 0, 0, 0,
                hwnd, (HMENU)IDC_STATUSBAR, g_hInstance, NULL
            );
            
            RefreshListView();
            break;
        }
        
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                // Button commands
                case IDC_BTN_ADD:
                case ID_EDIT_ADD:
                    ShowAddDialog();
                    break;
                    
                case IDC_BTN_EDIT:
                case ID_EDIT_MODIFY:
                    ShowEditDialog();
                    break;
                    
                case IDC_BTN_DELETE:
                case ID_EDIT_DELETE:
                    DeleteSelectedStudent();
                    break;
                    
                case IDC_BTN_SEARCH:
                    ShowSearchDialog();
                    break;
                    
                case IDC_BTN_STATS:
                    ShowStatsDialog();
                    break;
                    
                case IDC_BTN_EXPORT:
                    ExportToCSV();
                    break;
                    
                case IDC_BTN_IMPORT:
                case ID_FILE_IMPORT:
                    ImportData();
                    break;
                    
                case IDC_BTN_BULK_EDIT:
                case ID_EDIT_BULK_EDIT:
                    BulkEditStudents();
                    break;
                    
                case IDC_BTN_GRADE_CALC:
                case ID_TOOLS_GRADE_CALC:
                    ShowGradeCalcDialog();
                    break;
                    
                case IDC_BTN_REPORTS:
                case ID_TOOLS_REPORTS:
                    ShowReportsDialog();
                    break;
                    
                case IDC_BTN_SETTINGS:
                case ID_TOOLS_SETTINGS:
                    ShowSettingsDialog();
                    break;
                    
                case IDC_BTN_REFRESH:
                case ID_VIEW_REFRESH:
                    RefreshListView();
                    break;
                    
                // Menu commands
                case ID_FILE_NEW:
                    database.clear();
                    RefreshListView();
                    break;
                    
                case ID_FILE_SAVE:
                    SaveData();
                    ShowNotification("Data saved successfully!", "success");
                    break;
                    
                case ID_FILE_SAVEAS:
                    SaveAsData();
                    break;
                    
                case ID_FILE_EXPORT_PDF:
                    ExportToPDF();
                    break;
                    
                case ID_FILE_BACKUP:
                    CreateBackup();
                    break;
                    
                case ID_FILE_RESTORE:
                    RestoreBackup();
                    break;
                    
                case ID_FILE_OPEN:
                    LoadData();
                    RefreshListView();
                    break;
                    
                case ID_FILE_EXIT:
                    PostMessage(hwnd, WM_CLOSE, 0, 0);
                    break;
                    
                case ID_EDIT_DUPLICATE:
                    DuplicateStudent();
                    break;
                    
                case ID_VIEW_FILTERS:
                    ApplyFilters();
                    break;
                    
                case ID_TOOLS_ATTENDANCE:
                    MessageBox(hwnd, L"Attendance Tracker coming soon!", L"Feature", MB_OK | MB_ICONINFORMATION);
                    break;
                    
                case ID_HELP_TUTORIAL:
                    MessageBox(hwnd, L"Tutorial will be available in future updates!", L"Tutorial", MB_OK | MB_ICONINFORMATION);
                    break;
                    
                case ID_HELP_ABOUT:
                    ShowAboutDialog();
                    break;
            }
            break;
        }
        
        case WM_SIZE: {
            // Resize controls responsively
            RECT rcClient;
            GetClientRect(hwnd, &rcClient);
            
            if (g_hListView) {
                SetWindowPos(g_hListView, NULL,
                    10, 125,
                    rcClient.right - 20,
                    rcClient.bottom - 175,
                    SWP_NOZORDER);
            }
            
            if (g_hStatusBar) {
                SendMessage(g_hStatusBar, WM_SIZE, 0, 0);
            }
            break;
        }
        
        case WM_NOTIFY: {
            if (((LPNMHDR)lParam)->idFrom == IDC_LISTVIEW) {
                if (((LPNMHDR)lParam)->code == NM_DBLCLK) {
                    ShowEditDialog();
                } else if (((LPNMHDR)lParam)->code == LVN_ITEMCHANGED) {
                    LPNMLISTVIEW pnmv = (LPNMLISTVIEW)lParam;
                    if ((pnmv->uChanged & LVIF_STATE) && (pnmv->uNewState & LVIS_SELECTED)) {
                        g_selectedStudentIndex = pnmv->iItem;
                    }
                }
            }
            break;
        }
        
        case WM_CLOSE:
            SaveData();
            DestroyWindow(hwnd);
            break;
            
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
            
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// Initialize ListView columns with enhanced student data
void InitListView(HWND hListView) {
    LVCOLUMN lvc = {0};
    lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
    
    // Column 0: ID
    lvc.pszText = (LPWSTR)L"Student ID";
    lvc.cx = 100;
    ListView_InsertColumn(hListView, 0, &lvc);
    
    // Column 1: Name
    lvc.pszText = (LPWSTR)L"Full Name";
    lvc.cx = 180;
    ListView_InsertColumn(hListView, 1, &lvc);
    
    // Column 2: Age
    lvc.pszText = (LPWSTR)L"Age";
    lvc.cx = 60;
    ListView_InsertColumn(hListView, 2, &lvc);
    
    // Column 3: GPA
    lvc.pszText = (LPWSTR)L"GPA";
    lvc.cx = 70;
    ListView_InsertColumn(hListView, 3, &lvc);
    
    // Column 4: Major
    lvc.pszText = (LPWSTR)L"Major";
    lvc.cx = 150;
    ListView_InsertColumn(hListView, 4, &lvc);
    
    // Column 5: Status
    lvc.pszText = (LPWSTR)L"Status";
    lvc.cx = 100;
    ListView_InsertColumn(hListView, 5, &lvc);
    
    // Column 6: Email
    lvc.pszText = (LPWSTR)L"Email";
    lvc.cx = 200;
    ListView_InsertColumn(hListView, 6, &lvc);
    
    // Column 7: Phone
    lvc.pszText = (LPWSTR)L"Phone";
    lvc.cx = 120;
    ListView_InsertColumn(hListView, 7, &lvc);
    
    // Column 8: Enrollment Date
    lvc.pszText = (LPWSTR)L"Enrolled";
    lvc.cx = 100;
    ListView_InsertColumn(hListView, 8, &lvc);
    
    // Column 9: Nationality
    lvc.pszText = (LPWSTR)L"Nationality";
    lvc.cx = 100;
    ListView_InsertColumn(hListView, 9, &lvc);
}

// Enhanced refresh ListView with all student data
void RefreshListView() {
    if (!g_hListView) return;
    
    ListView_DeleteAllItems(g_hListView);
    
    for (size_t i = 0; i < database.size(); i++) {
        LVITEM lvi = {0};
        lvi.mask = LVIF_TEXT;
        lvi.iItem = (int)i;
        lvi.iSubItem = 0;
        
        // Column 0: ID
        wstring wid(database[i].id.begin(), database[i].id.end());
        lvi.pszText = (LPWSTR)wid.c_str();
        int index = ListView_InsertItem(g_hListView, &lvi);
        
        // Column 1: Name
        wstring wname(database[i].name.begin(), database[i].name.end());
        ListView_SetItemText(g_hListView, index, 1, (LPWSTR)wname.c_str());
        
        // Column 2: Age
        wstring wage = to_wstring(database[i].age);
        ListView_SetItemText(g_hListView, index, 2, (LPWSTR)wage.c_str());
        
        // Column 3: GPA
        wchar_t gpaStr[32];
        swprintf(gpaStr, 32, L"%.2f", database[i].gpa);
        ListView_SetItemText(g_hListView, index, 3, gpaStr);
        
        // Column 4: Major
        wstring wmajor(database[i].major.begin(), database[i].major.end());
        ListView_SetItemText(g_hListView, index, 4, (LPWSTR)wmajor.c_str());
        
        // Column 5: Status
        wstring wstatus(database[i].status.begin(), database[i].status.end());
        ListView_SetItemText(g_hListView, index, 5, (LPWSTR)wstatus.c_str());
        
        // Column 6: Email
        wstring wemail(database[i].email.begin(), database[i].email.end());
        ListView_SetItemText(g_hListView, index, 6, (LPWSTR)wemail.c_str());
        
        // Column 7: Phone
        wstring wphone(database[i].phone.begin(), database[i].phone.end());
        ListView_SetItemText(g_hListView, index, 7, (LPWSTR)wphone.c_str());
        
        // Column 8: Enrollment Date
        wstring wenrollment(database[i].enrollmentDate.begin(), database[i].enrollmentDate.end());
        ListView_SetItemText(g_hListView, index, 8, (LPWSTR)wenrollment.c_str());
        
        // Column 9: Nationality
        wstring wnationality(database[i].nationality.begin(), database[i].nationality.end());
        ListView_SetItemText(g_hListView, index, 9, (LPWSTR)wnationality.c_str());
    }
    
    // Update status bar with enhanced information
    wchar_t statusText[512];
    double avgGPA = 0;
    if (!database.empty()) {
        for (const auto& s : database) {
            avgGPA += s.gpa;
        }
        avgGPA /= database.size();
    }
    
    swprintf(statusText, 512, L"Total Students: %zu | Average GPA: %.2f | Ready", 
             database.size(), avgGPA);
    SendMessage(g_hStatusBar, SB_SETTEXT, 0, (LPARAM)statusText);
}

// Generate unique ID
string GenerateID(const string& name) {
    string id = "STU";
    srand((unsigned)time(NULL));
    for (int i = 0; i < 6; i++) {
        id += to_string(rand() % 10);
    }
    return id;
}

// Get current timestamp
string GetCurrentTimestamp() {
    time_t now = time(0);
    char buf[80];
    struct tm timeinfo;
    localtime_s(&timeinfo, &now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return string(buf);
}

// Load data from CSV
void LoadData() {
    database.clear();
    ifstream file("students.csv");
    if (!file.is_open()) return;
    
    string line;
    getline(file, line); // Skip header
    
    while (getline(file, line)) {
        stringstream ss(line);
        Student s;
        string temp;
        
        getline(ss, s.id, ',');
        getline(ss, s.name, ',');
        getline(ss, temp, ',');
        s.age = stoi(temp);
        getline(ss, temp, ',');
        s.gpa = stod(temp);
        getline(ss, s.major, ',');
        getline(ss, s.email, ',');
        getline(ss, s.phone, ',');
        getline(ss, s.address, ',');
        
        database.push_back(s);
    }
    file.close();
}

// Save data to CSV
void SaveData() {
    ofstream file("students.csv");
    file << "ID,Name,Age,GPA,Major,Email,Phone,Address\n";
    
    for (const auto& s : database) {
        file << s.id << "," << s.name << "," << s.age << ","
             << s.gpa << "," << s.major << "," << s.email << ","
             << s.phone << "," << s.address << "\n";
    }
    file.close();
}

// Save As with file dialog
void SaveAsData() {
    OPENFILENAME ofn;
    wchar_t szFile[260] = L"students.csv";
    
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = g_hMainWindow;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile) / sizeof(wchar_t);
    ofn.lpstrFilter = L"CSV Files\0*.csv\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
    ofn.lpstrDefExt = L"csv";
    
    if (GetSaveFileName(&ofn)) {
        // Convert wide string to string for file operations
        int size = WideCharToMultiByte(CP_UTF8, 0, szFile, -1, NULL, 0, NULL, NULL);
        string filename(size, 0);
        WideCharToMultiByte(CP_UTF8, 0, szFile, -1, &filename[0], size, NULL, NULL);
        filename.pop_back(); // Remove null terminator
        
        ofstream file(filename);
        file << "ID,Name,Age,GPA,Major,Email,Phone,Address\n";
        
        for (const auto& s : database) {
            file << s.id << "," << s.name << "," << s.age << ","
                 << s.gpa << "," << s.major << "," << s.email << ","
                 << s.phone << "," << s.address << "\n";
        }
        file.close();
        
        MessageBox(g_hMainWindow, L"Data saved successfully!", L"Save Complete", MB_OK | MB_ICONINFORMATION);
    }
}

// Export to CSV
void ExportToCSV() {
    SaveData();
    MessageBox(g_hMainWindow, L"Data exported to students.csv successfully!", 
               L"Export Complete", MB_OK | MB_ICONINFORMATION);
}

// Delete selected student
void DeleteSelectedStudent() {
    int selected = ListView_GetNextItem(g_hListView, -1, LVNI_SELECTED);
    if (selected == -1) {
        MessageBox(g_hMainWindow, L"Please select a student to delete!", 
                   L"No Selection", MB_OK | MB_ICONWARNING);
        return;
    }
    
    int result = MessageBox(g_hMainWindow, 
                           L"Are you sure you want to delete this student?",
                           L"Confirm Delete", MB_YESNO | MB_ICONQUESTION);
    
    if (result == IDYES) {
        database.erase(database.begin() + selected);
        SaveData();
        RefreshListView();
    }
}

// Show Add Dialog
void ShowAddDialog() {
    DialogBox(g_hInstance, MAKEINTRESOURCE(100), g_hMainWindow, AddDialogProc);
}

// Show Edit Dialog
void ShowEditDialog() {
    int selected = ListView_GetNextItem(g_hListView, -1, LVNI_SELECTED);
    if (selected == -1) {
        ShowNotification("Please select a student to edit!", "warning");
        return;
    }
    g_selectedStudentIndex = selected;
    DialogBox(g_hInstance, MAKEINTRESOURCE(101), g_hMainWindow, EditDialogProc);
}

// Show Search Dialog
void ShowSearchDialog() {
    DialogBox(g_hInstance, MAKEINTRESOURCE(102), g_hMainWindow, SearchDialogProc);
}

// Show Statistics Dialog
void ShowStatsDialog() {
    DialogBox(g_hInstance, MAKEINTRESOURCE(103), g_hMainWindow, StatsDialogProc);
}

// Show Settings Dialog
void ShowSettingsDialog() {
    DialogBox(g_hInstance, MAKEINTRESOURCE(104), g_hMainWindow, SettingsDialogProc);
}

// Show Reports Dialog
void ShowReportsDialog() {
    DialogBox(g_hInstance, MAKEINTRESOURCE(105), g_hMainWindow, ReportsDialogProc);
}

// Show Grade Calculator Dialog
void ShowGradeCalcDialog() {
    DialogBox(g_hInstance, MAKEINTRESOURCE(106), g_hMainWindow, GradeCalcDialogProc);
}

// Import data from CSV
void ImportData() {
    OPENFILENAME ofn;
    wchar_t szFile[260] = L"";
    
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = g_hMainWindow;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile) / sizeof(wchar_t);
    ofn.lpstrFilter = L"CSV Files\0*.csv\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    
    if (GetOpenFileName(&ofn)) {
        // Convert wide string to string
        int size = WideCharToMultiByte(CP_UTF8, 0, szFile, -1, NULL, 0, NULL, NULL);
        string filename(size, 0);
        WideCharToMultiByte(CP_UTF8, 0, szFile, -1, &filename[0], size, NULL, NULL);
        filename.pop_back();
        
        // Load the CSV file
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            getline(file, line); // Skip header
            
            int importCount = 0;
            while (getline(file, line)) {
                // Parse CSV line and add to database
                stringstream ss(line);
                Student s;
                string temp;
                
                getline(ss, s.id, ',');
                getline(ss, s.name, ',');
                getline(ss, temp, ',');
                s.age = stoi(temp);
                getline(ss, temp, ',');
                s.gpa = stod(temp);
                getline(ss, s.major, ',');
                getline(ss, s.email, ',');
                getline(ss, s.phone, ',');
                getline(ss, s.address, ',');
                getline(ss, s.enrollmentDate, ',');
                getline(ss, s.graduationYear, ',');
                getline(ss, s.emergencyContact, ',');
                getline(ss, s.nationality, ',');
                getline(ss, s.status, ',');
                getline(ss, temp, ',');
                s.tuitionFee = stod(temp);
                getline(ss, s.parentGuardian, ',');
                getline(ss, s.bloodGroup, ',');
                getline(ss, s.allergies, ',');
                getline(ss, s.notes);
                
                database.push_back(s);
                importCount++;
            }
            file.close();
            
            SaveData();
            RefreshListView();
            
            wchar_t message[256];
            swprintf(message, 256, L"Successfully imported %d students!", importCount);
            ShowNotification(string(message, message + wcslen(message)), "success");
        }
    }
}

// Bulk edit students
void BulkEditStudents() {
    MessageBox(g_hMainWindow, L"Bulk Edit functionality will be implemented in a future update!", 
               L"Feature Coming Soon", MB_OK | MB_ICONINFORMATION);
}

// Duplicate selected student
void DuplicateStudent() {
    int selected = ListView_GetNextItem(g_hListView, -1, LVNI_SELECTED);
    if (selected == -1) {
        ShowNotification("Please select a student to duplicate!", "warning");
        return;
    }
    
    Student original = database[selected];
    original.id = GenerateID(original.name + "_copy");
    original.name += " (Copy)";
    
    database.push_back(original);
    SaveData();
    RefreshListView();
    ShowNotification("Student duplicated successfully!", "success");
}

// Apply filters
void ApplyFilters() {
    MessageBox(g_hMainWindow, L"Advanced filtering will be available in the next update!", 
               L"Filters", MB_OK | MB_ICONINFORMATION);
}

// Export to PDF
void ExportToPDF() {
    MessageBox(g_hMainWindow, L"PDF export functionality will be available soon!", 
               L"PDF Export", MB_OK | MB_ICONINFORMATION);
}

// Create backup
void CreateBackup() {
    CreateDirectory(L"backup", NULL);
    
    time_t now = time(0);
    struct tm timeinfo;
    localtime_s(&timeinfo, &now);
    
    wchar_t filename[256];
    swprintf(filename, 256, L"backup/students_backup_%04d%02d%02d_%02d%02d%02d.csv",
             timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday,
             timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    
    // Convert to string and save
    int size = WideCharToMultiByte(CP_UTF8, 0, filename, -1, NULL, 0, NULL, NULL);
    string backupFile(size, 0);
    WideCharToMultiByte(CP_UTF8, 0, filename, -1, &backupFile[0], size, NULL, NULL);
    backupFile.pop_back();
    
    ofstream file(backupFile);
    file << "ID,Name,Age,GPA,Major,Email,Phone,Address,EnrollmentDate,GraduationYear,EmergencyContact,Nationality,Status,TuitionFee,ParentGuardian,BloodGroup,Allergies,Notes\n";
    
    for (const auto& s : database) {
        file << s.id << "," << s.name << "," << s.age << ","
             << s.gpa << "," << s.major << "," << s.email << ","
             << s.phone << "," << s.address << "," << s.enrollmentDate << ","
             << s.graduationYear << "," << s.emergencyContact << "," << s.nationality << ","
             << s.status << "," << s.tuitionFee << "," << s.parentGuardian << ","
             << s.bloodGroup << "," << s.allergies << "," << s.notes << "\n";
    }
    file.close();
    
    ShowNotification("Backup created successfully!", "success");
}

// Restore backup
void RestoreBackup() {
    OPENFILENAME ofn;
    wchar_t szFile[260] = L"";
    
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = g_hMainWindow;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile) / sizeof(wchar_t);
    ofn.lpstrFilter = L"CSV Backup Files\0*.csv\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = L"backup";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    
    if (GetOpenFileName(&ofn)) {
        int result = MessageBox(g_hMainWindow,
                               L"This will replace all current data. Continue?",
                               L"Confirm Restore", MB_YESNO | MB_ICONQUESTION);
        
        if (result == IDYES) {
            database.clear();
            // Use ImportData logic here
            ImportData();
            ShowNotification("Backup restored successfully!", "success");
        }
    }
}

// Show notification (simplified version)
void ShowNotification(const string& message, const string& type) {
    wstring wmessage(message.begin(), message.end());
    UINT iconType = MB_ICONINFORMATION;
    
    if (type == "warning") iconType = MB_ICONWARNING;
    else if (type == "error") iconType = MB_ICONERROR;
    else if (type == "success") iconType = MB_ICONINFORMATION;
    
    MessageBox(g_hMainWindow, wmessage.c_str(), L"Notification", MB_OK | iconType);
}

// Load settings from file
void LoadSettings() {
    // Default settings
    g_animationsEnabled = true;
    g_soundsEnabled = true;
    g_autoBackupEnabled = true;
    g_animationSpeed = 150;
    g_currentTheme = "Modern";
    g_backupPath = "backup/";
}

// Save settings to file
void SaveSettings() {
    // This would save settings to a config file
    // Implementation simplified for now
}

// Initialize animations
void InitializeAnimations() {
    if (g_animationsEnabled) {
        // Setup animation timers and effects
    }
}

// Animate button hover effect
void AnimateButton(HWND hButton, bool hover) {
    if (!g_animationsEnabled) return;
    
    // Simple color change animation
    if (hover) {
        SetWindowLongPtr(hButton, GWLP_USERDATA, 1);
    } else {
        SetWindowLongPtr(hButton, GWLP_USERDATA, 0);
    }
    InvalidateRect(hButton, NULL, TRUE);
}

// Slide in window effect
void SlideInWindow(HWND hWnd) {
    if (!g_animationsEnabled) return;
    
    AnimateWindow(hWnd, g_animationSpeed, AW_SLIDE | AW_HOR_POSITIVE);
}

// Fade in window effect
void FadeInWindow(HWND hWnd) {
    if (!g_animationsEnabled) return;
    
    AnimateWindow(hWnd, g_animationSpeed, AW_BLEND);
}

// Play UI sound
void PlayUISound(const string& soundType) {
    if (!g_soundsEnabled) return;
    
    if (soundType == "click") {
        MessageBeep(MB_OK);
    } else if (soundType == "error") {
        MessageBeep(MB_ICONERROR);
    } else if (soundType == "success") {
        MessageBeep(MB_ICONINFORMATION);
    }
}

// Validate student data
bool ValidateStudentData(const Student& student) {
    if (student.name.empty() || student.id.empty()) return false;
    if (student.age < 0 || student.age > 150) return false;
    if (student.gpa < 0.0 || student.gpa > 4.0) return false;
    return true;
}

// Show About Dialog
void ShowAboutDialog() {
    MessageBox(g_hMainWindow,
               L"MWINTELLIGENCE Student Management System\n\n"
               L"Version 2.0\n"
               L"Native Windows Application\n\n"
               L"© 2025 MWINTELLIGENCE\n"
               L"All rights reserved.",
               L"About",
               MB_OK | MB_ICONINFORMATION);
}

// Dialog procedures
INT_PTR CALLBACK AddDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_INITDIALOG:
            return TRUE;
            
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case IDC_BTN_OK: {
                    wchar_t name[100], major[100], email[100], phone[50], address[200];
                    wchar_t ageStr[10], gpaStr[10];
                    
                    GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 100);
                    GetDlgItemText(hDlg, IDC_EDIT_AGE, ageStr, 10);
                    GetDlgItemText(hDlg, IDC_EDIT_GPA, gpaStr, 10);
                    GetDlgItemText(hDlg, IDC_EDIT_MAJOR, major, 100);
                    GetDlgItemText(hDlg, IDC_EDIT_EMAIL, email, 100);
                    GetDlgItemText(hDlg, IDC_EDIT_PHONE, phone, 50);
                    GetDlgItemText(hDlg, IDC_EDIT_ADDRESS, address, 200);
                    
                    if (wcslen(name) == 0) {
                        MessageBox(hDlg, L"Please enter a name!", L"Error", MB_OK | MB_ICONERROR);
                        return TRUE;
                    }
                    
                    Student s;
                    // Convert wide strings to strings
                    int size = WideCharToMultiByte(CP_UTF8, 0, name, -1, NULL, 0, NULL, NULL);
                    s.name.resize(size - 1);
                    WideCharToMultiByte(CP_UTF8, 0, name, -1, &s.name[0], size, NULL, NULL);
                    
                    s.id = GenerateID(s.name);
                    s.age = _wtoi(ageStr);
                    s.gpa = _wtof(gpaStr);
                    
                    size = WideCharToMultiByte(CP_UTF8, 0, major, -1, NULL, 0, NULL, NULL);
                    s.major.resize(size - 1);
                    WideCharToMultiByte(CP_UTF8, 0, major, -1, &s.major[0], size, NULL, NULL);
                    
                    size = WideCharToMultiByte(CP_UTF8, 0, email, -1, NULL, 0, NULL, NULL);
                    s.email.resize(size - 1);
                    WideCharToMultiByte(CP_UTF8, 0, email, -1, &s.email[0], size, NULL, NULL);
                    
                    size = WideCharToMultiByte(CP_UTF8, 0, phone, -1, NULL, 0, NULL, NULL);
                    s.phone.resize(size - 1);
                    WideCharToMultiByte(CP_UTF8, 0, phone, -1, &s.phone[0], size, NULL, NULL);
                    
                    size = WideCharToMultiByte(CP_UTF8, 0, address, -1, NULL, 0, NULL, NULL);
                    s.address.resize(size - 1);
                    WideCharToMultiByte(CP_UTF8, 0, address, -1, &s.address[0], size, NULL, NULL);
                    
                    database.push_back(s);
                    SaveData();
                    RefreshListView();
                    
                    EndDialog(hDlg, IDOK);
                    return TRUE;
                }
                
                case IDC_BTN_CANCEL:
                    EndDialog(hDlg, IDCANCEL);
                    return TRUE;
            }
            break;
    }
    return FALSE;
}

INT_PTR CALLBACK EditDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_INITDIALOG: {
            if (g_selectedStudentIndex >= 0 && g_selectedStudentIndex < (int)database.size()) {
                Student& s = database[g_selectedStudentIndex];
                
                SetDlgItemTextA(hDlg, IDC_EDIT_NAME, s.name.c_str());
                SetDlgItemInt(hDlg, IDC_EDIT_AGE, s.age, FALSE);
                
                wchar_t gpaStr[20];
                swprintf(gpaStr, 20, L"%.2f", s.gpa);
                SetDlgItemText(hDlg, IDC_EDIT_GPA, gpaStr);
                
                SetDlgItemTextA(hDlg, IDC_EDIT_MAJOR, s.major.c_str());
                SetDlgItemTextA(hDlg, IDC_EDIT_EMAIL, s.email.c_str());
                SetDlgItemTextA(hDlg, IDC_EDIT_PHONE, s.phone.c_str());
                SetDlgItemTextA(hDlg, IDC_EDIT_ADDRESS, s.address.c_str());
            }
            return TRUE;
        }
            
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case IDC_BTN_OK: {
                    if (g_selectedStudentIndex >= 0 && g_selectedStudentIndex < (int)database.size()) {
                        wchar_t name[100], major[100], email[100], phone[50], address[200];
                        wchar_t ageStr[10], gpaStr[10];
                        
                        GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 100);
                        GetDlgItemText(hDlg, IDC_EDIT_AGE, ageStr, 10);
                        GetDlgItemText(hDlg, IDC_EDIT_GPA, gpaStr, 10);
                        GetDlgItemText(hDlg, IDC_EDIT_MAJOR, major, 100);
                        GetDlgItemText(hDlg, IDC_EDIT_EMAIL, email, 100);
                        GetDlgItemText(hDlg, IDC_EDIT_PHONE, phone, 50);
                        GetDlgItemText(hDlg, IDC_EDIT_ADDRESS, address, 200);
                        
                        Student& s = database[g_selectedStudentIndex];
                        
                        // Convert wide strings to strings
                        int size = WideCharToMultiByte(CP_UTF8, 0, name, -1, NULL, 0, NULL, NULL);
                        s.name.resize(size - 1);
                        WideCharToMultiByte(CP_UTF8, 0, name, -1, &s.name[0], size, NULL, NULL);
                        
                        s.age = _wtoi(ageStr);
                        s.gpa = _wtof(gpaStr);
                        
                        size = WideCharToMultiByte(CP_UTF8, 0, major, -1, NULL, 0, NULL, NULL);
                        s.major.resize(size - 1);
                        WideCharToMultiByte(CP_UTF8, 0, major, -1, &s.major[0], size, NULL, NULL);
                        
                        size = WideCharToMultiByte(CP_UTF8, 0, email, -1, NULL, 0, NULL, NULL);
                        s.email.resize(size - 1);
                        WideCharToMultiByte(CP_UTF8, 0, email, -1, &s.email[0], size, NULL, NULL);
                        
                        size = WideCharToMultiByte(CP_UTF8, 0, phone, -1, NULL, 0, NULL, NULL);
                        s.phone.resize(size - 1);
                        WideCharToMultiByte(CP_UTF8, 0, phone, -1, &s.phone[0], size, NULL, NULL);
                        
                        size = WideCharToMultiByte(CP_UTF8, 0, address, -1, NULL, 0, NULL, NULL);
                        s.address.resize(size - 1);
                        WideCharToMultiByte(CP_UTF8, 0, address, -1, &s.address[0], size, NULL, NULL);
                        
                        SaveData();
                        RefreshListView();
                    }
                    
                    EndDialog(hDlg, IDOK);
                    return TRUE;
                }
                
                case IDC_BTN_CANCEL:
                    EndDialog(hDlg, IDCANCEL);
                    return TRUE;
            }
            break;
    }
    return FALSE;
}

INT_PTR CALLBACK SearchDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_INITDIALOG:
            return TRUE;
            
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case IDC_BTN_OK: {
                    wchar_t searchTerm[100];
                    GetDlgItemText(hDlg, IDC_EDIT_SEARCH, searchTerm, 100);
                    
                    // Convert to string
                    int size = WideCharToMultiByte(CP_UTF8, 0, searchTerm, -1, NULL, 0, NULL, NULL);
                    string term(size - 1, 0);
                    WideCharToMultiByte(CP_UTF8, 0, searchTerm, -1, &term[0], size, NULL, NULL);
                    
                    // Search and highlight in ListView
                    ListView_DeleteAllItems(g_hListView);
                    
                    for (size_t i = 0; i < database.size(); i++) {
                        if (database[i].name.find(term) != string::npos || 
                            database[i].id.find(term) != string::npos ||
                            database[i].major.find(term) != string::npos) {
                            
                            LVITEM lvi = {0};
                            lvi.mask = LVIF_TEXT;
                            lvi.iItem = ListView_GetItemCount(g_hListView);
                            lvi.iSubItem = 0;
                            
                            wstring wid(database[i].id.begin(), database[i].id.end());
                            lvi.pszText = (LPWSTR)wid.c_str();
                            int index = ListView_InsertItem(g_hListView, &lvi);
                            
                            wstring wname(database[i].name.begin(), database[i].name.end());
                            ListView_SetItemText(g_hListView, index, 1, (LPWSTR)wname.c_str());
                            
                            wstring wage = to_wstring(database[i].age);
                            ListView_SetItemText(g_hListView, index, 2, (LPWSTR)wage.c_str());
                            
                            wchar_t gpaStr[32];
                            swprintf(gpaStr, 32, L"%.2f", database[i].gpa);
                            ListView_SetItemText(g_hListView, index, 3, gpaStr);
                            
                            wstring wmajor(database[i].major.begin(), database[i].major.end());
                            ListView_SetItemText(g_hListView, index, 4, (LPWSTR)wmajor.c_str());
                            
                            wstring wemail(database[i].email.begin(), database[i].email.end());
                            ListView_SetItemText(g_hListView, index, 5, (LPWSTR)wemail.c_str());
                            
                            wstring wphone(database[i].phone.begin(), database[i].phone.end());
                            ListView_SetItemText(g_hListView, index, 6, (LPWSTR)wphone.c_str());
                        }
                    }
                    
                    EndDialog(hDlg, IDOK);
                    return TRUE;
                }
                
                case IDC_BTN_CANCEL:
                    EndDialog(hDlg, IDCANCEL);
                    return TRUE;
            }
            break;
    }
    return FALSE;
}

INT_PTR CALLBACK StatsDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_INITDIALOG: {
            if (database.empty()) {
                SetDlgItemText(hDlg, IDC_STATIC_STATS, L"No students in database");
                return TRUE;
            }
            
            // Calculate statistics
            double totalGPA = 0;
            int totalAge = 0;
            map<string, int> majorCount;
            
            for (const auto& s : database) {
                totalGPA += s.gpa;
                totalAge += s.age;
                majorCount[s.major]++;
            }
            
            double avgGPA = totalGPA / database.size();
            double avgAge = (double)totalAge / database.size();
            
            wchar_t stats[1000];
            swprintf(stats, 1000, 
                L"Total Students: %zu\n"
                L"Average GPA: %.2f\n"
                L"Average Age: %.1f\n\n"
                L"Major Distribution:\n",
                database.size(), avgGPA, avgAge);
            
            wstring statsStr = stats;
            for (const auto& pair : majorCount) {
                wchar_t majorInfo[100];
                swprintf(majorInfo, 100, L"%S: %d students\n", pair.first.c_str(), pair.second);
                statsStr += majorInfo;
            }
            
            SetDlgItemText(hDlg, IDC_STATIC_STATS, statsStr.c_str());
            return TRUE;
        }
            
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case IDC_BTN_OK:
                case IDC_BTN_CANCEL:
                    EndDialog(hDlg, IDOK);
                    return TRUE;
            }
            break;
    }
    return FALSE;
}
