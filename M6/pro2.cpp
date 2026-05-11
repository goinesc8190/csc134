//goinesc
//CSC134
//4/24/26

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// ── Directions ──────────────────────────────────────────────────────────────
enum Direction {
    NORTH = 0,
    EAST  = 1,
    SOUTH = 2,
    WEST  = 3,
    NUM_DIRECTIONS = 4
};

const int NO_CONNECTION = -1;

// ── Rooms ────────────────────────────────────────────────────────────────────
enum Room {
    LIVING_ROOM = 0,
    KITCHEN     = 1,
    GARAGE      = 2,
    WORK_SHOP   = 3,
    BOAT_AWNING = 4,
    NUM_ROOMS   = 5
};

// ── Forward declarations ─────────────────────────────────────────────────────
void printRoom(const string names[], const string descriptions[], int room);
void printExits(int connections[][NUM_DIRECTIONS], int room);
int  commandToDirection(const string& command);
bool roomEvent(int room, bool& running);

// ============================================================================
//  main
// ============================================================================
int main()
{
    srand(static_cast<unsigned int>(time(0)));

    string roomNames[NUM_ROOMS] = {
        "Living Room",
        "Kitchen",
        "Garage",
        "Detached Work Shop",
        "Outside Boat Awning"
    };

    string roomDescriptions[NUM_ROOMS] = {
        "A real bachelor pad, with 1970s style furniture and drapes. "
        "Biscuit is resting on the couch enjoying his favorite show Maury.",

        "The floor is tiled black and white; the appliances look like a scene "
        "straight out of Hostel — an Elizabeth Taylor delight.",

        "One-car garage with a concrete floor, a dart board on the wall, "
        "and old furniture covered with moving blankets.",

        "Where money should be spent: Mac tools, a Sawstop table saw, "
        "and a puzzle of 1968 Pontiac GTO parts waiting to be assembled.",

        "A concrete slab under an awning built with a box-gable roof "
        "that really needs those shingles replaced."
    };

    int connections[NUM_ROOMS][NUM_DIRECTIONS];

    for (int r = 0; r < NUM_ROOMS; r++)
        for (int d = 0; d < NUM_DIRECTIONS; d++)
            connections[r][d] = NO_CONNECTION;

    connections[LIVING_ROOM][NORTH] = WORK_SHOP;
    connections[LIVING_ROOM][EAST]  = GARAGE;
    connections[LIVING_ROOM][WEST]  = KITCHEN;

    connections[WORK_SHOP][SOUTH]   = LIVING_ROOM;

    connections[KITCHEN][EAST]      = LIVING_ROOM;

    connections[GARAGE][WEST]       = LIVING_ROOM;
    connections[GARAGE][SOUTH]      = BOAT_AWNING;

    connections[BOAT_AWNING][NORTH] = GARAGE;

    // ── Outer restart loop ────────────────────────────────────────────────────
    bool playAgain = true;

    while (playAgain) {

        int  currentRoom = LIVING_ROOM;
        bool running     = true;

        cout << "\nTrey pulls into the driveway.\n"
             << "He grabs his keys, pushes open the front door,\n"
             << "and steps into the living room...\n";

        while (running) {

            printRoom(roomNames, roomDescriptions, currentRoom);

            if (!roomEvent(currentRoom, running))
                break;

            if (!running) break;

            printExits(connections, currentRoom);
            cout << "\n> ";

            string command;
            cin >> command;

            if (command == "quit" || command == "q") {
                running = false;
                continue;
            }

            if (command == "look" || command == "l") {
                continue;
            }

            int direction = commandToDirection(command);
            if (direction == -1) {
                cout << "I don't know how to '" << command << "'.\n";
                continue;
            }

            int next = connections[currentRoom][direction];
            if (next == NO_CONNECTION) {
                cout << "A wall blocks you.\n";
            } else {
                currentRoom = next;
            }
        }

        cout << "\nYou step back into the light. Thanks for playing.\n";
        cout << "\nWould you like to play again? (yes/no): ";

        string again;
        cin >> again;

        if (again == "yes" || again == "y") {
            cout << "\n--- Starting a new game ---\n";
        } else {
            playAgain = false;
        }
    }

    cout << "\nGoodbye. See you next time, Trey.\n";
    return 0;
}

