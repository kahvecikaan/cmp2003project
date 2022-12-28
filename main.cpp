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

#ifdef SUBMISSION
    FILE* submission = fopen("./submission.csv","w");

    int id;
    fprintf(submission,"ID,Predicted\n");
    fscanf(testfile,"%s",asd);
    while(fscanf(testfile, "%d,%lld,%lld",&id,&userid,&itemid)!=EOF){
        double foundrate = cossim(userid,itemid);
        n++;
        rmse += (foundrate - rating) * (foundrate - rating);
        fprintf(submission,"%d,%lf\n",id,foundrate);
        if(n/100 - (n-1)/100 != 0)
            cerr << n << endl;
    }
    cerr << n << endl;
    rmse /= n;
    rmse = sqrt(rmse);

    cout << "RMSE: " << rmse << endl;
     
    fclose(testfile);
#endif
#ifdef TEST
    FILE* submission = fopen("./submission.csv","w");

    fprintf(submission,"ID,Predicted\n");
    fscanf(testfile,"%s",asd);
    while(fscanf(testfile, "%lld,%lld,%lf",&userid,&itemid,&rating)!=EOF){
        double foundrate = cossim(userid,itemid);
        n++;
        rmse += (foundrate - rating) * (foundrate - rating);
        fprintf(submission,"%d,%lf\n",n-1,foundrate);
        if(n/100 - (n-1)/100 != 0)
            cerr << n << endl;
    }
    cerr << n << endl;
    rmse /= n;
    rmse = sqrt(rmse);

    cout << "RMSE: " << rmse << endl;
     
    fclose(testfile);
#endif
}

