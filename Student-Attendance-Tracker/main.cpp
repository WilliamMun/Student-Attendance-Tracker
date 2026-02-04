// *********************************************************
// Program: main.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC1L
// Tutorial Class: TT1L
// Trimester: 2530
// Member_1: 252UC2431W | MUN WILLIAM     | MUN.WILLIAM1@STUDENT.MMU.EDU.MY     | 010-830 7571
// Member_2: 252UC242ZA | WONG QIAN XIAN | WONG.QIAN.XIAN1@STUDENT.MMU.EDU.MY | 011-1098 2661
// Member_3: 252UC241W5 | KONG ZHUN RUI  | KONG.ZHUN.RUI1@STUDENT.MMU.EDU.MY  | 012-916 2693
// Member_4: 252UC241TT | ONG ZHONG YIK  | ONG.ZHONG.YIK1@STUDENT.MMU.EDU.MY  | 011-5990 6040
// *********************************************************
// Task Distribution
// Member_1:Create database, TrimDatabaseName, isValidDatabaseName, isDuplicateID, Refine and Modofiy Milestone 1 Code and Flowchart, Documentation 1.0, 2.0 7.0 8.0, 3.0 Flowchart for own part
// Member_2:FindIDColumn, LoadRecord, UpdateRecord, DeleteRecord, Documentation 6.0, 3.0 Flowchart for own part
// Member_3:LoadSheet, ShowSheet, Documentation 4.0, 3.0 Flowchart for own part
// Member_4:LoadDatabase, ShowDatabase, Documentation 5.0, 3.0 Flowchart for own part
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
#include <cstring>
#include <thread>
#include <chrono>
#include <sstream> // Required for CSV parsing

using namespace std;

namespace fs = std::filesystem;

// ===========================
// Global Variable Initialization
// ===========================
// Maximum limits
const int MAX_COLS = 10;
const int MAX_ROWS = 2000;

// Structure variable
struct ColumnData{
    int columnCount;
    string columnNames[MAX_COLS];
    string columnTypes[MAX_COLS];  // INT or TEXT
    string columnDescription[MAX_COLS];
};

struct AttendanceRecord{
    string tableData[MAX_ROWS][MAX_COLS];
    int rowCount = 0;
};

// =============================
// Function Prototype
// =============================
bool isInteger(const string &value);
bool isLabelStudentID(string);
bool filenameExisted(string);
bool isEmpty(string);
ColumnData createSheet(const string&);
void insertRow(ColumnData&, AttendanceRecord&);
void printCentered(string, int);
void showRecord(ColumnData&, AttendanceRecord&);
void saveRecord(const fs::path&, string&, ColumnData&, AttendanceRecord&);
bool isValidDatabaseName(const string&);
string trimDatabaseName(string&);
bool createDatabase(string&);
vector<string> loadDatabase();
void showDatabase(const vector<string>&);
vector<string> loadSheet(const string&);
void showSheet(const vector<string>&);
int findIDColumn(ColumnData&);
void loadRecord(string, ColumnData&, AttendanceRecord&);
bool updateRecord(ColumnData&, AttendanceRecord&);
bool deleteRecord(ColumnData&, AttendanceRecord&);
bool isDuplicateID(AttendanceRecord&, int, string);