// ============================================================================
//  roomEvent
// ============================================================================
bool roomEvent(int room, bool& running)
{
    string answer;
    int    roll;

    switch (room) {

        case LIVING_ROOM:
            cout << "\nBiscuit glances up from the couch with a agitated look.\n"
                 << "Do you want to wrestle Biscuit? (yes/no): ";
            cin >> answer;
            if (answer == "yes" || answer == "y") {
                roll = rand() % 100;
                if (roll < 75) {
                    cout << "\nYou pin Biscuit! He growls in defeat.\n";
                } else {
                    cout << "\nBiscuit takes you down hard — full-body roll off the couch.\n"
                         << "You tap out. GAME OVER.\n";
                    running = false;
                    return false;
                }
            } else {
                cout << "\nSmart move. Biscuit goes back to Maury.\n";
            }
            break;

        case KITCHEN:
            cout << "\nThe kitchen smells like this mornings breakfast.\n"
                 << "Do you want to cook dinner? (yes/no): ";
            cin >> answer;
            if (answer == "yes" || answer == "y") {
                roll = rand() % 100;
                if (roll < 70) {
                    cout << "\nDinner is served! A fine meal with no incidents whatsoever.\n";
                } else {
                    cout << "\nThe grease catches fire! Flames race up the backsplash.\n"
                         << "The kitchen is gone. GAME OVER.\n";
                    running = false;
                    return false;
                }
            } else {
                cout << "\nMaybe cereal tonight. Fair enough.\n";
            }
            break;

        case GARAGE:
            cout << "\nThe dart board is calling your name.\n"
                 << "Do you want to play darts? (yes/no): ";
            cin >> answer;
            if (answer == "yes" || answer == "y") {
                roll = rand() % 100;
                if (roll < 60) {
                    cout << "\nBull's-eye! Trey wins the game — arms raised in triumph.\n";
                } else {
                    cout << "\nThe dart sails wide, punches through a gas line behind the wall,\n"
                         << "and the garage fills with fumes. GAME OVER.\n";
                    running = false;
                    return false;
                }
            } else {
                cout << "\nYou leave the darts hanging on the board for another day.\n";
            }
            break;

        case BOAT_AWNING:
            cout << "\nThe river is just down the road and the boat is ready.\n"
                 << "Do you want to head to the river? (yes/no): ";
            cin >> answer;
            if (answer == "yes" || answer == "y") {
                roll = rand() % 100;
                if (roll < 75) {
                    cout << "\nYou hook up the boat and make it to the river without a hitch.\n"
                         << "Beautiful day on the water — fish are biting!\n";
                } else {
                    cout << "\nThe trailer has a flat tire and there is no spare in sight.\n"
                         << "You're not going anywhere. GAME OVER.\n";
                    running = false;
                    return false;
                }
            } else {
                cout << "\nMaybe another day. The boat sits quietly under the awning.\n";
            }
            break;

        case WORK_SHOP:
            cout << "\nThe 1968 Pontiac GTO will not start, waiting for Trey.\n"
                 << "Do you want to work on the GTO? (yes/no): ";
            cin >> answer;
            if (answer == "yes" || answer == "y") {
                roll = rand() % 100;
                if (roll < 50) {
                    cout << "\nShe fires right up! That 400-cubic-inch engine roars to life.\n"
                         << "Neighbors three blocks away heard that. Beautiful.\n";
                } else {
                    cout << "\nNothing. Not even a click. The GTO refuses to start,\n"
                         << "and so does Trey's motivation. GAME OVER.\n";
                    running = false;
                    return false;
                }
            } else {
                cout << "\nThe GTO will wait. It has waited this long already.\n";
            }
            break;

        default:
            break;
    }

    return true;
}

// ============================================================================
//  Helper functions
// ============================================================================

void printRoom(const string names[], const string descriptions[], int room)
{
    cout << "\n[ " << names[room] << " ]\n"
         << descriptions[room] << "\n";
}

void printExits(int connections[][NUM_DIRECTIONS], int room)
{
    const string dirNames[NUM_DIRECTIONS] = { "north", "east", "south", "west" };

    cout << "Exits: ";
    bool any = false;
    for (int d = 0; d < NUM_DIRECTIONS; d++) {
        if (connections[room][d] != NO_CONNECTION) {
            if (any) cout << ", ";
            cout << dirNames[d];
            any = true;
        }
    }
    if (!any) cout << "(none)";
    cout << "\n";
}

int commandToDirection(const string& command)
{
    if (command == "north" || command == "n") return NORTH;
    if (command == "east"  || command == "e") return EAST;
    if (command == "south" || command == "s") return SOUTH;
    if (command == "west"  || command == "w") return WEST;
    return -1;
}
