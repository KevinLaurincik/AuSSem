#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <cstdio>
#include "libds/amt/explicit_hierarchy.h"
#include <cstdlib>
#include <Windows.h>

using namespace std;

vector<vector<string>> contentKraje;
vector<vector<string>> contentOkresy;
vector<vector<string>> contentObce;
auto hierarchy = std::make_unique<ds::amt::MultiWayExplicitHierarchy<vector<string>>>();
ds::amt::MultiWayExplicitHierarchyBlock<vector<string>> actualPosition;

void readFile(string nazovSuboru) {
	vector<string> row;
	string line;
	string word;
	std::fstream file(nazovSuboru);

	if (file.is_open())
	{
		getline(file, line); //aby sa preskocil prvy riadok
		while (getline(file, line))
		{
			row.clear();

			stringstream str(line);

			while (getline(str, word, ';'))
				row.push_back(word);
			if (nazovSuboru == "kraje.csv")
			{
				contentKraje.push_back(row);
			}
			else if (nazovSuboru == "okresy.csv")
			{
				contentOkresy.push_back(row);
			}
			else if (nazovSuboru == "obce.csv")
			{
				contentObce.push_back(row);
			}
			else
			{
				cout << "Zle sa naèítal niektorý zo súborov!" << endl;
			}
		}
	}
	file.close();
};

void quickSort(vector<string>& param, std::function<bool(const string&, const string&)> compare, size_t min, size_t max) {
	string pivot = param.at(min + (max - min) / 2);
	int left = min;
	int right = max;
	do
	{
		while (compare(param.at(left), pivot))
		{
			left++;
		}
		while (right > 0 && compare(pivot, param.at(right)))
		{
			right--;
		}
		if (left <= right)
		{
			std::swap(param.at(left), param.at(right));
			left++;
			if (right > 0) {
				right--;
			}
		}
	} while (left <= right);

	if (min < right)
	{
		quickSort(param, compare, min, right);
	}
	if (left < max)
	{
		quickSort(param, compare, left, max);
	}
}

void sort(vector<string>& param, std::function<bool(const string&, const string&)> compare) {
	if (!param.empty())
	{
		quickSort(param, compare, 0, param.size() - 1);
	}
}

bool compareAlphabetical(const string& param1, const string& param2) {
	return param1 < param2;
}

bool compareVowelsCount(const string& param1, const string& param2) {
	string vowels = "aAáÁeEéÉiIíÍoOóÓôÔuUúÚyYýÝ";
	int vowelsCountParam1 = 0;
	int vowelsCountParam2 = 0;
	for (auto pismeno : param1)
	{
		if (vowels.find(pismeno) != std::string::npos)
		{
			vowelsCountParam1++;
		}
	}
	for (auto pismeno : param2)
	{
		if (vowels.find(pismeno) != std::string::npos)
		{
			vowelsCountParam2++;
		}
	}

	return vowelsCountParam1 < vowelsCountParam2;
}

void emplaceHierarchy() {
	auto& root = hierarchy->emplaceRoot();
	actualPosition = root;

	vector<string> koren = { "Slovenska republika" };
	root.data_ = koren;

	readFile("kraje.csv");
	readFile("okresy.csv");
	readFile("obce.csv");

	int premenna1 = 0;

	for (auto& data : contentKraje)
	{
		hierarchy->emplaceSon(root, premenna1).data_ = contentKraje[premenna1];
		//cout << hierarchy->accessSon(root, premenna1)->data_[2] << endl;

		int premenna2 = 0;
		int poradieOkresSyn = 0;

		for (auto& data2 : contentOkresy)
		{
			int premenna3 = 0;
			int poradieObecSyn = 0;

			if (contentOkresy[premenna2][1].find(contentKraje[premenna1][5].substr(contentKraje[premenna1][5].length() - 5)) != std::string::npos)
			{
				hierarchy->emplaceSon(*hierarchy->accessSon(*hierarchy->accessRoot(), premenna1), poradieOkresSyn).data_ = contentOkresy[premenna2];
				//cout << "\t" << hierarchy->accessSon(*hierarchy->accessSon(root, premenna1), poradieOkresSyn)->data_[2] << endl;

				for (auto& data3 : contentObce)
				{
					if (contentObce[premenna3][1].find(contentOkresy[premenna2][1]) != std::string::npos)
					{
						hierarchy->emplaceSon(*hierarchy->accessSon(*hierarchy->accessSon(root, premenna1), poradieOkresSyn), poradieObecSyn).data_ = contentObce[premenna3];
						//cout << "\t\t" << hierarchy->accessSon(*hierarchy->accessSon(*hierarchy->accessSon(root, premenna1), poradieOkresSyn), poradieObecSyn)->data_[2] << endl;
						poradieObecSyn++;
					}
					premenna3++;
				}
				poradieOkresSyn++;
			}
			premenna2++;
		}
		premenna1++;
	}
}

