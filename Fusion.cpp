#include<bits/stdc++.h>
#include<conio.h>
using namespace std;
typedef map<pair<char,double>,int> scoreTable;
typedef map<pair<char,double>,pair<int,int>> fusedTable;

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
    multimap <double,char> fuseSort;
    double score=INT_MAX;
    int Rank=INT_MAX;
    for(auto i=0;i<pCount;i++){
        pair<char,double> pr;
            for(auto j=0;j<matcher;j++){
                auto mp=next(buffer[j].begin(),i);
                pr=mp->first;
                if(pr.second<score) score=pr.second;
                if(mp->second<Rank) Rank=mp->second;
            }
        fuseSort.insert(make_pair(score,pr.first));
        fused.insert(make_pair(make_pair(pr.first,score),make_pair(Rank,-1)));
        score=INT_MAX;
        Rank=INT_MAX;
    }

    int ct=1;
    for(auto it=fuseSort.begin();it!=fuseSort.end();it++){
        auto select=fused.find(make_pair(it->second,it->first));
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
    multimap <double,char> fuseSort;
    double score=0;
    int Rank=0;
    for(auto i=0;i<pCount;i++){
        pair<char,double> pr;
            for(auto j=0;j<matcher;j++){
                auto mp=next(buffer[j].begin(),i);
                pr=mp->first;
                score+=pr.second;
                Rank+=mp->second;
            }
        fuseSort.insert(make_pair(score,pr.first));
        fused.insert(make_pair(make_pair(pr.first,score),make_pair(Rank,-1)));
        score=0;
        Rank=0;
    }

    int ct=1;
    for(auto it=fuseSort.begin();it!=fuseSort.end();it++){
        auto select=fused.find(make_pair(it->second,it->first));
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
fusedTable weightedBordaRank(vector<scoreTable> &buffer,int pCount,int matcher,vector<double> bordaWeights){
    fusedTable fused;
    multimap <double,char> fuseSort;
    double score=0;
    double Rank=0;
    for(auto i=0;i<pCount;i++){
        pair<char,double> pr;
            for(auto j=0;j<matcher;j++){
                auto mp=next(buffer[j].begin(),i);
                pr=mp->first;
                score+=pr.second*bordaWeights[j];
                Rank+=((double)mp->second)*bordaWeights[j]+0.1;
            }
        fuseSort.insert(make_pair(score,pr.first));
        fused.insert(make_pair(make_pair(pr.first,score),make_pair(Rank,-1)));
        score=0;
        Rank=0;
    }

    int ct=1;
    for(auto it=fuseSort.begin();it!=fuseSort.end();it++){
        auto select=fused.find(make_pair(it->second,it->first));
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
    fusedTable weightedbordarank=weightedBordaRank(buffer,pCount,matcher,bordaWeights);
    printFused(" Wighted Borda Count Rank",weightedbordarank);

return 0;
}
