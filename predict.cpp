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

double pearsonsimpredict(int unknownid, int movieid){
    set<pair<double,int>> pearsonsims;
    for(int user : users){
        if(user == unknownid)
            continue;
        if(usertomovies[user].find(movieid) == usertomovies[user].end())
            continue;
        
        vector<int> samemovies; // consider preprocessing these
        findsamemovies(samemovies,unknownid,user);
       
        int n = samemovies.size();
        
        if(n==0)
            continue;

        double up[3] = {};
        double down[4] = {};
        
        for(int movie : samemovies){
            
            double knrate = rates[user][movie];
            double unrate = rates[unknownid][movie];  
            up[0] += unrate * knrate;
            up[1] += unrate;
            up[2] += knrate;
            
            down[0] += unrate * unrate;
            down[1] += unrate;
            down[2] += knrate * knrate;
            down[3] += knrate;
            
        }
        up[0] *= n;
        down[0] *= n;
        down[1] *= down[1];
        down[2] *= n;
        down[3] *= down[3];
        
        double result = up[0] - up[1] * up[2];
        result /= sqrt(down[0] - down[1]) * sqrt(down[2] - down[3]);
        
        //cerr << result << endl;
        //if(isnan(result)){
            //cerr << unknownid << '\t' << user << endl;
            //for(int i : samemovies){
                //cerr << rates[unknownid][i] << '\t' << rates[user][i] << endl;
            //}
            //exit(0);
        //}

        if(isnan(result))
            continue;

        pearsonsims.emplace(result,user);
    }
    double ust = 0;
    double alt = 0;
    int i=0; 
    for(auto it=pearsonsims.rbegin();i<10&&it!=pearsonsims.rend();i++,it++){
        double coeff = it->first;
        int user = it->second;
        if(coeff+1 == 0){
            continue;
        }
        double a = ((coeff+1)/2. * (coeff+1)/2.) ;
        ust += a*rates[user][movieid];
        alt += a;
        //cerr << coeff << ' ' << user << ' ' << a << endl;
    }  
    return ust/alt;
}
