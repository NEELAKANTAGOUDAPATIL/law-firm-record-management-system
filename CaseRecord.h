#include <iostream>
#include <ncurses.h>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <string>

#include<bits/stdc++.h>

using namespace std;

namespace LawFirm
{
class CaseRecord
{
public:
	string lawyer;
	string title;
	string code;
	string type;
	string description;
	string buffer;

	void read_data();
	int pack();
	void write_to_file();

	bool remove(string);
	int search(string);
	void disp();
	void unpack(int);
	void modify(string);

  int hash(string);
};

int CaseRecord::hash(string key)
{
  int t;
  t=(((key[2]-48)*100)+((key[3]-48)*10)+(key[4]-48))%9;
  if(t==0)
    return 9;
  else
    return t;
}

void CaseRecord::read_data()
{
	//std::cin.get();
	std::cin.clear();
	std::cout << "Lawyer: ";
	getline(cin, lawyer, '\n');
	std::cout << "Title: ";
	getline(cin, title, '\n');
	std::cout << "Code: ";
	getline(cin, code, '\n');
	transform(code.begin(), code.end(), code.begin(), ::toupper);
	std::cout << "Case type: ";
	getline(cin, type, '\n');
	std::cout << "Description: ";
	getline(cin, description, '\n');
}

int CaseRecord::pack()
{
	buffer.erase();
	buffer += code + "|" + lawyer + "|" + title + "|" + type + "|" + description + "|";
  if (buffer.length()>100)
    return 0;
  else
  {
    while (buffer.length()<100)
      buffer = buffer + '_';
    buffer = buffer + '\n';
    return 1;
  }
}

void CaseRecord::write_to_file()
{
	int pos, cnt, count;
	fstream file;
  string temp;
	pos = hash(code);
  pos--;
  pos = pos*304;
	file.open("case_file.txt");
  file.seekp(pos, ios::beg);
	getline(file, temp);
	file.close();
  cnt = temp[0]-48;
  file.open("case_file.txt");
  if (cnt < 0)
  {
    file.seekp(pos, ios::beg);
    file.put('1');
    pos = pos+1;
  }
  else if (cnt < 9)
  {
    file.seekp(pos,ios::beg);
    file.put(++temp[0]);
    pos=pos+(100*cnt)+cnt+1;
  }
  std::cout << "Inserting at: " << pos;
  file.seekp(pos, ios::beg);
  file << buffer;
  file.close();
}

void CaseRecord::unpack(int flag)
{
	int i = 0;

  code.erase();
	while (buffer[i] != '|')
		code += buffer[i++];

	lawyer.erase();
  i++;
	while (buffer[i] != '|')
		lawyer += buffer[i++];

	title.erase();
	i++;
	while (buffer[i] != '|')
		title += buffer[i++];

	type.erase();
	i++;
	while (buffer[i] != '|')
		type += buffer[i++];

	description.erase();
	i++;
	while (buffer[i] != '|')
		description += buffer[i++];
}

int CaseRecord::search(string key)
{
	int pos = 0, flag = 0, cnt, i = 0, ipos=0;
  string temp;
	fstream file;
	pos = hash(key);
  pos--;
  pos = pos*304;
	file.open("case_file.txt");
	file.seekp(pos, ios::beg);
	getline(file, temp);
  cnt = temp[0]-48;
  while (i <= cnt)
  {
		ipos = pos+(100*i)+i+1;
    file.seekp(ipos, ios::beg);
    buffer.erase();
    getline(file, buffer);
    unpack(i++);
    if (key == code)
    {
      flag = 1;
      break;
    }
  }
  if (!flag)
	{
		std::cout << "\nRecord not found.\n";
		return -1;
	}
  else
  {
    std::cout << "\nRecord found:" << endl
  			  << "\tLawyer:\t\t" << lawyer << endl
  			  << "\tTitle:\t\t" << title << endl
  			  << "\tCase Code:\t" << code << endl
  				<< "\tCase Type:\t" << type << endl
  			  << "\tDescription:\t" << description << endl;
  }
	file.close();
	return ipos;
}

void CaseRecord::modify(string key)
{
	int c, pos;
	string temp;
	pos = search(key);
	if (pos != -1)
	{
		fstream file;
		file.open("case_file.txt");
		file.seekp(pos, ios::beg);
		getline(file, temp);
		do
		{
			cout << "\nWhich field do you want to modify?\n1. Lawyer Name \n2. Case Title\n3. Case Type\n4. Case Description\n5. Exit\n";
			cout << "Enter your choice: ";
			cin >> c;
			std::cin.get();
			std::cin.clear();
			switch (c)
			{
				case 1:
					std::cout << "\nLawyer Name: ";
					getline(cin, lawyer, '\n');
					break;

				case 2:
					std::cout << "\nCase Title: ";
					getline(cin, title, '\n');
					break;

				case 3:
					std::cout << "\nCase Type: ";
					getline(cin, type, '\n');
					break;

				case 4:
					std::cout << "\nCase Description: ";
					getline(cin, description, '\n');
					break;

				default:
					cout << "\nInvalid choice.\n";
			}
			std::cout << "\n\tCase Record modified successfully.\n";
			if (pack() == 0)
				std::cout << "\n\tInvalid data\n";
			else
			{
				file.seekp(pos, ios::beg);
			  file << buffer;
			}
		} while (c!=5);
		file.close();
		search(key);
	}
}

}
