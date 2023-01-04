submission:
	g++ -O2 -o a -std=c++17 -Wall -Wextra -Wshadow  main.cpp predict.cpp -DTRAIN_FILE="\"./train.csv\"" -DTEST_FILE="\"./test.csv\"" -DSUBMISSION_FILE="\"./submission.csv\"" -DSUBMISSION

test:
	g++ -O2 -o a -std=c++17 -Wall -Wextra -Wshadow  main.cpp predict.cpp -DTRAIN_FILE="\"./trainfromtrain.csv\"" -DTEST_FILE="\"./testfromtrain.csv\"" -DSUBMISSION_FILE="\"./submission.csv\"" -DTEST

Tsubmission:
	g++ -O2 -o a -std=c++17 -Wall -Wextra -Wshadow  main.cpp predict.cpp -DTRAIN_FILE="\"./Ttrain.csv\"" -DTEST_FILE="\"./Ttest.csv\"" -DSUBMISSION_FILE="\"./Tsubmission.csv\"" -DSUBMISSION

Ttest:
	g++ -O2 -o a -std=c++17 -Wall -Wextra -Wshadow  main.cpp predict.cpp -DTRAIN_FILE="\"./Ttrainfromtrain.csv\"" -DTEST_FILE="\"./Ttestfromtrain.csv\"" -DSUBMISSION_FILE="\"./Tsubmission.csv\"" -DTEST


