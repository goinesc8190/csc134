/*
//M7lab1 - Spherical (Radial) Display Version
//goinesc
//5/4/2026
*/

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cstring>
#include <cmath>
#include <string>

using namespace std;

// Direction constants
enum Direction {
    NORTH = 1,
    SOUTH = 2,
    EAST  = 4,
    WEST  = 8
};

// Mapping of direction to cell offset
const std::pair<int, int> DIRECTION_OFFSETS[] = {
    {0, 0},  // Placeholder for index 0
    {0, -1}, // NORTH
    {0, 1},  // SOUTH
    {0, 0},  // Placeholder
    {1, 0},  // EAST
    {0, 0},  // Placeholder
    {0, 0},  // Placeholder
    {0, 0},  // Placeholder
    {-1, 0}  // WEST
};

// Mapping of directions to their opposites
const Direction OPPOSITES[] = {
    (Direction)0, // Placeholder for index 0
    SOUTH,        // Opposite of NORTH is SOUTH
    NORTH,        // Opposite of SOUTH is NORTH
    (Direction)0, // Placeholder
    WEST,         // Opposite of EAST is WEST
    (Direction)0, // Placeholder
    (Direction)0, // Placeholder
    (Direction)0, // Placeholder
    EAST          // Opposite of WEST is EAST
};

// Cell class representing a single cell in the maze
class Cell {
private:
    int row;
    int col;
    int links; // Bit flags for linked directions

public:
    Cell(int row, int col) : row(row), col(col), links(0) {}

    int getRow() const { return row; }
    int getCol() const { return col; }

    bool linked(Direction direction) const {
        return (links & direction) != 0;
    }

    void link(Direction direction) {
        links |= direction;
    }

    void unlink(Direction direction) {
        links &= ~direction;
    }

    std::vector<Direction> getLinks() const {
        std::vector<Direction> result;
        if (linked(NORTH)) result.push_back(NORTH);
        if (linked(SOUTH)) result.push_back(SOUTH);
        if (linked(EAST))  result.push_back(EAST);
        if (linked(WEST))  result.push_back(WEST);
        return result;
    }
};

// Grid class representing the entire maze
class Grid {
private:
    int rows;
    int cols;
    std::vector<std::vector<Cell>> cells;
    std::mt19937 rng;

public:
    Grid(int rows, int cols) : rows(rows), cols(cols) {
        rng.seed(static_cast<unsigned int>(std::time(nullptr)));

        cells.resize(rows);
        for (int r = 0; r < rows; r++) {
            cells[r].reserve(cols);
            for (int c = 0; c < cols; c++) {
                cells[r].emplace_back(r, c);
            }
        }
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }

    bool isValid(int row, int col) const {
        return row >= 0 && row < rows && col >= 0 && col < cols;
    }

    Cell& at(int row, int col) {
        return cells[row][col];
    }

    const Cell& at(int row, int col) const {
        return cells[row][col];
    }

    int random(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }

    void linkCells(int row1, int col1, Direction dir) {
        if (!isValid(row1, col1)) return;

        int row2 = row1 + DIRECTION_OFFSETS[dir].second;
        int col2 = col1 + DIRECTION_OFFSETS[dir].first;

        if (!isValid(row2, col2)) return;

        at(row1, col1).link(dir);
        at(row2, col2).link(OPPOSITES[dir]);
    }

