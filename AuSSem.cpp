#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <cstdio>

using namespace std;

void startWithStr(string userInput, string nazorSuboru) {
	vector<vector<string>> content;
	vector<string> row;
	string line;
	string word;
	vector<vector<string>> result;

	std::fstream file(nazorSuboru);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			row.clear();

			stringstream str(line);

			while (getline(str, word, ';'))
				row.push_back(word);
			content.push_back(row);
		}
	}

	for (int i = 1; i < content.size(); i++)
	{
		if ((content[i][2].rfind(userInput, 0) == 0))
		{
			result.push_back(content[i]);
		}
	}

	for (int i = 0; i < result.size(); i++)
	{
		for (int j = 0; j < result[i].size(); j++)
		{
			cout << result[i][j] << " ";
		}
		cout << "\n";
	}
}

void containsStr(string userInput, string nazorSuboru) {
	vector<vector<string>> content;
	vector<string> row;
	string line;
	string word;
	vector<vector<string>> result;

	std::fstream file(nazorSuboru);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			row.clear();

			stringstream str(line);

			while (getline(str, word, ';'))
				row.push_back(word);
			content.push_back(row);
		}
	}

	for (int i = 1; i < content.size(); i++)
	{
		if (content[i][2].find(userInput) != string::npos)
		{
			result.push_back(content[i]);
		}
	}

	for (int i = 0; i < result.size(); i++)
	{
		for (int j = 0; j < result[i].size(); j++)
		{
			cout << result[i][j] << " ";
		}
		cout << "\n";
	}
}



int main()
{
	SetConsoleOutputCP(1250);
	SetConsoleCP(1250);
	setlocale(LC_ALL, "slovak");
	vector<vector<string>> content;
	vector<string> row;
	string line;
	string word;
	int userInput;
	string stringUserInput; 


	cout << "Stlačte 1 ak chcete prehladávať pomocou startWithStr" << endl;
	cout << "Stlačte 2 ak chcete prehladávať pomocou containsStr" << endl;
	
	//dorob check na to aby slo dat iba 1 alebo 2 
	while (!(cin >> userInput))
	{
		cout << "Nezadali ste číslo. Prosim zadajte znovu číslo: " << endl;
		cin.clear();
		cin.ignore(123, '\n');
	}
	
	cout << "Zadali ste číslo: " << userInput << endl;

	if (userInput == 1)
	{
		cout << "Zadajte reťazec, ktorým sa má vyhľadávaný výraz začínať: " << endl;
		cin >> stringUserInput;
		cout << "Nájdené kraje: " << endl << "\n";
		startWithStr(stringUserInput, "kraje.csv");
		cout << "Nájdené okresy: " << endl << "\n";
		startWithStr(stringUserInput, "okresy.csv");
		cout << "Nájdené obce: " << endl << "\n";
		startWithStr(stringUserInput, "obce.csv");
	}

	if (userInput == 2)
	{
		cout << "Zadajte reťazec, ktorý má vyhľadávaný výraz obsahovať: " << endl;
		cin >> stringUserInput;
		cout << "Nájdené kraje: " << endl << "\n";
		containsStr(stringUserInput, "kraje.csv");
		cout << "Nájdené okresy: " << endl << "\n";
		containsStr(stringUserInput, "okresy.csv");
		cout << "Nájdené obce: " << endl << "\n";
		containsStr(stringUserInput, "obce.csv");
	} 

	//pre zobrazenie nacitaneho csv suboru
	/*for (int i = 0; i < content.size(); i++)
	{
		for (int j = 0; j < content[i].size(); j++)
		{
			cout << content[i][j] << " ";
		}
		cout << "\n";
	}*/
}


