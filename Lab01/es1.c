#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//ricerca dicotomica, stampa log


char *cercaRegexp(char *src, char *regexp);

int testValid(char chr, char *regexp, int index);

int main(){
    char *str;

    str=cercaRegexp("vot noto ciao", "vot.");
    if(str!=NULL){
        printf("%s", str);
    }
    else
        printf("null");
}

char *cercaRegexp(char *src, char *regexp){
    char *str, *tryStr, chr;
    int found, len, i, valid;

    found=0;
    str=NULL;
    tryStr=src;

    len=0;
    valid=1;
    
    for(i=0;i<strlen(regexp);i++){

        if(regexp[i]=='['){
            valid=0;
        }

        if(regexp[i]==']'){
            valid=1;
        }

        if(valid && regexp[i]!= '\\')
            len++;
    }



    while(strlen(tryStr)>=len){
        valid=1;
        for(i=0;i<len;i++){
            chr = *(tryStr+i);
            if(!testValid(chr, regexp, i))
                valid=0;
        }

        if(valid)
            return(tryStr);

        tryStr++;
    }


    return(NULL);
}

int testValid(char chr, char *regexp, int index){
    int valid, satisfied, correct, len, finished;
    int i,j;

    valid=1;
    len=0;
    correct=1;
    finished=0;

    for(i=0;i<strlen(regexp) && valid==1 && !finished;i++){

        if(len==index){
            if(regexp[i]=='[' && regexp[i+1]=='^'){
                for(j=i+2; regexp[j]!=']'; j++){
                    if(regexp[j]==chr)
                        valid=0;
                }
            }
            else if(regexp[i]=='['){
                satisfied=0;
                for(j=i+1; regexp[j]!=']'; j++){
                    if(regexp[j]==chr)
                        satisfied=1;
                }

                if(satisfied==0)
                    valid=0;
            }
            else if(regexp[i]=='.'){

            }
            else if(regexp[i]=='\\' && regexp[i+1]=='a'){
                if(!islower(chr))
                    valid=0;
            }
            else if(regexp[i]=='\\' && regexp[i+1]=='A'){
                if(!isupper(chr))
                    valid=0;
            }
            else if(regexp[i]!=chr){
                valid=0;
            }

            finished=1;
        }

        if(regexp[i]=='['){
            correct=0;
        }

        if(regexp[i]==']'){
            correct=1;
        }

        if(correct && regexp[i]!= '\\')
            len++;

        
    }



    return(valid);


}