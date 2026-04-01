// m5lab1.h
// Function prototypes for Trey's Big Saturday

#ifndef M5LAB1_H
#define M5LAB1_H

#include <string>
using namespace std;



// Main game function (you will define this in m5lab1.cpp)
int getPlayerChoice(int maxChoice);
void showChoices(string choice1, string choice2, string choice3);
void game_start();
void wrestle_alligator();
void pontiac_gto();
void boating_newriver();

// Full functions go here
void game_start() {

    cout << "Trey wakes up on a bright Saturday morning." << endl;
    cout << "What should he do first?" << endl;

    showChoices("Wrestle his alligator Biscuit", "Work on his Pontiac GTO", "Go boating on the New River");
    int choice = getPlayerChoice(3);

    if (choice == 1) {
        wrestle_alligator();
                
    } else if (choice == 2) {
        pontiac_gto ();
        
    } else if (choice == 3) {
        boating_newriver ();
    }  
}

void wrestle_alligator() {
    cout << "Trey walks by Biscuit and smacks him on the head to piss him off."<< endl;
}
void pontiac_gto() {
    cout << "Trey walks out to the shop and starts looking for parts." << endl;
}
void boating_newriver() {
    cout << "Trey warms up the old Chevy and connects his boat to the hitch." << endl;
}
// You can add more function prototypes here as your story grows.
// Example:
// void morning_scene();
// void afternoon_scene();
// void evening_scene();




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

void showChoices(string choice1, string choice2, string choice3) {
    cout << "---- WHAT'S IT GONNA BE? ----" << endl;
    int num = 1;
    cout << num++ << ". " << choice1 << endl;

    if (choice2 != "") cout << num++ << ". " << choice2 << endl;
    if (choice3 != "") cout << num++ << ". " << choice3 << endl;
}

#endif
