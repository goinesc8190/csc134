//M5HW1
//CSC 134
//goinesc
//3/25/2026

#include <iostream>
#include "m5lab1.h"
using namespace std;

// Utility Function Prototypes
int getPlayerChoice(int maxChoice);
void showChoices(string choice1, string choice2, string choice3, string choice4 = "");

int main() {
    cout << "--- Trey's Big Saturday ---" << endl;

    game_start();

    cout << "\nTo be continued..." << endl;
    return 0;
}

// Utility Function Definitions
int getPlayerChoice(int maxChoice) {
    int choice;
    while (true) {
        cout << "Your choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Come on now, type a number." << endl;
            continue;
        }
        if (choice >= 1 && choice <= maxChoice) {
            return choice;
        }
        cout << "Pick a number between 1 and " << maxChoice << ", partner." << endl;
    }
}

void showChoices(string choice1, string choice2, string choice3, string choice4) {
    cout << "---- WHAT'S IT GONNA BE? ----" << endl;
    int num = 1;
    cout << num++ << ". " << choice1 << endl;

    if (choice2 != "") cout << num++ << ". " << choice2 << endl;
    if (choice3 != "") cout << num++ << ". " << choice3 << endl;
    if (choice4 != "") cout << num++ << ". " << choice4 << endl;
}