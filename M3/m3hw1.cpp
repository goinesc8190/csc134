// CSC 134
// M3HW1 - Gold
//Chris Goines
//3/9/2026

using namespace std;
#include <iostream>
#include <iomanip>  
#include <cstdlib>


// The questions
void question1(); 
void question2(); 
void question3();
void question4();

// main
int main() {
    question1();
    question2();
    question3(); 
    question4(); 
}

// The functions go here
void question1() {
    cout << "Hello I am Mack!" "Are you working on a Mack Pioneer?" << endl;
    //cout <<  "What model year is the Mack Pioneer?" >> endl;
    //cout <<  "What drive configuration is the Mack Pioneer?" >> endl;
    //cout <<  "Does the Max Pioneer have MaxRide Air suspension?" >> endl;
    // Get the answer
 
    string answer;
    cin >> answer;
    if (answer=="yes") {
     cout<<"Great the model year is 2025." << endl; 
}
    else if (answer=="no") {
        cout<<"Please return to the main menu." << endl; 
}
}


void question2() {

    // Declare all variables
string meal_name = "Shrimp Burger"; 
int    num_meals; 
double meal_price;   
double sub_total;          // price before tax and tips
double tax_rate = 0.08;    // 8% is 8/100 ("per cent")
double tip_amount;
double tax_amount;        // $ of the actual tax charged
double total_price;       // subtotal + tip + price  
double dine_in_tip = 0.15;

// user input
cout << "Welcome to the Been Scrimpin' Grill." << endl;
cout << "Todays Special:" << meal_name << endl; 
cout << endl;
cout << "Please enter price of the meal" << endl;
cin  >>  meal_price;
cout << "How many would you like? ";
cin  >> num_meals;
cout << "Is the order dine in or takeaway?" "Please enter 1 if the order is dine in, 2 if it is to go." << endl;
int choice;
cin >> choice;
if (choice==1) {
    cout<< dine_in_tip <<endl;
}
else if (choice==2) {
    cout << "Tip amount? (min 0?) "<<endl;
    cin  >> tip_amount;
}
// Do the calculation
sub_total = meal_price * num_meals;   
tax_amount = sub_total * tax_rate;
total_price = sub_total+tip_amount+tax_amount;

// Present the output
cout << setprecision(2) <<fixed; //remember to import <iomanip>
cout << endl;
cout <<"Your Order" << endl << "--------------------------------" << endl;
cout << num_meals << " x " << meal_name << "\t$" << meal_price << endl;
cout << "sub_total: \t\t$" << sub_total<< endl;
cout << "tax_amount:\t\t$" << tax_amount<< endl;
cout << "tip_amount: \t\t$" << tip_amount<< endl;
cout << "--------------------------------"<< endl;
cout << "total_price:\t\t$" << total_price<< endl;

}

void question3() {
    cout << "Q3: Done, see m3Lab1" << endl;
}

void question4() {

}