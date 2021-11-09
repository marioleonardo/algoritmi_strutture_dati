#include <stdio.h>

typedef struct{
    char codice[50], cognome[50], nome[50], via[50], citta[50], data[20]; 
    int cap;
} Item;

typedef struct node* link;

struct node {
    Item val;
    link next;
};

int main(){
    link head, p;

    head=NULL;

    

}

