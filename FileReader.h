#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class FileReader
{
	struct Obce
	{
		vector<int> sortNumber;
		vector<string> code;
		vector<string> officialTitle;
		vector<string> mediumTitle;
		vector<string> shortTitle;
		vector<int> note;
	};

	struct Okresy
	{
		vector<int> sortNumber;
		vector<string> code;
		vector<string> officialTitle;
		vector<string> mediumTitle;
		vector<string> shortTitle;
		vector<int> note;
	};

	struct Kraje
	{
		vector<int> sortNumber;
		vector<string> code;
		vector<string> officialTitle;
		vector<string> mediumTitle;
		vector<string> shortTitle;
		vector<int> note;
	};

	private:
		string line;

	public:

		
};

