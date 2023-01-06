# cmp2003project
Term project of CMP2003

You need to get train.csv and test.csv from https://www.kaggle.com/competitions/cmp2003-rating-prediction/data. 

## First task
```
g++ -std=c++17 -o a 40p.cpp
./a
```
## Second task

### Submission:

Generate Ttrain.csv and Ttest.csv:
```
g++ -std=c++17 -o a transpose.cpp
./a
```
Then:

```
make submission
./a
```
This will generate submission.csv, we need to generate Tsubmission.csv as well:
```
make Tsubmission
./a
```
With both CSVs generated, finally we need to merge them:
```
g++ -std=c++17 -o a mixusermovie.cpp
./a
```
And this generates Msubmission.csv, which is our actual submission.

