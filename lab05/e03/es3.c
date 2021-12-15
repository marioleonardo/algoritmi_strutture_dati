#include "inventario.h"
#include "personaggi.h"


void printMenu();
void scanMenu(char c, tabPg_t *tab, tabInv_t **tabInvPtr);

int main(){
    char c;
    tabPg_t tabPg;
    tabInv_t *tabInv;
    tabPg.head=NULL;
    tabPg.tail=NULL;

    while(1){
        printMenu();
        scanf(" %c", &c);
        scanMenu(c, &tabPg, &tabInv);

    }
}


void printMenu(){
    printf("Scegli il tuo comando\n\n1. caricare in una lista l'elenco di personaggi\n2. caricare l'elenco di oggetti\n3. aggiungere un nuovo personaggio\n4. eliminare un personaggio\n5. aggiungere un oggetto dall'equipaggiamento\n6. rimuovere un oggetto dall'equipaggiamento\n7. Stampa statistiche\n\n");
}

void scanMenu(char c, tabPg_t *tab, tabInv_t **tabInvPtr){
    char fileName[50], code[8], name[20];
    FILE *fp;


    switch(c){
        case '1':
            printf("Inserisci nome file: ");
            scanf("%s", fileName);
            fp=fopen(fileName, "r");
            handleFile(tab,fp);
            fclose(fp);
        break;
        case '2':
            printf("Inserisci nome file: ");
            scanf("%s ", fileName);
            fp=fopen(fileName, "r");
            *tabInvPtr=getObjFile(fp);
            fclose(fp);
        break;
        case '3':
            printf("Inserisci personaggio: ");
            scanPg(tab);
        break;
        case '4':
            printf("Inserisci personaggio da eliminare: ");
            scanf("%s ", code);
            removePg(tab, code);
        break;
        case '5':
            printf("Inserisci personaggio e oggetto");
            scanf("%s %s ", code, name);
            addObj(tab, *tabInvPtr, code, name);
        break;
        case '6':
            printf("Inserisci personaggio e oggetto");
            scanf("%s %s ", code, name);
            removeObj(tab, *tabInvPtr, code, name);
        break;
        case '7':
            printf("Inserisci personaggio: ");
            scanf("%s ", code);
            printStats(getByCode(tab, code));
        break;

    }
}