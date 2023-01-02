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

#include "predict.h"

using namespace std;

typedef long long ll;

#ifndef TRAIN_FILE
#define TRAIN_FILE "./train.csv" 
#endif
#ifndef TEST_FILE
#define TEST_FILE "./test.csv"
#endif

#ifdef TEST
const int testn = 10005;
#else
const int testn = 5005;
#endif

vector<pair<int,int>> testcases(testn);

int main(){
    ios_base::sync_with_stdio(false);cin.tie(nullptr);
    FILE * trainfile = fopen(TRAIN_FILE,"r");

    ll userid,itemid;
    double rating;
    char asd[1231];
    fscanf(trainfile,"%s",asd);
    while(fscanf(trainfile, "%lld,%lld,%lf",&userid,&itemid,&rating)!=EOF){
        usertomovies[userid].push_back(itemid);
        users.insert(userid);
        rates[userid][itemid] = rating;
    }
    cerr << "QQQQQ" << endl;
    fclose(trainfile);
    
    for(int u : users){
        auto be = usertomovies[u].begin();
        auto en = usertomovies[u].end();
        sort(be,en);
    }
cerr << "LLLLLL" << endl;
    FILE* testfile = fopen(TEST_FILE,"r");

    int n = 0;
    double rmse = 0;
    FILE* submission = fopen("./submission.csv","w");



#ifdef SUBMISSION
    int id;
    fprintf(submission,"ID,Predicted\n");
    fscanf(testfile,"%s",asd);
    while(fscanf(testfile, "%d,%lld,%lld",&id,&userid,&itemid)!=EOF){
        testcases[n].first = userid;
        testcases[n].second = itemid;
        n++;
    }
    cerr << "KKKKKK"<<endl;
    cerr << testcases.size() << endl;
    int haha = 0;
    for(auto &t : testcases){
        if(!samemovies[t.first].empty())
            continue;
        for(int u : users){
            findsamemovies(samemovies[t.first][u],u,t.first);
            //auto be = samemovies[t.first][u].begin();
            //auto en = samemovies[t.first][u].end();
            //sort(be,en);
        }
        if(haha%1000 == 0)
            cerr << haha << endl;
        haha++;
    }

    int i=0;
    for(auto &t : testcases){
        userid = t.first;
        itemid = t.second;
        double foundrate = pearsonsimpredict(userid,itemid);
        rmse += (foundrate - rating) * (foundrate - rating);
        fprintf(submission,"%d,%lf\n",i,foundrate);
        i++;
        if(i/100 - (i-1)/100 != 0)
            cerr << i << endl;
    }
    cerr << n << endl;
    rmse /= n;
    rmse = sqrt(rmse);

    cout << "RMSE: " << rmse << endl;
     
    fclose(testfile);
#endif
#ifdef TEST
    fprintf(submission,"ID,Predicted\n");
    fscanf(testfile,"%s",asd);
    vector<int> trueratings;
    for(int j=0;fscanf(testfile, "%lld,%lld,%lf",&userid,&itemid,&rating)!=EOF;j++){
        testcases[j].first = userid;
        testcases[j].second = itemid;
        trueratings.push_back(rating);
    }
    cerr << "KKKKKK"<<endl;
    cerr << testcases.size() << endl;
    int haha = 0;
    for(auto &t : testcases){
        if(!samemovies[t.first].empty())
            continue;
        for(int u : users){
            findsamemovies(samemovies[t.first][u],u,t.first);
            
            //auto be = samemovies[t.first][u].begin();
            //auto en = samemovies[t.first][u].end();
            //sort(be,en);
        }
        if(haha%1000 == 0)
            cerr << haha << endl;
        haha++;
        //cerr << t.first << ' ' << t.second << endl;
    }
    cerr << "JJJJJJJ" << endl;
    int i=0;
    for(auto &t : testcases){
        userid = t.first;
        itemid = t.second;
        double foundrate = pearsonsimpredict(userid,itemid);
        rating = trueratings[i];
        i++;
        rmse += (foundrate - rating) * (foundrate - rating);
        fprintf(submission,"%d,%lf\n",i-1,foundrate);
        if(i/100 - (i-1)/100 != 0)
            cerr << i << endl;
    }
    cerr << n << endl;
    rmse /= n;
    rmse = sqrt(rmse);

    cout << "RMSE: " << rmse << endl;
     
    fclose(testfile);
#endif
}

