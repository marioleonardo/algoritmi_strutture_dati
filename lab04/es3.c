#include <stdio.h>
#include <stdlib.h>
#define NUM_STONES 4

typedef enum {
    zaffiro,
    rubino, 
    smeraldo,
    topazio
} stone;

int trovaMaxVet(stone *vet, stone **result);

int trovaMaxVetRec(int livello, int max, int n, stone *vet, stone *temp, stone *result);

int main(){
    stone pietra;
    stone vetPietre[NUM_STONES];
    stone *result;
    int dim, i, numPietre;
    char out;

    vetPietre[smeraldo]=5;
    vetPietre[rubino]=11;
    vetPietre[topazio]=10;
    vetPietre[zaffiro]=7;

    dim=trovaMaxVet(vetPietre, &result);
    numPietre=vetPietre[0]+vetPietre[1]+vetPietre[2]+vetPietre[3];
    printf("%d su %d\n", dim, numPietre);
    for(i=0; i<dim; i++){    
        if(result[i]==smeraldo) out='s';
        if(result[i]==rubino) out='r';
        if(result[i]==topazio) out='t';
        if(result[i]==zaffiro) out='z';
        printf("%c ", out);
    }

}

int trovaMaxVet(stone *vet, stone **result){
    stone *temp;
    int numPietre;

    numPietre=vet[0]+vet[1]+vet[2]+vet[3];

    *result=malloc(numPietre*sizeof(stone));
    temp=malloc(numPietre*sizeof(stone));

    return trovaMaxVetRec(0, 0, numPietre, vet, temp, *result);
}

int trovaMaxVetRec(int livello, int max, int n, stone *vet, stone *temp, stone *result){
    int i,j, dim;

    dim=0;

    if(livello==0){ 
        for(i=0; i<NUM_STONES ; i++){
            if(vet[i]>0){
                vet[i]--;
                temp[livello]=i;
                dim=trovaMaxVetRec(livello+1, max, n, vet, temp, result);
                if(dim>max)
                    max=dim;
                vet[i]++;
            }
        }
    }

    if(livello>0)
    for(i=0; i<NUM_STONES ; i++){
        if(vet[i]>0 && (((temp[livello-1]==zaffiro || temp[livello-1]==topazio) && (i==zaffiro || i==rubino)) || ((temp[livello-1]==smeraldo || temp[livello-1]==rubino) && (i==smeraldo || i==topazio)))){
            vet[i]--;
            temp[livello]=i;
            dim=trovaMaxVetRec(livello+1, max, n, vet, temp, result);
            if(dim>max)
                max=dim;
            vet[i]++;
        }
    }

    
    if(dim==0 && livello>max){
        max=livello;
        for(i=0; i<max ; i++)   result[i]=temp[i];
        
    }
    return max;
}