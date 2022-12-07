#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

typedef long long ll;

std::unordered_map<ll, ll> user_rating_count;
std::unordered_map<ll , ll>movie_rating_count;
std::vector<std::pair<ll, ll>>user_output, movie_output;
int main() {
    std::ifstream infile;
    infile.open("./train.csv");
    std::string line;
    while(getline(infile, line)) {
        for(auto &i: line) {
            if(i == ',') {
                i = ' ';
            }
        }
        ll user_id, item_id;
        double rating;
        std::istringstream(line) >> user_id >> item_id >> rating;
        user_rating_count[user_id]++;
        movie_rating_count[item_id]++;
    }

    for(auto i : user_rating_count) {
        // std::cout << i.first << ' ' << i.second << std::endl;
        user_output.push_back({i.second, i.first});
    }

    for(auto i: movie_rating_count) {
        movie_output.push_back({i.second, i.first});
    }

    std::sort(user_output.rbegin(), user_output.rend());
    std::sort(movie_output.rbegin(), movie_output.rend());

    for(int i = 0; i<std::min(10, (int)user_output.size()); i++) {
        std::cout << user_output[i].second << ' ' << user_output[i].first << std::endl;
    }

    std::cout << std::endl;

    for(int i = 0; i<std::min(10, (int)movie_output.size()); i++) {
        std::cout << movie_output[i].second << ' ' << movie_output[i].first << std::endl;
    }
    return 0;
}
