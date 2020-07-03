#include "CaseRecord.h"
#include <curses.h>
#include <iostream>
#include <map>
#include <string.h>
#include <unistd.h>
using namespace std;
using namespace LawFirm;

int main()
{
	CaseRecord caseRecord;
	int choice, count, mod_choice, k;
	string key;
	while (1)
	{
		std::cout << "\nMain Menu\n\n1. Add\n2. Search\n3. Modify\n4. Exit\n";
		std::cout << "Enter the choice:";
		cin >> choice;
		std::cin.get();
		std::cin.clear();
		switch (choice)
		{
			case 1:
				std::cout << "Data Entry\n";
				caseRecord.read_data();
				k = caseRecord.pack();
        if (k == 0)
          std::cout << "\n\tInvalid data\n";
        else
				    caseRecord.write_to_file();
				break;
			case 2:
				std::cout << "\nEnter the case code whose details you want to view: ";
				getline(cin, key, '\n');
        transform(key.begin(), key.end(), key.begin(), ::toupper);
				caseRecord.search(key);
				break;
			case 3:
				std::cout << "Enter the case code whose details you want to modify: ";
				getline(cin, key, '\n');
        transform(key.begin(), key.end(), key.begin(), ::toupper);
				caseRecord.modify(key);
				break;
			case 4:
				std::cout << "\t\t\t\tThank You\n\n\n";
				return 0;
			default:
				std::cout << "\n\nWrong choice\n";
				break;
		}
	}
}
