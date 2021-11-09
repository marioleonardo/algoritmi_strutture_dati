#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define FILEIN "mat.txt"
#define DIM 10

int **malloc2dR(int nr, int nc);

void malloc2dP(int ***mat, int nr, int nc);

void readFile(FILE *fp, int **mat, int nr, int nc);

void separa(int **mat, int nr, int nc, int *v1, int *v2);

 int main(){
    int *bianche, *nere;
    int nr, nc, i;
    int **mat;

   FILE *fp_read;

   fp_read = fopen(FILEIN, "r");

   fscanf(fp_read, "%d %d", &nr, &nc);

   malloc2dP(&mat, nr, nc);

   readFile(fp_read, mat, nr, nc);

   bianche = malloc( sizeof(int)*((nr/2+nr%2)*(nc/2+nc%2)  +  (nr/2)*(nc/2)) );

   nere = malloc( sizeof(int)*((nr*nc) - ((nr/2+nr%2)*(nc/2+nc%2)  +  (nr/2)*(nc/2)))  );

   separa(mat, nr, nc, bianche, nere);
   
   for(i=0;i<nr;i++)
    free(mat[i]);
   free(mat);

 }

 int **malloc2dR(int nr, int nc){
   int **vettPunt, i; 

   vettPunt=(int**)malloc(nr*sizeof(int));

   for(i=0; i<nc; i++){
     vettPunt[i]=(int *)malloc(nc*sizeof(int));
   }

   return vettPunt;
 }

 void malloc2dP(int ***mat, int nr, int nc){
   int i;

   *mat=(int**)malloc(nr*sizeof(int));

   for(i=0; i<nc; i++){
     (*mat)[i]=(int *)malloc(nc*sizeof(int));
   }
 }

 void readFile(FILE *fp, int **mat, int nr, int nc){
   int i,j;
   
   for(i=0; i<nr; i++){
     for(j=0; j<nc; j++){
        fscanf(fp, "%d", &mat[i][j]);
     }
   }
 }

 void separa(int **mat, int nr, int nc, int *v1, int *v2){
   int i,j, index1, index2;
   

   index1=0;
   index2=0;



   for(i=0; i<nr;i++){
     for(j=0; j<nc; j++){
       if((i%2==0 && j%2==0) || (i%2==1 && j%2==1)){
          v1[index1]=mat[i][j];
          index1++;
       } else{
         v2[index2]=mat[i][j];
         index2++;
       }
     }
   }

    for(i=0;i<index1;i++)
      printf("%d ", v1[i]);
    printf("\n");
    
    for(i=0;i<index2;i++)
      printf("%d ", v2[i]);
    printf("\n");

    free(v1);
    free(v2);
 }