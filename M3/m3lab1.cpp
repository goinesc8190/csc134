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
    cout << "Elite Paint" << endl; 
    cout << "Welcome to Elite Paint Demo! Make the following choices before entering the paint booth."<< endl; 
    cout << "Are you driving a (1) 1978 Pontiac Trans Am or a (2) 1965 Lincoln Continental." << endl;
    cin >> choice;
    if (choice == 1) {
        do_choice_trans_am();
    }
    else if (choice == 2) {
        do_choice_lincoln();
    }




}