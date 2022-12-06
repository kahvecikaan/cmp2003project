#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

typedef long long ll;

unordered_map<ll,ll> userratingcount, movieratingcount;

vector<pair<ll,ll>> useroutput,movieoutput;

int main(){
    ifstream infile;
    infile.open("./train.csv");
    string s;
    infile >> s;
    while(infile >> s){
        for(int i=0;i<s.size();i++){
            if(s[i] == ','){
               s[i] = ' '; 
            }
        }
        ll userid,itemid;
        double rating;
        istringstream(s) >> userid >> itemid >> rating;
        userratingcount[userid]++;
        movieratingcount[itemid]++;
    }

    for(auto i : userratingcount){
        //cout << i.first << ' ' << i.second << endl;
        useroutput.push_back({i.second,i.first});
    }
    for(auto i : movieratingcount){
        movieoutput.push_back({i.second,i.first});
    }
    
    sort(useroutput.rbegin(), useroutput.rend());
    sort(movieoutput.rbegin(),movieoutput.rend());

    for(int i = 0;i<min(10,(int)useroutput.size());i++){
        cout << useroutput[i].second << ' ' << useroutput[i].first << endl;
    }
    cout << endl;
    for(int i = 0;i<min(10,(int)movieoutput.size());i++){
        cout << movieoutput[i].second << ' ' << movieoutput[i].first << endl;
    }
}
