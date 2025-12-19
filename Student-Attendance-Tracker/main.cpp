// *********************************************************
// Program: _________.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC1L
// Tutorial Class: TT1L
// Trimester: 2530
// Member_1: 252UC2431W | MUN WILLIAM    | MUN.WILLIAM1@STUDENT.MMU.EDU.MY    | 010-830 7571
// Member_2: 252UC242ZA | WONG QIAN XIAN | WONG.QIAN.XIAN1@STUDENT.MMU.EDU.MY | 011-1098 2661
// Member_3: 252UC241W5 | KONG ZHUN RUI  | KONG.ZHUN.RUI1@STUDENT.MMU.EDU.MY  | 012-916 2693
// Member_4: 252UC241TT | ONG ZHONG YIK  | ONG.ZHONG.YIK1@STUDENT.MMU.EDU.MY  | 011-5990 6040
// *********************************************************
// Task Distribution
// Member_1:
// Member_2:
// Member_3:
// Member_4:
// *********************************************************

// ===========================
// Preprocessor Directive
// ===========================
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
using namespace std;

// ===========================
// Global Variable Initialization
// ===========================
// Maximum limits
const int MAX_COLS = 10;
const int MAX_ROWS = 100;

// Global variables for sheet structure
string sheetName;
int columnCount;
string columnNames[MAX_COLS];
string columnTypes[MAX_COLS];  // INT or TEXT

// Attendance data storage
string tableData[MAX_ROWS][MAX_COLS];
int rowCount = 0;

// =============================
// Function Prototype
// =============================
bool isInteger(string);
void createSheet();
void insertRow();
void displayCSV();
void saveToCSV();

// =============================
// MAIN PROGRAM
// =============================
int main() {
    cout << "===========================================\n";
    cout << "   STUDENT ATTENDANCE TRACKER - MILESTONE 1\n";
    cout << "===========================================\n\n";

    createSheet();

    // Example loop to insert multiple rows
    char choice;

    do {
        insertRow();
        cout << "Insert another row? (Y/N): ";
        cin >> choice;
        cin.ignore();
        cout << "\n";
    } while (toupper(choice) == 'Y');

    displayCSV();

    // Auto-save to CSV
    saveToCSV(sheetName + ".csv");

    cout << "-------------------------------------------\n";
    cout << "End of Milestone 1 Output\n";
    cout << "-------------------------------------------\n";

    return 0;
}

// =============================
// Helper: Validate INT input
// =============================
bool isInteger(const string &value) {
    for (char c : value) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// =============================
// Create Attendance Sheet
// =============================
void createSheet() {
    cout << "Enter attendance sheet name: ";
    cin >> sheetName;

    cout << "\nAttendance sheet \"" << sheetName << "\" created successfully.\n\n";

    // Number of columns
    do {
        cout << "Define number of columns (max 10): ";
        cin >> columnCount;
        if (columnCount < 1 || columnCount > MAX_COLS) {
            cout << "Error: Invalid number of columns.\n";
        }
    } while (columnCount < 1 || columnCount > MAX_COLS);

    cin.ignore(); // Clear buffer

    // Enter column names and types
    for (int i = 0; i < columnCount; i++) {
        cout << "Enter column " << i + 1 << " name: ";
        getline(cin, columnNames[i]);

        cout << "Enter type for " << columnNames[i] << " (INT/TEXT): ";
        cin >> columnTypes[i];
        cin.ignore();

        // Convert type to uppercase for safety
        for (auto &c : columnTypes[i]) c = toupper(c);
    }

    cout << "\nSheet structure created successfully.\n\n";
}

// =============================
// Insert a row
// =============================
void insertRow() {
    if (rowCount >= MAX_ROWS) {
        cout << "Error: Maximum row limit reached.\n";
        return;
    }

    cout << "-------------------------------------------\n";
    cout << "Insert New Attendance Row\n";
    cout << "-------------------------------------------\n";

    for (int col = 0; col < columnCount; col++) {
        string value;

        while (true) {
            cout << "Enter " << columnNames[col] << ": ";
            getline(cin, value);

            // INT validation
            if (columnTypes[col] == "INT") {
                if (isInteger(value)) {
                    tableData[rowCount][col] = value;
                    break;
                } else {
                    cout << "Error: Invalid INT value. Please enter a number.\n";
                }
            }
            else {
                // TEXT → no validation needed
                tableData[rowCount][col] = value;
                break;
            }
        }
    }

    rowCount++;
    cout << "Row inserted successfully.\n\n";
}

// =============================
// View sheet in CSV mode
// =============================
void displayCSV() {
    cout << "-------------------------------------------\n";
    cout << "View Attendance Sheet (CSV Mode)\n";
    cout << "-------------------------------------------\n";

    // Print column headers
    for (int i = 0; i < columnCount; i++) {
        cout << columnNames[i];
        if (i < columnCount - 1) cout << ", ";
    }
    cout << "\n";

    // Print rows
    for (int r = 0; r < rowCount; r++) {
        for (int c = 0; c < columnCount; c++) {
            cout << tableData[r][c];
            if (c < columnCount - 1) cout << ", ";
        }
        cout << "\n";
    }

    cout << "\n";
}

// =============================
// Save to CSV File
// =============================
void saveToCSV(string filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Unable to create CSV file.\n";
        return;
    }

    // Write headers
    for (int i = 0; i < columnCount; i++) {
        file << columnNames[i];
        if (i < columnCount - 1) file << ",";
    }
    file << "\n";

    // Write rows
    for (int r = 0; r < rowCount; r++) {
        for (int c = 0; c < columnCount; c++) {
            file << tableData[r][c];
            if (c < columnCount - 1) file << ",";
        }
        file << "\n";
    }

    file.close();
    cout << "Data saved to " << filename << endl;
}
