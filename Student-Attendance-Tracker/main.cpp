// *********************************************************
// Program: main.cpp
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
#include <algorithm>
#include <iomanip>
#include <filesystem>
#include <vector>
using namespace std;

namespace fs = std::filesystem;

// ===========================
// Global Variable Initialization
// ===========================
// Maximum limits
const int MAX_COLS = 10;
const int MAX_ROWS = 2000;

// Global variables for sheet structure
string sheetName;
int columnCount;
string columnNames[MAX_COLS];
string columnTypes[MAX_COLS];  // INT or TEXT
string columnDescription[MAX_COLS];

// Attendance data storage
string tableData[MAX_ROWS][MAX_COLS];
int rowCount = 0;

// =============================
// Function Prototype
// =============================
bool isInteger(const string &value);
bool isLabelStudentID(string);
bool filenameExisted(string);
bool isEmpty(string);
void createSheet(); // do modification on this
void insertRow();
void printCentered(string, int);
void displayCSV();
void saveToCSV(string);
bool isValidDatabaseName(const string&);
string trimDatabaseName(string&);
bool createDatabase(const string&);
void loadDatabase();
void showDatabase();
void loadSheet();
void showSheet();
void loadRecord();
void updateRecord();
void deleteRecord();

// =============================
// MAIN PROGRAM
// =============================
int main() {

    // Local variable initialization
    int choiceDatabase, choiceSheet, choiceRecord;
    int noOfDatabase, noOfSheet, noOfRecord;
    string databaseName;
    string sheetName;
    string currentDatabase, currentSheet;
    bool createDatabaseStatus, createSheetStatus, choiceDatabaseStatus, choiceSheetStatus, choiceRecordStatus;
    bool exitProgram = false;
    bool exitDatabase = false;
    bool exitSheet = false;
    vector<string> databaseList;
    vector<string> sheetList;

    cout << "===========================================\n";
    cout << "  STUDENT ATTENDANCE TRACKER - MILESTONE 2\n";
    cout << "===========================================\n\n";
    cout << "Welcome to MMU Student Attendance Tracker!\n" << endl;

    //LEVEL 1: Database selection
    do {
        //loadDatabase();
        //showDatabase();
        cout << "Please select the database or create a new database: ";
        cin >> choiceDatabase;
        cin.ignore(1000, '\n');

        //LEVEL 1: Database Choice Input Validation + Process
        do {
            choiceDatabaseStatus = true;
            if(choiceDatabase == -1){
                do{
                    cout << "Enter database name: (Cannot contain illegal character:\\/:*?\"<>|)" << endl;
                    getline(cin, databaseName);

                    if(isEmpty(databaseName)){
                        cout << "Error: Database name cannot be empty. Please try again." << endl;
                        choiceDatabaseStatus = false;
                        continue;
                    }

                    createDatabaseStatus = createDatabase(databaseName);
                    if(createDatabaseStatus){
                        currentDatabase = databaseName;
                    }

                } while (!createDatabaseStatus || !choiceDatabaseStatus);

            } else if(choiceDatabase == -2){
                exitProgram = true;
                break;
            } else if(){
                //leave when loadDatabase() is done
            } else {
                cout << "Error: Invalid choice. Please try again." << endl;
                choiceDatabaseStatus = false;
            }

        } while(!choiceDatabaseStatus);

        if (choiceDatabase != -1 && choiceDatabase != -2){

            //LEVEL 2: Sheet selection
            do {
                //loadSheet();
                //showSheet();
                cout << "Please select the attendance sheet you want to update or create a new attendance sheet: ";
                cin >> choiceSheet;
                cin.ignore(1000, '\n');

                //LEVEL 2: Sheet Choice Input Validation + Process
                do {
                    choiceSheetStatus = true;
                    if(choiceSheet == -1){
                        do {
                            cout << "Enter sheet name: (Cannot contain illegal character:\\/:*?\"<>|)" << endl;
                            getline(cin, sheetName);

                            if(isEmpty(sheetName)){
                                cout << "Error: Sheet name cannot be empty. Please try again." << endl;
                                continue;
                                choiceSheetStatus = false;
                            }

                            createSheetStatus = createSheet(sheetName);

                            if(createSheetStatus){
                                currentSheet = sheetName;
                            }

                        } while(!createSheetStatus || !choiceSheetStatus);

                    } else if(choiceSheet == -2) {
                        exitDatabase = true;
                        cout << "Exit from " << databaseName << " ..." << endl;
                        break;
                    } else if(choiceSheet == -3)) {
                        exitDatabase = true;
                        exitProgram = true;
                        break;
                    } else if() {
                        //leave when loadSheet() is done
                    } else {
                        cout << "Error: Invalid choice. Please try again." << endl;
                        choiceSheetStatus = false;
                    }

                } while(!choiceSheetStatus);

                if (choiceSheet != -1 && choiceSheet != -2 && choiceSheet != -3) {

                    //LEVEL 3: Record selection
                    do {
                        //TO-DO: Check if is new sheet, then directly prompt user to input new record as many as they want (as in m1)
                        //loadRecord();
                        //displayCSV();
                        cout << "Action you can perform:" << endl;
                        cout << "1- Insert New Record" << endl;
                        cout << "2- Update Current Record" << endl;
                        cout << "3- Delete Record" << endl;
                        cout << "4- Exit Attendance Sheet" << endl;
                        cout << "5- Exit The Program" << endl;
                        cout << "Select the action you want to perform:";
                        cin >> choiceRecord;
                        cin.ignore(1000, '\n');

                        //LEVEL 3: Record Choice Input Validation + Process
                        do {
                            choiceRecordStatus = true;
                            switch(choiceRecord){
                                case 1:
                                    insertRow();
                                    break;
                                case 2:
                                    //updateRecord();
                                    break;
                                case 3:
                                    //deleteRecord();
                                    break;
                                case 4:
                                    exitSheet = true;
                                    cout << "Exit from " << sheetName << " ..." << endl;
                                    break;
                                case 5:
                                    exitSheet = exitDatabase = exitProgram = true;
                                    break;
                                default:
                                    cout << "Error: Invalid choice. Please try again." << endl;
                                    choiceRecordStatus = false;
                            }

                        } while(!choiceRecordStatus);
                    }

                    currentSheet = "";
                }

            } while(!exitDatabase);

            currentDatabase = "";
        }

    } while(!exitProgram);

    cout << "Thank you for using MMU Student Attendance Tracker System!" << endl;

    return 0;
}

