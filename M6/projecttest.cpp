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
    NUM_DIRECTIONS = 4          // Fixed: was 5 due to erroneous NORTHWEST entry
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
bool roomEvent(int room, bool& running);   // Returns false when game should end

// ============================================================================
//  main
// ============================================================================
int main()
{
    srand(static_cast<unsigned int>(time(0)));   // Seed random number generator

    // ── Room data ────────────────────────────────────────────────────────────
    string roomNames[NUM_ROOMS] = {
        "Living Room",
        "Kitchen",
        "Garage",
        "Detached Work Shop",
        "Outside Boat Awning"
    };

    string roomDescriptions[NUM_ROOMS] = {
        "A real bachelor pad, with 1970s style furniture and drapes. "
        "Biscuit is resting on the couch enjoying his morning show Maury.",

        "The floor is tiled black and white; the appliances look like a scene "
        "straight out of Hostel — an Elizabeth Taylor delight.",

        "One-car garage with a concrete floor, a dart board on the wall, "
        "and old furniture covered with moving blankets.",

        "Where money should be spent: Mac tools, a Sawstop table saw, "
        "and a puzzle of 1968 Pontiac GTO parts waiting to be assembled.",

        "A concrete slab under an awning built with a box-gable roof "
        "that really needs those shingles replaced."
    };

    // ── Connection map (adjacency table) ─────────────────────────────────────
    int connections[NUM_ROOMS][NUM_DIRECTIONS];

    for (int r = 0; r < NUM_ROOMS; r++)
        for (int d = 0; d < NUM_DIRECTIONS; d++)
            connections[r][d] = NO_CONNECTION;

    connections[LIVING_ROOM][NORTH] = WORK_SHOP;
    connections[LIVING_ROOM][EAST]  = GARAGE;
    connections[LIVING_ROOM][WEST]  = KITCHEN;

    connections[WORK_SHOP][SOUTH]   = LIVING_ROOM;

    connections[KITCHEN][EAST]      = LIVING_ROOM;

    connections[GARAGE][WEST]       = LIVING_ROOM;   // Fixed: was set twice
    connections[GARAGE][SOUTH]      = BOAT_AWNING;

    connections[BOAT_AWNING][NORTH] = GARAGE;

    // ── Game state ────────────────────────────────────────────────────────────
    int  currentRoom = LIVING_ROOM;
    bool running     = true;

    // ── Opening narrative ─────────────────────────────────────────────────────
    cout << "\nTrey pulls into the driveway after a long day.\n"
         << "He grabs his keys, pushes open the front door,\n"
         << "and steps into the living room...\n";

    // ── Game loop ─────────────────────────────────────────────────────────────
    while (running) {

        // Print where Trey is
        printRoom(roomNames, roomDescriptions, currentRoom);

        // Trigger the event for this room; ends the game if it returns false
        if (!roomEvent(currentRoom, running))
            break;

        if (!running) break;

        // Show available exits and prompt
        printExits(connections, currentRoom);
        cout << "\n> ";

        string command;
        cin >> command;

        // ── Non-movement commands ─────────────────────────────────────────────
        if (command == "quit" || command == "q") {
            running = false;
            continue;
        }

        if (command == "look" || command == "l") {
            continue;   // Loop back; room + exits will reprint at top
        }

        // ── Movement ──────────────────────────────────────────────────────────
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
    return 0;
}

// ============================================================================
//  roomEvent  –  Handles the interactive prompt for each room.
//  Returns true if the game continues, false if the player lost.
// ============================================================================
bool roomEvent(int room, bool& running)
{
    string answer;
    int    roll;

    switch (room) {

        // ── Living Room: wrestle Biscuit (75 win / 25 lose) ──────────────────
        case LIVING_ROOM:
            cout << "\nBiscuit glances up from the couch with a challenging look.\n"
                 << "Do you want to wrestle Biscuit? (yes/no): ";
            cin >> answer;
            if (answer == "yes" || answer == "y") {
                roll = rand() % 100;          // 0–99
                if (roll < 75) {              // 0–74 = win  (75 %)
                    cout << "\nYou pin Biscuit to the cushions! He wags his tail in defeat. Good boy.\n";
                } else {                      // 75–99 = lose (25 %)
                    cout << "\nBiscuit takes you down hard — full-body slam off the couch.\n"
                         << "You tap out. GAME OVER.\n";
                    running = false;
                    return false;
                }
            } else {
                cout << "\nSmart move. Biscuit goes back to Maury.\n";
            }
            break;

        // ── Kitchen: cook dinner (70 no fire / 30 fire) ──────────────────────
        case KITCHEN:
            cout << "\nThe kitchen smells like possibility.\n"
                 << "Do you want to cook dinner? (yes/no): ";
            cin >> answer;
            if (answer == "yes" || answer == "y") {
                roll = rand() % 100;
                if (roll < 70) {              // 0–69 = success (70 %)
                    cout << "\nDinner is served! A fine meal with no incidents whatsoever.\n";
                } else {                      // 70–99 = fire   (30 %)
                    cout << "\nThe grease catches fire! Flames race up the backsplash.\n"
                         << "The kitchen is gone. GAME OVER.\n";
                    running = false;
                    return false;
                }
            } else {
                cout << "\nMaybe cereal tonight. Fair enough.\n";
            }
            break;

        // ── Garage: play darts (60 win / 40 lose) ────────────────────────────
        case GARAGE:
            cout << "\nThe dart board is calling your name.\n"
                 << "Do you want to play darts? (yes/no): ";
            cin >> answer;
            if (answer == "yes" || answer == "y") {
                roll = rand() % 100;
                if (roll < 60) {              // 0–59 = win  (60 %)
                    cout << "\nBull's-eye! Trey wins the game — arms raised in triumph.\n";
                } else {                      // 60–99 = lose (40 %)
                    cout << "\nThe dart sails wide, punches through a gas line behind the wall,\n"
                         << "and the garage fills with fumes. GAME OVER.\n";
                    running = false;
                    return false;
                }
            } else {
                cout << "\nYou leave the darts hanging on the board for another day.\n";
            }
            break;

        // ── Boat Awning: head to the river (75 go / 25 flat) ─────────────────
        case BOAT_AWNING:
            cout << "\nThe river is just down the road and the boat is ready.\n"
                 << "Do you want to head to the river? (yes/no): ";
            cin >> answer;
            if (answer == "yes" || answer == "y") {
                roll = rand() % 100;
                if (roll < 75) {              // 0–74 = success (75 %)
                    cout << "\nYou hook up the boat and make it to the river without a hitch.\n"
                         << "Beautiful day on the water — fish are biting!\n";
                } else {                      // 75–99 = flat   (25 %)
                    cout << "\nThe trailer has a flat tire and there is no spare in sight.\n"
                         << "You're not going anywhere. GAME OVER.\n";
                    running = false;
                    return false;
                }
            } else {
                cout << "\nMaybe another day. The boat sits quietly under the awning.\n";
            }
            break;

        // ── Work Shop: work on the GTO (50 starts / 50 dead) ─────────────────
        case WORK_SHOP:
            cout << "\nThe 1968 Pontiac GTO sits in pieces, waiting for Trey.\n"
                 << "Do you want to work on the GTO? (yes/no): ";
            cin >> answer;
            if (answer == "yes" || answer == "y") {
                roll = rand() % 100;
                if (roll < 50) {              // 0–49 = starts (50 %)
                    cout << "\nShe fires right up! That 400-cubic-inch engine roars to life.\n"
                         << "Neighbors three blocks away heard that. Beautiful.\n";
                } else {                      // 50–99 = dead  (50 %)
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

    return true;   // Game continues
}

// ============================================================================
//  Helper functions
// ============================================================================

// Print the current room's name and description.
void printRoom(const string names[], const string descriptions[], int room)
{
    cout << "\n[ " << names[room] << " ]\n"
         << descriptions[room] << "\n";
}

// Print available exits, skipping NO_CONNECTION entries.
// The second dimension must be specified so the compiler can index the array.
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

// Convert a typed command to a Direction index, or -1 if unrecognised.
int commandToDirection(const string& command)
{
    if (command == "north" || command == "n") return NORTH;
    if (command == "east"  || command == "e") return EAST;
    if (command == "south" || command == "s") return SOUTH;
    if (command == "west"  || command == "w") return WEST;
    return -1;
}