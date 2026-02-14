// CSC 134
// m2t1 - Apple Sales
// Goines
// 2/13/2025

#include <iostream>
#include <iomanip> // for decimal places 
using namespace std;

int main() {
    // Declare my variables 
    string name;
    int numtools; 
    double pricepertool;
    double totalcost;
    
    cout << "What is your name?" <<endl;
    cin >> name; 
    cout << "How many tools are for sale?" <<endl;
    cin >> numtools;
    cout << "How much per tool?" <<endl;
    cin >> pricepertool; 


    // Do the work - Welcome them to the store.
    cout << "Welcome to the tool store" " " << name <<"."<< endl;
    cout << "We have "  << numtools << " " << "tools in stock" <<  "."  << endl;
    cout << "Price per tool is $"<<pricepertool << " each. " << endl; 

    // Calculate the total price
    totalcost = numtools * pricepertool;
    // Print the total
    cout << "To buy all of them will cost $" << totalcost << endl;
}
    