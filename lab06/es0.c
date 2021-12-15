#include <stdio.h>
#include <stdlib.h>

int solve(int *v, int dim);

int solveRec(int livello, int *v, int dim, int opt[8][8]);

int main(){
    int v[8]={0, 14, 22, 13, 25, 30, 11, 90};

    printf("\n%d", solve(v , 8));
}



int solve(int *v, int dim){
    int i, max;
    int opt[8][8];

    opt[1][1]=v[0];
    if(v[0]>v[1]){
        opt[2][1]=v[0];
        opt[2][2]=0;
    } else{
        opt[2][1]=0;
        opt[2][2]=v[1];
    }

    for(i=3; i<dim; i++){
        max=solveRec(i, v, dim, opt);
    }

    for(i=1; i<dim; i++){
        printf("%d ", opt[7][i]);
    }

    return max;
}

int solveRec(int livello, int *v, int dim, int opt[8][8]){
    int i, j, sum;

    i=livello;
    if(opt[livello-1][livello-1]==0){
        for(j=1; j<livello; j++){
            
            opt[i][j]=opt[i-1][j];
        }
        opt[i][livello]=v[livello];
    }
    else if (){
        for(j=1; j<livello-1; j++){
            opt[i][j]=opt[i-2][j];
            
        }
        opt[i][livello]=v[livello];
        opt[i][livello-1]=0;
    }

    sum=0;
    for(j=1; j<livello; j++){
        sum+=opt[i][j];
    }


    return sum;
}