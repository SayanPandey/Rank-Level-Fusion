#include<bits/stdc++.h>
#include<fstream>
#include<dirent.h>
using namespace std;
bool copyFile(const char *SRC, const char* DEST)
{
    std::ifstream src(SRC, std::ios::binary);
    std::ofstream dest(DEST, std::ios::binary);
    dest << src.rdbuf();
    return src && dest;
}

vector<string> tokenise(string s){
    vector<string> temp;
    string x;
    for(auto i=s.begin();i!=s.end();i++){
        if(*i!='_'){
            x.push_back(*i);
        }
        else{
            temp.push_back(x);
            x.clear();
        }

    }
    temp.push_back(x);
    return temp;
}

int main(void){
    DIR *dir;
    map <string,vector<string>> store;
    pair<map <string,vector<string>> ::iterator,bool> save;
    vector<string> ctk;

    //Place source folder and destination folder "WITH FORWARD SLASH / "
    string source="C:/Users/Sayan/Desktop/Final Project/Assets/LFWCROP/faces";
    string destination="C:/Users/Sayan/Desktop/Final Project/Assets/SortedImages/";
    char src[10000];
    strncpy(src, source.c_str(), sizeof(src));



    struct dirent *ent;
    if ((dir = opendir (src)) != NULL) {
      //print all the files and directories within directory
      while ((ent = readdir (dir)) != NULL) {


            vector<string> x = tokenise(ent->d_name);
            string folder,imageID;
            for(auto i=x.begin();i!=x.end();i++){
                if(*i!="." && *i!="..")
                    if(i!=prev(x.end(),1)){
                        folder+=*i+"_";
                    }
                    else{
                        imageID=*i;
                    }
            }

            int ct=1;
            if(folder!=""){
                auto select=store.find(folder);
                if(select!=store.end()){
                    select->second.push_back(imageID);

                }
                else{
                    ctk.push_back(imageID);
                    save=store.insert(make_pair(folder,ctk));
                }
            }

            ctk.clear();
            folder.clear();
            imageID.clear();
            x.clear();
      }
      closedir (dir);
    }
    else {
      // could not open directory
      perror ("");
      return EXIT_FAILURE;
    }

    int ct=1,total=0;
     for(auto i=store.begin();i!=store.end();i++){
         if(i->second.size()>1){
            cout<<ct++<<" "<<i->first<<" "<<endl;

            string temp =destination +i->first;
            char directory[10000];
            strncpy(directory, temp.c_str(), sizeof(directory));
            //cout<<tab2<<endl;
            mkdir(directory);

            for(auto k = i->second.begin();k != i->second.end();k++){
                char charDest[10000],charSrc[10000];
                string destination2=temp+"/"+i->first+*k;
                string source2=source+"/"+i->first+*k;

                strncpy(charDest, destination2.c_str(), sizeof(charDest));
                strncpy(charSrc, source2.c_str(), sizeof(charSrc));

                cout<<"  Source: "<<source2<<endl;
                cout<<"  Destination:   "<<destination2<<endl;

                copyFile(charSrc,charDest);
                destination2.clear();
                source2.clear();
            }
            temp.clear();
         }
         else{
            total++;
         }
      }
      cout<<"\nNo of unique people "<<total+ct<<endl;



return 0;
}
