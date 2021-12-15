#include <stdio.h>
#include <stdlib.h>
#define NUM_STONES 4

typedef enum {
    zaffiro,
    rubino, 
    smeraldo,
    topazio
} stone;

int trovaMaxVet(stone *vet, int ******stonesPtr);


int fz(int *****mat, stone *vet);
int fs(int *****mat, stone *vet);
int ft(int *****mat, stone *vet);
int fr(int *****mat, stone *vet);

int main(){
    stone pietra;
    stone vetPietre[NUM_STONES];
    int *****stones;
    int dim, i, numPietre;
    char out;

    

    vetPietre[smeraldo]=17;
    vetPietre[rubino]=20;
    vetPietre[topazio]=12;
    vetPietre[zaffiro]=13;
    

    stones=NULL;
    dim=trovaMaxVet(vetPietre, &stones);
    numPietre=vetPietre[0]+vetPietre[1]+vetPietre[2]+vetPietre[3];
    printf("%d su %d\n", dim, numPietre);
}

int trovaMaxVet(stone *vet, int ******stonesPtr){
    stone *temp;
    int *****stones, max1, max2, maxNum;
    int numPietre, i, j, k, l, m;

    if(stones==NULL){
        *stonesPtr=malloc(4* sizeof(int*));
        stones=*stonesPtr;
        for(i=0; i<4; i++){
            stones[i]=malloc((vet[0]+1)*sizeof(int*));
            for(j=0; j<vet[0]+1; j++){
                stones[i][j]=malloc((vet[1]+1)*sizeof(int*));
                    for(k=0; k<vet[1]+1; k++){
                        stones[i][j][k]=malloc((vet[2]+1)*sizeof(int*));
                        for(l=0; l<vet[2]+1; l++){
                            stones[i][j][k][l]=malloc((vet[3]+1)*sizeof(int));
                            for(m=0; m<vet[3]+1; m++){
                                stones[i][j][k][l][m]=-1;
                            }
                        }
                }
            }
        }
    }
    numPietre=vet[0]+vet[1]+vet[2]+vet[3];


    max1=(((fz(stones, vet)) > (ft(stones, vet))) ? (fz(stones, vet)) : (ft(stones, vet)));
    max2=(((fz(stones, vet)) > (ft(stones, vet))) ? (fz(stones, vet)) : (ft(stones, vet)));
    maxNum=(((max1) > (max2)) ? (max1) : (max2));

    if(stones!=NULL){
        *stonesPtr=malloc(4* sizeof(int*));
        stones=*stonesPtr;
        for(i=0; i<4; i++){
            for(j=0; j<vet[0]+1; j++){
                    for(k=0; k<vet[1]+1; k++){
                        for(l=0; l<vet[2]+1; l++){
                            free(stones[i][j][k][l]);
                        }
                        free(stones[i][j][k]);
                    }
                free(stones[i][j]);
            }
            free(stones[i]);
        }
        free(stones);
    }

    return maxNum;
}

int fs(int *****mat, stone *vet){
    int maxNum;
    int a,b;

    if (vet[smeraldo]<=0){
        return 0;
    }

    if (mat[smeraldo][vet[0]][vet[1]][vet[2]][vet[3]]!=-1){
        return mat[smeraldo][vet[0]][vet[1]][vet[2]][vet[3]];
    }

    vet[smeraldo]--;
    a=1+fs(mat, vet);
    b=1+ft(mat, vet);
    maxNum=a>b?a:b;
    vet[smeraldo]++;

    mat[smeraldo][vet[0]][vet[1]][vet[2]][vet[3]]=maxNum;

    return maxNum;
}

int ft(int *****mat, stone *vet){
    int maxNum;
    int a,b;


    if (vet[topazio]<=0){
        return 0;
    }

    if (mat[topazio][vet[0]][vet[1]][vet[2]][vet[3]]!=-1){
        return mat[topazio][vet[0]][vet[1]][vet[2]][vet[3]];
    }

    vet[topazio]--;
    a=1+fr(mat, vet);
    b=1+fz(mat, vet);
    maxNum=a>b?a:b;
    vet[topazio]++;

    mat[topazio][vet[0]][vet[1]][vet[2]][vet[3]]=maxNum;

    return maxNum;
}

int fz(int *****mat, stone *vet){
    int maxNum;
    int a,b;


    if (vet[zaffiro]<=0){
        return 0;
    }

    if (mat[zaffiro][vet[0]][vet[1]][vet[2]][vet[3]]!=-1){
        return mat[zaffiro][vet[0]][vet[1]][vet[2]][vet[3]];
    }

    vet[zaffiro]--;
    a=1+fz(mat, vet);
    b=1+fr(mat, vet);
    maxNum=a>b?a:b;
    vet[zaffiro]++;

    mat[zaffiro][vet[0]][vet[1]][vet[2]][vet[3]]=maxNum;

    return maxNum;
}

int fr(int *****mat, stone *vet){
    int maxNum;
    int a,b;


    if (vet[rubino]<=0){
        return 0;
    }

    if (mat[rubino][vet[0]][vet[1]][vet[2]][vet[3]]!=-1){
        return mat[rubino][vet[0]][vet[1]][vet[2]][vet[3]];
    }

    vet[rubino]--;
    a=1+fs(mat, vet);
    b=1+ft(mat, vet);
    maxNum=a>b?a:b;
    vet[rubino]++;

    mat[rubino][vet[0]][vet[1]][vet[2]][vet[3]]=maxNum;

    return maxNum;
}

