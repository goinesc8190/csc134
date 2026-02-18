/*  
CSC 134
M2hw1q3 - Pizza Party
goines
2/16/26
*/

#include <iostream>
#include <iomanip> 
using namespace std;

int main() { 
    string name;
    int numpizzas; // nine slices per pizza
    double slicespizza;
    double slicesperguest = 3.0;
    double numvisitors;
    double leftoverpizza;

    cout << "How many pizzas would you like?" << endl;
         cin >> numpizzas;
         cout <<"How many slices per pizza?" << endl;
         cin >> slicespizza;
         cout <<"How many visitors are coming?" << endl;
         cin >> numvisitors;
 
    // Caculate final
    leftoverpizza = numpizzas * slicespizza - numvisitors * slicesperguest;
  
    // Do the work
    cout << setprecision(2) <<fixed;
    cout << "Pieces of pizza left over = " << leftoverpizza << endl;
     
    
}