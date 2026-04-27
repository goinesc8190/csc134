
//M6lab1
//goinesc
//4/27/2026

#include <iostream>
#include <vector>
#include <algorithm>   // std::shuffle
#include <random>      // std::mt19937
using namespace std;

class Restaurant {
  private:
    string name;    // the name
    double rating;  // 0 to 5 stars

  public:
	// constructor 
	Restaurant(string n, double r) {
		name = n;
		rating = r;
	}
	// getters and setters
    void setName(string n) {
        name = n; 
    }
    void setRating(double r) {
        rating = r;
    }
    string getName() const {
        return name;
    }
    double getRating() const {
        return rating;
    }
  
};

int main() {
    
    
    cout << "Restaurant Reviews" << endl;
    
    //Create one Restaurant 
    Restaurant rest1 = Restaurant ("Mi Casita", 4.0);
    cout << rest1.getName() << endl;
    cout << rest1.getRating() << endl;

    // Make another using user input
    Restaurant rest2 = Restaurant("",0.0);
    string n;
    double r;
    cout << "Restaurant Name: ";
    cin>> n;
    cout << "Rating (1.0-5.0): ";
    cin >> r;
    rest2.setName(n);
    rest2.setRating(r);
    cout << rest2.getName() <<endl;
    cout << rest2.getRating() << endl;
    //rest2.display(); 
}