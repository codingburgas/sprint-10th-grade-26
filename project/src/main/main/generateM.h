#pragma once
#include <iostream>

using namespace std;
void DrowMaze(int Size, int M[][50]) {
    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) { 
            if (M[i][j] == 0) {
                cout << " #";
            }
            else {
                cout << "  ";
            }
             
        }
        cout << endl;
    }
}
void FindPathInMaze(int Size, int M[][50]) {
    //initialize the maze
    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) { M[i][j] = 0; }
    }

    M[0][0] = 1; //beginning of the maze
    M[Size - 1][Size - 1] = 1; //end of the maze

    int Step, Row = 0, Col = 0;
    srand((unsigned)time(0));
    while ((Row < Size - 1) || (Col < Size - 1)) {
        Step = rand();
        //cout << Step<<" ";
        Step = Step % 2; // 0 =Right; 1 =Down; 2=Right Down;
        //cout << Step << " " << endl;
        switch (Step) {
        case 0: { if (Col < Size - 1) { Col++; M[Row][Col] = 1; } } break;
        case 1: { if (Row < Size - 1) { Row++; M[Row][Col] = 1; } } break;
        //case 2: { if ((Row < Size - 1) && (Col < Size - 1)) { Row++; Col++; M[Row][Col] = 1; } } break;
        }
    }
}