/* Milestone 1 Code:
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
    saveToCSV(sheetName + ".txt");

    cout << "-------------------------------------------\n";
    cout << "End of Milestone 1 Output\n";
    cout << "-------------------------------------------\n";
*/

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
// Helper: Validate input similar to Student ID
// =============================
bool isLabelStudentID(string value) {
    value.erase(remove_if(value.begin(), value.end(), ::isspace), value.end());

    for (char &c : value) {
        c = tolower(c);
    }

    return (value == "studentid" || value == "id");
}

// =============================
// Helper: Validate filename existed
// =============================
bool filenameExisted(string fileName) {
    if (fs::exists(fileName)){
        cout << "Error: The filename " << sheetName << " already existed.\n" << endl;
        return false;
    } else {
        cout << "\nAttendance sheet \"" << sheetName << "\" created successfully.\n\n";
        return true;
    }
}

// =============================
// Helper: Validate empty input
// =============================
bool isEmpty(string value) {
    if (value == "")
        return true;
    else
        return false;
}

// =============================
// Create Attendance Sheet
// =============================
void createSheet() {
    bool fileStatus;
    do {
        cout << "Enter attendance sheet name: ";
        cin >> sheetName;
        string fileName = sheetName+".txt";

        fileStatus = filenameExisted(fileName);
    } while(fileStatus == false);

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
        do {
            cout << "Enter column " << i + 1 << " name: ";
            getline(cin, columnNames[i]);

            if (isEmpty(columnNames[i]))
                cout << "Error: Input cannot be empty.\n";
        } while (isEmpty(columnNames[i]));

        if (isLabelStudentID(columnNames[i]))
            columnTypes[i] = "INT";
        else
            columnTypes[i] = "TEXT";

        do {
            cout << "Enter column " << i + 1 << " description (enter x if you want to leave it blank):" << endl;
            getline(cin, columnDescription[i]);

            if (isEmpty(columnDescription[i]))
                cout << "Error: Input cannot be empty.\n";
        } while (isEmpty(columnDescription[i]));
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
            if(columnDescription[col] == "x" || columnDescription[col] == "X")
                cout << "Enter " << columnNames[col] << " (" << columnTypes[col] << "): ";
            else
                cout << "Enter " << columnNames[col] << " (" << columnTypes[col] << ")" << " [" << columnDescription[col] << "]"  ": ";
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
                // TEXT -> no validation needed
                tableData[rowCount][col] = value;
                break;
            }
        }
    }

    rowCount++;
    cout << "Row inserted successfully.\n\n";
}