// =============================
// MAIN PROGRAM
// =============================
int main() {

    // Local variable initialization
    int databaseCount, sheetCount;
    int choiceDatabaseInt, choiceSheetInt, choiceRecordInt;
    string choiceDatabase, choiceSheet;
    int choiceRecord;
    string databaseName;
    string sheetName;
    string currentDatabase, currentSheet;
    bool createDatabaseStatus, createSheetStatus, choiceDatabaseStatus, choiceSheetStatus, choiceRecordStatus;
    bool exitProgram = false;
    bool exitDatabase = false;
    bool exitSheet = false;
    bool newSheet = false;
    vector<string> databaseList;
    vector<string> sheetList;
    ColumnData columnRecord;
    AttendanceRecord rowRecord;

    cout << "===========================================\n";
    cout << "  STUDENT ATTENDANCE TRACKER - MILESTONE 2\n";
    cout << "===========================================\n\n";
    cout << "Welcome to MMU Student Attendance Tracker!\n" << endl;

    //LEVEL 1: Database selection
    do {

        //LEVEL 1: Database Choice Input Validation + Process
        do {
            cout << "Loading database from system ...\n" << endl;
            this_thread::sleep_for(chrono::seconds(1));

            databaseList = loadDatabase();
            cout << "Available Database:" << endl;
            showDatabase(databaseList);

            cout << "Please select the database or create a new database: (Enter number) ";
            cin >> choiceDatabase;
            cin.ignore(1000, '\n');

            if(!isInteger(choiceDatabase)){
                cout << "Error: Choice must be an integer. Please try again." << endl;
                this_thread::sleep_for(chrono::seconds(1));
                choiceDatabaseStatus = false;
                continue;
            }


            choiceDatabaseInt = stoi(choiceDatabase);

            choiceDatabaseStatus = true;
            if(choiceDatabaseInt == -1){
                do{
                    cout << "Enter database name: (Cannot contain illegal character:\\/:*?\"<>|)" << endl;
                    getline(cin, databaseName);

                    if(isEmpty(databaseName)){
                        cout << "Error: Database name cannot be empty. Please try again." << endl;
                        this_thread::sleep_for(chrono::seconds(1));
                        choiceDatabaseStatus = false;
                        continue;
                    }

                    createDatabaseStatus = createDatabase(databaseName);
                    if(createDatabaseStatus){
                        currentDatabase = databaseName;
                        choiceDatabaseStatus = true;
                    }

                } while (!createDatabaseStatus || !choiceDatabaseStatus);

            } else if(choiceDatabaseInt == -2){
                exitProgram = true;
                break;
            } else if((choiceDatabaseInt - 1) >= 0 && choiceDatabaseInt <= databaseList.size()){
                currentDatabase = databaseList[choiceDatabaseInt - 1];
                databaseName = currentDatabase;
                choiceDatabaseStatus = true;
            } else {
                cout << "Error: Invalid choice. Please try again." << endl;
                this_thread::sleep_for(chrono::seconds(1));
                choiceDatabaseStatus = false;
            }

        } while(choiceDatabaseStatus == false);

        if (choiceDatabaseInt != -2){

            //LEVEL 2: Sheet selection
            string databasePath = "Database/" + currentDatabase;

            do {
                exitDatabase = false;
                cout << "\nLoading " << currentDatabase << " ...\n" << endl;
                this_thread::sleep_for(chrono::seconds(1));

                cout << "------------------------------------------------\n";
                cout << "Database- " << currentDatabase << endl;
                cout << "------------------------------------------------\n";

                //LEVEL 2: Sheet Choice Input Validation + Process
                do {
                    sheetList = loadSheet(databasePath);
                    showSheet(sheetList);
                    cout << "Please select the attendance sheet you want to update or create a new attendance sheet: (Enter number) ";
                    cin >> choiceSheet;
                    cin.ignore(1000, '\n');

                    if(!isInteger(choiceSheet)){
                        cout << "Error: Choice must be an integer. Please try again." << endl;
                        this_thread::sleep_for(chrono::seconds(1));
                        choiceSheetStatus = false;
                        continue;
                    }

                    choiceSheetInt = stoi(choiceSheet);

                    if(choiceSheetInt == -1){
                        do {
                            choiceSheetStatus = true;
                            createSheetStatus = false;

                            cout << "Enter sheet name: (Cannot contain illegal character:\\/:*?\"<>|)" << endl;
                            getline(cin, sheetName);

                            if(isEmpty(sheetName)){
                                cout << "Error: Sheet name cannot be empty. Please try again." << endl;
                                this_thread::sleep_for(chrono::seconds(1));
                                choiceSheetStatus = false;
                                continue;
                            }

                            if(!isValidDatabaseName(sheetName)){
                                cout << "Error: Sheet name invalid. It may contains illegal characters (\\/:*?\"<>|." << endl;
                                this_thread::sleep_for(chrono::seconds(1));
                                continue;
                            }

                            if(!filenameExisted(databasePath + "/" + sheetName+".txt")){
                                cout << "Error: The filename " << sheetName << " already existed.\n" << endl;
                                this_thread::sleep_for(chrono::seconds(1));
                                continue;
                            }

                            columnRecord = createSheet(databasePath + "/" + sheetName + ".txt");
                            createSheetStatus = true;
                            newSheet = true;

                            if(createSheetStatus){
                                cout << "\nAttendance sheet \"" << sheetName << "\" created successfully.\n\n";
                                currentSheet = sheetName;
                                break;
                            }

                        } while(!createSheetStatus || !choiceSheetStatus);

                    } else if(choiceSheetInt == -2) {
                        exitDatabase = true;
                        cout << "\nExit from " << currentDatabase << " ...\n" << endl;
                        break;
                    } else if(choiceSheetInt == -3) {
                        exitDatabase = true;
                        exitProgram = true;
                        break;
                    } else if((choiceSheetInt - 1) >= 0 && choiceSheetInt <= sheetList.size()) {
                        // Logic for selecting an EXISTING sheet
                        currentSheet = sheetList[choiceSheetInt - 1];
                        sheetName = currentSheet;
                        choiceSheetStatus = true;

                        // Load existing data immediately
                        loadRecord(databasePath + "/" + sheetName + ".txt", columnRecord, rowRecord);

                    } else {
                        cout << "Error: Invalid choice. Please try again." << endl;
                        this_thread::sleep_for(chrono::seconds(1));
                        choiceSheetStatus = false;
                    }

                } while(!choiceSheetStatus);

                if (choiceSheetInt != -2 && choiceSheetInt != -3) {

                    //LEVEL 3: Record selection
                    do {

                        if(newSheet){
                            char choice;
                            do {
                                insertRow(columnRecord, rowRecord);
                                cout << "Insert another row? (Y/N): ";
                                cin >> choice;
                                cin.ignore(1000, '\n');
                                cout << "\n";
                            } while (toupper(choice) == 'Y');

                            saveRecord((databasePath + "/" + sheetName+".txt"), sheetName, columnRecord, rowRecord);
                            newSheet = false;
                        }

                        cout << endl;
                        // Display current data (Acts as the View function)
                        showRecord(columnRecord, rowRecord);

                        cout << "Action you can perform:" << endl;
                        cout << "1- Insert New Record" << endl;
                        cout << "2- Update Current Record" << endl;
                        cout << "3- Delete Record" << endl;
                        cout << "4- Exit Attendance Sheet" << endl;
                        cout << "5- Exit The Program" << endl;
                        cout << "Select the action you want to perform: (enter number) ";

                        if(!(cin >> choiceRecord)){
                            cout << "Error: Input must be an integer.\n";
                            this_thread::sleep_for(chrono::seconds(1));
                            cin.clear();
                            cin.ignore(1000, '\n');
                            continue; // Restart loop immediately
                        }
                        cin.ignore(1000,'\n');

                        //LEVEL 3: Record Choice Input Validation + Process
                        switch(choiceRecord){
                            case 1:
                            {
                                insertRow(columnRecord, rowRecord);
                                saveRecord(databasePath + "/" + sheetName+".txt", sheetName, columnRecord, rowRecord);
                                break;
                            }
                            case 2:
                                if(updateRecord(columnRecord, rowRecord)){
                                    saveRecord(databasePath + "/" + sheetName+".txt", sheetName, columnRecord, rowRecord);
                                }
                                break;
                            case 3:
                                if(deleteRecord(columnRecord, rowRecord)){
                                    saveRecord(databasePath + "/" + sheetName+".txt", sheetName, columnRecord, rowRecord);
                                }
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
                                this_thread::sleep_for(chrono::seconds(1));
                        }

                    } while(!exitSheet);

                    rowRecord.rowCount = 0;
                    columnRecord.columnCount = 0;

                    exitSheet = false;
                    currentSheet = "";
                }

            } while(!exitDatabase);

            currentDatabase = "";
        }

    } while(!exitProgram);

    cout << "Thank you for using MMU Student Attendance Tracker System!" << endl;

    return 0;
}

