#include "MyTreap.h"

MyTreap::MyTreap()
{
}

void MyTreap::emplaceTreap()
{
	reader.readFile("kraje.csv");
	reader.readFile("okresy.csv");
	reader.readFile("obce.csv");

	int riadok = 0;
	for (auto& kraj : reader.contentKraje)
	{
		tabulkaKraje->insert(reader.contentKraje[riadok][2], reader.contentKraje[riadok]);
		//cout << tabulkaKraje->find(contentKraje[riadok][2])[2] << endl;
		riadok++;
	}

	riadok = 0;
	for (auto& okres : reader.contentOkresy)
	{
		vector<string>* duplicity;
		duplicity = &reader.contentOkresy[riadok];
		if (tabulkaOkresy->tryFind(reader.contentOkresy[riadok][3], duplicity))
		{
			vector<string> duplicityList;
			vector<string> oldRecord = tabulkaOkresy->find(reader.contentOkresy[riadok][3]);
			for (int i = 0; i < oldRecord.size(); i++)
			{
				duplicityList.push_back(oldRecord[i]);
			}
			duplicityList.emplace_back("\t");
			for (int i = 0; i < reader.contentOkresy[riadok].size(); i++)
			{
				duplicityList.push_back(reader.contentOkresy[riadok][i]);
			}
			duplicityList.emplace_back("\t");

			tabulkaOkresy->remove(reader.contentOkresy[riadok][3]);

			tabulkaOkresy->insert(duplicityList[3], duplicityList);
		}
		else
		{
			tabulkaOkresy->insert(reader.contentOkresy[riadok][3], reader.contentOkresy[riadok]);
		}
		//cout << tabulkaOkresy->find(contentOkresy[riadok][3])[3] << endl;
		riadok++;
	}

	riadok = 0;
	for (auto& obec : reader.contentObce)
	{
		vector<string>* duplicity;
		duplicity = &reader.contentObce[riadok];

		if (tabulkaObce->tryFind(reader.contentObce[riadok][2], duplicity))
		{
			vector<string> duplicityList;
			vector<string> oldRecord = tabulkaObce->find(reader.contentObce[riadok][2]);
			for (int i = 0; i < oldRecord.size(); i++)
			{
				duplicityList.push_back(oldRecord[i]);
			}
			duplicityList.emplace_back("\t");
			for (int i = 0; i < reader.contentObce[riadok].size(); i++)
			{
				duplicityList.push_back(reader.contentObce[riadok][i]);
			}
			duplicityList.emplace_back("\t");

			tabulkaObce->remove(reader.contentObce[riadok][2]);

			tabulkaObce->insert(duplicityList[2], duplicityList);
		}
		else
		{
			tabulkaObce->insert(reader.contentObce[riadok][2], reader.contentObce[riadok]);
		}

		//cout << tabulkaObce->find(contentObce[riadok][2])[2] << endl;
		riadok++;
	}
}

void MyTreap::searchMenuTreap()
{
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
			cout << endl;
			cout << "Nájdené kraje: " << endl << "\n";
			if (tabulkaKraje->contains(stringUserInput))
			{
				cout << tabulkaKraje->find(stringUserInput)[2] << endl;
				for (int i = 0; i < tabulkaKraje->find(stringUserInput).size(); i++)
				{
					cout << tabulkaKraje->find(stringUserInput)[i] << " ";
				}
			}
			else
			{
				cout << "Na základe k¾úèa sa nenašiel výsledok!" << endl;
			}
			cout << endl;
		}
		else if (userInput == 2)
		{
			cout << "Zadajte k¾úè ktorý chcete vyh¾ada: " << endl;
			string stringUserInput;
			cin.ignore();
			getline(cin, stringUserInput);
			cout << endl;
			cout << "Nájdené okresy: " << endl << "\n";
			if (tabulkaOkresy->contains(stringUserInput))
			{
				cout << tabulkaOkresy->find(stringUserInput)[2] << endl;
				for (int i = 0; i < tabulkaOkresy->find(stringUserInput).size(); i++)
				{
					cout << tabulkaOkresy->find(stringUserInput)[i] << " ";
				}
			}
			else
			{
				cout << "Na základe k¾úèa sa nenašiel výsledok!" << endl;
			}
			cout << endl;
		}
		else if (userInput == 3)
		{
			cout << "Zadajte k¾úè ktorý chcete vyh¾ada: " << endl;
			string stringUserInput;
			cin.ignore();
			getline(cin, stringUserInput);
			cout << endl;
			cout << "Nájdené obce: " << endl << "\n";
			if (tabulkaObce->contains(stringUserInput))
			{
				cout << tabulkaObce->find(stringUserInput)[2] << endl;
				for (int i = 0; i < tabulkaObce->find(stringUserInput).size(); i++)
				{
					cout << tabulkaObce->find(stringUserInput)[i] << " ";
				}
			}
			else
			{
				cout << "Na základe k¾úèa sa nenašiel výsledok!" << endl;
			}
			cout << endl;
		}
		else if (userInput == 4)
		{
			exit(1);
		}
		else
		{
			cout << "Nesprávne ste zadali volbu!" << endl;
		}
	}
}

MyTreap::~MyTreap()
{
	for (auto& row : reader.contentKraje) {
		row.clear();
	}
	reader.contentKraje.clear();
	for (auto& row : reader.contentOkresy) {
		row.clear();
	}
	reader.contentOkresy.clear();
	for (auto& row : reader.contentObce) {
		row.clear();
	}
	reader.contentObce.clear();
	tabulkaKraje->clear();
	tabulkaOkresy->clear();
	tabulkaObce->clear();
}
