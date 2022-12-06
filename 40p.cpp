#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

map<ll,ll> userratingcount;

vector<pair<ll,ll>> output;

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
    }

    for(auto i : userratingcount){
        cout << i.first << ' ' << i.second << endl;
        output.push_back({i.second,i.first});
    }

    sort(output.rbegin(), output.rend());
    
    for(int i = 0;i<min(10,(int)output.size());i++){
        cout << output[i].second << ' ' << output[i].first << endl;
    }

}
