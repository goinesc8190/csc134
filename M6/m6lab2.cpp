//goinesc
//CSC134
//4/24/26

// ============================================================================
//  M6LAB2: The Dungeon Map — Adjacency List Starter
//  CSC 134 — Module 6: Arrays
// ============================================================================
//
//  THE BIG IDEA
//  ------------
//  Our dungeon has 5 rooms. Rooms connect to neighbors via N / E / S / W.
//  We need a way to answer: "If I'm in room X and I move north, where do I
//  end up?"
//
//  The answer: an ADJACENCY LIST stored as a 2D array.
//      connections[fromRoom][direction] = destination room
//
//  We ALSO use PARALLEL ARRAYS to hold each room's name and description —
//  same index in every array points to the same room.
//
//
//  THE MAP
//  -------
//                         [ Detached ]
//                              |
//                              N
//                              |
//         [ Kitchen ] --w--  [ Living Room ]  --E--> [ Garage ]
//                                                        |
//                                                        S
//                                                  [ Boat Awning ]
//
//  Start: ENTRY. Explore with n / e / s / w. Type 'look' or 'quit'.
//
//
//  FUTURE REFACTOR NOTE
//  --------------------
//  Once we learn structs, rooms become a single struct with fields for
//  name, description, and exits. For now, parallel arrays keep everything
//  out in the open where we can see it.
// ============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

enum Direction {
    NORTH = 0,
    EAST  = 1,
    SOUTH = 2,
    WEST  = 3,
    NORTHWEST = 4,
    NUM_DIRECTIONS = 5
};
const int NO_CONNECTION = -1; // Doesn't go anywhere

const string DIRECTION_NAMES[NUM_DIRECTIONS] = {
    "north", "east", "south", "west"
};

enum Room {
    LIVING_ROOM = 0,
    KITCHEN = 1,
    GARAGE  = 2,
    WORK_SHOP   = 3,
    BOAT_AWNING = 4,
    NUM_ROOMS = 5,
};

// The full version of these two functions is at the bottom of the file
void printRoom(const string names[], const string descriptions[], int room);
void printExits(int connections[][NUM_DIRECTIONS], int room);
int commandToDirection(const string& command);

int main()
{
    string roomNames[NUM_ROOMS] = {
       "Living Room",
       "Kitchen",
       "Garage",
       "Detached Work Shop",
       "Outside Boat Awning",
};

 string roomDescriptions[NUM_ROOMS] = {
        "A real bachelor pad, with 1970s style funiture and drapes. Biscuit is resting on the couch enjoying his morning show Maurey.",
        "The floor is tiled black and white, the appliances look like a scene from Hostile, a Elizabeth Taylor delight.",
        " One car garage concrete floor, dart board, and old furniture covered with moving blankets.", 
        "Where money should be spent, Mac tools, Sawstop table saw, and a puzzle of 1968 Pontiac GTO parts.",
        "Concrete slap and awning built with a box gable roof that needs the shingles replaced."
};
// Set up the array
int connections[NUM_ROOMS][NUM_DIRECTIONS]; 
  
for (int r = 0; r < NUM_ROOMS; r++){
    for (int d = 0; d < NUM_DIRECTIONS; d++) {
        connections[r][d]= NO_CONNECTION;
     }
}
    connections[LIVING_ROOM][NORTH] = WORK_SHOP;
    connections[LIVING_ROOM][EAST] = GARAGE;
    connections[LIVING_ROOM][WEST] = KITCHEN;
    connections[LIVING_ROOM][SOUTH] = NO_CONNECTION;

    connections[WORK_SHOP][NORTH] = NO_CONNECTION;
    connections[WORK_SHOP][EAST] = NO_CONNECTION;
    connections[WORK_SHOP][WEST] = NO_CONNECTION;
    connections[WORK_SHOP][SOUTH] = LIVING_ROOM;

    connections[KITCHEN][NORTH] = NO_CONNECTION;
    connections[KITCHEN][EAST] = LIVING_ROOM;
    connections[KITCHEN][WEST] = NO_CONNECTION;
    connections[KITCHEN][SOUTH] = LIVING_ROOM;

    connections[GARAGE][NORTH] = NO_CONNECTION;
    connections[GARAGE][WEST] = NO_CONNECTION;
    connections[GARAGE][WEST] = LIVING_ROOM;
    connections[GARAGE][SOUTH] = BOAT_AWNING;

    connections[BOAT_AWNING][NORTH] = GARAGE;
    connections[BOAT_AWNING][SOUTH] = NO_CONNECTION;
    connections[BOAT_AWNING][EAST] = NO_CONNECTION;
    connections[BOAT_AWNING][WEST] = NO_CONNECTION;

    
// ----- Game state -----
    int  currentRoom = LIVING_ROOM;
    bool running = true;
    
   
// ----- Game loop -----
    while (running)
    {
        printRoom(roomNames, roomDescriptions, currentRoom);
        printExits(connections, currentRoom);

        cout << "\n> ";
        string command;
        cin >> command;

        // Handle non-movement commands first.
        if (command == "quit" || command == "q")
        {
            running = false;
            continue;
        }
        if (command == "look" || command == "l")
        {
            // Loop back around; the top of the loop re-prints the room.
            continue;
        }

        // Translate the command into a direction index (0-3), or -1 if
        // it isn't a direction.
        int direction = commandToDirection(command);
        if (direction == -1)
        {
            cout << "I don't know how to '" << command << "'." << endl;
            continue;
        }

        // Look up where that direction leads from the current room.
        // THIS IS THE POINT OF THE ADJACENCY LIST — one array lookup.
        int next = connections[currentRoom][direction];
        if (next == NO_CONNECTION)
        {
            cout << "A wall blocks you." << endl;
        }
        else
        {
            currentRoom = next;
        }
    }

    cout << "\nYou step back into the light. Thanks for playing." << endl;
    return 0;
}

// ===========================================================================
//  Function definitions
// ===========================================================================

// Print the current room's name and description.
// Arrays come in "by reference" even though the syntax hides it — the
// function can read them but we treat them as const to make that clear.
void printRoom(const string names[], const string descriptions[], int room)
{
    cout << "\n[ " << names[room] << " ]" << endl;
    cout << descriptions[room] << endl;
}

// Print the list of exits from a room. Walks the direction axis of the
// 2D array and skips any NO_CONNECTION entries.
//
// 2D-array parameter note: when a function takes a 2D array, you must tell
// the compiler the SIZE of every dimension except the first. That's why
// the parameter reads [][NUM_DIRECTIONS] — the compiler needs to know how
// wide each row is to do the math.
void printExits(int connections[][NUM_DIRECTIONS], int room)
{
    const string dirNames[NUM_DIRECTIONS] = { "north", "east", "south", "west" };

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

// Turn a typed command into a direction index, or -1 if it isn't a direction.
// Keeping this in its own function means the game loop doesn't drown in
// four near-identical if/else branches.
int commandToDirection(const string& command)
{
    if (command == "north" || command == "n") return NORTH;
    if (command == "east"  || command == "e") return EAST;
    if (command == "south" || command == "s") return SOUTH;
    if (command == "west"  || command == "w") return WEST;
    return -1;
}
void printRoom(const string names[], const string descriptions[], int room);
void printExits(int connections[][NUM_DIRECTIONS], int room);
int  commandToDirection(const string& command);

void printRoom(const string names[], const string descriptions[], int room);
void printExits(int connections[][NUM_DIRECTIONS], int room);
int  commandToDirection(const string& command);

