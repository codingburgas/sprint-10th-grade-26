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

void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

bool canMove(const vector<vector<int>>& maze, int x, int y) {
    return x >= 0 && x < maze.size() &&
        y >= 0 && y < maze[0].size() &&
        maze[x][y] == 0;
}
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

            maze[x + dx[dir]][y + dy[dir]] = 0;
            maze[nx][ny] = 0;

            path.push({ nx, ny });
        }
        else {
            path.pop();
        }
    }

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
    cout << "  Collected: " << collected << "/5\n" << endl;

    for (int i = 0; i < maze.size(); i++) {
        cout << "  ";
        for (int j = 0; j < maze[i].size(); j++) {
            if (i == player.x && j == player.y) {
                cout << "P ";
            }
            else if (i == goal.x && j == goal.y) {
                cout << "X ";
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

    cout << "\n  Moves: 0" << endl;
}

void updateGoal(const Goal& goal, const vector<vector<int>>& maze) {
    setCursorPosition(2 + goal.y * 2, 5 + goal.x);
    cout << "X ";
}

void updatePlayer(const Player& oldPos, const Player& newPos, const Goal& goal, const vector<vector<int>>& maze) {
    setCursorPosition(2 + oldPos.y * 2, 4 + oldPos.x);
    if (oldPos.x == goal.x && oldPos.y == goal.y) {
        cout << "X ";
    }
    else {
        cout << "  ";
    }

    setCursorPosition(2 + newPos.y * 2, 4 + newPos.x);
    cout << "P ";
}

void updateCollectedCounter(int collected, int mazeSize) {
    setCursorPosition(13, 2);
    cout << collected << "/5   ";
}
int main() {
    srand(time(0));

    int size;
    cout << "Enter maze size (5-50): ";
    cin >> size;

    if (size < 5 || size > 50) {
        cout << "Please enter a size between 5 and 50." << endl;
        return 1;
    }

    vector<vector<int>> maze;
    generateMaze(maze, size);

    Player player = { 0, 0 };
    Goal goal = { 0, 0 };

    placeGoalRandomly(goal, maze, player);

    int moves = 0;
    int collected = 0;

    drawInitialMaze(maze, player, goal, collected);

    while (true) {
        if (player.x == goal.x && player.y == goal.y) {
            collected++;
            updateCollectedCounter(collected, size);

            if (collected >= 5) {
                setCursorPosition(0, 7 + size);
                cout << "\n  CONGRATULATIONS! You collected all 5 goals!" << endl;
                cout << "  Total moves: " << moves << endl;
                cout << "\n  Press any key to exit..." << endl;
                _getch();
                break;
            }

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
            setCursorPosition(0, 7 + size);
            cout << "\n  Game quit. Thanks for playing!" << endl;
            break;
        }

        if (canMove(maze, newX, newY)) {
            player.x = newX;
            player.y = newY;
            moves++;

            updatePlayer(oldPos, player, goal, maze);
        }
    }

    setCursorPosition(0, 10 + size);
    return 0;
}