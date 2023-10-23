#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define LENGHT(a)(int)(sizeof(a)/sizeof(a[0]))


void CambiaCaratteri(char *pointer,int inizio, int fine){
    *(pointer+inizio)='*';
    for(int i=0;i<fine-1;i++){
        for (int j = inizio+1 ; j < 50 -1; j++)  
        {  
            *(pointer+j) = *(pointer+j+1);  
        } 
    }
}

bool ControlloUguali(char stringa1[], char stringa2[], int pos, int len)
{
    int i=0;
    char substring[1000];
 
    while (i < len) {
        substring[i] = stringa1[pos + i - 1];
        i++;
    }
    return strncmp(substring, stringa2, len);
    
}

int main(){
    char stringa1[100];
    int lung1=0;
    char lettura=' ';
    printf("Scrivi la prima stringa: ");
    while((lettura=getchar())!='\n'&& lung1<LENGHT(stringa1)){
        stringa1[lung1]=lettura;
        lung1++;
    }

    char stringa2[lung1];
    int lung2=0;
    lettura=' ';
    printf("Scrivi la seconda stringa che deve essere contenuta nella prima: ");
    while((lettura=getchar())!='\n'&& lung2<LENGHT(stringa2)){
        stringa2[lung2]=lettura;
        lung2++;
    }

    bool cambio=false;
    for(int i=0;i<lung1;i++){
        if(stringa1[i]==stringa2[0]){
            cambio = ControlloUguali(stringa1, stringa2, i, lung2);
        }     
        if(cambio){
            CambiaCaratteri(stringa1,i,lung2);
            lung1-=(lung2-1);
        }
        cambio=false;
    }
    printf("\nLa tua stringa finale: ");
    for(int i=0;i<lung1;i++){
        printf("%c", stringa1[i]);
    }
    printf("\n");

    return 0;
}