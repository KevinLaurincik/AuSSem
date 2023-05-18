#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <cstdio>
#include "libds/adt/table.h"
#include <cstdlib>
#include <Windows.h>

using namespace std;

auto tabulkaKraje = std::make_unique<ds::adt::Treap<string, vector<string>>>();
auto tabulkaOkresy = std::make_unique<ds::adt::Treap<string, vector<string>>>();
auto tabulkaObce = std::make_unique<ds::adt::Treap<string, vector<string>>>();

void emplaceTreap() {
	readFile("kraje.csv");
	readFile("okresy.csv");
	readFile("obce.csv");

	int riadok = 0;
	for (auto& kraj : contentKraje)
	{
		tabulkaKraje->insert(contentKraje[riadok][2], contentKraje[riadok]);
		//cout << tabulkaKraje->find(contentKraje[riadok][2])[2] << endl;
		riadok++;
	}

	riadok = 0;
	for (auto& okres : contentOkresy)
	{
		vector<string>* duplicity;
		duplicity = &contentOkresy[riadok];
		if (tabulkaOkresy->tryFind(contentOkresy[riadok][3], duplicity))
		{
			vector<string> duplicityList;
			vector<string> oldRecord = tabulkaOkresy->find(contentOkresy[riadok][3]);
			for (int i = 0; i < oldRecord.size(); i++)
			{
				duplicityList.push_back(oldRecord[i]);
			}
			duplicityList.emplace_back("\t");
			for (int i = 0; i < contentOkresy[riadok].size(); i++)
			{
				duplicityList.push_back(contentOkresy[riadok][i]);
			}
			duplicityList.emplace_back("\t");

			tabulkaOkresy->remove(contentOkresy[riadok][3]);

			tabulkaOkresy->insert(duplicityList[3], duplicityList);
		}
		else
		{
			tabulkaOkresy->insert(contentOkresy[riadok][3], contentOkresy[riadok]);
		}
		//cout << tabulkaOkresy->find(contentOkresy[riadok][3])[3] << endl;
		riadok++;
	}

	riadok = 0;
	for (auto& obec : contentObce)
	{
		vector<string>* duplicity;
		duplicity = &contentObce[riadok];

		if (tabulkaObce->tryFind(contentObce[riadok][2], duplicity))
		{
			vector<string> duplicityList;
			vector<string> oldRecord = tabulkaObce->find(contentObce[riadok][2]);
			for (int i = 0; i < oldRecord.size(); i++)
			{
				duplicityList.push_back(oldRecord[i]);
			}
			duplicityList.emplace_back("\t");
			for (int i = 0; i < contentObce[riadok].size(); i++)
			{
				duplicityList.push_back(contentObce[riadok][i]);
			}
			duplicityList.emplace_back("\t");

			tabulkaObce->remove(contentObce[riadok][2]);

			tabulkaObce->insert(duplicityList[2], duplicityList);
		}
		else
		{
			tabulkaObce->insert(contentObce[riadok][2], contentObce[riadok]);
		}

		//cout << tabulkaObce->find(contentObce[riadok][2])[2] << endl;
		riadok++;
	}
}
void searchMenuTreap() {
	while (true)
	{
		cout << endl;
		cout << "#--------------------------------------------------------------#" << endl;
		cout << "Ak chcete preh¾adáva kraje stlaète 1" << endl;
		cout << "Ak chcete preh¾adáva okresy stlaète 2" << endl;
		cout << "Ak chcete preh¾adáva obce stlaète 3" << endl;
		cout << "Ak chcete ukonèi aplikáciu stlaète 4" << endl;
		cout << "#--------------------------------------------------------------#" << endl;
		cout << endl;

		int userInput;
		while (!(cin >> userInput))
		{
			cout << "Nezadali ste èíslo. Prosim zadajte znovu èíslo: " << endl;
			cin.clear();
			cin.ignore(123, '\n');
		}

		cout << "Zadali ste èíslo: " << userInput << endl;

		if (userInput == 1)
		{
			cout << "Zadajte k¾úè ktorý chcete vyh¾ada: " << endl;
			string stringUserInput;
			cin.ignore();
			getline(cin, stringUserInput);
			cout << "Nájdené kraje: " << endl << "\n";
			cout << tabulkaKraje->find(stringUserInput)[2] << endl;
			for (int i = 0; i < tabulkaKraje->find(stringUserInput).size(); i++)
			{
				cout << tabulkaKraje->find(stringUserInput)[i] << " ";
			}
			cout << endl;
		}
		else if (userInput == 2)
		{
			cout << "Zadajte k¾úè ktorý chcete vyh¾ada: " << endl;
			string stringUserInput;
			cin.ignore();
			getline(cin, stringUserInput);
			cout << "Nájdené okresy: " << endl << "\n";
			for (int i = 0; i < tabulkaOkresy->find(stringUserInput).size(); i++)
			{
				cout << tabulkaOkresy->find(stringUserInput)[i] << " ";
			}
			cout << endl;
		}
		else if (userInput == 3)
		{
			cout << "Zadajte k¾úè ktorý chcete vyh¾ada: " << endl;
			string stringUserInput;
			cin.ignore();
			getline(cin, stringUserInput);
			cout << "Nájdené obce: " << endl << "\n";
			for (int i = 0; i < tabulkaObce->find(stringUserInput).size(); i++)
			{
				cout << tabulkaObce->find(stringUserInput)[i] << " ";
			}
			cout << endl;
		}
		else if (userInput == 4)
		{
			exit(1);
			delete& tabulkaKraje;
			delete& tabulkaOkresy;
			delete& tabulkaObce;
		}
		else
		{
			cout << "Nesprávne ste zadali volbu!" << endl;
		}
	}
	//prejdi forom vsetky vector stingy t tabulkach a deletni ich potom daj delete samostatnej sabulky tak isto aj hierarchy
	delete& tabulkaKraje;
	delete& tabulkaOkresy;
	delete& tabulkaObce;
}
;
