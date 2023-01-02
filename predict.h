#ifndef PREDICT_H
#define PREDICT_H

#include <unordered_map>
#include <set>
#include <vector>

extern const int max_users;

extern std::vector<std::vector<int>> usertomovies;
extern std::vector<std::unordered_map<int,double>> rates;
extern std::vector<std::unordered_map<int,std::vector<int>>> samemovies;
extern std::set<int> users;

void findsamemovies(std::vector<int>& samemovies, int unknownid, int knownid);

double cossim(int unknownid,int movieid);

double pearsonsimpredict(int unknownid, int movieid);

#endif
