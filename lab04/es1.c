#include <stdio.h>
#include <stdlib.h>

struct grafo{
    int numNodi, numArchi;
    int **archi;
};

void printVertexCover(struct grafo graph);

void generatePowerset(int livello, int *vet, struct grafo graph);

int main(){
    int numNodi, numArchi, i;
    FILE *fp_read;
    struct grafo graph;


    fp_read=fopen("grafo.txt", "r");

    fscanf(fp_read, "%d %d", &graph.numNodi, &graph.numArchi);
    graph.archi=malloc(graph.numArchi*sizeof(int**));


    for(i=0;i<graph.numArchi;i++){
        graph.archi[i]=malloc(2*sizeof(int));
        fscanf(fp_read, "%d %d", &graph.archi[i][0], &graph.archi[i][1]);
    }

    printVertexCover(graph);

}

void generatePowerset(int livello, int *vet, struct grafo graph){
    int i;

    if(livello>=graph.numNodi){
        for(i=0;i<graph.numArchi;i++){

            if (vet[graph.archi[i][0]]==0 && vet[graph.archi[i][1]]==0)
                return;
        }

        for(i=0;i<graph.numNodi;i++)
            if(vet[i]==1)
                printf("%d ", i);

        printf("\n");
        
        return;
    }

    vet[livello]=0;
    generatePowerset(livello+1, vet, graph);
    vet[livello]=1;
    generatePowerset(livello+1, vet, graph);

    return;
}

void printVertexCover(struct grafo graph){
    int *vet,i,j;

    vet=malloc(graph.numNodi*sizeof(int));

    generatePowerset(0, vet, graph);
}