// =============================
// Helper: Print Text Align to Center
// =============================
void printCentered(string text, int width) {
    //Remove leading/trailing whitespace to ensure accurate length
    text.erase(text.find_last_not_of(" \n\r\t") + 1);
    text.erase(0, text.find_first_not_of(" \n\r\t"));

    int len = text.length();
    if (len >= width) {
        cout << text;
    } else {
        int pos = (width - len) / 2;
        cout << string(pos, ' ') << text << string(width - len - pos, ' ');
    }
}

// =============================
// View sheet in CSV mode
// =============================
void displayCSV() {
    cout << "-------------------------------------------\n";
    cout << "View Attendance Sheet (CSV Mode)\n";
    cout << "-------------------------------------------\n";

    int maxLength[columnCount];

    for (int j = 0; j < columnCount; j++) {
        maxLength[j] = columnNames[j].length();

        for (int k = 0; k < rowCount; k++) {
            // Use a temporary trimmed string for length checking
            string temp = tableData[k][j];
            temp.erase(temp.find_last_not_of(" ") + 1);
            if (temp.length() > (size_t)maxLength[j]){
                maxLength[j] = temp.length();
            }
        }
    }

    // Print column headers
    for (int i = 0; i < columnCount; i++) {
        printCentered(columnNames[i], maxLength[i]);
        if (i < columnCount - 1) cout << " , ";
    }
    cout << "\n";

    // Print rows
    for (int r = 0; r < rowCount; r++) {
        for (int c = 0; c < columnCount; c++) {
            printCentered(tableData[r][c], maxLength[c]);
            if (c < columnCount - 1) cout << " , ";
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

    // Write descriptions
    for (int i = 0; i < columnCount; i++) {
        file << columnDescription[i];
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

// =============================
// Helper: Validate databaseName
// =============================
bool isValidDatabaseName(const string& databaseName){
    string forbidden = "\\/:*?\"<>|";

    for (char c : databaseName){
        if(forbidden.find(c) != string::npos)
            return false;
    }

    if(databaseName.back() == '.'){
        return false;
    }

    return true;
}

// =============================
// Helper: Trim space at the end of databaseName
// =============================
string trimDatabaseName(string& databaseName){
    int counter = 0;
    while(!isEmpty(databaseName) && databaseName.back() == ' '){
        databaseName.pop_back();
        counter++;
    }
    if (counter>0){
        cout << "Note: Trailing space detected and removed.";
    }
    return databaseName;
}

// =============================
// Create Database (folder)
// =============================
bool createDatabase(const string& databaseName){
    if (!isValidDatabaseName(databaseName))){
        cout << "Error: Database name invalid. It may contains illegal characters (\\/:*?\"<>|.)" << endl;
        return false;
    }
    databaseName = trimDatabaseName(databaseName);
    fs::path relativePath(databaseName);

    // Error handling: Check duplication of databaseName
    if (fs::exists(relativePath)){
        cout << "Error: Database name already exists. Please give a different name." << endl;
        return false;
    }

    if (fs::create_directory(relativePath)){
        cout << "Database " << databaseName << " created successfully!" << endl;
        return true;
    } else {
        cout << "Error: Database failed to be created. Please try again." << endl;
        return false;
    }
}

//=========================================
//load record, update record, delete record
//=========================================
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