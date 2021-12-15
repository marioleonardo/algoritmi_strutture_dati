#ifndef PERSONAGGI_H
#define PERSONAGGI_H
#include <stdio.h>
#include <stdlib.h>
#include "inventario.h"

typedef struct {
    char codice[7];
    char nome[51];
    char classe[51];
    tabEquip_t *equip;
    stat_t stat;
    stat_t statFinal;
    int valid;
} pg_t;

typedef struct node_t* link;

typedef struct node_t{
    pg_t pg;
    link next;
} nodoPg_t;

typedef struct{
    nodoPg_t *head;
    nodoPg_t *tail;
    int nPg;
} tabPg_t;

link newNodePg (pg_t pg, link next); 
void insertPg(tabPg_t *tab, pg_t temp);
pg_t* getByCode(tabPg_t *tab, char *code);
void handleFile(tabPg_t *tab, FILE *fp);
pg_t removePg(tabPg_t *tab, char *code);
void printStats(pg_t *pg);
void printListPg(tabPg_t *tab);
void scanPg(tabPg_t *tab);
void addObj(tabPg_t *tab, tabInv_t *inv, char *code,  char *name);
void removeObj(tabPg_t *tab, tabInv_t *inv, char *code,  char *name);
void calculateStats(pg_t *pg);

#endif