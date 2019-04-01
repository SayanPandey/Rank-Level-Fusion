#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main() {
	// your code goes here
	map<int,map<int,int>> x;
	for(auto i=1;i<=10;i++){
		for(auto j=1;j<=10;j++){
		//auto set = x.insert(make_pair(i,i+3));
		//auto p = set.first->second;
		//p=12;
		map<int,int> p;
		p.insert(make_pair(j,i*j));
		auto set = x.insert(make_pair(i,p));
        (set.first->second).insert(make_pair(j,i*j));
        /*map<int,int> z;
		z.insert(make_pair(0,139));
        set.first->second=z;*/
		}


	}
	for(auto i=x.begin();i!=x.end();i++){
        cout<<"\nTable for "<<i->first<<endl;
		for(auto j=(i->second).begin();j!=(i->second).end();j++){
		    //j->second=14;
			cout<<i->first<<" * "<<j->first<<" = "<<j->second<<endl;
		}
	}
	return 0;
}
