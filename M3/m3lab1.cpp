// m3lab1
// goines
// 2/23/2026

#include <iostream>
#include <iomanip>   
#include <cstdlib>
using namespace std;

void do_choice_trans_am(); // (1978 Pontiac Trans AM);
void do_choice_lincoln();  // (1965_Lincoln_Continental);
void do_choice_3();
void do_choice_4();

int main() {
    int choice;
    string do_choice_trans_am();
    
    cout << "Elite Paint" << endl; 
    cout << "Welcome to Elite Paint Demo! Make the following choices before entering the paint booth."<< endl; 
    cout << "Are you driving a or a"<< endl;
    cout << "1. 1978 Pontiac Trans Am." << endl; 
    cout << "2. 1965 Lincoln Continental." << endl;

    cout << "Please choose choice one or choice two" << endl;
    cin >> choice;
    
    if (choice == 1) {
        do_choice_trans_am() = "1978 Pontiac Trans AM";
    }
    else if (choice == 2) {
        do_choice_lincoln();
    }

return 0; //end of game

}