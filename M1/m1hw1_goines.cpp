// CSC134
// M1HW1
// Goines
// 01/25/2026

#include <iostream> 
#include <iomanip> // for decimal places
using namespace std; 

int main() {
    //declare my variables 
    string movie_name = "\"Young Guns\"";
    int released_date = 1988;
    double boxoffice_gross = 45.7;
    int date_first = 1877; 
    
    // do the work
    cout << " The movie " << movie_name << " was released in " << released_date << "." << endl;
    cout << " It grossed " << boxoffice_gross << " billion dollars in the box office. " << endl;
    cout << " The fictional movie is about the Lincoln County, New Mexico war that started in " << date_first << " and lasted for one year." << endl;
    cout << " Emilio Estevez's character, Billy the Kid, has the most memorable quote \"I'll make you famous\"."<< endl; 
    cout << " Another recognizable quote is Dirty Steve Stevens saying,\"he aint all there, is he?\"." << endl;
    cout << " A box office success " << movie_name << " was followed by a sequel \"Young Guns II\" and it has been announced a third movie will be released this year." << endl; 
}  