#pragma once
#include "pch.h"
#include<iostream>
#include<map>
#include<vector>
#include<iomanip>
#include<string>
#include<fstream>
#include <stdlib.h>
#include <direct.h>
#include <stdio.h>
#include "dirent.h"

using namespace std;

char* changeToChar2(string directory) {
	char dest[10000];
	strncpy_s(dest, directory.c_str(), sizeof(dest));
	return dest;
}

void writeTine(map<string,double> timetable,string destination, string title) {
	ofstream file;
	file.open(changeToChar2(destination + "/" + title + ".csv"));
	file << "Name," << title << endl;
	file << "," << endl; file << "," << endl;

	//Placing the ranks
	for (auto i = timetable.begin(); i != timetable.end(); i++) {
		file << i->first<< "," << i->second<< endl;
	}
}
