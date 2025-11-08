#include <iostream>
#include "generateM.h"
using namespace std;

int main()
{
    int N; //size ot the maze
    do {
        cout << "Input size of the Labyrinth (10,20,30,40,50):";
        cin >> N;

        if ((N == 10) || (N == 20) || (N == 30) || (N == 40) || (N == 50)) {
            int L[50][50];
            FindPathInMaze(N, L);
            DrowMaze(N, L);
        }
    } while ((N == 10) || (N == 20) || (N == 30) || (N == 40) || (N == 50));

}