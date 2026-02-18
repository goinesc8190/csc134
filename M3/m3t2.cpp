// CSC 134
// M3T2 - Craps!
// goinesc
// 2/16/26
// Start the game of craps.

using namespace std;
#include <iostream>
#include <cstdlib> // for random
#include <ctime> //for time

// Function declarations
// (Tell the program what functions will be!)
int roll(); 

//main() goes here
int main() {
   // Seed the random number generator
   int seed = time (0);
   srand(seed);
   
    int number = roll ();
    int first, second, total;
   string result; // did we win or lose?
    first = roll ();
    second = roll ();
    total = first + second;
    cout << "You rolled a " << first << "+" << second << "=" << total << endl;
    
    // how did we do?
    if (total == 7) {
        result = "win";
    }
    else if (total == 11) {
        result = "win";
    }
    else if (total == 2) {
        result = "lose";
    }
    else if (total == 3) {
        result = "lose";
    }
    else if (total == 12) {
        result = "lose";
    }
    else {   
    result = "lose";
    } 
    cout << " ROLL results " <<  result <<endl;
    return 0;
}


// Function definitions
// (Actually write the Entire function!)
int roll() {
    // rand() gives a large random number
    // % 6 divides by six, anf keeps the remainder
    // finally, add 1 so it'o to five.
    int my_roll = (rand() % 6) + 1;
    return my_roll; 


}