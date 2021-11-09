#include <stdio.h>

struct casella{
    int found;
    int number;
    int possibilities[9];
};

int readMat(FILE *fp, struct casella mat[9][9]);

int insertNum(struct casella mat[9][9], int num, int r, int c);

int isValid(struct casella mat[9][9]);

int makeEasyMove(struct casella mat[9][9]);

int main(){
    struct casella mat[9][9];
    int n;
    FILE *fp_read;

    fp_read=fopen("ex.txt", "r");

    n=readMat(fp_read, mat);

    printf("dim: %d\n", n);
}

int makeEasyMove(struct casella mat[9][9]){
    int i, j, k, cnt, made, r, c, n;

    made=0;

    for(i=0; i<9; i++){
        for(j=0; j<9 && mat[i][j].found==0; j++){
            cnt=0;
            for(k=0; k<9; k++){
                cnt+=mat[i][j].possibilities[k];
                r=i ? mat[i][j].possibilities[k]==1 : r;
                c=j ? mat[i][j].possibilities[k]==1 : c;
                n=k ? mat[i][j].possibilities[k]==1 : n;
            }
            if(cnt==1){
                mat[r][c].found=1;
                mat[r][c].number=n;
                made=r*9+c;
                return made;
            }
        }
    }

    return made;
}

int isValid(struct casella mat[9][9]){
    int i, j, k, cnt, valid;

    valid=1;

    for(i=0; i<9; i++){
        for(j=0; j<9 && mat[i][j].found==0; j++){
            cnt=0;
            for(k=0; k<9; k++){
                cnt+=mat[i][j].possibilities[k];
            }
            if(cnt==0)
                valid==0;
        }
    }

    return valid;
}

int insertNum(struct casella mat[9][9], int num, int r, int c){
    int i, j, valid;

    valid=mat[r][c].possibilities[num-1]==1;

    if(valid){
        mat[r][c].found=1;
        mat[r][c].number=num-1;
    }


    //remove row col
    for(i=0; i<9; i++){
        mat[i][c].possibilities[num-1]=0;
        mat[r][i].possibilities[num-1]=0;
    }

    //remove square
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
             mat[i+(r-r%3)][j+(c-c%3)].possibilities[num-1]=0;
        }
    }

    return valid;
}

int readMat(FILE *fp, struct casella mat[9][9]){
    
    int number, i, j, k, cnt;

    cnt=0;

    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            for(k=0; k<9; k++){
                mat[i][j].possibilities[k]=1;
            }
        }
    }

    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            fscanf(fp, "%d", &number);
            if(number==0){
                mat[i][j].found=0;
            }
            else{
                insertNum(mat, number, i, j);
                cnt++;
            }
        }
    }

    return cnt;
}