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

    FILE* test = fopen("./test.csv","r");
    FILE *Ttest = fopen("./Ttest.csv","w");
    //fscanf(test,"%s",asd);
    //fprintf(Ttest,"%s\n",asd);

    int id;
    double dds;
    while(fscanf(test,"%d,%d,%lf",&id,&user,&dds)!=EOF){
        fprintf(Ttest,"%d,%d,%lf\n",user,id,dds);
    } 
    fclose(Ttest);
    fclose(Ttrain);
}
