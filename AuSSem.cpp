#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <cstdio>
#include "libds/amt/explicit_hierarchy.h"
#include "AuSSem.h"
#include <cstdlib>


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
			std::cout << result[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void emplaceHierarchy() {
	auto hierarchy = std::make_unique<ds::amt::MultiWayExplicitHierarchy<vector<string>>>();
	auto& root = hierarchy->emplaceRoot();

	vector<string> koren = { "Slovenska republika" };
	root.data_ = koren;

	vector<vector<string>> contentKraje;
	vector<vector<string>> contentOkresy;
	vector<vector<string>> contentObce;
	vector<string> row;
	string line;
	string word;

	int x = 0;
	std::fstream file("kraje.csv");

	if (file.is_open())
	{
		getline(file, line); //aby sa preskocil prvy riadok
		while (getline(file, line))
		{
			row.clear();

			stringstream str(line);

			while (getline(str, word, ';'))
				row.push_back(word);
			contentKraje.push_back(row);
		}
	}

	std::fstream file2("okresy.csv");
	if (file2.is_open())
	{
		getline(file2, line);
		while (getline(file2, line))
		{
			row.clear();

			stringstream str(line);

			while (getline(str, word, ';'))
				row.push_back(word);
			contentOkresy.push_back(row);
		}
	}

	int z = 0;
	std::fstream file3("obce.csv");
	if (file3.is_open())
	{
		getline(file3, line);
		while (getline(file3, line))
		{
			row.clear();

			stringstream str(line);

			while (getline(str, word, ';'))
				row.push_back(word);
			contentObce.push_back(row);
			
		}
	}

	int premenna1 = 0;
	
	for ( auto &data : contentKraje)
	{
		hierarchy->emplaceSon(root, premenna1).data_ = contentKraje[premenna1];
		cout << hierarchy->accessSon(root, premenna1)->data_[2] << endl;

		int premenna2 = 0;
		int poradieOkresSyn = 0;

		for (auto &data2 : contentOkresy)
		{
			int premenna3 = 0;
			int poradieObecSyn = 0;

			if (contentOkresy[premenna2][1].find(contentKraje[premenna1][5].substr(contentKraje[premenna1][5].length() - 5)) != std::string::npos)
			{
				hierarchy->emplaceSon(*hierarchy->accessSon(*hierarchy->accessRoot(), premenna1), poradieOkresSyn).data_ = contentOkresy[premenna2];
				cout << "\t" << hierarchy->accessSon(*hierarchy->accessSon(root, premenna1), poradieOkresSyn)->data_[2] << endl;

				for(auto &data3 : contentObce)
				{
					if (contentObce[premenna3][1].find(contentOkresy[premenna2][1]) != std::string::npos)
					{
						hierarchy->emplaceSon(*hierarchy->accessSon(*hierarchy->accessSon(root, premenna1), poradieOkresSyn), poradieObecSyn).data_ = contentObce[premenna3];
						cout << "\t\t" << hierarchy->accessSon(*hierarchy->accessSon(*hierarchy->accessSon(root, premenna1), poradieOkresSyn), poradieObecSyn)->data_[2] << endl;
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

	int userInput = 0;
	int userInputSon;
	int userInputALGChosen;
	string userStringInput;
	ds::amt::MultiWayExplicitHierarchyBlock<vector<string>> actualPosition = root;


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
		cout << "Stlač 1 ak sa chceš presunúť na otca." << endl;
		cout << "Stlač 2 ak sa chceš presunúť na konkrétneho syna." << endl;
		cout << "Stlač 3 ak chceš použiť prehľadávacie algoritmy na synov." << endl;
		cout << "Stlač 4 ak chceš overit typ uzemnej jednotky" << endl;
		cout << "Stlač 5 ak chceš skončíť.";
		cout << endl;

		cin >> userInput;

		if (userInput == 1)
		{
			if (hierarchy->level(actualPosition) == 0)
			{
				cout << "Nemožeš sa presunúť na otca lebo si v koreni celej hierarchie!" << endl;
			}
			else
			{
				actualPosition = *hierarchy->accessParent(actualPosition);
				cout << "Nachádzaš sa na: " << actualPosition.data_[2] << endl;
			}
		}
		else if (userInput == 2)
		{
			for (int i = 0; i < hierarchy->degree(actualPosition); i++)
			{
				cout << "Stlačte:" << " [" << i << "] " << hierarchy->accessSon(actualPosition, i)->data_[2] << endl;
			}
			cin >> userInputSon;
			actualPosition = *hierarchy->accessSon(actualPosition, userInputSon);
			cout << "Nachádzaš sa na: " << actualPosition.data_[2] << endl;
		}
		else if (userInput == 3)
		{
			cout << "Stlačte 1 ak chcete prehladávať pomocou startWithStr" << endl;
			cout << "Stlačte 2 ak chcete prehladávať pomocou containsStr" << endl;
			cin >> userInputALGChosen;

			if (userInputALGChosen == 1)
			{
				cout << "Zadajte reťazec, ktorým sa má vyhľadávaný výraz začínať: " << endl;
				cin >> userStringInput;
				int pomocna = 0;
				for (int i = 0; i < hierarchy->degree(actualPosition); i++)
				{
					if (hierarchy->accessSon(actualPosition, i)->data_[2].rfind(userStringInput, 0) == 0)
					{
						pomocna++;
						/*cout << hierarchy->accessSon(actualPosition, i)->data_[2] << endl;*/
						cout << "Stlačte:" << " [" << i << "] " << hierarchy->accessSon(actualPosition, i)->data_[2] << " ak chcete prejsť na tohto syna." << endl;
						cin >> userInputSon;
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
				cout << "Zadajte reťazec, ktorý má vyhľadávaný výraz obsahovať: " << endl;
				cin >> userStringInput;
				int pomocna = 0;
				for (int i = 0; i < hierarchy->degree(actualPosition); i++)
				{
					if (hierarchy->accessSon(actualPosition, i)->data_[2].find(userStringInput) != string::npos)
					{
						pomocna++;
						/*cout << hierarchy->accessSon(actualPosition, i)->data_[2] << endl;*/
						cout << "Stlačte:" << " [" << i << "] " << hierarchy->accessSon(actualPosition, i)->data_[2] << " ak chcete prejsť na tohto syna." << endl;
						cin >> userInputSon;
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
			cout << "Napis jedno z uvedených: štát, kraj, okres, obec. Takto zistíš či sa na tejto pozícií v hierarchií aktuálne nachádzaš" << endl;
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
			exit(1);
		}
	}
	
}



int main()
{
	SetConsoleOutputCP(1250);
	SetConsoleCP(1250);
	setlocale(LC_ALL, "slovak");
	vector<vector<string>> content;
	vector<vector<string>> contentKraje;
	vector<vector<string>> contentOkresy;
	vector<vector<string>> contentObce;
	vector<string> row;
	string line;
	string word;
	int userInput;
	string stringUserInput;



 	cout << "Stlačte 1 ak chcete prehladávať pomocou startWithStr" << endl;
	cout << "Stlačte 2 ak chcete prehladávať pomocou containsStr" << endl;
	emplaceHierarchy();
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
}


