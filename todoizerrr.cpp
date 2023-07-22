/* a to-do list app with advanced functionality */
/* creates two .txt files for state storage */
/* one is main and the other is backup for specific scenarios */
/* they are automatically deleted if empty */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <map>
#include <chrono>
#include <thread>
#include "todoizerrr.hpp"

using std::cout, std::cin, std::string, std::getline, std::ifstream, std::ofstream;

// global variables here
std::vector<string> allTasks;
static bool r_creating = false;
static bool r_editing = false;
static bool r_completing = false;
static bool r_enteringEditMessage = false; 
// r_ stands for reset (of the clock)

/*********************************************************************************************************/

inline void welcomeMessage() {
    cout << COLOR_CYAN << "\n\n\t\t- - - - - Welcome to TODOIZERRR v1.1! - - - - -\n" << RESET_COLOR;
    cout << COLOR_GREEN << "Your tasks: \n" << RESET_COLOR;
}

void tasksFromFile() {
    string task;
    ifstream auxFile(FILE1);

    if(auxFile.is_open()) {
        while(auxFile.good()) {
            getline(auxFile, task);
            allTasks.push_back(task);
        }
    }

    auxFile.close();
}

void transferToCopy(string readFromHere, string writeToHere) {
    string content;
    ifstream auxFile(readFromHere);
    ofstream auxCopy(writeToHere);

    for(int i = 0; !auxFile.eof(); ++i) {
        content += auxFile.get();
    }

    auxFile.close();

    content.erase(content.end() - 1);
    auxCopy << content;          
    auxCopy.close();
}


void displayTasksAndOptions() {
    if(allTasks.size() == 0 || (allTasks.size() == 1 && allTasks.at(0) == "")) {
        cout << "  " << "Nothing to be done! :)\n";
    } else {
        for(size_t i = 0; i < allTasks.size(); ++i) {
            cout << "  " << i+1 << ". " << allTasks.at(i) << '\n';
        }
    }
    
    cout << '\n' << BOLD << "Options: \n" << RESET_COLOR;
    cout << "  > Create a new task ('" << COLOR_YELLOW << "c" << RESET_COLOR << "') \n";
    cout << "  > Edit an existing task ('" << COLOR_YELLOW << "e" << RESET_COLOR << "') \n";
    cout << "  > Mark task as completed ('" << COLOR_YELLOW << "m" << RESET_COLOR << "') \n\n";
}

void todoizer() {
    string option;

    cout << "\n: ";
    getline(cin, option);
    char o = toupper(option[0]);

    if(option.length() > 1) {
        showEverything();
        invalidInput();
        todoizer();
    }

    switch(o) {
        case 'C':
            showEverything();
            taskCreator();
            showEverything();
            break;
        case 'E':
            showEverything();
            taskEditor();
            showEverything();
            break;
        case 'M':
            showEverything();
            taskComplete();
            showEverything();
            break;
        case 'X':
            CLEAR_TERMINAL
            if(allTasks.size() == 0 || (allTasks.size() == 1 && allTasks.at(0) == "")) {
                remove(FILE1);
                remove(FILE2);
            }
            exit(0);
        default:
            showEverything();
            invalidInput();
            break;
    }

    todoizer();
}

inline void invalidInput() {
    cout << "Invalid input.";
}

int taskCreator() {
    string newTask;
    ofstream auxFile(FILE1, std::ios_base::app);
    ofstream auxCopy(FILE2, std::ios_base::app);

    r_creating = true;

    while(newTask == "") {
        cout << "\nWhat do you need to do?: ";
        getline(cin, newTask);
        showEverything();
    }

    if(auxFile.is_open() && auxCopy.is_open()) {
        if(allTasks.at(0) == "") {
            auxFile << newTask;
            auxCopy << newTask;
            allTasks.at(0) = newTask;
            return 0;
        } else {
            auxFile << '\n' << newTask;
            auxCopy << '\n' << newTask;
        }
        allTasks.push_back(newTask);
    }

    r_creating = false;

    auxFile.close();
    auxCopy.close();
    return 0;
}

void taskEditor() {
    float num;
    string editedTask;
    ofstream auxFile(FILE1, std::ios_base::trunc);

    transferToCopy(FILE1, FILE2);

    r_editing = true;

    cout << "\nWhich task do you want to edit? (type a number): ";

    while(1) {
        cin >> num;
        num = std::abs(num);
        if(!cin || num == 0 || num > allTasks.size() || std::floor(num) != num) {
            showEverything();
            invalidInput();
            cin.clear();
            CLEAR_INPUT_BUFFER
            cout << "\nWhich task do you want to edit? (type a number): ";
        } else {
            num = static_cast<int>(num);
            break;
        }
    }

    r_editing = false;
    r_enteringEditMessage = true;

    while(editedTask == "") {
        showEverything();
        cout << "\nType a new message for task " << num << ": ";
        CLEAR_INPUT_BUFFER
        getline(cin, editedTask);
        showEverything();
    }

    --num;
    allTasks.at(num) = editedTask;

    if(auxFile.is_open()) {
        for(size_t i = 0; i < allTasks.size(); ++i) {
            if(i != allTasks.size()-1) {
                auxFile << allTasks[i] << '\n';
            } else {
                auxFile << allTasks[i];
            }
        }
    }

    r_enteringEditMessage = false;

    auxFile.close();
    transferToCopy(FILE1, FILE2);
}

