#include "MyHierarchy.h"

Hierarchy::Hierarchy()
{
}

void Hierarchy::quickSort(vector<string>&param, std::function<bool(const string&, const string&)> compare, size_t min, size_t max) {
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

void Hierarchy::sort(vector<string>& param, std::function<bool(const string&, const string&)> compare) {
	if (!param.empty())
	{
		quickSort(param, compare, 0, param.size() - 1);
	}
}

bool Hierarchy::compareAlphabetical(const string& param1, const string& param2) {
	return param1 < param2;
}

bool Hierarchy::compareVowelsCount(const string& param1, const string& param2) {
	string vowels = "aA��eE��iI��oO����uU��yY��";
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

void Hierarchy::emplaceHierarchy() {
	auto& root = hierarchy->emplaceRoot();
	actualPosition = root;

	vector<string> koren = { "Slovenska republika" };
	root.data_ = koren;

	reader.readFile("kraje.csv");
	reader.readFile("okresy.csv");
	reader.readFile("obce.csv");

	int premenna1 = 0;

	for (auto& data : reader.contentKraje)
	{
		hierarchy->emplaceSon(root, premenna1).data_ = reader.contentKraje[premenna1];
		//cout << hierarchy->accessSon(root, premenna1)->data_[2] << endl;

		int premenna2 = 0;
		int poradieOkresSyn = 0;

		for (auto& data2 : reader.contentOkresy)
		{
			int premenna3 = 0;
			int poradieObecSyn = 0;

			if (reader.contentOkresy[premenna2][1].find(reader.contentKraje[premenna1][5].substr(reader.contentKraje[premenna1][5].length() - 5)) != std::string::npos)
			{
				hierarchy->emplaceSon(*hierarchy->accessSon(*hierarchy->accessRoot(), premenna1), poradieOkresSyn).data_ = reader.contentOkresy[premenna2];
				//cout << "\t" << hierarchy->accessSon(*hierarchy->accessSon(root, premenna1), poradieOkresSyn)->data_[2] << endl;

				for (auto& data3 : reader.contentObce)
				{
					if (reader.contentObce[premenna3][1].find(reader.contentOkresy[premenna2][1]) != std::string::npos)
					{
						hierarchy->emplaceSon(*hierarchy->accessSon(*hierarchy->accessSon(root, premenna1), poradieOkresSyn), poradieObecSyn).data_ = reader.contentObce[premenna3];
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

void Hierarchy::searchMenuHierarchy() {
	int userInput = 0;
	int userInputSon;
	int userInputALGChosen;
	string userStringInput;

	cout << endl;
	cout << endl;
	cout << "Si v koreni hierarchie: Slovensk� republika" << endl << "\n";
	cout << "M��e� sa presun�t na synov: " << endl;
	for (int i = 0; i < reader.contentKraje.size(); i++)
	{
		cout << reader.contentKraje[i][2] << endl;
	}
	while (true)
	{
		cout << endl;
		cout << "#--------------------------------------------------------------#" << endl;
		cout << "Stla� 1 ak sa chce� presun�� na otca." << endl;
		cout << "Stla� 2 ak sa chce� presun�� na konkr�tneho syna." << endl;
		cout << "Stla� 3 ak chce� pou�i� preh�ad�vacie algoritmy na synov." << endl;
		cout << "Stla� 4 ak chce� overit typ uzemnej jednotky" << endl;
		cout << "Stla� 5 ak chce� skon��." << endl;
		cout << "#--------------------------------------------------------------#" << endl;
		cout << endl;

		cin >> userInput;

		if (userInput == 1)
		{
			if (hierarchy->level(actualPosition) == 0)
			{
				cout << "Nemo�e� sa presun�� na otca lebo si v koreni celej hierarchie!" << endl;
			}
			else
			{
				actualPosition = *hierarchy->accessParent(actualPosition);
				if (hierarchy->level(actualPosition) == 0)
				{
					cout << "Nach�dza� sa na: " << actualPosition.data_[0] << endl;
				}
				else
				{
					cout << "Nach�dza� sa na: " << actualPosition.data_[2] << endl;
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
				cout << "Stla�te:" << " [" << i << "] " << hierarchy->accessSon(actualPosition, i)->data_[2] << endl;
			}

			cout << endl;
			cout << "#--------------------------------------------------------------#" << endl;
			cout << "Stla�te 1 ak sa chcete presun�� na konkr�tneho syna bez triedenia." << endl;
			cout << "Stla�te 2 ak chcete �daje utriedi� pomocou compareAlphabetical." << endl;
			cout << "Stla�te 3 ak chcete �daje utriedi� pomocou compareVowelsCount." << endl;
			cout << "#--------------------------------------------------------------#" << endl;
			cout << endl;
			while (!(cin >> userMenuInput))
			{
				cout << "Nezadali ste ��slo. Prosim zadajte znovu ��slo: " << endl;
				cin.clear();
				cin.ignore(123, '\n');
			}

			if (userMenuInput == 1)
			{
				for (int i = 0; i < hierarchy->degree(actualPosition); i++)
				{
					temp.push_back(hierarchy->accessSon(actualPosition, i)->data_[2]);
					cout << "Stla�te:" << " [" << i << "] " << hierarchy->accessSon(actualPosition, i)->data_[2] << endl;
				}
				cout << "Zadajte index syna: " << endl;
				while (!(cin >> userInputSon))
				{
					cout << "Nezadali ste ��slo. Prosim zadajte znovu ��slo: " << endl;
					cin.clear();
					cin.ignore(123, '\n');
				}
				actualPosition = *hierarchy->accessSon(actualPosition, userInputSon);
				cout << "Nach�dza� sa na: " << actualPosition.data_[2] << endl;
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
				cout << "Zadali ste zl� vstup!" << endl;
			}
		}
		else if (userInput == 3)
		{
			cout << endl;
			cout << "#--------------------------------------------------------------#" << endl;
			cout << "Stla�te 1 ak chcete prehlad�va� pomocou startWithStr" << endl;
			cout << "Stla�te 2 ak chcete prehlad�va� pomocou containsStr" << endl;
			cout << "#--------------------------------------------------------------#" << endl;
			cout << endl;

			while (!(cin >> userInputALGChosen))
			{
				cout << "Nezadali ste ��slo. Prosim zadajte znovu ��slo: " << endl;
				cin.clear();
				cin.ignore(123, '\n');
			}

			if (userInputALGChosen == 1)
			{
				cout << "Zadajte re�azec, ktor�m sa m� vyh�ad�van� v�raz za��na�: " << endl;
				cin >> userStringInput;
				int pomocna = 0;
				for (int i = 0; i < hierarchy->degree(actualPosition); i++)
				{
					if (hierarchy->accessSon(actualPosition, i)->data_[2].rfind(userStringInput, 0) == 0)
					{
						pomocna++;
						cout << hierarchy->accessSon(actualPosition, i)->data_[2] << endl;
						cout << "Stla�te:" << " [" << i << "] " << hierarchy->accessSon(actualPosition, i)->data_[2] << " ak chcete prejs� na tohto syna." << endl;
						while (!(cin >> userInputSon))
						{
							cout << "Nezadali ste ��slo. Prosim zadajte znovu ��slo: " << endl;
							cin.clear();
							cin.ignore(123, '\n');
						}
						actualPosition = *hierarchy->accessSon(actualPosition, userInputSon);
						cout << "Nach�dza� sa na: " << actualPosition.data_[2] << endl;
					}
				}
				if (pomocna == 0)
				{
					cout << "Nena�li sa �iadne v�sledky!" << endl;
				}
			}
			else if (userInputALGChosen == 2)
			{
				cout << "Zadajte re�azec, ktor� m� vyh�ad�van� v�raz obsahova�: " << endl;
				cin >> userStringInput;
				int pomocna = 0;
				for (int i = 0; i < hierarchy->degree(actualPosition); i++)
				{
					if (hierarchy->accessSon(actualPosition, i)->data_[2].find(userStringInput) != string::npos)
					{
						pomocna++;
						cout << hierarchy->accessSon(actualPosition, i)->data_[2] << endl;
						cout << "Stla�te:" << " [" << i << "] " << hierarchy->accessSon(actualPosition, i)->data_[2] << " ak chcete prejs� na tohto syna." << endl;
						while (!(cin >> userInputSon))
						{
							cout << "Nezadali ste ��slo. Prosim zadajte znovu ��slo: " << endl;
							cin.clear();
							cin.ignore(123, '\n');
						}
						actualPosition = *hierarchy->accessSon(actualPosition, userInputSon);
						cout << "Nach�dza� sa na: " << actualPosition.data_[2] << endl;
					}
				}
				if (pomocna == 0)
				{
					cout << "Nena�li sa �iadne v�sledky!" << endl;
				}
			}
			else {
				cout << "Nezadali ste 1 alebo 2!" << endl;
			}
		}
		else if (userInput == 4)
		{
			cout << "Napis jedno z uveden�ch: �t�t, kraj, okres, obec. Takto zist� �i sa na tejto poz�ci� v hierarchi� aktu�lne nach�dza�" << endl;
			cin >> userStringInput;
			if (userStringInput == "�t�t")
			{
				if (hierarchy->level(actualPosition) == 0)
				{
					cout << "�no, ste pr�ve na �t�te!" << endl;
				}
				else
				{
					cout << "Nie, nie ste pr�ve na �t�te!" << endl;
				}
			}
			else if (userStringInput == "kraj")
			{
				if (hierarchy->level(actualPosition) == 1)
				{
					cout << "�no, ste pr�ve na kraji!" << endl;
				}
				else
				{
					cout << "Nie, nie ste pr�ve na kraji!" << endl;
				}
			}
			else if (userStringInput == "okres")
			{
				if (hierarchy->level(actualPosition) == 2)
				{
					cout << "�no, ste pr�ve na okrese!" << endl;
				}
				else
				{
					cout << "Nie, nie ste pr�ve na okrese!" << endl;
				}
			}
			else if (userStringInput == "obec")
			{
				if (hierarchy->level(actualPosition) == 3)
				{
					cout << "�no, ste pr�ve na obci" << endl;
				}
				else
				{
					cout << "Nie, nie ste pr�ve na obci!" << endl;
				}
			}
			else {
				cout << "Nezadali ste spr�vny string!" << endl;
			}
		}
		else if (userInput == 5)
		{
			exit(1);
		}
		else
		{
			cout << "Zadali ste zl� vstup!" << endl;
		}
	}
}

Hierarchy::~Hierarchy()
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
	hierarchy->clear();
}

