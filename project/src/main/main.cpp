#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int main()
{
cout << "  ___  _____ " << endl;
cout << " |__ \\| ____|" << endl;  
cout << "    ) | |__  " << endl;
cout << "   / /|___ \\ " << endl;  
cout << "  / /_ ___) |" << endl;
cout << " |____|____/ " << endl;


cout<<"1.Start" << endl;
cout <<"2.rules" << endl;
cout <<"3.exit" << endl;
int choice;
cin >> choice;
if(choice == 1){
    cout << "enter maze size: ";
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