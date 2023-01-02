#ifndef PREDICT_H
#define PREDICT_H

#include <unordered_map>
#include <set>
#include <vector>

extern const int max_users;

extern std::vector<std::set<long long>> usertomovies;
extern std::vector<std::unordered_map<long long,double>> rates;
extern std::set<long long> users;

void findsamemovies(std::vector<int>& samemovies, int unknownid, int knownid);

double cossim(int unknownid,int movieid);

double pearsonsimpredict(int unknownid, int movieid);

#endif
