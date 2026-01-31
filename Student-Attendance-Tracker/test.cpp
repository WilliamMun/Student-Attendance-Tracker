// *********************************************************
// Program: main.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC1L
// Tutorial Class: TT1L
// Trimester: 2530
// Member_1: 252UC2431W | MUN WILLIAM     | MUN.WILLIAM1@STUDENT.MMU.EDU.MY    | 010-830 7571
// Member_2: 252UC242ZA | WONG QIAN XIAN | WONG.QIAN.XIAN1@STUDENT.MMU.EDU.MY | 011-1098 2661
// Member_3: 252UC241W5 | KONG ZHUN RUI  | KONG.ZHUN.RUI1@STUDENT.MMU.EDU.MY  | 012-916 2693
// Member_4: 252UC241TT | ONG ZHONG YIK  | ONG.ZHONG.YIK1@STUDENT.MMU.EDU.MY  | 011-5990 6040
// *********************************************************

#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <filesystem>
#include <sstream>

using namespace std;

// ===========================
// Global Variable Initialization
// ===========================
const int MAX_COLS = 10;
const int MAX_ROWS = 2000;

// Struct to represent a single row/record
struct Record {
    string fields[MAX_COLS];
};

string sheetName;
int columnCount;
string columnNames[MAX_COLS];
string columnTypes[MAX_COLS];  // INT or TEXT
string columnDescription[MAX_COLS];

// Array of structures to store all attendance data
Record attendanceRecords[MAX_ROWS];
int rowCount = 0;

// =============================
// Function Prototypes
// =============================
bool isInteger(const string &value);
bool isLabelStudentID(string value);
bool filenameExisted(string fileName);
bool isEmpty(string value);
void createSheet();
void insertRow();
void updateRecord();
void deleteRecord();
void printCentered(string text, int width);
void displayCSV();
void saveToCSV(string filename);
void loadRecord(string selectedSheet);
int findIDColumn();

// =============================
// MAIN PROGRAM
// =============================
int main() {
    cout << "===========================================\n";
    cout << "   STUDENT ATTENDANCE TRACKER - MILESTONE 1\n";
    cout << "===========================================\n\n";

    bool programRunning = true;

    while (programRunning) {
        // --- STARTUP / MAIN MENU ---
        int startChoice = 0;
        cout << "MAIN MENU:\n";
        cout << "1. Create New Attendance Sheet\n";
        cout << "2. Open Existing Attendance Sheet\n";
        cout << "3. Exit The Program\n";
        cout << "Select option: ";

        if (!(cin >> startChoice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nERROR: Invalid input! Please enter a number.\n\n";
            continue;
        }
        cin.ignore();

        if (startChoice == 3) {
            programRunning = false;
            break;
        }
        else if (startChoice == 2) {
            string name;
            cout << "Enter the sheet name to open (without .txt): ";
            getline(cin, name);
            loadRecord(name);
        }
        else if (startChoice == 1) {
            createSheet();
        }
        else {
            cout << "Invalid option selected.\n\n";
            continue;
        }

        // --- ATTENDANCE OPERATIONS MENU (Inside a sheet) ---
        int choice;
        bool inSheet = true;

        while (inSheet) {
            cout << "\n--------------------------------------------------\n";
            string title = "Attendance Sheet - " + sheetName;
            printCentered(title, 50);
            cout << "\n--------------------------------------------------\n";

            displayCSV();

            cout << "Action you can perform:\n";
            cout << "1- Insert new record\n";
            cout << "2- Update record\n";
            cout << "3- Delete record\n";
            cout << "4- Close current sheet (Return to Main Menu)\n";
            cout << "5- Exit The Program\n";
            cout << "Select the action you want to perform: ";

            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nERROR: Invalid choice format!\n";
                continue;
            }
            cin.ignore();

            switch (choice) {
                case 1:
                    insertRow();
                    saveToCSV(sheetName + ".txt");
                    break;
                case 2:
                    updateRecord();
                    saveToCSV(sheetName + ".txt");
                    break;
                case 3:
                    deleteRecord();
                    saveToCSV(sheetName + ".txt");
                    break;
                case 4:
                    saveToCSV(sheetName + ".txt");
                    cout << "\nClosing " << sheetName << " and returning to Main Menu...\n\n";
                    inSheet = false; // Exit inner loop
                    break;
                case 5:
                    saveToCSV(sheetName + ".txt");
                    cout << "Exiting program. Goodbye!\n";
                    inSheet = false;
                    programRunning = false; // Exit both loops
                    break;
                default:
                    cout << "ERROR: " << choice << " is not a valid option!\n";
                    break;
            }
        }
    }
    return 0;
}

// =============================
// Core Functions
// =============================

void loadRecord(string selectedSheet) {
    string fileName = selectedSheet + ".txt";
    ifstream file(fileName);

    if (!file) {
        cout << "Error: File " << fileName << " not found!\n\n";
        sheetName = "";
        return;
    }

    string line, word;

    // 1. Retrieve headers
    if (getline(file, line)) {
        stringstream ss(line);
        columnCount = 0;
        while (getline(ss, word, ',') && columnCount < MAX_COLS) {
            columnNames[columnCount] = word;
            columnTypes[columnCount] = (isLabelStudentID(word)) ? "INT" : "TEXT";
            columnCount++;
        }
    }

    // 2. REFINED: Retrieve descriptions instead of skipping
    if (getline(file, line)) {
        stringstream ssDesc(line);
        int dCol = 0;
        while (getline(ssDesc, word, ',') && dCol < columnCount) {
            columnDescription[dCol] = word;
            dCol++;
        }
    }

    // 3. Retrieve records
    rowCount = 0;
    while (rowCount < MAX_ROWS && getline(file, line)) {
        stringstream ss(line);
        int col = 0;
        while (getline(ss, word, ',') && col < columnCount) {
            attendanceRecords[rowCount].fields[col] = word;
            col++;
        }
        rowCount++;
    }

    file.close();
    sheetName = selectedSheet;
    cout << "\nFile loaded successfully! " << rowCount << " records retrieved.\n";
}

