#include <stdio.h>

int majority( int *a, int N);

int majorityRec2( int *a, int N,  int *occ);

int majorityRec( int *a, int N);

int main(){
    int vet[100]={1,2,3,6,7,7,2,7,7,7,7,7}, N=12;

    printf("%d", majority(vet, N));
}


int majority( int *a, int N){
    int occ;
    return majorityRec2(a, N, &occ);
}

int majorityRec2( int *a, int N, int *occ){
    int n1, n2, i, ctr, m;
    int occ1, occ2;
    
    if(N==1){
        *occ=1;
        return a[0];
    
    }

    n1=majorityRec2(a, N/2, &occ1);
    n2=majorityRec2(a+N/2, N-N/2, &occ2);

    if(n1!=-1){
        ctr=0;
        for(i=N/2; i<N; i++)
            if(a[i]==n1)
                ctr++;
        
        if(ctr+occ1>N/2){
            *occ=ctr+occ1;
            return n1;
        }
    }
       
    if(n2!=-1){
        ctr=0;
        for(i=0; i<N/2; i++)
            if(a[i]==n2)
                ctr++;
    
        if(ctr+occ2>N/2){
            *occ=ctr+occ2;
            return n2;
        }
    }

    return -1;
}

int majorityRec( int *a, int N){
    int n1, n2, i, occ, m;
    
    if(N==1)
        return a[0];

    n1=majorityRec(a, N/2);
    n2=majorityRec(a+N/2, N-N/2);

    if(n1!=-1){
        occ=0;
        for(i=0; i<N; i++)
            if(a[i]==n1)
                occ++;
        
        if(occ>N/2)
            return n1;
    }
        
    if(n2!=-1){
        occ=0;
        for(i=0; i<N; i++)
            if(a[i]==n2)
                occ++;
    
        if(occ>N/2)
            return n2;
    }

    return -1;
}