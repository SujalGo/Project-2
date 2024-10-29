#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include "County.h"
#include "List.h"

using namespace std;

int main()
{
	string line, county, state;
	int index, pop;

	List<County*> countyList;

	County* newCounty;

    int choice;
    string fileName;


    do{                                                                                 //Asks user what they want to do in the program
        cout << "\nWhat Would you like to do?";
        cout << "\n1.  Merge Sort";
        cout << "\n2.  Selection Sort";
        cout << "\n3.  End Program";
        cout << "\nCHOOSE 1-2:  ";

        cin >> choice;
    
        switch(choice){
            case 1:                                                                     
                countyList.mergeSort();
                break;
            case 2:
                countyList.selectionSort();
                break;
            case 3:
                cout << "Closing program...";
                break;
            default:
                break;
        }
    }while(choice != 3);

	cin.get();
	return 0;
}