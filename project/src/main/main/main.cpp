#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <stack>
#include <algorithm>
#include "valuce.h"
#include "generateM.h"

using namespace std;

int main()
{
    cout << "enter maze size: ";
    cin >> mazeSize;


    GenerateMazeDFS(mazeSize, maze);

    drawGame(maze, playerX, playerY, mazeSize, showDeadEnds);

    
}