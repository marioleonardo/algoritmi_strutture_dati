#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char codice[6], cognome[50], nome[50], via[50], citta[50], data[20]; 
    int cap;
    int valid;
} Item;

typedef struct node* link;

struct node {
    Item val;
    link next;
};

void insertElement(link *head, Item val);

Item searchItem(link head, char *code);

Item deleteNode(link *headPtr, link p);

Item deleteItemCode(link *headPtr, char *code);

Item deleteItemDates(link *headPtr, char *date1, char *date2);

void printListFile(link head, FILE *fp);

void printMenu();

void menuSwitch(char cmd, link *headPtr);

int main(){
    link head, p;
    Item val;
    char cmd;

    head=NULL;


    printMenu();
    scanf("%c", &cmd);
    while(cmd!='7'){
        menuSwitch(cmd, &head);
        printMenu();
        scanf(" %c", &cmd);
    }



}

void menuSwitch(char cmd, link *headPtr){
    Item val;
    FILE *fp_write, *fp_read;
    char fileName[100], codice[6], date1[20], date2[20];

    switch (cmd)
    {
    case '1':
        printf("Inserisci codice nome cognome data_nascita via citta cap separati da uno spazio");
        scanf("%s %s %s %s %s %s %d", val.codice, val.data, val.cognome, val.nome, val.citta, val.via, &val.cap);
        insertElement(headPtr, val);
        break;
    case '2':
        printf("inserisci nome file\n");
        scanf("%s", fileName);
        fp_read=fopen(fileName, "r");
        while(fscanf(fp_read, "%s %s %s %s %s %s %d", val.codice, val.data, val.cognome, val.nome, val.citta, val.via, &val.cap)!=0);
        fclose(fp_read);
        break;
    case '3':
        printf("inserisci codice\n");
        scanf("%s", codice);
        val=searchItem(*headPtr, codice);
        printf( "found: %s %s %s %s %s %s %d\n", val.codice, val.data, val.cognome, val.nome, val.citta, val.via, val.cap);
        break;
    case '4':
        printf("inserisci codice\n");
        scanf("%s", codice);
        val=deleteItemCode(headPtr, codice);
        printf( "found: %s %s %s %s %s %s %d\n", val.codice, val.data, val.cognome, val.nome, val.citta, val.via, val.cap);
        break;
    case '5':
        printf("inserisci prima data\n");
        scanf("%s", date1);
        printf("inserisci seconda data\n");
        scanf("%s", date2);
        do{
            val=deleteItemDates(headPtr, date1, date2);
            if(val.valid)
                printf( "found: %s %s %s %s %s %s %d\n", val.codice, val.data, val.cognome, val.nome, val.citta, val.via, val.cap);
        } while(val.valid);
        break;
    case '6':
        printf("inserisci nome file\n");
        scanf("%s", fileName);
        fp_write=fopen(fileName, "w");
        printListFile(*headPtr, fp_write);
        fclose(fp_write);
        break;
    
    
    default:
        break;
    }
}


void printMenu(){

    printf("Choose your operation:\n1. inserisci elemento tastiera\n2. inserisci elemento file\n3. ricerca per codice\n4.elimina per codice\n5. elimina (due date [gg/mm/aaaa])\n6. stampa su file\n7. exit\n\n");

}

void insertElement(link *head, Item val){
    link new, p;

    new=malloc(sizeof(struct node));

    val.valid=1;

    new->val=val;

    if(*head==NULL){
        *head=new;
        new->next=NULL;
    }
    else{
        p=*head;
        while(p->next!=NULL && strcmp(val.data, p->val.data)<0)
            p=p->next;
        
        if(p->next->next!=NULL)
            new->next=p->next->next;
        else
            new->next=NULL;
        p->next=new;
    }
}

Item searchItem(link head, char *code){
    link p;
    Item result;

    p=head;
    result.valid=0;

    while(p->next!=NULL && strcmp(code, p->val.codice)!=0)
        p=p->next;
    if(strcmp(code, p->val.codice)==0)
        return p->val;
    else 
        return result;
}

Item deleteNode(link *headPtr, link p){
    link x;
    Item result;

    x=*headPtr;
    result=p->val;

    if( p==*headPtr && x->next==NULL){
        *headPtr=NULL;
        free(p);
        return result;
    } else if( p==*headPtr && x->next!=NULL){
        *headPtr=x->next;
        free(p);
        return result;
    }

    while(x->next!=p && x->next!=NULL)
        x=x->next;
    
    if(x->next==NULL){
        result.valid=0;
        return result;
    }
    
    if(x->next==p && x->next->next==NULL){
        x->next=NULL;
        free(p);
        return result;
    }

    if(x->next==p && x->next->next!=NULL){
        x->next=x->next->next;
        free(p);
        return result;
    }

    
}

Item deleteItemCode(link *headPtr, char *code){
    link p;
    Item result;

    p=*headPtr;
    result.valid=0;

    while(p->next!=NULL && strcmp(code, p->val.codice)!=0)
        p=p->next;
    if(strcmp(code, p->val.codice)==0)
        return deleteNode(headPtr, p);
    else 
        return result;
}

Item deleteItemDates(link *headPtr, char *date1, char *date2){
    link p;
    Item result;
    char dateTemp[50];

    p=*headPtr;
    result.valid=0;

    //date1 è piu grande

    while(p->next!=NULL && strcmp(p->val.data, date1)>0)
        p=p->next;
    if(strcmp(p->val.data, date2)>0)
        return deleteNode(headPtr, p);
    else 
        return result;
}

void printListFile(link head, FILE *fp){
    link x;
    Item val;

    x=head;

    while(x!=NULL){
        val=x->val;
        fprintf(fp, "%s %s %s %s %s %s %d\n", val.codice, val.data, val.cognome, val.nome, val.citta, val.via, val.cap);
        x=x->next;
    }
}
