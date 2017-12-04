#pragma once
#include <string>
#include <cstring>
#include <iostream>
#include "strSplit.h"
#include <fstream>
using namespace std;
string * fileParser(fstream & loadData) {
	string buff;
	string * token;

	// Parse Game Data
	if (!loadData.eof()) {
		getline(loadData, buff);
		return token = strSplit(buff, "\t");
	}

	return nullptr;
}
