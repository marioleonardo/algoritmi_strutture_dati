#ifndef INVENTARIO_H
#define INVENTARIO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int hp, mp, atk, def, mag, spr;
} stat_t;

typedef struct{
    char nome[51];
    char tipo[51];
    stat_t stat;
} inv_t;

typedef struct {
    inv_t *vettInv;
    int nInv;
    int maxInv;
} tabInv_t;
    
typedef struct {
    int inUso;
    inv_t **vettEq;
} tabEquip_t;



tabInv_t *getObjFile (FILE *fp);
void printObj(inv_t* obj);
inv_t* getObjByName (tabInv_t *inv,char* name);
void printTab(tabInv_t *tab);

#endif 