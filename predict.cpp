#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

#include "predict.h"

using namespace std;
typedef long long ll;

const int max_users = 40000;

vector<vector<int>> usertomovies(max_users);
vector<unordered_map<int,double>> rates(max_users);
vector<unordered_map<int,vector<int>>> samemovies(max_users);
double movieratesum[max_users];//max_movies < max_users
int movieratecount[max_users];
double userratesum[max_users];//max_movies < max_users
int userratecount[max_users];
set<int> users;

void findsamemovies(vector<int>& _samemovies, int unknownid, int knownid){
    vector<int>& unknownmovies = usertomovies[unknownid];
    vector<int>& knownmovies = usertomovies[knownid];

    vector<int>::iterator unkit = unknownmovies.begin();
    vector<int>::iterator knit = knownmovies.begin();
    while(unkit != unknownmovies.end() && knit != knownmovies.end()){
        if(*unkit == *knit){
            _samemovies.push_back(*unkit);
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
        if(!binary_search(usertomovies[user].begin(),usertomovies[user].end(),movieid))
            continue;
         
        //vector<int> samemovies;
        //findsamemovies(samemovies,unknownid,user);
        if(samemovies[unknownid][user].size() < 3) // pass same movie amount lower than 5
            continue;
        double upside = 0;
        double adownside=0,bdownside = 0;

        for(int movie : samemovies[unknownid][user]){
            double knrate = rates[user][movie];
            double unrate = rates[unknownid][movie];
            upside += knrate * unrate; 
            adownside += knrate*knrate;
            bdownside += unrate*unrate;
        }
        cossims.emplace(upside/(sqrt(adownside) * sqrt(bdownside)),user);
    }
    double ust = 0, alt = 0;
    int i=0; 
    for(auto it=cossims.rbegin();it!=cossims.rend();i++,it++){
        double w = it->first;
        int u = it->second;
        if(isnan(w))
            continue;
        if(isnan(rates[u][movieid]))
            cerr << "BBBBBBBB" << endl;
        ust += (rates[u][movieid] - (userratesum[u]/userratecount[u])) * w;
        alt += abs(w);
        //cerr << alt << endl;
        if(isnan(userratesum[u]/userratecount[u])){
            cerr << u << ' ' <<  userratesum[u]<< ' ' << userratecount[u] << ' '  << "BAAAAAA" << endl;
        }
    }
    //ret /= min(100,(int)cossims.size());
    //return ret;
    if(isnan(ust/alt))
        cerr << ust << ' ' << alt << ' '  << "AAAAAAAA" << endl;
    if(ust == 0){
        double ret = 0;
        for(auto asda : rates[unknownid]){
            ret += asda.second;
        }
        return ret/rates[unknownid].size();
    }
    //cerr << ust/alt + userratesum[unknownid]/userratecount[unknownid]<< endl;
    return ust/alt + userratesum[unknownid]/userratecount[unknownid];
}

double adjustedcossim(int unknownid, int movieid){
    set<pair<double,int>> adjcossims;
    for(int user : users){
        if(user == unknownid)
            continue;
        if(!binary_search(usertomovies[user].begin(),usertomovies[user].end(),movieid))
            continue;
        
        vector<int> &_samemovies = samemovies[unknownid][user];
        //findsamemovies(samemovies,unknownid,user);
       
        int n = _samemovies.size();
        
        if(n<5)
            continue;

        double up[3] = {};
        double down[4] = {};
        
        for(int movie : _samemovies){
            
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

        adjcossims.emplace(result,user);
    }
    double ust = 0;
    double alt = 0;
    int i=0; 
    for(auto it=adjcossims.rbegin();/*i<10&&*/it!=adjcossims.rend();i++,it++){
        double coeff = it->first;
        int user = it->second;
        if(coeff <= 0.3)
            break;
        if(coeff+1 == 0){
            continue;
        }
        double a = (coeff) ;
        ust += a*(rates[user][movieid] - (userratesum[user] / userratecount[user]));
        alt += abs(a);
        //cerr << coeff << ' ' << user << ' ' << a << endl;
    } 
    if(isnan(ust/alt + userratesum[unknownid] / userratecount[unknownid]))
        cerr << ust << ' ' << alt << " AAAAAA" << endl;
    return ust/alt + userratesum[unknownid] / userratecount[unknownid];
}

double pearsonsim(int unknownid, int movieid){
    set<pair<double,int>> pearsonsims;
    for(int user : users){
        if(user == unknownid)
            continue;
        if(!binary_search(usertomovies[user].begin(),usertomovies[user].end(),movieid))
            continue;
        
        vector<int> &_samemovies = samemovies[unknownid][user];
        int n = _samemovies.size();
        
        if(n<3)
            continue;

        double up = 0;;
        double down[2] = {};
        
        for(int movie : _samemovies){
             double avg = (movieratesum[movie]/movieratecount[movie]);
             double a = rates[unknownid][movie] - avg;
             double b = rates[user][movie] - avg;
             up += a - b;
             down[0] += a * a;
             down[1] += b * b;
        }
        double result = up / (sqrt(down[0]) * sqrt(down[1]));
        
        if(isnan(result))
            continue;

        pearsonsims.emplace(result,user);
    }
    double ust = 0;
    double alt = 0;
    int i=0; 
    for(auto it=pearsonsims.rbegin();/*i<5&&*/it!=pearsonsims.rend();i++,it++){
        double coeff = it->first;
        int user = it->second;
        //if(coeff <= 0.3)
            //break;
        if(coeff+1 == 0){
            continue;
        }
        double a = (coeff+1)/2.;//((coeff+1)/2. * (coeff+1)/2.) ;
        ust += a*rates[user][movieid];
        alt += a;
        //cerr << coeff << ' ' << user << ' ' << a << endl;
    } 
    if(isnan(ust/alt))
        cerr << ust << ' ' << alt << " AAAAAA" << endl;
    return ust/alt;
}
