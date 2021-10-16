#include <stdio.h>
#include <string.h>
#define filein ".\\log.txt"
#define MAX_CHAR_CORSA 30
#define MAX_LENGTH_DATA 1000

typedef enum {
    o_partenza,
    o_arrivo,
    o_codice,
    o_data,
    r_partenza,
    r_errore,
    r_fine
} comando_e;

typedef struct corsa{
    char code[MAX_CHAR_CORSA+1];
    char start[MAX_CHAR_CORSA+1];
    char dest[MAX_CHAR_CORSA+1];
    char timeStart[MAX_CHAR_CORSA+1];
    char timeEnd[MAX_CHAR_CORSA+1];
    int date[3];
    int delay;
} t_corsa;

typedef struct request{
    int code;
    char startCorsa[MAX_CHAR_CORSA+1];
    int dest;
    int date;
    int start;         
} t_request;

comando_e leggiComando();

int sort(t_request req, t_corsa data[], int lenData);

int query(t_request req, t_corsa data[], int lenData, int res[]);

int menuParola(comando_e cmd, t_corsa data[MAX_LENGTH_DATA], int lenData);

int handleFileInput(char fileName[], t_corsa data[]);


int dateCompare(int date1[3], int date2[3]);

void printMenu();

int main(){
    int finished, status, lenData;
    comando_e command;
    t_corsa data[MAX_LENGTH_DATA];
    lenData = handleFileInput(filein, data);
    

    finished = 0;
    printMenu();
    while(!finished){
        printf("\nInsersici comando: ");

        lenData = handleFileInput(filein, data);

        command = leggiComando();
        if(command == r_fine)                   finished=1;
        
        status = menuParola(command, data, lenData);
        
        if((command == r_errore || status == 1) && !finished)   printf("Errore di acquisizione\n");
    }

    return 0;
}

void printMenu(){
    printf("\nElenco comandi menu: \n\
    1.ricerca stazione partenza\n\
    2.ordina data\n\
    3.ordina codice\n\
    4.ordina stazione partenza\n\
    5.ordina stazione di arrivo\n\n"
    );
}

comando_e leggiComando(){
    char word[MAX_CHAR_CORSA];
    comando_e command;

    gets(word);
    command = r_errore;
    if(strcmp(word, "1") == 0)              command = r_partenza;
    if(strcmp(word, "2") == 0)              command = o_data;
    if(strcmp(word, "3") == 0)              command = o_codice;
    if(strcmp(word, "4") == 0)              command = o_partenza;
    if(strcmp(word, "5") == 0)              command = o_arrivo;
    if(strcmp(word, "fine") == 0)           command = r_fine;

    return command;    
}

int menuParola(comando_e cmd, t_corsa data[MAX_LENGTH_DATA], int lenData){
    t_request req;
    t_corsa corsa;
    int responseList[MAX_LENGTH_DATA], lenResponse, i, delayTot;
    
    memset(&req, 0, sizeof(req));
    switch(cmd){

        case r_partenza:        gets( req.startCorsa);        break;
        case o_data:            req.date=1;                   break;
        case o_partenza:        req.start=1;                  break;
        case o_arrivo:          req.dest=1;                   break;
        case o_codice:          req.code=1;                   break;
        case r_errore:
        default:             return 1;  //Error handling
    }

    if(cmd!=r_partenza)
        lenResponse = sort(req, data, lenData);
    else
        lenResponse = query(req, data, lenData, responseList);

    if(lenResponse > 0){

        for(i=0 ; i<lenResponse ; i++){
            if(cmd==r_partenza)
                corsa=data[responseList[i]];
            else
                corsa = data[i];
            printf("corsa %d: %s Da: %-15s A: %-15s Il: %d/%02d/%02d Partenza: %s Arrivo: %s Ritardo: %d\n", 
                    i, corsa.code, corsa.start, corsa.dest, corsa.date[0], corsa.date[1], corsa.date[2],
                    corsa.timeStart, corsa.timeEnd, corsa.delay);
        }

        
    }

    return 0;
}

int query(t_request req, t_corsa data[], int lenData, int res[]){
    int i, indexRes, valid, validDate;

    for(i=0 , indexRes=0 ; i<lenData ; i++){      
        
        valid=1;

        if(req.startCorsa[0] != '\0' && strstr( data[i].start, req.startCorsa) == NULL)       valid=0;


        if(valid){
            res[indexRes] = i;
            indexRes++;
        }
    }

    return indexRes;
}

int handleFileInput(char fileName[], t_corsa data[]){
    int lenData, i;
    char c[MAX_CHAR_CORSA+1], s[MAX_CHAR_CORSA+1], d[MAX_CHAR_CORSA+1], ts[MAX_CHAR_CORSA+1], te[MAX_CHAR_CORSA+1];
    int a, m, g, dl;
    FILE *fp;

    if((fp=fopen(fileName, "r")) == NULL){
        printf("Errore apertura file\n");
        return 0;
    }

    fscanf(fp, "%d", &lenData);
    for(i=0 ; i<lenData ; i++){
        fscanf(fp, "%s %s %s %d/%d/%d %s%s %d", c, s, d, &a, &m, &g, ts, te, &dl);
        strcpy(data[i].code, c);
        strcpy(data[i].start, s);
        strcpy(data[i].dest, d);
        strcpy(data[i].timeStart, ts);
        strcpy(data[i].timeEnd, te);
        data[i].date[0] = a;
        data[i].date[1] = m;
        data[i].date[2] = g;
        data[i].delay   = dl;
    }

    fclose(fp);
    return lenData;
}

int dateCompare(int date1[3], int date2[3]){
    int valid, d1,d2;

    // simple method wich converts aaaa mm gg in a integer aaaammgg for comparison
    d1 = date1[0]*10000+ date1[1]*100+ date1[2];
    d2 = date2[0]*10000+date2[1]*100+date2[2];

    return d1>d2;
}


int sort(t_request req, t_corsa data[], int lenData){
    int i,j, dateSort, partSort, destSort, codeSort;
    t_corsa temp;


    for(i=0;i<lenData-1;i++){
        for(j=0;j<lenData-i-1;j++){
            dateSort= req.date==1 && dateCompare(data[j].date,data[j+1].date);
            codeSort= req.code==1 && strcmp(data[j].code,data[j+1].code)>0;
            partSort= req.start==1 && strcmp(data[j].start,data[j+1].start)>0;
            destSort= req.dest==1 && strcmp(data[j].dest,data[j+1].dest)>0;
            if(dateSort || codeSort || destSort || partSort){
                temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
            }
        }
    }

    return(lenData);
}