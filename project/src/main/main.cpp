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
cout << " ____        _       ______                   " << endl;
cout << "|  _ \      | |     |  ____|                  " << endl;
cout << "| |_) |_   _| |_ ___| |__ ___  _ __ __ _  ___ " << endl;
cout << "|  _ <| | | | __/ _ \  __/ _ \| '__/ _` |/ _ \" << endl;
cout << "| |_) | |_| | ||  __/ | | (_) | | | (_| |  __/"; << endl;
cout << "|____/ \__, |\__\___|_|  \___/|_|  \__, |\___|; << endl;
cout << "        __/ |                       __/ |     "; << endl;
cout << "       /___/                       /___/      " << endl;
cout<<"1.Start" << endl;
cout <<"2.rules" << endl;
cout <<"3.exit" << endl;
int choice;
cin >> choice;
if(choice == 1){
    cout << "enter maze size: ";
    cin >> mazeSize;


    GenerateMazeDFS(mazeSize, maze);

    drawGame(maze, playerX, playerY, mazeSize, showDeadEnds);
}
if(choice == 2){
    cout << "Rules of the Game:" << endl;
    cout << "1.Rule one" << endl;
    cout << "2.Rule two" << endl;
    cout << "3.Rule three" << endl;
}
if (choice == 3){
    exit(0);
}
    

    
}