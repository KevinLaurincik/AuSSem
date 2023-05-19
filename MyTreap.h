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
#include "FileReader.h"

using namespace std;

class MyTreap {
private:
	std::unique_ptr<ds::adt::Treap<std::string, std::vector<std::string>>,
		std::default_delete<ds::adt::Treap<std::string, std::vector<std::string>>>>
		tabulkaKraje = std::make_unique<ds::adt::Treap<string, vector<string>>>();
	std::unique_ptr<ds::adt::Treap<std::string, std::vector<std::string>>,
		std::default_delete<ds::adt::Treap<std::string, std::vector<std::string>>>>
		tabulkaOkresy = std::make_unique<ds::adt::Treap<string, vector<string>>>();
	std::unique_ptr<ds::adt::Treap<std::string, std::vector<std::string>>,
		std::default_delete<ds::adt::Treap<std::string, std::vector<std::string>>>>
		tabulkaObce = std::make_unique<ds::adt::Treap<string, vector<string>>>();
	FileReader reader;
public:
	MyTreap();
	void emplaceTreap();
	void searchMenuTreap();
	~MyTreap();
};