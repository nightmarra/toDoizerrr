#pragma once

#include <string>

#define CLEAR_TERMINAL std::cout << "\033[2J\033[1;1H";
#define CLEAR_INPUT_BUFFER std::cin.ignore(1, '\n');
#define FILE1 "auxiliary.txt"
#define FILE2 "auxiliary_copy.txt"
//
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_CYAN "\033[36m"
//
#define BOLD "\033[1m"
#define RESET_COLOR "\033[0m"


inline void welcomeMessage();
inline void invalidInput();

void tasksFromFile();
void transferToCopy(std::string readFromHere, std::string writeToHere);
void displayTasksAndOptions();
void todoizer();
void taskEditor();
void taskComplete();
void concurrentTime();
void showTime();
void showEverything();

int taskCreator();

std::string getTime();
std::string displayTime(bool displayNow);