void createSheet() {
    bool fileStatus;
    do {
        cout << "Enter new attendance sheet name: ";
        getline(cin, sheetName);
        fileStatus = filenameExisted(sheetName + ".txt");
        if(!fileStatus) cout << "Error: Filename already exists!\n";
    } while (!fileStatus);

    cout << "Define number of columns (max 10): ";
    cin >> columnCount;
    cin.ignore();

    for (int i = 0; i < columnCount; i++) {
        cout << "Enter column " << i + 1 << " name: ";
        getline(cin, columnNames[i]);
        columnTypes[i] = (isLabelStudentID(columnNames[i])) ? "INT" : "TEXT";
        cout << "Enter column " << i + 1 << " description (or x): ";
        getline(cin, columnDescription[i]);
    }
    rowCount = 0;
    saveToCSV(sheetName + ".txt");
    cout << "\nSheet \"" << sheetName << "\" created successfully.\n";
}

void insertRow() {
    if (rowCount >= MAX_ROWS) {
        cout << "Error: Maximum record limit reached.\n";
        return;
    }
    cout << "\n--- Insert New Attendance Row ---\n";
    for (int col = 0; col < columnCount; col++) {
        string value;
        cout << "Enter " << columnNames[col] << " (" << columnTypes[col] << "): ";
        getline(cin, value);
        attendanceRecords[rowCount].fields[col] = value;
    }
    rowCount++;
    cout << "Row inserted successfully!\n";
}

void updateRecord() {
    int idCol = findIDColumn();
    if (idCol == -1) {
        cout << "Error: No Student ID column defined. Cannot search.\n";
        return;
    }
    string id;
    cout << "Select Student ID you want to update: ";
    getline(cin, id);

    for (int i = 0; i < rowCount; i++) {
        if (attendanceRecords[i].fields[idCol] == id) {
            cout << "\nUpdating record for " << id << ". Enter 'x' to keep current value.\n";
            for (int j = 0; j < columnCount; j++) {
                string val;
                cout << "Column: " << columnNames[j] << " (Current: " << attendanceRecords[i].fields[j] << "): ";
                getline(cin, val);
                if (val != "x" && val != "X") {
                    attendanceRecords[i].fields[j] = val;
                }
            }
            cout << "Update successful!\n";
            return;
        }
    }
    cout << "ERROR: Student ID " << id << " not found!\n";
}

void deleteRecord() {
    int idCol = findIDColumn();
    if (idCol == -1) return;
    string id;
    cout << "Select Student ID you want to delete: ";
    getline(cin, id);

    for (int i = 0; i < rowCount; i++) {
        if (attendanceRecords[i].fields[idCol] == id) {
            cout << "\nRecord found: ";
            for(int c=0; c<columnCount; c++) cout << attendanceRecords[i].fields[c] << " ";

            cout << "\nAre you sure you want to delete? (Y/N): ";
            char confirm; cin >> confirm; cin.ignore();
            if (toupper(confirm) == 'Y') {
                for (int k = i; k < rowCount - 1; k++) {
                    attendanceRecords[k] = attendanceRecords[k + 1];
                }
                rowCount--;
                cout << "Delete successful!\n";
            }
            return;
        }
    }
    cout << "ERROR: Student ID " << id << " not found.\n";
}

// =============================
// Helper Functions
// =============================

bool isLabelStudentID(string value) {
    value.erase(remove_if(value.begin(), value.end(), ::isspace), value.end());
    for (char &c : value) c = tolower(c);
    return (value == "studentid" || value == "id");
}

bool filenameExisted(string fileName) {
    return !filesystem::exists(fileName);
}

int findIDColumn() {
    for (int i = 0; i < columnCount; i++) {
        if (isLabelStudentID(columnNames[i])) return i;
    }
    return -1;
}

void printCentered(string text, int width) {
    int pos = (width - (int)text.length()) / 2;
    if (pos < 0) pos = 0;
    cout << string(pos, ' ') << text << string(max(0, width - (int)text.length() - pos), ' ');
}

void displayCSV() {
    if (rowCount == 0) {
        cout << "\n[No records in current sheet]\n\n";
        return;
    }
    for (int i = 0; i < columnCount; i++) {
        printCentered(columnNames[i], 15);
        if (i < columnCount - 1) cout << " , ";
    }
    cout << "\n";
    for (int r = 0; r < rowCount; r++) {
        for (int c = 0; c < columnCount; c++) {
            printCentered(attendanceRecords[r].fields[c], 15);
            if (c < columnCount - 1) cout << " , ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void saveToCSV(string filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not save to file.\n";
        return;
    }

    // Line 1: Column Names
    for (int i = 0; i < columnCount; i++) file << columnNames[i] << (i < columnCount - 1 ? "," : "");
    file << "\n";

    // Line 2: Descriptions (Required placeholder for loadRecord logic)
    for (int i = 0; i < columnCount; i++) file << (columnDescription[i] == "" ? "x" : columnDescription[i]) << (i < columnCount - 1 ? "," : "");
    file << "\n";

    // Data Lines
    for (int r = 0; r < rowCount; r++) {
        for (int c = 0; c < columnCount; c++) {
            file << attendanceRecords[r].fields[c] << (c < columnCount - 1 ? "," : "");
        }
        file << "\n";
    }
    file.close();
}