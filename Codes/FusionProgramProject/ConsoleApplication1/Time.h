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

//Reading CSV file
vector<vector<string>> readCSV2(string path, map<string, double> &valuetore, double *average) {

	ifstream file;
	file.open(changeToChar2(path));

	//Checking file 
	if (!file.is_open()) {
		cout << "Falied to open file to get CPU Times." << endl;
		exit(-1);
	}

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
			string name; double time;
			// To get return values to a map. 
			int marker = 1;
			while (getline(ss, token, ','))
			{
				csvColumn.push_back(token);
				if (marker == 1 && token!="") {
					marker = 2;
					name = token;
				}
				else if (marker == 2 && token != "") {
					marker = 1;
					time = stof(token);
					*average += time;
				}
			}
			if(*average>0)
				valuetore.insert(make_pair(name, time));
			parse.push_back(csvColumn);
			csvColumn.clear();
		}
	}

	//Print Parse
	/*for (auto i = parse.begin(); i != parse.end(); i++) {
		for (auto j = (*i).begin(); j != (*i).end(); j++) {
			cout << *j << " ";
		}
		cout << endl;
	}*/
	*average /= valuetore.size();
	return parse;
}

void writeAverageTime() {
	string matlabTimes = "../../../CPUTimes/matlabTimes.csv";
	string visualStudioTimes = "../../../CPUTimes/visualStudioTime.csv";
	double avgM = 0.0, avgV = 0.0;
	//Store for times
	map<string, double> matlabStore, visualStudioStore;
	readCSV2(matlabTimes,matlabStore,&avgM);
	readCSV2(visualStudioTimes,visualStudioStore,&avgV);

	ofstream file;
	file.open(changeToChar2("../../../CPUTimes/averageTime.csv"));
	file << "Name,Matlab Time(in s),Avg Matlab Time,VS Time(in s),Avg VS Time,Total Time(in s),Avg Total Time"<<endl;
	file << ",,,,,," << endl; file << ",,,,,," << endl;

	//Placing the ranks
	for (auto i = matlabStore.begin(), j = visualStudioStore.begin(); i != matlabStore.end(), j != visualStudioStore.end(); i++,j++) {
		file << i->first << "," << i->second << "," << avgM << ",";
		file << j->second << "," << avgV << ",";
		file << (i->second + j->second) << "," << (avgM + avgV) << endl;			
	}
}
