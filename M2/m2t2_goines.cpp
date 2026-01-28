/*
CSC 134
M2T2 - Receipt calculator
goines
1/26/26
Goal: A correct looking receipt that handles sales tax.
Assumption: Sales tax is 8% (varies by county)
*/

#include <iostream>
using namespace std;
// if don't use namespace, type std: :cout every time instead of cout (also cin)

int main() {
// Declare all variables
string meal_name = "Shrimp Burger"; 
int    num_meals; 
double meal_price = 5.99;   // 5.99
double sub_total;          // price before tax and tips
double tax_rate = 0.08;    // 8% is 8/100 ("per cent")
double tip_amount;
double tax_amount;        // $ of the actual tax charged
double total_price;       // subtotal + tip + price  


// user input
cout << "Welcome to the Been Scrimpin' Grill." << endl;
cout << "Todays Special:" << meal_name << endl; 
cout << endl;
cout << "How many would you like? ";
cin  >> num_meals;
cout << "Tip amount? (min 0?) ";
cin  >>  tip_amount;

// Do the calculation
sub_total = meal_price * num_meals;   


// Present the output
cout << endl;
cout <<"Your Order" << endl << "--------------------------" << endl;
cout << num_meals << " x " << meal_name << "\t$" << meal_price << endl;
cout << "sub_total: \t\t$" << sub_total<< endl;
cout << "Tip amount \t\t$" << tip_amount<< endl;


return 0; //no errors

} 
 