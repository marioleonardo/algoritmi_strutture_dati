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
    r_log,
    r_errore,
    r_fine
} comando_e;

typedef struct corsa{
    char code[MAX_CHAR_CORSA+1];
    char start[MAX_CHAR_CORSA+1];
    char dest[MAX_CHAR_CORSA+1];
    char timeStart[MAX_CHAR_CORSA+1];
    char timeEnd[MAX_CHAR_CORSA+1];
    int timeStartInt;
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

int sort(t_request req, t_corsa data[], t_corsa *sorted[], int lenData);

int query(t_request req, t_corsa data[], int lenData, int res[]);

int menuParola(comando_e cmd, t_corsa data[MAX_LENGTH_DATA], int lenData);

int handleFileInput(char fileName[], t_corsa data[]);

int queryDicotomica(t_request req, t_corsa data[], int lenData, int res[]);

int dateCompare(int date1[3], int date2[3], int t1, int t2);

void printMenu();

int main(){
    int finished, status, lenData;
    comando_e command;
    t_request req;
    t_corsa data[MAX_LENGTH_DATA];
    lenData = handleFileInput(filein, data);
    


    finished = 0;
    printMenu();
    while(!finished){
        printf("\nInsersici comando: ");

        command = leggiComando();
        if(command == r_fine)                   finished=1;
        
        status = menuParola(command, data, lenData);
        
        if((command == r_errore || status == 1) && !finished)   printf("Errore di acquisizione\n");
    }

    return 0;
}

void printMenu(){
    printf("\nElenco comandi menu: \n\
    0.stampa log [monitor / nome file]\n\
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
    if(strcmp(word, "0") == 0)              command = r_log;   
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
    t_corsa  *orderCodeData[MAX_LENGTH_DATA], *orderDateData[MAX_LENGTH_DATA], *orderStartData[MAX_LENGTH_DATA], *orderStopData[MAX_LENGTH_DATA];
    int responseList[MAX_LENGTH_DATA], lenResponse, i, delayTot;
    char outputFile[30];
    FILE *fp_write;


    req.code=1;
    sort(req, data, orderCodeData, lenData);
    req.code=0;

    req.date=1;
    sort(req, data, orderDateData, lenData);
    req.date=0;

    req.start=1;
    sort(req, data, orderStartData, lenData);
    req.start=0;


    req.dest=1;
    sort(req, data, orderStopData, lenData);
    req.dest=0;

    switch(cmd){
        case r_log:             gets(outputFile);             break;
        case r_partenza:        gets( req.startCorsa);        break;
        case o_data:            
        case o_partenza:        
        case o_arrivo:          
        case o_codice:                                        break;
        case r_errore:
        default:             return 1;  //Error handling
    }


    if(cmd==r_log){
        lenResponse=lenData;
        fp_write=fopen(outputFile, "w");
    }
    else if(cmd==r_partenza)
        lenResponse = queryDicotomica(req, data, lenData, responseList);
    else
        lenResponse=lenData;
        


    if(lenResponse > 0){

        for(i=0 ; i<lenResponse ; i++){
            if(cmd==r_log)
                corsa=data[i];
            else if(cmd==r_partenza)
                corsa=data[responseList[i]];
            else{
                if(cmd==o_codice)
                    corsa = *orderCodeData[i];
                if(cmd==o_data)
                    corsa = *orderDateData[i];
                if(cmd==o_partenza)
                    corsa = *orderStartData[i];
                if(cmd==o_arrivo)
                    corsa = *orderStopData[i];
            }
            if(cmd==r_log && strcmp(outputFile,"monitor")!=0){
                
                fprintf(fp_write,"corsa %d: %s Da: %-15s A: %-15s Il: %d/%02d/%02d Partenza: %s Arrivo: %s Ritardo: %d\n", 
                        i, corsa.code, corsa.start, corsa.dest, corsa.date[0], corsa.date[1], corsa.date[2],
                        corsa.timeStart, corsa.timeEnd, corsa.delay);
            }
            else
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


int queryDicotomica(t_request req, t_corsa data[], int lenData, int res[]){
    int i, indexRes, valid, validDate, l, r, m, diff, sortedStr, j;
    t_corsa temp;

    l=0;
    r=lenData-1;
    indexRes=0;

    for(i=0;i<lenData-1;i++){
        for(j=0;j<lenData-i-1;j++){
            sortedStr = strcmp(data[j].start,data[j+1].start)>0;
            if(sortedStr){
                temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
            }
        }
    }

    while(r>=l){      
        m=(r+l)/2;
        
        diff=strncmp( data[m].start, req.startCorsa, (strlen(req.startCorsa)-1));

        if(diff>0){
            r=m-1;
        } else if(diff<0){
            l=m+1;
        } else if(diff==0){
            for(i=m; strncmp( data[i-1].start, req.startCorsa, (strlen(req.startCorsa)-1))==0 && i-1>0;i--);
            for(indexRes=0;strncmp( data[i].start, req.startCorsa, (strlen(req.startCorsa)-1))==0;i++, indexRes++){
                res[indexRes]=i;
            }
            return(indexRes);
        }
    }
    return(indexRes);
}

int handleFileInput(char fileName[], t_corsa data[]){
    int lenData, i;
    char c[MAX_CHAR_CORSA+1], s[MAX_CHAR_CORSA+1], d[MAX_CHAR_CORSA+1], ts[MAX_CHAR_CORSA+1], te[MAX_CHAR_CORSA+1];
    int a, m, g, dl, secondi, minuti, ore;
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
        sscanf(data[i].timeStart, "%d:%d:%d", &ore, &secondi, &minuti);
        data[i].timeStartInt = ore*3600 + minuti*60 + secondi;
    }

    fclose(fp);
    return lenData;
}

int dateCompare(int date1[3], int date2[3], int t1, int t2){
    int valid, d1,d2;

    // simple method wich converts aaaa mm gg in a integer aaaammgg for comparison
    d1 = date1[0]*10000+ date1[1]*100+ date1[2];
    d2 = date2[0]*10000+date2[1]*100+date2[2];

    
    if(d1!=d2)
        return d1>d2;
    else
        return t1>t2;
}

int sort(t_request req, t_corsa data[], t_corsa *sorted[], int lenData){
    int i,j, dateSort, partSort, destSort, codeSort, t1, t2, s, h, m;
    t_corsa *temp;

    for(i=0; i<lenData; i++){
        sorted[i]=&data[i];
    }

    for(i=0;i<lenData-1;i++){
        for(j=0;j<lenData-i-1;j++){
            dateSort= req.date==1 && dateCompare(sorted[j]->date,sorted[j+1]->date, sorted[j]->timeStartInt, sorted[j+1]->timeStartInt);
            codeSort= req.code==1 && strcmp(sorted[j]->code,sorted[j+1]->code)>0;
            partSort= req.start==1 && strcmp(sorted[j]->start,sorted[j+1]->start)>0;
            destSort= req.dest==1 && strcmp(sorted[j]->dest,sorted[j+1]->dest)>0;
            if(dateSort || codeSort || destSort || partSort){
                temp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = temp;
            }
        }
    }

    return(lenData);
}