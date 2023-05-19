#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdio>
#include "libds/amt/explicit_hierarchy.h"
#include "libds/adt/table.h"
#include <cstdlib>
#include <Windows.h>
#include "MySequence.h"
#include "MyHierarchy.h"
#include "MyTreap.h"


using namespace std;

int main()
{
	SetConsoleOutputCP(1250);
	SetConsoleCP(1250);
	setlocale(LC_ALL, "slovak");
	
	while (true)
	{
		int userMenuInput;

		cout << "#--------------------------------------------------------------#" << endl;
		cout << "Vyberte si, ktorú údajovú štruktúru chcete použiť: " << endl;
		cout << "Stlačte [1] ak chcete použiť Sequence!" << endl;
		cout << "Stlačte [2] ak chcete použiť viac-cestnú explicitnú hierarchiu!" << endl;
		cout << "Stlačte [3] ak chcete použiť Treap!" << endl;
		cout << "#--------------------------------------------------------------#" << endl;

		while (!(cin >> userMenuInput))
		{
			cout << "Nezadali ste číslo. Prosim zadajte znovu číslo: " << endl;
			cin.clear();
			cin.ignore(123, '\n');
		}

		cout << "Zadali ste číslo: " << userMenuInput << endl;

		if (userMenuInput == 1)
		{
			Sequence sequence;
			sequence.searchMenuSequence();
		}
		else if (userMenuInput == 2)
		{
			Hierarchy hierarchy;
			hierarchy.emplaceHierarchy();
			hierarchy.searchMenuHierarchy();
			hierarchy.~Hierarchy();
			//emplaceHierarchy();
			//searchMenuHierarchy();
		}
		else if (userMenuInput == 3)
		{
			MyTreap treap;
			treap.emplaceTreap();
			treap.searchMenuTreap();
		}
		else
		{
			cout << "Zadali ste zlý vstup!" << endl;
		}
	}
}


