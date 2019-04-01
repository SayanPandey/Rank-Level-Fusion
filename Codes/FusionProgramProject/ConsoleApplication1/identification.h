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
					cout << name <<" has occured with same rank more than once."<<endl;
				}
			}
		}

		//Printing the iden
		
		
	}
	IdenMatrix  idnG = iden;
	
}