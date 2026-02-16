/*
CSC 134
M2HW1 - Gold
Chris Goines
2/15/2026
*/

#include <iostream>
#include <iomanip> // for decimal places 
using namespace std;

int main() { 
// Declare variables
string name;
int accountbalance; 
double deposit;
double withdrawal;
double finalbalance;
double witfinalbalance;
double depfinalbalance;

cout << "What is your name?" <<endl;
    cin >> name; 
    cout << "What is your starting account balance?" <<endl;
    cin >> accountbalance;
    cout << "How much is your deposit?" <<endl;
    cin >> deposit; 
    cout << "What is the amount of your withdrawal?" <<endl;
    cin >> withdrawal;
    
    // Calculate finalbalance;
     depfinalbalance = accountbalance + deposit; 
     witfinalbalance = accountbalance + deposit - withdrawal; 
    
    // Do the work.
    cout << setprecision(2) <<fixed;
    cout << name << endl;
    cout << "Account Number: 52378429"<< endl;
    cout << "Withdrawal Final Balance $"<<  witfinalbalance<< endl;
    cout << "Deposit Final Balance $" << depfinalbalance << endl;
}
    