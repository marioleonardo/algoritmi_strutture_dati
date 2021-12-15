#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int tStart, tEnd;
} att;

void attSel(int N, att *v);

int attSelRec(int livello, int N, att *v, int max, att **temp, int *occ, att **result);

int validate(att **temp, int n, att value);

int main(){
    att *activities;
    char s[50]="1 2 2 4 2 5 3 5 5 7 6 8";
    char *ptr;
    int N=6, i, j, readChar;

    ptr=s;
    activities=malloc(N*sizeof(att));
    for(i=0; i<N; i++){
        sscanf(ptr,"%d %d %n", &activities[i].tStart, &activities[i].tEnd, &readChar);
        ptr=ptr+readChar;
    } 
    printf("\n");

    attSel(N, activities);     
}

void attSel(int N, att *v){
    int max, tempMax, i, *occ;
    att **temp, **result;

    temp=(att**)malloc( sizeof(att*)*N);
    result=(att**)malloc(sizeof(att*)*N);
    occ=calloc(N, sizeof(int));

    max=attSelRec(0, N, v, 0, temp, occ, result);

    tempMax=max;
    i=0;
    while(tempMax>0){
        printf("(%d, %d), ", result[i]->tStart, result[i]->tEnd);
        tempMax-=(result[i]->tEnd - result[i]->tStart);
        i++;
    }

    printf("\nIlmassimo e' %d", max);
}

int attSelRec(int livello, int N, att *v, int max, att **temp, int *occ, att **result){
    int dim, i, j, end, sum;

    end=1;

    for(i=0; i<N; i++){
        if(occ[i]==0 && validate(temp, livello, (v[i]))){
            occ[i]=1;
            temp[livello]=&(v[i]);
            max=attSelRec(livello+1, N, v, max, temp, occ, result);
            occ[i]=0;
            end=0;
        }
    }

    if(end==1){
        sum=0;
        for(i=0; i<livello;i++){
            sum=sum+ (temp[i]->tEnd - temp[i]->tStart);
            
        }
        if(sum>max){
            max=sum;
            for(i=0; i<livello;i++)
                result[i]=temp[i];
        }

    }

    return max;
}

int validate(att **temp, int n, att value){
    int i, valid;

    valid=1;

    for(i=0; i<n; i++){
        if(value.tEnd>temp[i]->tStart && value.tStart<temp[i]->tEnd)
            valid=0;
    }

    return valid;

}