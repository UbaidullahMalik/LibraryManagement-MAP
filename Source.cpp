#include <iostream>
#include<cstdlib>
#include<ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include<map>
#include<iterator>
#pragma warning (disable:4996)
#define filename "libsys.txt"

using namespace std;

struct Node
{
	string book_name;
	string author_name;
	string year;
	Node* next;
	Node()
	{
		book_name = "";
		author_name = "";
		year = "";
		next = NULL;
	}
	Node(string bkname, string athname, string y)
	{
		book_name = bkname;
		author_name = athname;
		year = y;
		next = NULL;
	}
};

class Library
{
public:
	Library()
	{
		fstream obj;
		obj.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
		if (!obj)
		{
			obj.open(filename, fstream::in | fstream::out | fstream::trunc);
			obj.close();
		}
	}
	void addBook(map<string, Node*>& Map1)
	{
		int year, month, day;
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		year = tm.tm_year + 1900;
		month = tm.tm_mon + 1;
		day = tm.tm_mday;

		ofstream file(filename, ios::out);
		if (!file.is_open())
		{
			cout << "Error opening file" << endl;
			return;
		}

		Node* datasep;
		typename map<string, Node*> ::iterator it;
		for (it = Map1.begin(); it != Map1.end(); ++it)
		{
			datasep = it->second;
			file << datasep->book_name << ",";
			file << datasep->author_name << ",";
			file << it->first << ",";
			file << datasep->year << ",";
			file << day << "-";
			file << month << "-";
			file << year << "-";
			file << "\n";
		}

		file.close();

		cout << "\n Data added Successfully !!" << endl;
	}
	void deleteBook(map<string, Node*>& Map1, string sbn)
	{
		bool recordfound = false;
		if (!Map1.empty())
		{
			typename map<string, Node*> ::iterator it;
			for (it = Map1.begin(); it != Map1.end(); ++it)
			{
				if ((it->first) == sbn)
				{
					recordfound = true;
					break;
				}
			}

		}
		if (recordfound == true)
		{
			Map1.erase(sbn);
			int year, month, day;
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			year = tm.tm_year + 1900;
			month = tm.tm_mon + 1;
			day = tm.tm_mday;

			ofstream file(filename, ios::out);
			if (!file.is_open())
			{
				cout << "Error opening file" << endl;
				return;
			}

			Node* datasep;
			typename map<string, Node*> ::iterator pt;
			for (pt = Map1.begin(); pt != Map1.end(); ++pt)
			{
				datasep = pt->second;
				file << datasep->book_name << ",";
				file << datasep->author_name << ",";
				file << pt->first << ",";
				file << datasep->year << ",";
				file << day << "-";
				file << month << "-";
				file << year << "-";

				file << "\n";
			}

			file.close();
			cout << "\n Data deleted Successfully !!" << endl;
		}
		else
		{
			cout << "Record not found!" << endl;
		}


	}
	void searchBook(map<string, Node*>& Map1)
	{
		string keyword;
		int choice = 0;
		bool flag = false;
		int dsp = 0;
		string stype = "";

		cin.ignore();
		cout << "Enter ISBN: ";
		getline(cin, keyword);
		bool recordfound = false;
		Node* datasep;

		typename map<string, Node*> ::iterator it;
		cout << endl;
		for (it = Map1.begin(); it != Map1.end(); ++it)
		{
			datasep = it->second;
			if (it->first == keyword)
			{
				cout << "Book Name: \t" << datasep->book_name << endl;
				cout << "Author Name: \t" << datasep->author_name << endl;
				cout << "Book ISBN: \t" << it->first << endl;
				cout << "Book Year: \t" << datasep->year << endl;
				cout << endl;
				recordfound = true;
			}
		}
		if (recordfound == false)
		{
			cout << "No record found :(" << endl;
		}

	}
	void updateBook(map<string, Node*>& Map1, string sbn)
	{
		string bname, aname;
		string y;
		bool recordfound = false;
		Node* datasep;
		typename map<string, Node*> ::iterator it;
		for (it = Map1.begin(); it != Map1.end(); ++it)
		{
			datasep = it->second;
			if (it->first == sbn)
			{
				cin.ignore();
				cout << "Please enter Book name(to update): ";
				getline(cin, bname);
				cout << "Please enter Author name(to update): ";
				getline(cin, aname);
				cout << "Please enter Year(to update): ";
				getline(cin, y);
				datasep->year = y;
				datasep->book_name = bname;
				recordfound = true;
			}
		}
		if (recordfound == false)
		{
			cout << "No record found!" << endl;
		}
		else
		{
			int year, month, day;
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			year = tm.tm_year + 1900;
			month = tm.tm_mon + 1;
			day = tm.tm_mday;

			ofstream file(filename, ios::out);
			if (!file.is_open())
			{
				cout << "Error opening file" << endl;
				return;
			}

			Node* datasep;
			typename map<string, Node*> ::iterator pt;
			for (pt = Map1.begin(); pt != Map1.end(); ++pt)
			{
				datasep = pt->second;
				file << datasep->book_name << ",";
				file << datasep->author_name << ",";
				file << pt->first << ",";
				file << datasep->year << ",";
				file << day << "-";
				file << month << "-";
				file << year;
				file << "\n";
			}

			file.close();

			cout << "\n Data updated Successfully !!";
		}
	}
	void listOfAllBooks(map<string, Node*>& Map1)
	{
		if (!Map1.empty())
		{
			int i = 0;
			Node* temp;
			typename map<string, Node*> ::iterator it;
			for (it = Map1.begin(); it != Map1.end(); ++it)
			{
				temp = it->second;
				cout << "Record : " << i + 1 << endl;
				cout << "Book Name: \t" << temp->book_name << endl;
				cout << "Author Name: \t" << temp->author_name << endl;
				cout << "Book ISBN: \t" << it->first << endl;
				cout << "Book Year: \t" << temp->year << endl;
				cout << endl;
				i++;
			}
		}
		else
		{
			return;
		}
	}
	void readfile(map<string, Node*>& Map1)
	{
		string temp, bookname, authorname, sbn;
		string yr;
		int index = 0;
		ifstream obj;
		obj.open(filename);
		getline(obj, temp);
		while (!obj.eof())
		{
			index = temp.find(',');
			bookname = temp.substr(0, index);

			temp = temp.substr(index + 1);
			index = temp.find(',');
			authorname = temp.substr(0, index);

			temp = temp.substr(index + 1);
			index = temp.find(',');
			sbn = temp.substr(0, index);

			temp = temp.substr(index + 1);
			index = temp.find(',');
			yr = temp.substr(0, index);

			Node* currdata = new Node(bookname, authorname, yr);
			Map1.insert(pair<string, Node*>(sbn, currdata));
			getline(obj, temp);
		}
		obj.close();

	}
};