    // ---------------------------------------------------------------
    // Radial / spherical display
    // The maze rows become concentric rings (row 0 = innermost ring).
    // Each cell in a ring occupies an angular slice of that ring.
    // Walls are drawn using ASCII characters on a 2D character canvas.
    // ---------------------------------------------------------------
    void display() const {
        // Scale factor: how many terminal characters per cell
        const int CELL_W = 4; // characters wide per cell
        const int CELL_H = 2; // characters tall per cell

        // Outer radius in cells (rows), add 1 for border
        int outerR = rows + 1;

        // Canvas size: diameter + some padding
        int canvasSize = (outerR * 2 + 2) * max(CELL_W, CELL_H) + 4;
        int cx = canvasSize / 2; // centre x
        int cy = canvasSize / 4; // centre y (terminals are ~2:1 char ratio)

        // Actual canvas height accounts for terminal char aspect ratio
        int canvasH = canvasSize / 2 + 2;
        int canvasW = canvasSize;

        // Fill canvas with spaces
        std::vector<std::string> canvas(canvasH, std::string(canvasW, ' '));

        auto putChar = [&](int x, int y, char ch) {
            if (y >= 0 && y < canvasH && x >= 0 && x < canvasW) {
                // Only overwrite space or weaker characters
                char existing = canvas[y][x];
                // Priority: '#' > '+' > '-' > '|' > '.' > ' '
                auto priority = [](char c) -> int {
                    if (c == '#') return 5;
                    if (c == '+') return 4;
                    if (c == '-') return 3;
                    if (c == '|') return 2;
                    if (c == '.') return 1;
                    return 0;
                };
                if (priority(ch) >= priority(existing)) {
                    canvas[y][x] = ch;
                }
            }
        };

        // Draw a line of characters between two points
        auto drawLine = [&](int x0, int y0, int x1, int y1, char ch) {
            int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
            int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
            int err = dx + dy;
            while (true) {
                putChar(x0, y0, ch);
                if (x0 == x1 && y0 == y1) break;
                int e2 = 2 * err;
                if (e2 >= dy) { err += dy; x0 += sx; }
                if (e2 <= dx) { err += dx; y0 += sy; }
            }
        };

        // Draw circle outline using midpoint algorithm
        auto drawCircle = [&](int ox, int oy, int rx, int ry, char ch) {
            // Parametric circle adjusted for terminal aspect ratio
            int steps = max(rx, ry) * 8;
            for (int i = 0; i < steps; i++) {
                double angle = 2.0 * M_PI * i / steps;
                int x = ox + (int)round(rx * cos(angle));
                int y = oy + (int)round(ry * sin(angle));
                putChar(x, y, ch);
            }
        };

        // Terminal chars are roughly 2x taller than wide, so scale Y by 0.5
        // We use separate rx and ry throughout.
        double termAspect = 0.5; // ry = rx * termAspect

        // --- Draw outer boundary circle ---
        {
            int rx = outerR * CELL_W;
            int ry = (int)(rx * termAspect);
            drawCircle(cx, cy, rx, ry, '#');
        }

        // --- Draw inner dot at centre ---
        putChar(cx, cy, '*');

        // --- Draw each ring and its cell walls ---
        for (int r = 0; r < rows; r++) {
            // Inner and outer radii for this ring (in canvas characters)
            int innerRx = (r + 1) * CELL_W;
            int outerRx = (r + 2) * CELL_W;
            int innerRy = (int)(innerRx * termAspect);
            int outerRy = (int)(outerRx * termAspect);

            // Draw the inner arc for this ring
            drawCircle(cx, cy, innerRx, innerRy, '-');

            for (int c = 0; c < cols; c++) {
                // Angular slice for this cell
                double angleStart = 2.0 * M_PI * c / cols;
                double angleEnd   = 2.0 * M_PI * (c + 1) / cols;
                double angleMid   = (angleStart + angleEnd) / 2.0;

                // Draw WEST wall (radial line at angleStart) if not linked WEST
                // (skip first cell to avoid duplicate with last cell's east wall)
                if (!cells[r][c].linked(WEST)) {
                    // Draw radial spoke from inner to outer radius
                    int x0 = cx + (int)round(innerRx * cos(angleStart));
                    int y0 = cy + (int)round(innerRy * sin(angleStart));
                    int x1 = cx + (int)round(outerRx * cos(angleStart));
                    int y1 = cy + (int)round(outerRy * sin(angleStart));
                    drawLine(x0, y0, x1, y1, '|');
                } else {
                    // Linked west — draw a small passage indicator dot
                    int mx = cx + (int)round(((innerRx + outerRx) / 2.0) * cos(angleStart));
                    int my = cy + (int)round(((innerRy + outerRy) / 2.0) * sin(angleStart));
                    putChar(mx, my, '.');
                }

                // Draw NORTH wall (inner arc segment) if not linked NORTH
                // Already drawn as the ring boundary — mark open passages
                if (cells[r][c].linked(NORTH) && r > 0) {
                    // Clear/mark the inner arc at this cell's angle as open
                    int steps = max(3, (int)(innerRx * (angleEnd - angleStart)));
                    for (int s = 0; s <= steps; s++) {
                        double a = angleStart + (angleEnd - angleStart) * s / steps;
                        int x = cx + (int)round(innerRx * cos(a));
                        int y = cy + (int)round(innerRy * sin(a));
                        putChar(x, y, ' ');
                    }
                }

                // Place a cell content indicator (space = open cell)
                int mx = cx + (int)round(((innerRx + outerRx) / 2.0) * cos(angleMid));
                int my = cy + (int)round(((innerRy + outerRy) / 2.0) * sin(angleMid));
                putChar(mx, my, ' ');
            }
        }

        // Draw outer arc
        {
            int rx = (rows + 1) * CELL_W;
            int ry = (int)(rx * termAspect);
            drawCircle(cx, cy, rx, ry, '#');
        }

        // --- Print the canvas ---
        // Find bounding box to trim whitespace
        int minY = canvasH, maxY = 0, minX = canvasW, maxX = 0;
        for (int y = 0; y < canvasH; y++) {
            for (int x = 0; x < canvasW; x++) {
                if (canvas[y][x] != ' ') {
                    minY = min(minY, y);
                    maxY = max(maxY, y);
                    minX = min(minX, x);
                    maxX = max(maxX, x);
                }
            }
        }

        if (minY > maxY) {
            std::cout << "(empty canvas)" << std::endl;
            return;
        }

        // Add 1 cell padding
        minY = max(0, minY - 1);
        maxY = min(canvasH - 1, maxY + 1);
        minX = max(0, minX - 1);
        maxX = min(canvasW - 1, maxX + 1);

        for (int y = minY; y <= maxY; y++) {
            std::cout << canvas[y].substr(minX, maxX - minX + 1) << "\n";
        }
    }
};

