#include <stdio.h>


int gcd(int a, int b);

int main(){
    int a,b;

    printf("%d", gcd(48, 12));
}

int gcd(int a, int b){
    int result, temp;

    if(b>a){
        temp=b;
        b=a;
        a=temp;
    }

    if(b==1){
        return(1);
    }

    if(a==b){
        return(a);
    }

    if(a%2==0 && b%2==0){
        result = 2 * gcd(a/2, b/2);
    } else if (a%2!=0 && b%2==0){
        result = gcd(a, b/2);
    } else if (a%2==0 && b%2!=0){
        result = gcd(a/2, b);
    } else if (a%2!=0 && b%2!=0){
        result = gcd((a-b)/2, b);
    }



    return(result);
}