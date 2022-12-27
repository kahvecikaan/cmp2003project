#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;

unordered_map<ll,set<ll>> usertomovies;
unordered_map<ll,unordered_map<ll,double>> rates;
set<long long> users;

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
    for(auto it=cossims.rbegin();i<100&&it!=cossims.rend();i++,it++){
        ret += rates[it->second][movieid];
    }
    ret /= min(100,(int)cossims.size());
    return ret;
}
