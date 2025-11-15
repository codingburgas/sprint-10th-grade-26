#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 55;
int mazeSize;
int maze[MAX_SIZE][MAX_SIZE];
int playerX = 1, playerY = 0;
bool gameRunning = true;
bool showDeadEnds = false;
char input;