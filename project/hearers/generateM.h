void GenerateMazeDFS(int Size, int M[][MAX_SIZE]) {

    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) {
            M[i][j] = 0;
        }
    }


    int startX = 1;
    int startY = 1;
    M[startY][startX] = 1;


    int dx[] = { 2, 0, -2, 0 };
    int dy[] = { 0, 2, 0, -2 };

    stack<pair<int, int>> st;
    st.push({ startX, startY });

    srand((unsigned)time(0));

    while (!st.empty()) {
        int x = st.top().first;
        int y = st.top().second;


        vector<int> directions = { 0, 1, 2, 3 };
        random_shuffle(directions.begin(), directions.end());

        bool found = false;
        for (int dir : directions) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if (nx > 0 && nx < Size - 1 && ny > 0 && ny < Size - 1 && M[ny][nx] == 0) {

                M[y + dy[dir] / 2][x + dx[dir] / 2] = 1;
                M[ny][nx] = 1;
                st.push({ nx, ny });
                found = true;
                break;
            }
        }

        if (!found) {
            st.pop();
        }
    }


    M[0][1] = 1; // Start entrance
    M[Size - 1][Size - 2] = 1; // End exit
}


void GenerateMazeWithDeadEnds(int Size, int M[][MAX_SIZE]) {
    // Initialize with all walls
    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) {
            M[i][j] = 0;
        }
    }

    int x = 1, y = 1;
    M[y][x] = 1;

    srand((unsigned)time(0));


    while (x < Size - 2 || y < Size - 2) {
        if (rand() % 2 == 0 && x < Size - 2) {
            x++;
        }
        else if (y < Size - 2) {
            y++;
        }
        M[y][x] = 1;


        if (rand() % 3 == 0) {
            int branchX = x, branchY = y;
            int branchLength = rand() % 4 + 1;

            for (int i = 0; i < branchLength; i++) {
                int dir = rand() % 4;
                switch (dir) {
                case 0: if (branchX > 1) branchX--; break;
                case 1: if (branchX < Size - 2) branchX++; break;
                case 2: if (branchY > 1) branchY--; break;
                case 3: if (branchY < Size - 2) branchY++; break;
                }
                M[branchY][branchX] = 1;


                if (rand() % 2 == 0) break;
            }
        }
    }


    M[0][1] = 1;
    M[Size - 1][Size - 2] = 1;
}
int countDeadEnds(int Size, int M[][MAX_SIZE]) {
    int deadEnds = 0;
    for (int i = 1; i < Size - 1; i++) {
        for (int j = 1; j < Size - 1; j++) {
            if (M[i][j] == 1) {
                int neighbors = 0;
                if (M[i - 1][j] == 1) neighbors++;
                if (M[i + 1][j] == 1) neighbors++;
                if (M[i][j - 1] == 1) neighbors++;
                if (M[i][j + 1] == 1) neighbors++;

                if (neighbors == 1) {
                    deadEnds++;
                }
            }
        }
    }
    return deadEnds;
}


void clearScreen() {
    system("cls");
}

void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawGame(int maze[][MAX_SIZE], int playerX, int playerY, int mazeSize, bool showDeadEnds = false) {
    setCursorPosition(0, 0);

    for (int i = 0; i < mazeSize; i++) {
        for (int j = 0; j < mazeSize; j++) {
            if (i == playerY && j == playerX) {
                cout << "P ";
            }
            else if (maze[i][j] == 0) {
                cout << "# ";
            }
            else {

                if (showDeadEnds && i > 0 && i < mazeSize - 1 && j > 0 && j < mazeSize - 1) {
                    int neighbors = 0;
                    if (maze[i - 1][j] == 1) neighbors++;
                    if (maze[i + 1][j] == 1) neighbors++;
                    if (maze[i][j - 1] == 1) neighbors++;
                    if (maze[i][j + 1] == 1) neighbors++;

                    if (neighbors == 1) {

                        continue;
                    }
                }
                cout << "  ";
            }
        }
        cout << endl;
    }

    cout << "Use WASD to move. Press 'q' to quit." << endl;
    cout << "Position: (" << playerX << ", " << playerY << ")" << endl;
    cout << "Goal: Reach position (" << mazeSize - 2 << ", " << mazeSize - 1 << ")" << endl;
    cout << "Press 'r' for new maze, 'x' to toggle dead end highlight" << endl;


    if (playerX == mazeSize - 2 && playerY == mazeSize - 1) {
        cout << "Congratulations! You reached the end of the maze!" << endl;
    }
}