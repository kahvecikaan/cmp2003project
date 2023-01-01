submission:
	g++ -O2 -o a -std=c++17 -Wall -Wextra -Wshadow  main.cpp predict.cpp -DTRAIN_FILE="\"./train.csv\"" -DTEST_FILE="\"./test.csv\"" -DSUBMISSION

test:
	g++ -O2 -o a -std=c++17 -Wall -Wextra -Wshadow  main.cpp predict.cpp -DTRAIN_FILE="\"./trainfromtrain.csv\"" -DTEST_FILE="\"./testfromtrain.csv\"" -DTEST

