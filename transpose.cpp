#include <iostream>

using namespace std;

int main(){
    FILE* train = fopen("./train.csv","r");
    FILE *Ttrain = fopen("./Ttrain.csv","w");
    char asd[1233];
    fscanf(train,"%s",asd);
    fprintf(Ttrain,"%s\n",asd);

    int user,item;
    double rate;
    while(fscanf(train,"%d,%d,%lf",&user,&item,&rate)!=EOF){
        fprintf(Ttrain,"%d,%d,%lf\n",item,user,rate);
    }  
    fclose(train);
    fclose(Ttrain);
    FILE* test = fopen("./test.csv","r");
    FILE *Ttest = fopen("./Ttest.csv","w");
    //fscanf(test,"%s",asd);
    //fprintf(Ttest,"%s\n",asd);

    int id;
    
    fscanf(test,"%s",asd);
    fprintf(Ttest,"%s\n",asd);
    while(fscanf(test,"%d,%d,%d",&id,&user,&item)!=EOF){
        fprintf(Ttest,"%d,%d,%d\n",id,item,user);
    } 
    fclose(test);
    fclose(Ttest);
}
