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
        cout << "\n3.  ";
        cout << "\n4.  ";
        cout << "\n5.  ";
        cout << "\n6.  ";
        cout << "\nCHOOSE 1-6:  ";

        cin >> choice;
    
        switch(choice){
            case 1:                                                                     
                countyList.mergeSort();
                break;
            case 2:
                countyList.selectionSort();
                break;
            case 3:

                break;
            case 4:
                
                break;
            case 5:
                
                break;
            case 6:

                break;
            default:
                
                break;
        }
    }while(choice != 6);



	countyList.selectionSort();
	
	countyList.print();

	cin.get();
	return 0;
}