// =============================
// Helper: Validate INT input
// =============================
bool isInteger(const string &value) {
    if (value.empty())
        return false;

    int start = 0;

    if (value[0] == '-') {
        if (value.length() == 1)
            return false;
        start = 1;
    }

    for (int i = start; i < value.length(); i++) {
        if (!isdigit(value[i])) {
            return false;
        }
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
// Helper: Find which column index holds the Student ID
// =============================
int findIDColumn(ColumnData& colData) {
    for (int i = 0; i < colData.columnCount; i++) {
        // We check the NAME using your helper function
        if (isLabelStudentID(colData.columnNames[i])) {
            return i;
        }
    }
    return -1; // Not found
}

// =============================
// Helper: Validate filename existed
// =============================
bool filenameExisted(string sheetName) {
    if (fs::exists(sheetName)){
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
ColumnData createSheet(const string& sheetName) {

    string fileName = sheetName+".txt";
    ColumnData record;

    cout << "-------------------------------------------\n";
    cout << "Create Sheet Structure\n";
    cout << "-------------------------------------------\n";

    // Number of columns
    do {
        cout << "Define number of columns (max 10): ";
        if(!(cin >> record.columnCount)){
            cin.clear();
            cin.ignore(1000, '\n');
        }
        if (record.columnCount < 1 || record.columnCount > MAX_COLS) {
            cout << "Error: Invalid number of columns.\n";
        }
    } while (record.columnCount < 1 || record.columnCount > MAX_COLS);

    cin.ignore(1000, '\n'); // Clear buffer

    // Enter column names and types
    for (int i = 0; i < record.columnCount; i++) {
        do {
            cout << "Enter column " << i + 1 << " name: ";
            getline(cin, record.columnNames[i]);

            if (isEmpty(record.columnNames[i]))
                cout << "Error: Input cannot be empty.\n";
        } while (isEmpty(record.columnNames[i]));

        if (isLabelStudentID(record.columnNames[i]))
            record.columnTypes[i] = "INT";
        else
            record.columnTypes[i] = "TEXT";

        do {
            cout << "Enter column " << i + 1 << " description (enter x if you want to leave it blank):" << endl;
            getline(cin, record.columnDescription[i]);

            if (isEmpty(record.columnDescription[i]))
                cout << "Error: Input cannot be empty.\n";
        } while (isEmpty(record.columnDescription[i]));
    }

    cout << "\nSheet structure created successfully.\n\n";

    return record;
}

// =============================
// Insert a row
// =============================
void insertRow(ColumnData& column, AttendanceRecord& row) {

    if (row.rowCount >= MAX_ROWS) {
        cout << "Error: Maximum row limit reached.\n";
        return;
    }

    cout << "-------------------------------------------\n";
    cout << "Insert New Attendance Row\n";
    cout << "-------------------------------------------\n";

    for (int col = 0; col < column.columnCount; col++) {
        string value;

        while (true) {
            if(column.columnDescription[col] == "x" || column.columnDescription[col] == "X")
                cout << "Enter " << column.columnNames[col] << " (" << column.columnTypes[col] << "): ";
            else
                cout << "Enter " << column.columnNames[col] << " (" << column.columnTypes[col] << ")" << " [" << column.columnDescription[col] << "]"  ": ";
            getline(cin, value);

            // INT validation
            if (column.columnTypes[col] == "INT") {
                if (isInteger(value)) {
                    if (isLabelStudentID(column.columnNames[col])) {
                        if (isDuplicateID(row, col, value)) {
                            cout << "Error: Student ID " << value << " already exists in the list.\n";
                            this_thread::sleep_for(chrono::seconds(1));
                            continue;
                        }
                    }

                    row.tableData[row.rowCount][col] = value;
                    break;
                } else {
                    cout << "Error: Invalid INT value. Please enter a number.\n";
                    this_thread::sleep_for(chrono::seconds(1));
                }
            }
            else {
                // TEXT -> no validation needed
                if (!isEmpty(value)) {
                    row.tableData[row.rowCount][col] = value;
                    break;
                } else {
                    cout << "Error: Field cannot be empty. Please enter data.\n";
                    this_thread::sleep_for(chrono::seconds(1));
                }
            }
        }
    }

    row.rowCount++;

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
void showRecord(ColumnData& column, AttendanceRecord& row) {
    cout << "-------------------------------------------\n";
    cout << "View Attendance Sheet\n";
    cout << "-------------------------------------------\n";

    int maxLength[column.columnCount];

    for (int j = 0; j < column.columnCount; j++) {
        maxLength[j] = column.columnNames[j].length();

        for (int k = 0; k < row.rowCount; k++) {
            // Use a temporary trimmed string for length checking
            string temp = row.tableData[k][j];
            temp.erase(temp.find_last_not_of(" ") + 1);
            if (temp.length() > (size_t)maxLength[j]){
                maxLength[j] = temp.length();
            }
        }
    }

    // Print column headers
    for (int i = 0; i < column.columnCount; i++) {
        printCentered(column.columnNames[i], maxLength[i]);
        if (i < column.columnCount - 1) cout << " , ";
    }
    cout << "\n";

    // Print rows
    for (int r = 0; r < row.rowCount; r++) {
        for (int c = 0; c < column.columnCount; c++) {
            printCentered(row.tableData[r][c], maxLength[c]);
            if (c < column.columnCount - 1) cout << " , ";
        }
        cout << "\n";
    }

    cout << "\n";
}

// =============================
// Save to CSV File
// =============================
void saveRecord(const fs::path& relPath, string& filename, ColumnData& column, AttendanceRecord& row) {
    ofstream file(relPath);

    if (!file.is_open()) {
        cout << "Error: Unable to create CSV file.\n";
        this_thread::sleep_for(chrono::seconds(1));
        return;
    }

    // Write headers
    for (int i = 0; i < column.columnCount; i++) {
        file << column.columnNames[i];
        if (i < column.columnCount - 1) file << ",";
    }
    file << "\n";

    // Write descriptions
    for (int i = 0; i < column.columnCount; i++) {
        file << column.columnDescription[i];
        if (i < column.columnCount - 1) file << ",";
    }
    file << "\n";

    // Write rows
    for (int r = 0; r < row.rowCount; r++) {
        for (int c = 0; c < column.columnCount; c++) {
            file << row.tableData[r][c];
            if (c < column.columnCount - 1) file << ",";
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
    // string containing characters typically forbidden in file systems
    string forbidden = "\\/:*?\"<>|";

    for (char c : databaseName){
        // check if the current character 'c' exists within the 'forbidden' string
        if(forbidden.find(c) != string::npos)
            return false;
    }

    // file systems often reject names ending in a period (.) as it causes path issues
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
    // continue removing characters from the end as long as the string 
    // is not empty and the last character is a space
    while(!isEmpty(databaseName) && databaseName.back() == ' '){
        databaseName.pop_back();
        counter++;
    }
    // feedback to the user if the input was modified
    if (counter>0){
        cout << "Note: Trailing space detected and removed.";
    }
    return databaseName;
}

// =============================
// Create Database (folder)
// =============================
bool createDatabase(string& databaseName){
    if (!isValidDatabaseName(databaseName)){
        cout << "Error: Database name invalid. It may contains illegal characters (\\/:*?\"<>|.)" << endl;
        return false;
    }
    databaseName = trimDatabaseName(databaseName);

    fs::path parentDir = "Database";
    // Error handling: Check Database folder is exists
    if (!fs::exists(parentDir)){
        fs::create_directory(parentDir);
    }

    //Combine parent folder and database name
    fs::path fullPath = parentDir / databaseName;

    // Error handling: Check duplication of databaseName
    if (fs::exists(fullPath)){
        cout << "Error: Database name already exists. Please give a different name." << endl;
        return false;
    }

    if (fs::create_directory(fullPath)){
        cout << "Database " << databaseName << " created successfully!" << endl;
        return true;
    } else {
        cout << "Error: Database failed to be created. Please try again." << endl;
        return false;
    }
}

// Load Sheet in Database
vector<string> loadSheet(const string& path) {
    vector<string> sheetList;

    if (!fs::exists(path)) {
        cout << "Error: Database folder not found.\n";
        return sheetList;
    }

    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            sheetList.push_back(entry.path().stem().string());
        }
    }

    sort(sheetList.begin(), sheetList.end());
    return sheetList;
}

// =============================
// Show Sheet
// =============================
void showSheet(const vector<string>& sheets) {
    int index = 1;

    // iterate through each sheet name and display it with a .txt extension
    for (const auto& sheet : sheets) {
        cout << index++ << "- " << sheet << ".txt" << endl;
    }

    cout << "-1- Create New Sheet" << endl;
    cout << "-2- Exit the Database" << endl;
    cout << "-3- Exit the Program" << endl;
}

vector<string> loadDatabase() {

    vector<string> databaseList;

    // check if the "Database" folder exists and is actually a directory
    if (fs::exists("Database") && fs::is_directory("Database")){
        // iterate through every item found inside the "Database" folder
        for (const auto& entry : fs::directory_iterator("Database")) {
            // only add to the list if the entry is a folder (database), not a file
            if (entry.is_directory()) {
                // extract just the filename and add to our list
                databaseList.push_back(entry.path().filename().string());
            }
        }
    }

    return databaseList;
}

// =============================
// Show Database
// =============================
void showDatabase(const vector<string> &databaseList){
    // loop through the vector to print each database with its corresponding index
    for(int i = 0; i < databaseList.size(); i++){
        // (i+1) ensures the list starts from 1 for better readability
        cout << (i+1) << "- " << databaseList[i] << endl;
    }
    cout << "-1- Create New Database" << endl;
    cout << "-2- Exit the Program" << endl;
}

// =============================
// Load Record Implementation
// =============================
void loadRecord(string fullPath, ColumnData& colData, AttendanceRecord& rowData) {
    // initialize with name and open file
    ifstream file(fullPath);

    //no file is found
    if (!file.is_open()) {
        cout << "Error: File " << fullPath << " not found!\n\n";
        return;
    }

    // declare line to hold the full string
    string line;

    // 1. retrieve headers
    // get the first line, starts with the first column (index0), the word is empty first
    if (getline(file, line)) {
        colData.columnCount = 0;
        string word = "";

        // loop through every character in the line
        // starts for the first column, for the whole line
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == ',') {
                // comma found, check first if exceeds or not, then save the current word into the first column
                // then call function checks its type, increment to the next column
                if (colData.columnCount < MAX_COLS) {
                    colData.columnNames[colData.columnCount] = word;
                    colData.columnTypes[colData.columnCount] = (isLabelStudentID(word)) ? "INT" : "TEXT";
                    colData.columnCount++;
                }
                word = ""; // reset word for the next column
            }
            // if its not a comma and not a carriage return, the words is added one by one alphabet
            else if (line[i] != '\r') {
                word = word + line[i];
            }
        }
        // save the very last word after the loop finishes
        // the line doesnt end with a comma
        if (colData.columnCount < MAX_COLS) {
            colData.columnNames[colData.columnCount] = word;
            colData.columnTypes[colData.columnCount] = (isLabelStudentID(word)) ? "INT" : "TEXT";
            colData.columnCount++;
        }
    }

    // 2. retrieve descriptions
    // read second line, initialize col for description purpose, word is empty now first
    if (getline(file, line)) {
        int dCol = 0;
        string word = "";

        for (int i = 0; i < line.length(); i++) {
            // comma found, check first if exceeds or not, then save the current word into the first column
            // then call function checks its type, increment to the next column
            if (line[i] == ',') {
                if (dCol < colData.columnCount) {
                    colData.columnDescription[dCol] = word;
                    dCol++;
                }
                word = ""; // reset word for the next column
            }
            // if its not a comma and not a carriage return, the words is added one by one alphabet
            else if (line[i] != '\r') {
                word = word + line[i];
            }
        }
        // save the last word, doesnt have comma
        if (dCol < colData.columnCount) {
            colData.columnDescription[dCol] = word;
        }
    }

    // 3. retrieve records, for detail student name, id and status, etc
    // initialize start with first row, and check if there more lines existing
    rowData.rowCount = 0;
    while (rowData.rowCount < MAX_ROWS && getline(file, line)) {
        if (isEmpty(line)) continue; // skip empty lines, and go back to while loop, check next line

        // start with first row, first column
        int col = 0;
        string word = "";

        // if there is a comma, save the first word into the first column
        // like an array, then proceed to the beside column
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == ',') {
                if (col < colData.columnCount) {
                    rowData.tableData[rowData.rowCount][col] = word;
                    col++;
                }
                word = "";
            }
            else if (line[i] != '\r') {
                word = word + line[i];
            }
        }
        // save the last word, that doesnt have a comma
        if (col < colData.columnCount) {
            rowData.tableData[rowData.rowCount][col] = word;
        }

        rowData.rowCount++;
    }
     // close the file and show number of students that has been retrieved
    file.close();
    cout << "\nFile loaded successfully! " << rowData.rowCount << " records retrieved.\n";
}

// =============================
// Update Record Implementation
// =============================
bool updateRecord(ColumnData& colData, AttendanceRecord& rowData) {
    // 1. call the findidcolumna and assign the index to idcol
    int idCol = findIDColumn(colData);

    // if return -1 means no student id can be found
    if (idCol == -1) {
        cout << "Error: No Student ID column found. Cannot identify records.\n";
        return false;
    }

    // declare id that want to be find and get input
    string id;
    cout << "Select Student ID you want to update: ";
    getline(cin, id);

    // we gotten the column from the idcol above, we stick to the same column and interate the rows
    for (int i = 0; i < rowData.rowCount; i++) {
        // compare input ID with data in the ID column
        if (rowData.tableData[i][idCol] == id) {
            cout << "\nUpdating record for " << id << ". Enter 'x' to keep current value.\n";

            for (int j = 0; j < colData.columnCount; j++) {
                // skip updating the ID column itself, and go through everything else
                if (j == idCol) continue;

                // use val to store the input, it cannot be empty, shows the current column and info
                // if the input is not x, we update with the latest input
                // if input is x, we remain the same
                // return true so main will run and update the database
                string val;
                do {
                    cout << "Column: " << colData.columnNames[j] << " (Current: " << rowData.tableData[i][j] << "): ";
                    getline(cin, val);

                    if (isEmpty(val)) {
                        cout << "Error: Input cannot be empty. Please try again.\n";
                    }
                } while (isEmpty(val));

                if (val != "x" && val != "X") {
                    rowData.tableData[i][j] = val;
                }
            }
            cout << "Update successful!\n";
            return true;
        }
    }
    cout << "ERROR: Student ID " << id << " not found!\n";
    this_thread::sleep_for(chrono::seconds(1));
    return false;
}

// =============================
// Delete Record Implementation
// =============================
bool deleteRecord(ColumnData& colData, AttendanceRecord& rowData) {
    // 1. call the findidcolumn and assign index to idcol
    int idCol = findIDColumn(colData);

    // if idcol is return with -1, no column with id is found and will not delete any record in main
    if (idCol == -1) {
        cout << "Error: No Student ID column found.\n";
        this_thread::sleep_for(chrono::seconds(1));
        return false;
    }

    // declare variable to hold id input and get input
    string id;
    cout << "Select Student ID you want to delete: ";
    getline(cin, id);

    // loop through every row but the same column space from the idCol to find the same input iD
    for (int i = 0; i < rowData.rowCount; i++) {
        if (rowData.tableData[i][idCol] == id) {
            // if found, it shows all the info of the student
            cout << "\nRecord found: ";
            for(int c = 0; c < colData.columnCount; c++) {
                cout << rowData.tableData[i][c] << " ";
            }

            cout << "\nAre you sure you want to delete? (Y/N): ";
            // declare variable to hold confirm input
            char confirm;
            cin >> confirm;
            cin.ignore(1000, '\n');

            // if input is Y, runs the delete
            if (toupper(confirm) == 'Y') {
                // shift rows up to overwrite the deleted one, then it is copy column by column
                for (int k = i; k < rowData.rowCount - 1; k++) {
                    for (int c = 0; c < colData.columnCount; c++) {
                        // assign the below row upwards one by one
                        rowData.tableData[k][c] = rowData.tableData[k + 1][c];
                    }
                }
                // decrement for number of row, still exist, but when loop doesnt loop to the extra one
                rowData.rowCount--;
                cout << "Delete successful!\n";
                return true;
            } else {
                cout << "Delete cancelled.\n";
                return false;
            }
        }
    }
    cout << "ERROR: Student ID " << id << " not found.\n";
    this_thread::sleep_for(chrono::seconds(1));
    return false;
}

// =============================
// Helper: Check for Duplicate ID
// =============================
bool isDuplicateID(AttendanceRecord& row, int colIndex, string valueToCheck) {
    // iterate through every row in the current data set
    for (int r = 0; r < row.rowCount; r++) {
        // check if the data at the current row and column matches our input
        if (row.tableData[r][colIndex] == valueToCheck) {
            return true;
        }
    }
    return false;
}