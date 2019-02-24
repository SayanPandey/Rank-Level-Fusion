#include<bits/stdc++.h>
#include<conio.h>
using namespace std;
typedef map<pair<char,double>,int> scoreTable;
typedef map<pair<char,double>,pair<int,int>> fusedTable;
typedef map<pair<char,double>,pair<double,int>> fusedTableFloat;

//Random float generation
double doubleRand() {
  return double(rand()) / (double(RAND_MAX) + 1.0)*10;
}

//Setting correct ranks
void setRanks(scoreTable &scoreBoard,multimap<double,char> &rankSort){
    int ct=1;
    for(auto i=rankSort.begin();i!=rankSort.end();i++){
        auto it=scoreBoard.find(make_pair(i->second,i->first));
        if(it!=scoreBoard.end()){
            it->second=ct++;
        }
        else{
            it->second=-1;
        }
    }
    rankSort.clear();
}

//Prepare Buffers
vector<scoreTable> generateBuffer(int pCount,int matchers){

    //Map to store the individual scores of the person.
     scoreTable scoreBoard;

    //Vector to store all score boards.
    vector<scoreTable> buffer;

    //Set to sort values
    multimap<double,char> rankSort;

    char c='A';
    while(matchers--){

        //Setting values
        for(auto i=0;i<pCount;i++){
            double d = doubleRand();
            scoreBoard.insert(make_pair(make_pair(c,d),0));
            rankSort.insert(make_pair(d,c++));
        }

        //Sorted Rank list
        setRanks(scoreBoard,rankSort);

        //Calculating ranks;
        buffer.push_back(scoreBoard);
        scoreBoard.clear();
        c='A';

    }
    return buffer;
}

//Print Buffer
void printBuffer(vector<scoreTable> &buffer){
    int matcher=1;
    //Loop for every matcher.
    vector<scoreTable>::iterator i;
    for(i=buffer.begin();i!=buffer.end();i++){

        cout<<"\n Score Board for Matcher : "<<matcher++<<endl;
        cout<<"\n Name of the Person"<<setw(12)<<"Score"<<setw(12)<<"Rank\n"<<endl;

        for(auto scoreBoard=(*i).begin();scoreBoard!=(*i).end();scoreBoard++){
            auto personScore=scoreBoard->first;
            auto Rank=scoreBoard->second;
            cout<<" "<<personScore.first<<setw(30)<<personScore.second<<setw(10)<<Rank<<endl;
        }
    }
}

//Highest rank function
fusedTable highestRank(vector<scoreTable> &buffer,int pCount,int matcher){
    fusedTable fused;
    multimap <int,fusedTable::iterator> fuseSort;
    double score=INT_MAX;
    int Rank=INT_MAX;
    for(auto i=0;i<pCount;i++){
        pair<char,double> pr;
        scoreTable::iterator mp;
            for(auto j=0;j<matcher;j++){
                mp=next(buffer[j].begin(),i);
                pr=mp->first;
                if(pr.second<score) score=pr.second;
                if(mp->second<Rank) Rank=mp->second;
            }

        //Return type is a Pair<iterator,boolean(true if inserted)>.
        auto fusedIterator=fused.insert(make_pair(make_pair(pr.first,score),make_pair(Rank,-1)));
        fuseSort.insert(make_pair(Rank,fusedIterator.first));
        score=INT_MAX;
        Rank=INT_MAX;
    }

    int ct=1;
    for(auto it=fuseSort.begin();it!=fuseSort.end();it++){
        auto select=it->second;
        if(select!=fused.end()){
            auto pr1=select->first;
            int Rank=select->second.first;
            fused.erase(select);
            fused.insert(make_pair(pr1,make_pair(Rank,ct++)));
        }

    }
    return fused;
}

//Borda Count method
fusedTable bordaCountRank(vector<scoreTable> &buffer,int pCount,int matcher){
    fusedTable fused;
    multimap <int,fusedTable::iterator> fuseSort;
    double score=0;
    int Rank=0;
    for(auto i=0;i<pCount;i++){
        pair<char,double> pr;
        scoreTable::iterator mp;
            for(auto j=0;j<matcher;j++){
                mp=next(buffer[j].begin(),i);
                pr=mp->first;
                score+=pr.second;
                Rank+=mp->second;
            }

        //Return type is a Pair<iterator,boolean(true if inserted)>.
        auto fusedIterator=fused.insert(make_pair(make_pair(pr.first,score),make_pair(Rank,-1)));
        fuseSort.insert(make_pair(Rank,fusedIterator.first));
        score=0;
        Rank=0;
    }

    int ct=1;
    for(auto it=fuseSort.begin();it!=fuseSort.end();it++){
        auto select=it->second;
        if(select!=fused.end()){
            auto pr1=select->first;
            int Rank=select->second.first;
            fused.erase(select);
            fused.insert(make_pair(pr1,make_pair(Rank,ct++)));
        }

    }
    return fused;
}

