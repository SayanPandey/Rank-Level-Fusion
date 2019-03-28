// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include<iostream>
#include<map>
#include<vector>
#include<iomanip>
#include<string>

#include "FusionAlgo.h"
#include "FileSort.h"
#include "dirent.h"

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

int main(void) {
	
	int x;
	cout << "Press accordingly for the following "<<endl;
	cout << "Press 1 : To sort images according to names." << endl;
	cout << "Press 2 : To generate a random Fusion Table." << endl;
	cout << "Press 3 : To Get original fusion ranks into a CSV file." << endl;
	cin >> x;

	//Code for Above functionalities.
	vector<string> csvList;
	string source = "../../../ScoreBoard"/;
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
		

		break;

	}
	



	return 0;
}