void searchMenuHierarchy() {
	int userInput = 0;
	int userInputSon;
	int userInputALGChosen;
	int userSortInput;
	string userStringInput;
	
	cout << endl;
	cout << endl;
	cout << "Si v koreni hierarchie: Slovenská republika" << endl << "\n";
	cout << "Môžeš sa presunút na synov: " << endl;
	for (int i = 0; i < contentKraje.size(); i++)
	{
		cout << contentKraje[i][2] << endl;
	}
	while (true)
	{
		cout << endl;
		cout << "#--------------------------------------------------------------#" << endl;
		cout << "Stlaè 1 ak sa chceš presunú na otca." << endl;
		cout << "Stlaè 2 ak sa chceš presunú na konkrétneho syna." << endl;
		cout << "Stlaè 3 ak chceš použi preh¾adávacie algoritmy na synov." << endl;
		cout << "Stlaè 4 ak chceš overit typ uzemnej jednotky" << endl;
		cout << "Stlaè 5 ak chceš skonèí." << endl;
		cout << "#--------------------------------------------------------------#" << endl;
		cout << endl;
	
		cin >> userInput;
	
		if (userInput == 1)
		{
			if (hierarchy->level(actualPosition) == 0)
			{
				cout << "Nemožeš sa presunú na otca lebo si v koreni celej hierarchie!" << endl;
			}
			else
			{
				actualPosition = *hierarchy->accessParent(actualPosition);
				if (hierarchy->level(actualPosition) == 0)
				{
					cout << "Nachádzaš sa na: " << actualPosition.data_[0] << endl;
				}
				else
				{
					cout << "Nachádzaš sa na: " << actualPosition.data_[2] << endl;
				}
			}
		}
		else if (userInput == 2)
		{
			int userMenuInput;
			vector<string> temp;
			for (int i = 0; i < hierarchy->degree(actualPosition); i++)
			{
				temp.push_back(hierarchy->accessSon(actualPosition, i)->data_[2]);
				cout << "Stlaète:" << " [" << i << "] " << hierarchy->accessSon(actualPosition, i)->data_[2] << endl;
			}

			cout << endl;
			cout << "#--------------------------------------------------------------#" << endl;
			cout << "Stlaète 1 ak sa chcete presunú na konkrétneho syna bez triedenia." << endl;
			cout << "Stlaète 2 ak chcete údaje utriedi pomocou compareAlphabetical." << endl;
			cout << "Stlaète 3 ak chcete údaje utriedi pomocou compareVowelsCount." << endl;
			cout << "#--------------------------------------------------------------#" << endl;
			cout << endl;
			while (!(cin >> userMenuInput))
			{
				cout << "Nezadali ste èíslo. Prosim zadajte znovu èíslo: " << endl;
				cin.clear();
				cin.ignore(123, '\n');
			}

			if (userMenuInput == 1)
			{
				for (int i = 0; i < hierarchy->degree(actualPosition); i++)
				{
					temp.push_back(hierarchy->accessSon(actualPosition, i)->data_[2]);
					cout << "Stlaète:" << " [" << i << "] " << hierarchy->accessSon(actualPosition, i)->data_[2] << endl;
				}
				cout << "Zadajte index syna: " << endl;
				while (!(cin >> userInputSon))
				{
					cout << "Nezadali ste èíslo. Prosim zadajte znovu èíslo: " << endl;
					cin.clear();
					cin.ignore(123, '\n');
				}
				actualPosition = *hierarchy->accessSon(actualPosition, userInputSon);
				cout << "Nachádzaš sa na: " << actualPosition.data_[2] << endl;
			}
			else if (userMenuInput == 2)
			{
				sort(temp, compareAlphabetical);
				for (int i = 0; i < temp.size(); i++)
				{
					cout << temp[i] << endl;
				}
			}
			else if (userMenuInput == 3)
			{
				sort(temp, compareVowelsCount);
				for (int i = 0; i < temp.size(); i++)
				{
					cout << temp[i] << endl;
				}
			}
			else
			{
				cout << "Zadali ste zlý vstup!" << endl;
			}
		}
		else if (userInput == 3)
		{
			cout << endl;
			cout << "#--------------------------------------------------------------#" << endl;
			cout << "Stlaète 1 ak chcete prehladáva pomocou startWithStr" << endl;
			cout << "Stlaète 2 ak chcete prehladáva pomocou containsStr" << endl;
			cout << "#--------------------------------------------------------------#" << endl;
			cout << endl;

			while (!(cin >> userInputALGChosen))
			{
				cout << "Nezadali ste èíslo. Prosim zadajte znovu èíslo: " << endl;
				cin.clear();
				cin.ignore(123, '\n');
			}
	
			if (userInputALGChosen == 1)
			{
				cout << "Zadajte reazec, ktorým sa má vyh¾adávaný výraz zaèína: " << endl;
				cin >> userStringInput;
				int pomocna = 0;
				for (int i = 0; i < hierarchy->degree(actualPosition); i++)
				{
					if (hierarchy->accessSon(actualPosition, i)->data_[2].rfind(userStringInput, 0) == 0)
					{
						pomocna++;
						cout << hierarchy->accessSon(actualPosition, i)->data_[2] << endl;
						cout << "Stlaète:" << " [" << i << "] " << hierarchy->accessSon(actualPosition, i)->data_[2] << " ak chcete prejs na tohto syna." << endl;
						while (!(cin >> userInputSon))
						{
							cout << "Nezadali ste èíslo. Prosim zadajte znovu èíslo: " << endl;
							cin.clear();
							cin.ignore(123, '\n');
						}
						actualPosition = *hierarchy->accessSon(actualPosition, userInputSon);
						cout << "Nachádzaš sa na: " << actualPosition.data_[2] << endl;
					}
				}
				if (pomocna == 0)
				{
					cout << "Nenašli sa žiadne výsledky!" << endl;
				}
			}
			else if (userInputALGChosen == 2)
			{
				cout << "Zadajte reazec, ktorý má vyh¾adávaný výraz obsahova: " << endl;
				cin >> userStringInput;
				int pomocna = 0;
				for (int i = 0; i < hierarchy->degree(actualPosition); i++)
				{
					if (hierarchy->accessSon(actualPosition, i)->data_[2].find(userStringInput) != string::npos)
					{
						pomocna++;
						cout << hierarchy->accessSon(actualPosition, i)->data_[2] << endl;
						cout << "Stlaète:" << " [" << i << "] " << hierarchy->accessSon(actualPosition, i)->data_[2] << " ak chcete prejs na tohto syna." << endl;
						while (!(cin >> userInputSon))
						{
							cout << "Nezadali ste èíslo. Prosim zadajte znovu èíslo: " << endl;
							cin.clear();
							cin.ignore(123, '\n');
						}
						actualPosition = *hierarchy->accessSon(actualPosition, userInputSon);
						cout << "Nachádzaš sa na: " << actualPosition.data_[2] << endl;
					}
				}
				if (pomocna == 0)
				{
					cout << "Nenašli sa žiadne výsledky!" << endl;
				}
			}
			else {
				cout << "Nezadali ste 1 alebo 2!" << endl;
			}
		}
		else if (userInput == 4)
		{
			cout << "Napis jedno z uvedených: štát, kraj, okres, obec. Takto zistíš èi sa na tejto pozícií v hierarchií aktuálne nachádzaš" << endl;
			cin >> userStringInput;
			if (userStringInput == "štát")
			{
				if (hierarchy->level(actualPosition) == 0)
				{
					cout << "Áno, ste práve na štáte!" << endl; 
				}
				else
				{
					cout << "Nie, nie ste práve na štáte!" << endl;
				}
				}
			else if(userStringInput == "kraj")
			{
				if (hierarchy->level(actualPosition) == 1)
				{
					cout << "Áno, ste práve na kraji!" << endl;
				}
				else
				{
					cout << "Nie, nie ste práve na kraji!" << endl;
				}
			}
			else if (userStringInput == "okres")
			{
				if (hierarchy->level(actualPosition) == 2)
				{
					cout << "Áno, ste práve na okrese!" << endl;
				}
				else
				{
					cout << "Nie, nie ste práve na okrese!" << endl;
				}
			}
			else if (userStringInput == "obec")
			{
				if (hierarchy->level(actualPosition) == 3)
				{
					cout << "Áno, ste práve na obci" << endl;
				}
				else
				{
					cout << "Nie, nie ste práve na obci!" << endl;
				}
			}
			else {
				cout << "Nezadali ste správny string!" << endl;
			}
		}
		else if(userInput == 5)
		{
			//destruktor
			for (auto& row : contentKraje) {
				row.clear();
			}
			contentKraje.clear();
			for (auto& row : contentOkresy) {
				row.clear();
			}
			contentOkresy.clear();
			for (auto& row : contentObce) {
				row.clear();
			}
			contentObce.clear();
			exit(1);
			delete& hierarchy;

		}
	}
	//destruktor
	for (auto& row : contentKraje) {
		row.clear();
	}
	contentKraje.clear();
	for (auto& row : contentOkresy) {
		row.clear();
	}
	contentOkresy.clear();
	for (auto& row : contentObce) {
		row.clear();
	}
	contentObce.clear();
	delete &hierarchy;
}