//Weighted Borda Count method
fusedTableFloat weightedBordaRank(vector<scoreTable> &buffer,int pCount,int matcher,vector<double> bordaWeights){
    fusedTableFloat fused;
    multimap <int,fusedTableFloat::iterator> fuseSort;
    double score=0;
    double Rank=0;
    for(auto i=0;i<pCount;i++){
        pair<char,double> pr;
        scoreTable::iterator mp;
            for(auto j=0;j<matcher;j++){
                mp=next(buffer[j].begin(),i);
                pr=mp->first;
                score+=pr.second*bordaWeights[j];
                Rank+=mp->second*bordaWeights[j];
            }

        //Return type is a Pair<iterator,boolean(true if inserted)>.
        auto fusedIterator=fused.insert(make_pair(make_pair(pr.first,score),make_pair(Rank,-1)));
        fuseSort.insert(make_pair(Rank,fusedIterator.first));
        score=0;
        Rank=0;
    }

    int ct=1;
    for(auto it=fuseSort.begin();it!=fuseSort.end();it++){
        auto select=it->second;
        if(select!=fused.end()){
            auto pr1=select->first;
            double Rank=select->second.first;
            fused.erase(select);
            fused.insert(make_pair(pr1,make_pair(Rank,ct++)));
        }

    }
    return fused;
}

//Function to print fused table
void printFused(string name,fusedTable &rankTable){

    cout<<name<<" Fused Table"<<endl;
    cout<<"\n Name of the Person"<<setw(12)<<"Score"<<setw(22)<<"Fused Rank"<<setw(22)<<"Combined Rank \n"<<endl;

    for(auto i=rankTable.begin();i!=rankTable.end();i++){
        auto pr1=i->first;
        auto pr2=i->second;
        cout<<" "<<pr1.first<<setw(30)<<pr1.second<<setw(18)<<pr2.first<<setw(20)<<pr2.second<<endl;
    }

}

//Function to print fused table
void printFusedFloat(string name,fusedTableFloat &rankTable){

    cout<<name<<" Fused Table"<<endl;
    cout<<"\n Name of the Person"<<setw(12)<<"Score"<<setw(22)<<"Fused Rank"<<setw(22)<<"Combined Rank \n"<<endl;

    for(auto i=rankTable.begin();i!=rankTable.end();i++){
        auto pr1=i->first;
        auto pr2=i->second;
        cout<<" "<<pr1.first<<setw(30)<<pr1.second<<setw(18)<<pr2.first<<setw(20)<<pr2.second<<endl;
    }

}

fusedTableFloat bayesFuseRank(int pCount,int matcher,vector<vector<int>>genuineProb,vector<vector<int>>imposterProb){
fusedTableFloat fused;
    multimap <int,fusedTableFloat::iterator> fuseSort;
    double score=0;
    double Rank=0;
    for(auto i=0;i<pCount;i++){
        pair<char,double> pr;
        scoreTable::iterator mp;
            for(auto j=0;j<matcher;j++){
                mp=next(buffer[j].begin(),i);
                pr=mp->first;
            }

        //Return type is a Pair<iterator,boolean(true if inserted)>.
        auto fusedIterator=fused.insert(make_pair(make_pair(pr.first,score),make_pair(Rank,-1)));
        fuseSort.insert(make_pair(Rank,fusedIterator.first));
        //score=0;
        //Rank=0;
    }

    int ct=1;
    for(auto it=fuseSort.begin();it!=fuseSort.end();it++){
        auto select=it->second;
        if(select!=fused.end()){
            auto pr1=select->first;
            double Rank=select->second.first;
            fused.erase(select);
            fused.insert(make_pair(pr1,make_pair(Rank,ct++)));
        }

    }
    return fused;
}
int main(void){

    int pCount=20,matcher=6;

    //Buffers and listing buffers.
    auto buffer=generateBuffer(pCount,matcher);
    printBuffer(buffer);

    //creating random weights;
    vector<double> bordaWeights;
    for(auto i=0;i<matcher;i++){
        bordaWeights.push_back(doubleRand()/10);
    }

    vector<vector<double>> genuineProb,imposterProb;
    //Genuine probabilities
    for(auto i=0;i<matcher;i++){
        for(auto j=0;j<pCount;j++){
            genuineProb[i][j]=doubleRand()/10;
        }
    }
    //Imposter Probabilities
    for(auto i=0;i<matcher;i++){
        for(auto j=0;j<pCount;j++){
            genuineProb[i][j]=doubleRand()/10;
        }
    }

    //Highest ranking
    cout<<"-------------------------------------------------------"<<endl;
    fusedTable highestrank=highestRank(buffer,pCount,matcher);
    printFused(" Highest Rank",highestrank);

    //Borda ranking
    cout<<"-------------------------------------------------------"<<endl;
    fusedTable bordacountrank=bordaCountRank(buffer,pCount,matcher);
    printFused(" Borda Count Rank",bordacountrank);

    //Weighted Borda ranking
    cout<<"-------------------------------------------------------"<<endl;
    fusedTableFloat weightedbordarank=weightedBordaRank(buffer,pCount,matcher,bordaWeights);
    printFusedFloat(" Wighted Borda Count Rank",weightedbordarank);

    //Bayes Fuse ranking
    cout<<"-------------------------------------------------------"<<endl;
    fusedTableFloat bayesfuserank=bayesFuseRank(pCount,matcher,genuineProb,imposterProb);
    printFusedFloat(" Bayes Fuse Count Rank",bayesfuserank);

return 0;
}
