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

//Below is a datatype to store score values.
typedef map<pair<string, double>, int> scoreTable2;

//To store identification ranks;
typedef map<string, map<int, int>> IdenMatrix;
IdenMatrix iden;

char* changeToChar3(string directory) {
	char dest[10000];
	strncpy_s(dest, directory.c_str(), sizeof(dest));
	return dest;
}

//Writing to csv.
map<string,pair<int,int>> writeIden(IdenMatrix &iden) {
	//Creting folders
	string destination = "../../../Identity";
	_mkdir(changeToChar3(destination));
	_mkdir(changeToChar3(destination+"/Frequency"));

	//Storage
	map<string, pair<int, int>> store;

	for (auto i = iden.begin(); i != iden.end(); i++) {
		ofstream file;
		auto title = i->first; //Name of the person
		int maxRank=0, Freq=0;
		file.open(changeToChar3(destination + "/Frequency/" + title + ".csv"));
		file << "Rank,Frequency" << endl;
		for (auto j = (i->second).begin(); j != (i->second).end(); j++) {
			file << j->first << "," << j->second << endl;

			//Geting max Frequency Ranks.
			if (j->second > Freq) {
				Freq = j->second;
				maxRank = j->first;
			}
		}
		store.insert(make_pair(title, make_pair(maxRank, Freq)));
	}
	return store;
}

void writeStore(map<string, pair<int, int>> &store) {

	string destination = "../../../Identity";
	ofstream file;
	file.open(changeToChar3(destination + "/maxRankFrequency.csv"));
	file << "Name,Max Rank,Max Frequency" << endl;

	for (auto i = store.begin(); i != store.end(); i++) {
		
		auto name = i->first; //Name of the person
		int maxRank = i->second.first, Freq = i->second.second;
		
		file << name << "," << maxRank << "," << Freq << endl;
	}
}

void getIndentificationRanks(vector<scoreTable2> parse){
	
	for (auto i = parse.begin(); i != parse.end(); i++) {
		for (auto j = (*i).begin(); j != (*i).end(); j++) {

			//Setting values
			string name = j->first.first;
			int rank = j->second;
		
			//Inserting
			map<int, int> x;
			x.insert(make_pair(rank, 1));
			auto detect = iden.insert(make_pair(name,x));

			//Sub map iterator
			
			if (detect.second == false) {
				auto detect2 = (detect.first->second).insert(make_pair(rank,1));
				if (detect2.second == false) {
					(detect2.first->second) += 1;
					//cout << name <<" has occured with same rank more than once."<<endl;
				}
			}
		}

		//Printing the iden
		
		
	}
	IdenMatrix  idnG = iden;
}