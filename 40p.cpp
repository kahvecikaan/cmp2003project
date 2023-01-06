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
    
    cout << "User\tRatings" << endl;
    for(int i = 0;i<min(10,(int)useroutput.size());i++){
        cout << useroutput[i].second << '\t' << useroutput[i].first << endl;
    }
    cout << endl;

    cout << "Movie\tRatings" << endl;
    for(int i = 0;i<min(10,(int)movieoutput.size());i++){
        cout << movieoutput[i].second << '\t' << movieoutput[i].first << endl;
    }
}
