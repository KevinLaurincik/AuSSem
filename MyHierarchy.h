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
#include "FileReader.h"

using namespace std;

class Hierarchy {
private:
	ds::amt::MultiWayExplicitHierarchyBlock<vector<string>> actualPosition;
	std::unique_ptr<ds::amt::MultiWayExplicitHierarchy<std::vector<std::string>>, 
		std::default_delete<ds::amt::MultiWayExplicitHierarchy<std::vector<std::string>>>>
			hierarchy = std::make_unique<ds::amt::MultiWayExplicitHierarchy<vector<string>>>();
	FileReader reader;

public:
	Hierarchy();
	void quickSort(vector<string>& param, std::function<bool(const string&, const string&)> compare, size_t min, size_t max);
	void sort(vector<string>& param, std::function<bool(const string&, const string&)> compare);
	static bool compareAlphabetical(const string& param1, const string& param2);
	static bool compareVowelsCount(const string& param1, const string& param2);
	void emplaceHierarchy();
	void searchMenuHierarchy();
	~Hierarchy();
};
