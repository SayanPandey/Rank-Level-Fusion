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
#include<sstream>

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

void writeIdentity(map<string, pair<int, int>> &store) {

	string destination = "../../../Identity";
	ofstream file;
	file.open(changeToChar3(destination + "/percentageRank.csv"));
	file << "Name,Min Rank,Frequency in fused tables,Percentage" << endl;

	for (auto i = store.begin(); i != store.end(); i++) {

		auto name = i->first; //Name of the person
		int maxRank = i->second.first, Freq = i->second.second;
		double percent = (double(Freq) / store.size()) * 100;

		file << name << "," << maxRank << "," << Freq <<","<< percent << endl;
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

map<string, int> readCSV2(string path) {

	ifstream file;
	file.open(changeToChar3(path));
	//Checking file 
	if (!file.is_open()) {
		cout << "Falied to open fused rank tables." << endl;
		exit(-1);
	}
	string temp;
	vector<vector<string>> parse;
	map<string, int> list;
	//Reading Lines from the stream
	while (getline(file, temp))
	{
		vector<string> csvColumn;
		string csvElement;
		// read every element from the line that is seperated by commas
		// and put it into the vector or strings
		while (getline(file, csvElement, '\n'))
		{
			//Setting string stream
			stringstream ss(csvElement);
			string token;
			int flag = 0;
			string name;
			int rank;
			while (getline(ss, token, ','))
			{
				csvColumn.push_back(token);
				if (flag == 0 && token!="") {
					flag = 1;
					name = token;
				}
				else if(flag==2 && token != "")  {
					flag = 0;
					rank = stoi(token);
				}
				else {
					flag = 2;
				}
			}
			list.insert(make_pair(name, rank));
			parse.push_back(csvColumn);
			csvColumn.clear();
		}
	}

	//Print Parse
	/*for (auto i = parse.begin(); i != parse.end(); i++) {
		int x = 1;
		cout << x << " ";
		for (auto j = (*i).begin(); j != (*i).end(); j++) {
			cout << *j << " ";
		}
		cout << endl;
	}*/
	file.close();
	return list;
}

map<string, pair<int, int>> readCSV3(string path) {

	ifstream file;
	file.open(changeToChar3(path));
	//Checking file 
	if (!file.is_open()) {
		cout << "Falied to open fused rank tables." << endl;
		exit(-1);
	}
	string temp;
	vector<vector<string>> parse;
	map<string, pair<int, int>> list;
	//Reading Lines from the stream
	while (getline(file, temp))
	{
		vector<string> csvColumn;
		string csvElement;
		// read every element from the line that is seperated by commas
		// and put it into the vector or strings
		while (getline(file, csvElement, '\n'))
		{
			//Setting string stream
			stringstream ss(csvElement);
			string token;
			int flag = 0;
			string name;
			int rank;
			int freq;
			while (getline(ss, token, ','))
			{
				csvColumn.push_back(token);
				if (flag == 0 && token != "") {
					flag = 1;
					name = token;
				}
				else if (flag == 1 && token != "") {
					flag = 2;
					rank = stoi(token);
				}
				else if(flag == 2 && token != "") {
					flag = 0;
					freq = stoi(token);
				}
			}
			list.insert(make_pair(name,make_pair(rank,freq)));
			parse.push_back(csvColumn);
			csvColumn.clear();
		}
	}

	//Print Parse
	/*for (auto i = parse.begin(); i != parse.end(); i++) {
		int x = 1;
		cout << x << " ";
		for (auto j = (*i).begin(); j != (*i).end(); j++) {
			cout << *j << " ";
		}
		cout << endl;
	}*/
	file.close();
	return list;
}

void readFusedRankList(vector<string> &csvList,string title="Highest Rank") {

	vector<map<string,int>> storeHighRank;
	map<string, pair<int, int>> store;

	int ct = 0;
	//To get Fused high rank tables
	for (auto i = csvList.begin(); i != csvList.end(); i++) {
		cout << *i << endl;
		(*i).erase((*i).end() - 4, (*i).end());
		auto parse = readCSV2("../../../Output_Fused_Rank/" + *i + "/" + title+".csv");
		storeHighRank.push_back(parse);
		ct++;
	}

	//To get max Score Frequen score table;
	store = readCSV3("../../../Identity/maxRankFrequency.csv");


	map<string,pair<int, int>> toIdentify;
	for (auto i = store.begin(); i != store.end(); i++) {
		int freq = 0;
		string name = i->first;
		int maxFreqRank = i->second.first;
		for (auto j = storeHighRank.begin(); j != storeHighRank.end(); j++) {
			auto x = (*j).find(name);
			if (x != (*j).end()) {
				if (x->second == maxFreqRank) freq++;
			}
		}
		toIdentify.insert(make_pair(name,make_pair(maxFreqRank, freq)));
	}
	writeIdentity(toIdentify);
}