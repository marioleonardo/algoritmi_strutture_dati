#include <stdio.h>
#include <stdlib.h>
#define filein "brani.txt"

typedef struct {char **scelte; int num_scelte; } Livello;

int combine(int pos, Livello *val, char **sol, char **solParz, int n, int cnt);

int main(){
    FILE *fp_read;
    Livello *val;
    int i, j, n, dimSol, cnt;
    char **sol, **solParz;
    
    fp_read=fopen(filein, "r");

    fscanf(fp_read,"%d", &n);

    val = malloc(n*sizeof(Livello));

    dimSol=1;


    for (i=0; i<n; i++){
        fscanf(fp_read,"%d", &val[i].num_scelte);
        val[i].scelte = malloc(val[i].num_scelte*sizeof(char*));
        dimSol*=val[i].num_scelte;
        for(j=0; j<val[i].num_scelte;j++){
            val[i].scelte[j]=malloc(sizeof(char)*255);
            fscanf(fp_read, "%s", val[i].scelte[j]);
        }
    }

    sol = malloc(n*sizeof(char*)*dimSol);
    solParz = malloc(n*sizeof(char*));
    cnt=0;

    cnt=combine(0, val, sol, solParz, n, cnt);

    for(i=0;i<n;i++){
        for(j=0;j<val[i].num_scelte;j++){
            free(val[i].scelte[j]);
        }
        free(val[i].scelte);
    }
    free(val);
    free(sol);
    free(solParz);

}

int combine(int pos, Livello *val, char **sol, char **solParz, int n, int cnt) {
    int i;
    if (pos >= n) {
        for (i = 0; i < n; i++)
            sol[cnt*n+i]=solParz[i];
        return cnt+1;
    }
    
    for (i = 0; i < val[pos].num_scelte; i++) {
        solParz[pos] = val[pos].scelte[i];
        cnt = combine(pos+1, val, sol, solParz, n, cnt);
    }
    
    return cnt;
}