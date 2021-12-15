#include <stdlib.h>
#include "personaggi.h"

void insertPg(tabPg_t *tab, pg_t temp){
    link newPg;
    int i;

    temp.valid=1;
    temp.statFinal=temp.stat;
    temp.equip=malloc(sizeof(tabEquip_t));
    temp.equip->vettEq=malloc(sizeof(inv_t*)*8);
    for(i=0; i<8; i++)     temp.equip->vettEq[i]=NULL;
    newPg = newNodePg(temp, NULL);

 
    if (tab == NULL || newPg == NULL){
        return;
    }
    if (tab->head == NULL){
        tab->head = tab->tail = newPg; 
    }
    else{
        tab->tail->next = newPg; 
        tab->tail = newPg;
    }

    
}

link newNodePg(pg_t pg, link next){
    link x= malloc(sizeof (nodoPg_t));
    if (x==NULL){
        return NULL;
    } else{
        x->pg = pg;
        x->next = next;
    }
    return x;
}



void handleFile(tabPg_t *tab, FILE *fp){
    int i;
    pg_t temp;
    


    while(fscanf(fp, "%s %s %s %d%d%d%d%d%d ", temp.codice,  temp.nome,  temp.classe,  temp.stat.hp, temp.stat.mp, temp.stat.atk, temp.stat.def, temp.stat.mag, temp.stat.spr )>0){
        insertPg(tab, temp);
    }
    
}

void scanPg(tabPg_t *tab){
    pg_t temp;
    
    if(fscanf(stdin, "%s %s %s %d%d%d%d%d%d ", temp.codice,  temp.nome,  temp.classe,  temp.stat.hp, temp.stat.mp, temp.stat.atk, temp.stat.def, temp.stat.mag, temp.stat.spr )>0){
        insertPg(tab, temp);
    }
}

pg_t* getByCode(tabPg_t *tab, char *code){

    link x;
    for (x=tab->head; x!=NULL && strcmp(x->pg.codice, code)!=0; x=x->next){
        if (strcmp(x->pg.codice,code)==0){
            return &(x->pg);
            }
    }
    return NULL;
}

pg_t removePg(tabPg_t *tab, char *code){
    link x,p;
    pg_t res;
    
    for (x=tab->head, p = NULL; x!=NULL && strcmp(x->pg.codice,code)!=0; p=x,x=x->next){
        if (strcmp(x->pg.codice,code)==0){
            if (x==tab->head){ 
                tab->head = x->next;
                x->next = NULL;
            }
            else {
                p->next = x->next;
                x->next = NULL;
            }
        }
        res=x->pg;
        free(x);
        return res;
    }
    res.valid=0;
    return res;
}

void printStats(pg_t *pg){
    int i;
    printf("STAMPA PERSONAGGIO\n");
    printf("codice: %s  nome: %s  classe: %s\n", pg->codice, pg->nome, pg->classe);
    printf("OGGETTI PRESENTI NELL' EQUIPAGGIAMENTO:\n");
    for (i = 0; pg->equip->vettEq[i] != NULL; i++) {
        printf("#%d oggetto:\n", i);
        printObj((pg->equip->vettEq[i]));
    }
    printf("STATISTICHE BASI DEL PERSONAGGIO:\n");
    printf("hp: %d  mp: %d  atk: %d  def: %d  mag: %d  spr: %d\n", pg->stat.hp, pg->stat.mp, pg->stat.atk, pg->stat.def,
           pg->stat.mag, pg->stat.spr);
    if (pg->equip->inUso > 0) { 
        printf("STATISTICHE PERSONAGGIO CON EQUIPAGGIAMENTO:\n");
        if (pg->statFinal.hp<0){
            printf("hp: 0  ");
        }
        else{
            printf("hp: %d  ",pg->statFinal.hp);
        }
        if (pg->statFinal.mp<0){
            printf("mp: 0  ");
        }
        else{
            printf("mp: %d  ",pg->statFinal.mp);
        }
        if (pg->statFinal.atk<0){
            printf("atk: 0  ");
        }
        else{
            printf("atk: %d  ",pg->statFinal.atk);
        }
        if (pg->statFinal.def<0){
            printf("def: 0  ");
        }
        else{
            printf("def: %d  ",pg->statFinal.def);
        }
        if (pg->statFinal.mag<0){
            printf("mag: 0  ");
        }
        else{
            printf("mag: %d  ",pg->statFinal.mag);
        }
        if (pg->statFinal.spr<0){
            printf("spr: 0  ");
        }
        else{
            printf("spr: %d\n",pg->statFinal.spr);
        }
    }
    else{
        printf("Il personaggio non ha nessun oggetto nell' equipaggiamento.\n");
    }
}

void printListPg(tabPg_t *tab){
    link x;
    printf("STAMPA LISTA PERSONAGGI\n");
    for (x = tab->head; x!=NULL; x=x->next){
        printStats(&(x->pg));
    }
}

void addObj(tabPg_t *tab, tabInv_t *inv, char *code,  char *name){
    pg_t *pg;
    inv_t *obj;
    int i, valid;

    pg=getByCode(tab, code);
    obj=getObjByName(inv, name);

    valid=1;
    for(i=0; i<8 && valid; i++){
        if(pg->equip->vettEq[i]==NULL){
            valid=0;
            pg->equip->vettEq[i]=obj;
        }
    }

    calculateStats(pg);
}

void removeObj(tabPg_t *tab, tabInv_t *inv, char *code,  char *name){
    pg_t *pg;
    inv_t *obj;
    int i, valid;

    pg=getByCode(tab, code);
    obj=getObjByName(inv, name);

    valid=1;
    for(i=0; i<8 && valid; i++){
        if(pg->equip->vettEq[i]==obj){
            valid=0;
            pg->equip->vettEq[i]=NULL;
        }
    }

    calculateStats(pg);
}

void calculateStats(pg_t *pg){
    int i;

    for(i=0; i<8; i++){
        if(pg->equip->vettEq[i]!=NULL){
            pg->stat.atk+=pg->equip->vettEq[i]->stat.atk;
            pg->stat.def+=pg->equip->vettEq[i]->stat.def;
            pg->stat.hp +=pg->equip->vettEq[i]->stat.hp;
            pg->stat.mag+=pg->equip->vettEq[i]->stat.mag;
            pg->stat.mp+=pg->equip->vettEq[i]->stat.mp;
            pg->stat.spr+=pg->equip->vettEq[i]->stat.spr;
        }
    }

}