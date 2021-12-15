#include "inventario.h"


tabInv_t *getObjFile (FILE *fp){
    char nome[51], tipo[51];
    int i;

    tabInv_t *inv = malloc(sizeof(tabInv_t));
    fscanf(fp,"%d",&inv->nInv);
    
    inv->vettInv = (inv_t *)malloc(inv->nInv * sizeof(inv_t));
    for (i=0; i<inv->nInv; i++){
        fscanf(fp,"%s%s",inv->vettInv[i].nome,inv->vettInv[i].tipo);
        fscanf(fp,"%d%d%d%d%d%d",inv->vettInv[i].stat.hp,&inv->vettInv[i].stat.mp,
               &inv->vettInv[i].stat.atk, &inv->vettInv[i].stat.def,&inv->vettInv[i].stat.mag,&inv->vettInv[i].stat.spr);
        
    }
    
    return inv;
}

void printObj(inv_t* obj){
 
    printf("NOME: %s\t TIPO: %s\n",obj->nome,obj->tipo);
    printf("hp: %d  mp: %d  atk: %d  def: %d  mag: %d  spr: %d\n",obj->stat.hp,obj->stat.mp,obj->stat.atk,obj->stat.def,obj->stat.mag,obj->stat.spr);
}

inv_t* getObjByName (tabInv_t *inv,char* name){
    int k,min=0,max;
    max=inv->nInv;
    while (min<=max){
        k=min+((max-min)/2);
        if (strcmp(inv->vettInv[k].nome,name)==0){
            return &inv->vettInv[k];
        }
        else if (strcmp(inv->vettInv[k].nome,name)<0){
            min = min +1;
        }
        else if (strcmp(inv->vettInv[k].nome,name)>0){
            max = max-1;
        }
    }
    return NULL;
}

void printTab(tabInv_t *tab){
    int i;
    printf("Numero oggetti  %d\n",tab->nInv);
    for (i=0; i<tab->nInv; i++){
        printObj(&(tab->vettInv[i]));
    }
 
}