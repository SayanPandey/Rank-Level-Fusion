// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include<iostream>
#include<map>
#include<vector>
#include<iomanip>
#include<string>
#include <sstream>

#include "FusionAlgo.h"
#include "FileSort.h"
#include "dirent.h"

//Below is a datatype to store score values.
typedef map<pair<string, double>, int> scoreTable2;

int getScoreList(vector<string> &csvList) {
	DIR *dir;
	vector<string> store;

	//Setting directories to store fused results;
	string source = "../../../ScoreBoard";
	_mkdir("../../../Output_Fused_Rank");

	char src[10000];
	strncpy_s(src, source.c_str(), sizeof(src));

	struct dirent *ent;
	if ((dir = opendir(src)) != NULL) {
		//print all the files and directories within directory
		while ((ent = readdir(dir)) != NULL) {
			//cout << ent->d_name << endl;
				csvList.push_back(ent->d_name);
		}

		//To remove directory "." and ".."
		csvList.erase(csvList.begin(), csvList.begin() + 2);
		closedir(dir);
	}
	else {
		// could not open directory
		perror("");
		return EXIT_FAILURE;
	}
	return 0;
}

char* changeToChar(string directory) {
	char dest[10000];
	strncpy_s(dest, directory.c_str(), sizeof(dest));
	return dest;
}

//Reading CSV file
vector<vector<string>> readCSV(string path) {

	ifstream file;
	file.open(changeToChar(path));
	string temp;
	vector<vector<string>> parse;

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
			while (getline(ss, token, ','))
			{
				csvColumn.push_back(token);
			}
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
	return parse;
}

void putRanks(scoreTable2 &fused, multimap<double, scoreTable2::iterator> &fuseSort) {
	int ct = 1;
	for (auto it = fuseSort.begin(); it != fuseSort.end(); it++) {
		auto select = it->second;
		if (select != fused.end()) {
			auto name = select->first.first;
			int score = select->first.second;
			fused.erase(select);
			fused.insert(make_pair(make_pair(name,score),ct++));
		}

	}
}


vector<scoreTable2> setTable(vector < vector<string>> &parse) {
	scoreTable2 sift, cor, emd;
	vector<scoreTable2> temp;

	//To set initial Ranks
	multimap<double, scoreTable2::iterator> rankSortSift, rankSortCor, rankSortEmd;

	for (auto i = parse.begin(); i != parse.end(); i++) {
		auto row = (*i).begin();
		string name = *(row);
		if(name!=""){

		//Getting Values
		double siftsc = stof((*(row+1)));
		double corsc = stof(*((*i).begin()+2));
		double emdsc = stof(*((*i).begin()+3));
		auto getSift = sift.insert(make_pair(make_pair(name,siftsc),0));
		auto getCor = cor.insert(make_pair(make_pair(name, corsc), 0));
		auto getEmd = emd.insert(make_pair(make_pair(name, emdsc), 0));

		//Inserting in sorting maps
		rankSortSift.insert(make_pair(siftsc, getSift.first));
		rankSortCor.insert(make_pair(corsc,getCor.first));
		rankSortEmd.insert(make_pair(emdsc, getEmd.first));
		}
	}

	//Putting ranks
	putRanks(sift, rankSortSift);
	putRanks(cor, rankSortCor);
	putRanks(emd, rankSortEmd);

	//Making Buffer
	temp.push_back(sift);
	temp.push_back(cor);
	temp.push_back(emd);
	return temp;
}


int main(void) {
	
	int x;
	cout << "Press accordingly for the following "<<endl;
	cout << "Press 1 : To sort images according to names." << endl;
	cout << "Press 2 : To generate a random Fusion Table." << endl;
	cout << "Press 3 : To Get original fusion ranks into a CSV file." << endl;
	cin >> x;

	//Code for Above functionalities.
	vector<string> csvList;
	string source = "../../../ScoreBoard/";
	string destination = "../../../Output_Fused_Rank/";



	switch (x) {
	case 1:
		sortImages();
		break;

	case 2:
		fusionAlgoRandom();
		break;

	case 3:
		goto setRank;
		break;

	default:
		exit(0);
	}

	setRank:
	//Here We make all the codes
	vector<vector<string>> parse;



	getScoreList(csvList);
	//Iterating through each CSV FIle
	for (auto i = csvList.begin(); i != csvList.end(); i++) {

		string fileName = *i;

		//Creating Directory names
		(*i).erase((*i).end()-4, (*i).end()); 
		string directory = destination + *i;
		cout << "Making Directory with name at " << directory << endl;
		_mkdir(changeToChar(directory));

		//Reading CSV file
		parse=readCSV(source + fileName);
		auto scoreBuffer=setTable(parse);
		printBuffer(scoreBuffer);
		

		break;

	}
	



	return 0;
}
