#include "FileReader.h"

FileReader::FileReader()
{
}

void FileReader::readFile(string nazovSuboru) {
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