#include<stdio.h>
#include<limits.h>
#include<float.h>

int main(){
    //dichiarazione di variabili utilizzando tutti i tipi dati e i relativi qualificatori
    char c = 'a';
    short int si = SHRT_MAX;
    int i = INT_MAX;
    long int li = LONG_MAX;
    unsigned char uc = UCHAR_MAX;
    unsigned short int usi = USHRT_MAX;
    unsigned int ui = UINT_MAX;
    unsigned long int uli = ULONG_MAX;
    float f = FLT_MAX;
    double d = DBL_MAX;
    long double ld = LDBL_MAX;

    //stampa dei valori delle variabili
    printf("Valore char: %c\n", c);
    printf("Valore short int: %hi\n", si);
    printf("Valore int: %d\n", i);
    printf("Valore long int: %li\n", li);
    printf("Valore unsigned char: %hhu\n", uc);
    printf("Valore unsigned short int: %hu\n", usi);
    printf("Valore unsigned int: %u\n", ui);
    printf("Valore unsigned long int: %lu\n", uli);
    printf("Valore float: %f\n", f);
    printf("Valore double: %lf\n", d);
    printf("Valore long double: %Lf\n", ld);

    //stampa dell'occupazione di memoria delle variabili in byte
    printf("Occupazione di memoria char: %lu byte\n", sizeof(c));
    printf("Occupazione di memoria short int: %lu byte\n", sizeof(si));
    printf("Occupazione di memoria int: %lu byte\n", sizeof(i));
    printf("Occupazione di memoria long int: %lu byte\n", sizeof(li));
    printf("Occupazione di memoria unsigned char: %lu byte\n", sizeof(uc));
    printf("Occupazione di memoria unsigned short int: %lu byte\n", sizeof(usi));
    printf("Occupazione di memoria unsigned int: %lu byte\n", sizeof(ui));
    printf("Occupazione di memoria unsigned long int: %lu byte\n", sizeof(uli));
    printf("Occupazione di memoria float: %lu byte\n", sizeof(f));
    printf("Occupazione di memoria double: %lu byte\n", sizeof(d));
    printf("Occupazione di memoria long double: %lu byte\n", sizeof(ld));

    //stampa del numero di caratteri di ogni printf
    printf("Numero caratteri printf char: %d - ", printf("%c\n", c));
    printf("Numero caratteri printf short int: %d - ", printf("%hi\n", si));
    printf("Numero caratteri printf int: %d - ", printf("%d\n", i));
    printf("Numero caratteri printf long int: %d - ", printf("%li\n", li));
    printf("Numero caratteri printf unsigned char: %d - ", printf("%hhu\n", uc));
    printf("Numero caratteri printf unsigned short int: %d - ", printf("%hu\n", usi));
    printf("Numero caratteri printf unsigned int: %d - ", printf("%u\n", ui));
    printf("Numero caratteri printf unsigned long int: %d - ", printf("%lu\n", uli));
    printf("Numero caratteri printf float: %d - ", printf("%f\n", f));
    printf("Numero caratteri printf double: %d - ", printf("%lf\n", d));
    printf("Numero caratteri printf long double: %d - ", printf("%Lf\n", ld));

    //valori minimo e massimo ammissibili per ogni tipo di variabile
    printf("Valore minimo signed char: %d\n", SCHAR_MIN);
    printf("Valore massimo signed char: %d\n", SCHAR_MAX);
    printf("Valore minimo short int: %d\n", SHRT_MIN);
    printf("Valore massimo short int: %d\n", SHRT_MAX);
    printf("Valore minimo int: %d\n", INT_MIN);
    printf("Valore massimo int: %d\n", INT_MAX);
    printf("Valore minimo long int: %ld\n", LONG_MIN);
    printf("Valore massimo long int: %ld\n", LONG_MAX);
    printf("Valore minimo unsigned char: %d\n", 0);
    printf("Valore massimo unsigned char: %d\n", UCHAR_MAX);
    printf("Valore minimo unsigned short int: %d\n", 0);
    printf("Valore massimo unsigned short int: %hu\n", USHRT_MAX);
    printf("Valore minimo unsigned int: %d\n", 0);
    printf("Valore massimo unsigned int: %u\n", UINT_MAX);
    printf("Valore minimo unsigned long int: %lu\n", 0L);
    printf("Valore massimo unsigned long int: %lu\n", ULONG_MAX);
    printf("Valore minimo float: %f\n", -FLT_MAX);
    printf("Valore massimo float: %f\n", FLT_MAX);
    printf("Valore minimo double: %lf\n", -DBL_MAX);
    printf("Valore massimo double: %lf\n", DBL_MAX);
    printf("Valore minimo long double: %Lf\n", -LDBL_MAX);
    printf("Valore massimo long double: %Lf\n", LDBL_MAX);

    return 0;
}
