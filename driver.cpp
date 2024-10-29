#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "County.h"
#include "List.h"

using namespace std;

int main()
{
    ifstream file;
	stringstream temp;
	string line, county, state;
	int index = 0, pop;
    file.open("counties_list.csv", ios::in);

	List<County*> countyList;

	County* newCounty;

    int choice;
    string fileName;


    do{                                                                                 //Asks user what they want to do in the program
        cout << "\nWhat Would you like to do?";
        cout << "\n1.  Merge Sort";
        cout << "\n2.  Selection Sort";
        cout << "\n3.  Add a new county";
        cout << "\n4.  Print all counties";
        cout << "\n5.  End Program";
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

                if(file.good()){
                        index++;

                        cin.ignore();
                        cout << "\nPlease enter the name of your county:\t\t";
                        getline(cin, county);

                        cout << "\nPlease enter the state in which it's located:\t";
                        getline(cin, state);

                        cout << "\nPlease enter the population of your county:\t";
                        cin >> pop;

                        newCounty = new County(index, county, state, pop);
                        countyList.append(newCounty);
                }

                file.close();
                break;
            case 4:
                countyList.print();
                break;
            case 5:
                cout << "Closing program...";
                break;
            default:
                break;
        }
    }while(choice != 3);

	return 0;
}