void taskComplete() {
    float num;
    ofstream auxFile(FILE1, std::ios_base::trunc);

    cout << "\nWhich task have you completed? (type a number): ";

    r_completing = true;

    while(1) {
        cin >> num;
        num = std::abs(num);
        if(!cin || num == 0 || num > allTasks.size() || std::floor(num) != num) {
            showEverything();
            invalidInput();
            cin.clear();
            CLEAR_INPUT_BUFFER
            cout << "\nWhich task have you completed? (type a number): ";
        } else {
            num = static_cast<int>(num);
            break;
        }
    }

    CLEAR_INPUT_BUFFER
    --num;
    allTasks.erase(allTasks.begin()+num);

    if(allTasks.size() == 0) {
        allTasks.push_back("");
    }

    if(auxFile.is_open()) {
        for(size_t i = 0; i < allTasks.size(); ++i) {
            if(i != allTasks.size()-1) {
                auxFile << allTasks[i] << '\n';
            } else {
                auxFile << allTasks[i];
            }
        }
    }

    r_completing = false;

    auxFile.close();
    transferToCopy(FILE1, FILE2);
}

string getTime() {
    auto t = std::chrono::system_clock::now();
    std::time_t c_t = std::chrono::system_clock::to_time_t(t);
    string currentTime = string(std::ctime(&c_t));

    currentTime[currentTime.length() - 1] = '\0';
    return currentTime;
}

string displayTime(bool displayNow) {
    char* save;
    char* splitter[7];
    string currentTime = getTime();

    if(!displayNow) {
        if(currentTime[17] != '0' || currentTime[18] != '0') {
            return "";
        }
    }

    splitter[0] = strtok_s(currentTime.data(), " :", &save);
    for(int i = 1; i < 7; ++i) {
        if(splitter != NULL) {
            splitter[i] = strtok_s(NULL, " :", &save);
        }        
    }

    std::map<string, string>Days;
    Days["Mon"] = "Monday";
    Days["Tue"] = "Tuesday";
    Days["Wed"] = "Wednesday";
    Days["Thu"] = "Thursday";
    Days["Fri"] = "Friday";
    Days["Sat"] = "Saturday";
    Days["Sun"] = "Sunday";

    std::map<string, string>Months;
    Months["Jan"] = "January";
    Months["Feb"] = "February";
    Months["Mar"] = "March";
    Months["Apr"] = "April";
    Months["May"] = "May";
    Months["Jun"] = "June";
    Months["Jul"] = "July";
    Months["Aug"] = "August";
    Months["Sep"] = "September";
    Months["Oct"] = "October";
    Months["Nov"] = "November";
    Months["Dec"] = "December";

    string timeLine = "Today is " + 
    Months[splitter[1]] + " " + 
    splitter[2] + ", " + 
    splitter[6] +" | " +
    Days[splitter[0]] +" | " +
    splitter[3] + ":" + 
    splitter[4];
    return timeLine;
}

void concurrentTime() {
    while(1) {
        string time = displayTime(false);

        if(time != "") {
            CLEAR_TERMINAL
            cout << time << COLOR_RED << "\t\t\t  type " 
            << RESET_COLOR << "'" 
            << COLOR_YELLOW << "x" 
            << RESET_COLOR << "'" 
            << COLOR_RED << " to exit\n" 
            << RESET_COLOR;

            welcomeMessage();
            displayTasksAndOptions();

            if(r_creating) {
                cout << "\nWhat do you need to do?: ";
            } else if(r_editing) {
                cout << "\nWhich task do you want to edit? (type a number): ";
            } else if(r_enteringEditMessage) {
                cout << "\nType a new message for your task: ";
            } else if(r_completing) {
                cout << "\nWhich task have you completed? (type a number): ";
            } else {
                cout << "\n: ";
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void showTime() {
    string time = displayTime(true);

    CLEAR_TERMINAL
    cout << time << COLOR_RED << "\t\t\t  type " 
            << RESET_COLOR << "'" 
            << COLOR_YELLOW << "x" 
            << RESET_COLOR << "'" 
            << COLOR_RED << " to exit\n" 
            << RESET_COLOR;
}

void showEverything() {
    showTime();
    welcomeMessage();
    displayTasksAndOptions();
}

int main() {
    ofstream auxFile(FILE1, std::ios_base::app);
    ofstream auxCopy(FILE2, std::ios_base::app);

    auxFile.close();
    auxCopy.close();

    cout << "Press Enter... ";
    std::getchar();

    transferToCopy(FILE2, FILE1);

    tasksFromFile();
    showEverything();
    
    std::thread t1(concurrentTime);
    std::thread t2(todoizer);

    t1.join();
    t2.join();
    return 0;
}