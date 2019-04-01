// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include<iostream>
#include<map>
#include<vector>
#include<iomanip>
#include<string>
#include <sstream>
#include <time.h>
#include<fstream>


#include "FusionAlgo.h"
#include "FileSort.h"
#include "dirent.h"
#include "Time.h"

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

//Write into CSV File
void write(string destination,scoreTable2 scoretable,string title,string head){
	ofstream file;
	file.open(changeToChar(destination+"/"+title+".csv"));
	file << "Name,"<<title<<","<< head << endl;
	file << ",," << endl; file << ",," << endl;

	//Placing the ranks
	for (auto i = scoretable.begin(); i != scoretable.end(); i++) {
		file << i->first.first << "," << i->first.second << "," << i->second << endl;
	}
}

//Borda Count Method
scoreTable2 getBordaCountRank(vector<scoreTable2> &buffer, int pCount, int matcher) {
	scoreTable2 fused;
	multimap <int, scoreTable2::iterator> fuseSort;
	double score = 0;
	int Ranksum = 0;
	for (auto i = 0; i < pCount; i++) {
		pair<string, double> pr;
		scoreTable2::iterator mp;
		for (auto j = 0; j < matcher; j++) {
			mp = next(buffer[j].begin(), i);
			pr = mp->first;
			score += pr.second;
			Ranksum += mp->second;
		}

		//Return type is a Pair<iterator,boolean(true if inserted)>.
		auto fusedIterator = fused.insert(make_pair(make_pair(pr.first, Ranksum),-1));
		fuseSort.insert(make_pair(Ranksum, fusedIterator.first));
		score = 0;
		Ranksum = 0;
	}

	int ct = 1;
	for (auto it = fuseSort.begin(); it != fuseSort.end(); it++) {
		auto select = it->second;
		if (select != fused.end()) {
			string name = select->first.first;
			int Ranksum = select->first.second;
			fused.erase(select);
			fused.insert(make_pair(make_pair(name,Ranksum), ct++));
		}

	}
	return fused;
}

//Highest rank function
scoreTable2 getHighestRank(vector<scoreTable2> &buffer, int pCount, int matcher) {
	scoreTable2 fused;
	multimap <int, scoreTable2::iterator> fuseSort;
	double highRank = INT_MAX;
	int Rank = INT_MAX;
	for (auto i = 0; i < pCount; i++) {
		pair<string, double> pr;
		scoreTable2::iterator mp;
		for (auto j = 0; j < matcher; j++) {
			mp = next(buffer[j].begin(), i);
			pr = mp->first;
			if (mp->second < highRank) highRank = mp->second;
		}

		//Return type is a Pair<iterator,boolean(true if inserted)>.
		auto fusedIterator = fused.insert(make_pair(make_pair(pr.first, highRank), -1));
		fuseSort.insert(make_pair(highRank, fusedIterator.first));
		highRank = INT_MAX;
		Rank = INT_MAX;
	}

	int ct = 1;
	for (auto it = fuseSort.begin(); it != fuseSort.end(); it++) {
		auto select = it->second;
		if (select != fused.end()) {
			auto pr1 = select->first;
			int highRank = it->first;
			fused.erase(select);
			fused.insert(make_pair(make_pair(pr1.first, highRank), ct++));
		}

	}
	return fused;
}

//Put Ranks
void putRanks(scoreTable2 &fused, multimap<double, scoreTable2::iterator> &fuseSort) {
	int ct = 1;
	for (auto it = fuseSort.begin(); it != fuseSort.end(); it++) {
		auto select = it->second;
		if (select != fused.end()) {
			auto name = select->first.first;
			double score = select->first.second;
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
	cout << "Press 3 : To Get original fusion ranks into a CSV file by Borda CountMethod." << endl;
	cout << "Press 4 : To Get original fusion ranks into a CSV file by Highest Rank Method." << endl;
	cout << "Press 5 : To Get CPU exection time data and output it to a CSV file." << endl;
	cout << "Press 6 : To Get Ideentification ranks from the fused tables to a CSV file." << endl;
	cin >> x;

	//Code for Above functionalities.
	vector<string> csvList;
	string source = "../../../ScoreBoard/";
	string destination = "../../../Output_Fused_Rank/";



	switch (x) {
	case 1:
		sortImages();
		return 0;

	case 2:
		fusionAlgoRandom();
		return 0;

	case 3:
		goto setRank;
		break;

	case 4:
		goto setRank;
		break;

	case 5:
		writeAverageTime();
		return 0;

	default:
		exit(0);
	}

	setRank:
	//Here We make all the codes
	vector<vector<string>> parse;

	//To store time;
	map<string, double> timeTable;

	int personCount=1;
	getScoreList(csvList);
	//Iterating through each CSV FIle
	for (auto i = csvList.begin(); i != csvList.end(); i++) {

		//Calculation of execution time
		//To calculate time
		clock_t tStart = clock();

		cout << "Please Wait" << endl;
		string fileName = *i;

		//Creating Directory names
		(*i).erase((*i).end()-4, (*i).end()); 
		string directory = destination + *i;
		cout << "Making Directory with name at " << directory << endl;
		_mkdir(changeToChar(directory));

		//Reading CSV file
		parse=readCSV(source + fileName);
		auto scoreBuffer=setTable(parse);
		//printBuffer(scoreBuffer);

		
		write(directory,*(scoreBuffer.begin()),"Scores","Sift Ranks");
		write(directory, *(scoreBuffer.begin()+1), "Scores", "Corelation Ranks");
		write(directory, *(scoreBuffer.begin()+2), "Scores", "EMD Ranks");


		scoreTable2 fused;
		if (x == 3) {
			//Writing the Borda Count fused Ranks
			fused = getBordaCountRank(scoreBuffer, (*scoreBuffer.begin()).size(), scoreBuffer.size());
			write(directory, fused, "Borda Fused Rank", "Fused Ranks");
			cout << "Fused Rank generation for " << fileName << " done" << endl;
		}
		else if(x==4) {
			fused = getHighestRank(scoreBuffer, (*scoreBuffer.begin()).size(), scoreBuffer.size());
			write(directory, fused, "Highest Rank", "Fused Ranks");
			cout << "Fused Rank generation for " << fileName << " done" << endl;
		}
		
		//Time Taken
		double timeTaken=(double)(clock() - tStart) / CLOCKS_PER_SEC;
		timeTable.insert(make_pair(fileName, timeTaken));

		//Calling write every time just to ensure time is generated even if the process is haulted
		writeTine(timeTable, "../../../CPUTimes", "visualStudioTime");
		cout << personCount++ << " out of " << (*scoreBuffer.begin()).size() << " done" << endl;

	}
	//To end Ranking
	return 0;

	return 0;
}
