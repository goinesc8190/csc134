// m3lab1
// goines
// 2/23/2026

#include <iostream>
#include <iomanip>   
#include <cstdlib>
using namespace std;

void do_choice_trans_am(); // (1978 Pontiac Trans AM);
void do_choice_lincoln();  // (1965_Lincoln_Continental);
void do_choice_paint_red();
void do_choice_paint_green();

// Global variable -- keeps the vehicle choice
string vehicle;

int main() {
    int choice;
    
    
    cout << "Elite Paint" << endl; 
    cout << "Welcome to Elite Paint Demo! Make the following choices before entering the paint booth."<< endl; 
    cout << "Are you driving"<< endl;
    cout << "1. 1978 Pontiac Trans Am." << endl; 
    cout << "2. 1965 Lincoln Continental." << endl;

    cout << "Please choose choice one or choice two" << endl;
    cin >> choice;
    
    if (choice == 1) {
        do_choice_trans_am(); //  "1978 Pontiac Trans AM";
        
    }
    else if (choice == 2) {
        do_choice_lincoln(); // "1965 Lincoln Continental";
        // now call the paint choice
    }

return 0; //end of game

}

void do_choice_trans_am() {
    vehicle = "1978 Pontiac Trans AM";
    cout << " Would you like to paint your car red or green? " << endl;
    cout << " Please choose choice one or choice two" << endl;
    cout << " 1. Red " << endl;
    cout << " 2. Green " << endl;
    
    int choice;
    cin >> choice; 
    if (choice == 1) {
    do_choice_paint_red(); 
    }
   else if (choice == 2)  { 
    do_choice_paint_green();
   }   
}

void do_choice_lincoln() {
    vehicle = "1965 Lincoln Continental";
}

void do_choice_paint_red() {
    cout << "You painted the " << vehicle << " red" << endl;

}
void do_choice_paint_green(){
    cout << "You painted the " << vehicle << " green" << endl;
}