// BinaryTree maze generator — unchanged
class BinaryTreeMaze {
public:
    static void on(Grid& grid) {
        for (int r = 0; r < grid.getRows(); r++) {
            for (int c = 0; c < grid.getCols(); c++) {
                std::vector<Direction> neighbors;

                if (r > 0) {
                    neighbors.push_back(NORTH);
                }
                if (c < grid.getCols() - 1) {
                    neighbors.push_back(EAST);
                }

                if (!neighbors.empty()) {
                    int index = grid.random(0, neighbors.size() - 1);
                    Direction direction = neighbors[index];
                    grid.linkCells(r, c, direction);
                }
            }
        }
    }
};

void print_help(const char* program_name) {
    cout << "MazeBuilder (Spherical Display) - Binary Tree algorithm\n\n";
    cout << "Usage: " << program_name << " [OPTIONS] [rows] [columns]\n\n";
    cout << "Arguments:\n";
    cout << "  rows     Number of concentric rings (default: 6)\n";
    cout << "  columns  Number of cells per ring   (default: 12)\n\n";
    cout << "Options:\n";
    cout << "  -h, --help  Show this help message and exit\n\n";
    cout << "Notes:\n";
    cout << "  The maze is displayed as a circular/spherical pattern.\n";
    cout << "  Rows become concentric rings; columns become angular slices.\n";
    cout << "  Walls: '#' outer border, '|' radial walls, '-' arc walls.\n";
    cout << "  For best appearance use a square terminal (rows ~= cols/2).\n";
}

int main(int argc, char* argv[]) {
    // Defaults tuned for spherical display
    int rows = 6;
    int cols = 12;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help(argv[0]);
            return 0;
        }
    }

    if (argc > 1) rows = std::atoi(argv[1]);
    if (argc > 2) cols = std::atoi(argv[2]);

    Grid grid(rows, cols);
    BinaryTreeMaze::on(grid);

    std::cout << "\n  === Spherical Maze (Binary Tree) ===\n";
    std::cout << "  Rings: " << rows << "  |  Cells per ring: " << cols << "\n\n";

    grid.display();

    std::cout << "\n  Legend: '#' wall  '|' radial wall  '-' arc wall  '.' open passage\n\n";

    return 0;
}