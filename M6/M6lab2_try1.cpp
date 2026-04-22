/*
//M6lab2
//goinesc
//4/15/2026
*/


// M6LAB2: The Dungeon Map Module 6: Arrays
//

//
// THE BIG IDEA
// ------------
// Our dungeon has 5 rooms. Rooms connect to neighbors via N / E
// S / W.
// We need a way to answer: "If I'm in room X and I move north,
//where do I
// end up?"
//
// The answer: an ADJACENCY LIST stored as a 2D array.
// connections[fromRoom][direction] = destination room
//
// We ALSO use PARALLEL ARRAYS to hold each room's name and
//description sets up the world and runs the game loop.
//
//=================================================================
//==========

#define NUM_ROOMS

#include <iostream>
#include <string> 
using namespace std;

int main()
{
// ----- Parallel arrays: both indexed by Room -----
// roomNames[CRYPT] and roomDescriptions[CRYPT] describe the same place.
 string roomNames [NUM_ROOMS] = {
"Entry Hall",
"Ancient Library",
"Cold Kitchen",
"Overgrown Garden",
"Forgotten Crypt"
};
string roomDescriptions[NUM_ROOMS] = {
"A grand hall. A cracked chandelier creaks overhead.",
"Shelves of rotting books. The air tastes like dust.",
"A long kitchen. The stove is cold. Someone left a plate.", 
"Stone paths snake through weeds. A fountain gurgles weakly.",
"A low, damp chamber. The walls remember things you don't."
};
// ----- The adjacency table (a 2D array) -----
// connections[fromRoom][direction] = destination room (or NO_CONNECTION).

int main () connections [NUM_ROOMS] [NUM_DIRECTIONS];
// Step 1: fill every cell with NO_CONNECTION. Clean slate.
// (Nested loops re-describe this room" << endl;
cout << "quit one array lookup.int next = connections[currentRoom][direction];if (next == NO_CONNECTION)
{
cout << "A wall blocks you." << endl;
}
else
{
currentRoom = next;
}
}
cout << "\nYou step back into the light. Thanks for playing."<< endl;
return 0;
}
//
=================================================================
==========
// Function definitions
//
=================================================================
==========
// Print the current room's name and description.
// Arrays come in "by reference" even though the syntax hides it
the compiler needs to know how
// wide each row is to do the math.
void printExits(int connections[][NUM_DIRECTIONS], int room)
{
const string dirNames[NUM_DIRECTIONS] = { "north", "east",
"south", "west" };
cout << "Exits: ";
bool any = false;
for (int d = 0; d < NUM_DIRECTIONS; d++)
{
if (connections[room][d] != NO_CONNECTION)
{
if (any) cout << ", ";
cout << dirNames[d];
any = true;
}
}
if (!any) cout << "(none)";
cout << endl;
}
// Turn a typed command into a direction index, or -1 if it isn't
a direction.
// Keeping this in its own function means the game loop doesn't
drown in
// four near-identical if/else branches.
int commandToDirection(const string& command)
{
if (command == "north" || command == "n") return NORTH;
if (command == "east" || command == "e") return EAST;
if (command == "south" || command == "s") return SOUTH;
if (command == "west" || command == "w") return WEST;
return -1;
}
