#include <iostream>
#include <cmath>
using namespace std;

int main(){
    FILE* sub = fopen("./submission.csv","r");
    FILE* Tsub = fopen("./Tsubmission.csv","r");
    FILE* Msub = fopen("./Msubmission.csv","w");

    char asd[1231];
    fscanf(sub,"%s",asd);
    fscanf(Tsub,"%s",asd);
    fprintf(Msub,"%s\n",asd);

    int id,Tid;
    double pre,Tpre,Mpre;
    while(fscanf(sub,"%d,%lf",&id,&pre) != EOF && fscanf(Tsub,"%d,%lf",&Tid,&Tpre) != EOF){
        if(isnan(pre) && isnan(Tpre))
            Mpre = 3;
        else if(isnan(Tpre))
            Mpre = pre;
        else if(isnan(pre))
            Mpre = Tpre;
        else
            Mpre = (pre+Tpre)/2.;
        fprintf(Msub,"%d,%lf\n",id,Mpre);
    }
    fclose(Msub);
}
