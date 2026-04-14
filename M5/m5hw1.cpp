//CSC 134
//M5HW1
//goinesc
//4/1/26

#include <iostream>
#include <string> month1, month2, month3
using namespace std;

// List all question prototypes here
void question1();
void question2();
// rest go here


// main() here
int main() {

    question1();
    
    question2();
    // and so on
    return 0;
}

// All full questions (function definitions) go here
void question1() {
    
    string month1, month2, month3;
    
    cout << "Please enter the month of the rainfall" << endl;
    cout << "Enter month one"<< endl;
    cin >> month1;
    cout << "Enter month two" << endl;
    cin >> month2;
    cout << "Enter month three" << endl;
    cin >> month3; 

    // Gather average rainfall for 3 months.
}
void question2() {
   string month1, month2, month3;
   double rainfl1, rainfl2, rainfl3, average; 
 cout << "Enter the amount of rainfall in inches for month one" << endl;
    cin >> rainfl1; 
 cout << "Enter the amount of rainfall in inches for month two" << endl;
    cin >> rainfl2; 
 cout << "Enter the amount of rainfall in inches for month three" << endl;
    cin >> rainfl3; 

    // caculation
    average=rainfl1+rainfl2+rainfl3 / 3.0;  

 cout <<"The average rainfall for all three months is" " "<< month1 << month2 << month3 << average <<" " "inches."<< endl;

}