int main()
{
	map<string, Node*> L;
	Library C;
	C.readfile(L);
	cout << "Welcome to Library Information System" << endl << endl;
	cout << "Following is the list of all available books" << endl;
	C.listOfAllBooks(L);
	int outerChoice = 0;
	while (outerChoice != 9)
	{
		int innerChoice = 0;
		while (innerChoice != 9)
		{
			cout << "Welcome to Library Information System" << endl;
			cout << "1. Add Book" << endl;
			cout << "2. Search Book" << endl;
			cout << "3. Update Book" << endl;
			cout << "4. Delete Book" << endl;
			cout << "5. List of All Books" << endl;
			cout << "0. Exit" << endl;
			cout << "\n Enter your choice : ";

			cin >> innerChoice;
			string bookname, bookauthor, bookisbn, bookyear;

			switch (innerChoice)
			{
			case 1:
			{
				cin.ignore();
				cout << "\n ---- Add a new Book ----";
				cout << "\n Enter book name : ";
				getline(cin, bookname);
				cout << "\n Enter book author : ";
				getline(cin, bookauthor);
				cout << "\n Enter SBN Number: ";
				getline(cin, bookisbn);
				cout << "\n Enter Year: ";
				getline(cin, bookyear);
				Node* temp = new Node(bookname, bookauthor, bookyear);
				L.insert(pair<string, Node*>(bookisbn, temp));
				C.addBook(L);
				break;
			}
			case 2:
			{
				C.searchBook(L);
				break;
			}
			case 3:
			{
				cout << "Enter ISBN number of book to Update: ";
				cin >> bookisbn;
				C.updateBook(L, bookisbn);
				break;
			}
			case 4:
			{
				cin.ignore();
				cout << "Enter ISBN number of book to delete: ";
				getline(cin, bookisbn);
				C.deleteBook(L, bookisbn);
				break;
			}
			case 5:
			{
				C.listOfAllBooks(L);
				break;
			}
			case 0:
			{
				return 0;
			}
			default:
			{
				cout << "\n\n Invalid Choice. Press any key to continue..";
				getchar();
			}
			}
		}
	}
}