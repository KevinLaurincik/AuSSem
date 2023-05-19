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

class FileReader
{
public:
	FileReader();
	vector<vector<string>> contentKraje;
	vector<vector<string>> contentOkresy;
	vector<vector<string>> contentObce;
	void readFile(string nazovSuboru);
};

