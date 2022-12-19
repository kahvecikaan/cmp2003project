#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <ctime>
#include <cmath>

using namespace std;

typedef long long ll;

#define TRAIN_FILE "./trainfromtrain.csv" 
#define TEST_FILE "./testfromtrain.csv"

unordered_map<ll,set<ll>> usertomovies;
unordered_map<ll,unordered_map<ll,double>> rates;
set<int> users;

void findsamemovies(vector<int>& samemovies, int unknownid, int knownid){
    set<ll>& unknownmovies = usertomovies[unknownid];
    set<ll>& knownmovies = usertomovies[knownid];

    set<ll>::iterator unkit = unknownmovies.begin();
    set<ll>::iterator knit = knownmovies.begin();
    while(unkit != unknownmovies.end() && knit != knownmovies.end()){
        if(*unkit == *knit){
            samemovies.push_back(*unkit);
            ++unkit;
        }
        else if(*unkit < *knit)
            ++unkit;
        else
            ++knit;
    }
}

double cossim(int unknownid,int movieid){
    set<pair<double,int>> cossims;

    for(int user : users){
       // cerr << "SD" << user << endl;
        if(user == unknownid)
            continue;
        if(usertomovies[user].find(movieid) == usertomovies[user].end())
            continue;
        
        vector<int> samemovies;
        findsamemovies(samemovies,unknownid,user);
        
        double upside = 0;
        double adownside=0,bdownside = 0;

        for(int movie : samemovies){
            double knrate = rates[user][movie];
            double unrate = rates[unknownid][movie];
            upside += knrate * unrate; 
            adownside += knrate*knrate;
            bdownside += unrate*unrate;
        }
        cossims.emplace(upside/(sqrt(adownside) * sqrt(bdownside)),user);
    }
    double ret = 0;
    int i=0; 
    for(auto it=cossims.rbegin();i<10&&it!=cossims.rend();i++,it++){
        ret += rates[it->second][movieid];
    }
    ret /= min(10,(int)cossims.size());
    return ret;
}


int main(){
    ios_base::sync_with_stdio(false);cin.tie(nullptr);
    FILE * trainfile = fopen(TRAIN_FILE,"r");

    ll userid,itemid;
    double rating;
    char asd[1231];
    fscanf(trainfile,"%s",asd);
    while(fscanf(trainfile, "%lld,%lld,%lf",&userid,&itemid,&rating)!=EOF){
        usertomovies[userid].insert(itemid);
        users.insert(userid);
        rates[userid][itemid] = rating;
    }

    fclose(trainfile);


    FILE* testfile = fopen(TEST_FILE,"r");

    int n = 0;
    double rmse = 0;
    while(fscanf(testfile, "%lld,%lld,%lf",&userid,&itemid,&rating)!=EOF){
        double foundrate = cossim(userid,itemid);
        n++;
        rmse += (foundrate - rating) * (foundrate - rating);
        if(n/100 - (n-1)/100 != 0)
            cerr << n << endl;
    }
    cerr << n << endl;
    rmse /= n;
    rmse = sqrt(rmse);

    cout << "RMSE: " << rmse << endl;
    
    fclose(testfile);
}
