#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int tStart, tEnd;
} att;

void attSel(int N, att *v);


int main(){
    att *activities;
    char s[50]="2 4 1 2 2 5 3 5 5 7 6 8";
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
    int max, tempMax, i, j, *occ, *opt;
    att temp, **result;

    opt=malloc(N*sizeof(int));
    result=(att**)malloc(sizeof(att*)*N);

    for(i=0; i<N-1; i++){
        for(j=0; j<N-i-1; j++){
            if(v[j].tEnd>v[j+1].tEnd){
                temp=v[j+1];
                v[j+1]=v[j];
                v[j]=temp;
            }
        }
    }

    opt[0]=(v[0].tEnd-v[0].tStart);
    result[0]=&v[0];
    for(i=1; i<N; i++){
        if(v[i].tStart>=v[i-1].tEnd){
                opt[i]=opt[i-1]+(v[i].tEnd-v[i].tStart);
                result[i]=&v[i];
        } else{
            for(j=i; j>=0 && v[i].tStart<v[j].tEnd; j--);
            
            if(opt[j]+(v[i].tEnd-v[i].tStart)>opt[i-1]){
                opt[i]=opt[j]+(v[i].tEnd-v[i].tStart);
                for(j=i; j>=0 && v[i].tStart<v[j].tEnd; j--)
                    result[j]=NULL;
                result[i]=&v[i];
            }
            else{
                opt[i]=opt[i-1];
                result[i]=NULL;
            }
        }
    }

    i=0;
    while(i<N){
        if(result[i]!=NULL)
        printf("(%d, %d), ", result[i]->tStart, result[i]->tEnd);

        i++;
    } 

    printf("\nIlmassimo e' %d", opt[N-1]);

    free(result);
    free(opt);
}
