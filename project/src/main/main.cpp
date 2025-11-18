#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

const int dx[] = { -1, 0, 1, 0 };
const int dy[] = { 0, 1, 0, -1 };

struct Player {
    int x, y;
};

struct Goal {
    int x, y;
};

void placeGoalRandomly(Goal& goal, const vector<vector<int>>& maze, const Player& player) {
    vector<pair<int, int>> validPositions;
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            if (maze[i][j] == 0 && !(i == player.x && j == player.y)) {
                validPositions.push_back({ i, j });
            }
        }
    }
    if (!validPositions.empty()) {
        int randomIndex = rand() % validPositions.size();
        goal.x = validPositions[randomIndex].first;
        goal.y = validPositions[randomIndex].second;
    }
}

void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void generateMaze(vector<vector<int>>& maze, int size) {
    maze.assign(size, vector<int>(size, 1));

    stack<pair<int, int>> path;

    int startX = 0, startY = 0;
    maze[startX][startY] = 0;
    path.push({ startX, startY });

    while (!path.empty()) {
        int x = path.top().first;
        int y = path.top().second;

        vector<int> directions;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i] * 2;
            int ny = y + dy[i] * 2;

            if (nx >= 0 && nx < size && ny >= 0 && ny < size && maze[nx][ny] == 1) {
                directions.push_back(i);
            }
        }

        if (!directions.empty()) {
            int dir = directions[rand() % directions.size()];
            int nx = x + dx[dir] * 2;
            int ny = y + dy[dir] * 2;

            // Carve the path AND the cell between
            maze[x + dx[dir]][y + dy[dir]] = 0;
            maze[nx][ny] = 0;

            path.push({ nx, ny });
        }
        else {
            path.pop();
        }
    }

    // Ensure goal area is accessible
    maze[size - 1][size - 1] = 0;
    if (size > 1) {
        maze[size - 2][size - 1] = 0;
        maze[size - 1][size - 2] = 0;
    }
}

void drawInitialMaze(const vector<vector<int>>& maze, const Player& player, const Goal& goal, int collected) {
    system("cls");
    hideCursor();

    cout << "\n  === MAZE GAME ===" << endl;
    cout << "  Move: W/A/S/D | Collect 5 goals! | Press Q to quit" << endl;
    cout << "  Collected: " << collected << "/5" << endl;
    cout << endl;

    for (int i = 0; i < maze.size(); i++) {
        cout << "  ";
        for (int j = 0; j < maze[i].size(); j++) {
            if (i == player.x && j == player.y) {
                setColor(10); // Green for player
                cout << "P ";
                setColor(7); // Reset to white
            }
            else if (i == goal.x && j == goal.y) {
                setColor(12); // Red for goal
                cout << "X ";
                setColor(7); // Reset to white
            }
            else if (maze[i][j] == 1) {
                cout << "██";
            }
            else {
                cout << "  ";
            }
        }
        cout << endl;
    }
}

void updateGoal(const Goal& goal, const vector<vector<int>>& maze) {
    setCursorPosition(2 + goal.y * 2, 5 + goal.x);
    setColor(12); // Red for goal
    cout << "X ";
    setColor(7); // Reset to white
    cout.flush();
}

void updatePlayer(const Player& oldPos, const Player& newPos, const Goal& goal, const vector<vector<int>>& maze) {
    // Clear old position
    setCursorPosition(2 + oldPos.y * 2, 5 + oldPos.x);
    if (oldPos.x == goal.x && oldPos.y == goal.y) {
        setColor(12); // Red for goal
        cout << "X ";
        setColor(7); // Reset to white
    }
    else {
        cout << "  ";
    }

    // Draw new position
    setCursorPosition(2 + newPos.y * 2, 5 + newPos.x);
    setColor(10); // Green for player
    cout << "P ";
    setColor(7); // Reset to white
    cout.flush();
}

void updateCollectedCounter(int collected, int mazeSize) {
    setCursorPosition(13, 3);
    cout << collected << "/5   ";
    cout.flush();
}

bool canMove(const vector<vector<int>>& maze, int x, int y) {
    return x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size() && maze[x][y] == 0;
}

void showMenu() {
    system("cls");
    cout << "  ___  _____ " << endl;
    cout << " |__ \\| ____|" << endl;
    cout << "    ) | |__  " << endl;
    cout << "   / /|___ \\ " << endl;
    cout << "  / /_ ___) |" << endl;
    cout << " |____|____/ " << endl;
    cout << "1 - Start Game" << endl;
    cout << "2 - Exit" << endl;
    cout << "3 - Help" << endl;
}

void showHelp() {
    system("cls");
    cout << "\n=== HELP ===" << endl;
    cout << "*1 Use W/A/S/D keys to move the player (P) through the maze." << endl;
    cout << "*2 Collect 5 goals (X) to win the game." << endl;
    cout << "*3 Press Q to quit the game at any time." << endl;
    cout << "*4 Complete the maze in the least number of moves possible!" << endl;
    cout << "\nPress any key to return to menu..." << endl;
    _getch();
}

int main() {
    srand(time(0));

    while (true) {
        showMenu();

        int choice;
        cin >> choice;

        if (choice == 2) {
            cout << "\nThanks for playing! Goodbye!" << endl;
            break;
        }
        else if (choice == 3) {
            showHelp();
        }
        else if (choice == 1) {
            int size;
            cout << "Enter maze size (5-50): ";
            cin >> size;

            if (size < 5 || size > 50) {
                cout << "Please enter a size between 5 and 50." << endl;
                cout << "Press any key to continue..." << endl;
                _getch();
                continue;
            }

            vector<vector<int>> maze;
            generateMaze(maze, size);

            Player player = { 0, 0 };
            Goal goal = { 0, 0 };

            // Place first goal randomly
            placeGoalRandomly(goal, maze, player);

            int moves = 0;
            int collected = 0;

            drawInitialMaze(maze, player, goal, collected);

            while (true) {
                if (player.x == goal.x && player.y == goal.y) {
                    collected++;
                    updateCollectedCounter(collected, size);

                    if (collected >= 5) {
                        setCursorPosition(0, 8 + size);
                        cout << "\n CONGRATULATIONS! You collected all 5 goals!" << endl;
                        cout << "  Total moves: " << moves << endl;
                        cout << "\n  Press any key to return to menu..." << endl;
                        _getch();
                        break;
                    }

                    // Place new goal
                    placeGoalRandomly(goal, maze, player);
                    updateGoal(goal, maze);
                }

                char input = _getch();
                input = tolower(input);

                Player oldPos = player;
                int newX = player.x;
                int newY = player.y;

                if (input == 'w') newX--;
                else if (input == 's') newX++;
                else if (input == 'a') newY--;
                else if (input == 'd') newY++;
                else if (input == 'q') {
                    setCursorPosition(0, 8 + size);
                    cout << "\n  Game quit. Returning to menu..." << endl;
                    _getch();
                    break;
                }

                if (canMove(maze, newX, newY)) {
                    player.x = newX;
                    player.y = newY;
                    moves++;

                    updatePlayer(oldPos, player, goal, maze);
                }
            }
        }
        else {
            cout << "Invalid choice! Please select 1, 2, or 3." << endl;
            cout << "Press any key to continue..." << endl;
            _getch();
        }
    }

    return 0;
}