//CSC 134
//M3T1
//goines
//Ask width and length of two rectangles.
//Find the area.

#include <iostream>
using namespace std;

int main() {

    // Variables
    double lenl, widl, len2, wid2;
    double area1, area2;

    // Ask user for the length and width
    cout << "What is the length of the first rectangle? ";
    cin >> lenl;
    cout << "What is the width of the first rectangle? ";
    cin >> widl;
    cout << "What is the length of the second rectangle? ";
    cin >> len2;
    cout << "What is the width of the second rectangle? ";
    cin >> wid2;
   
    // Display area of both rectangle. 
    area1 = lenl * widl; 
    area2 = len2 * wid2;
    
    cout << "The area of rectangle one = " << area1 << endl;
    cout << "The area of rectangle two = " << area2 << endl;
    
    return 0;
}
