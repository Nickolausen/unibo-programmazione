#include <stdio.h>
#include <math.h> 
//Per separare nel terminale
#define LINE_SPLITTER puts("\n-------------")
//Utilizzo per non dover resettare la variabile al suo stesso
//valore tutte le volte che ci faccio operazioni sopra
#define RESET_VARIABILE operCompatti1=6

/*
    Componenti del gruppo:
    > Nicholas Magi (nicholas.magi@studio.unibo.it);
    > Tommaso Maestri (tommaso.maestri@studio.unibo.it);
    > Riccardo Ventrucci (riccardo.ventrucci@studio.unibo.it);
    > Leonardo Perretta (leonardo.perretta2@studio.unibo.it);
*/

int main() 
{
    //definisco le variabili che utilizzo per gli operatori
    int operCompatti1=6, operCompatti2=3;

    printf("\nOperatori compatti:");

    //mando in output le varie tipologie di operatori ogni volta 
    //resettando la variabile su cui faccio le operazioni
    printf("\n    Op *= risultato: %.1d", operCompatti1*=operCompatti2);
    RESET_VARIABILE;

    printf("\n    Op -= risultato: %.1d", operCompatti1-=operCompatti2);
    RESET_VARIABILE;

    printf("\n    Op /= risultato: %.1d", operCompatti1/=operCompatti2);
    RESET_VARIABILE;

    printf("\n    Op += risultato: %.1d", operCompatti1+=operCompatti2);
    RESET_VARIABILE;

    printf("\n    Op modulo= risultato: %.1d \n", operCompatti1%=operCompatti2);
    LINE_SPLITTER;

    printf("\nOperatori relazionali:");
    if(5>4){
        printf("\n  5 è maggiore di 4");
    }
    if(5>=4){
        printf("\n  5 è maggiore o uguale a 4");
    }
    if(4<5){
        printf("\n  4 è minore di 5");
    }
    if(4<=5){
        printf("\n  4 è minore o uguale a 5");
    }
    if(4==4){
        printf("\n  4 è uguale a 4");
    }
    if(4!=5){
        printf("\n  4 è diverso da 5");
    }
    LINE_SPLITTER;

    printf("\n Operatori logici");
    if(5>4&&9>6){
        printf("\n  5 è maggiore di 4 e 9 è maggiore di 6");
    }
    if(5>4||1>9){
        printf("\n  5 è maggiore di 4 o 1 è maggiore di 9");
    }
    LINE_SPLITTER;

    printf("\nOperatori bitwise");
    int a=60,b=13;
    printf("\n  A&B= %d", a&b);
    printf("\n  A|B= %d", a|b);
    printf("\n  A^B= %d", a^b);
    printf("\n  ~A= %d", ~a);

    LINE_SPLITTER;
    

    //definisco le variabile per far vedere la differenza tra pre
    // e post incremento
    int c=5, d=5;
    printf("\nPre/Post-incrementi:");

    printf("\n    pre %.1d", c++);
    printf("\n    post %.1d \n", ++d);

    LINE_SPLITTER;
    LINE_SPLITTER;    

    //Comportamento scorretto
    printf("Comportamento Scorretto");
    int num1 = 100000, num2 = 100000, result_overflow;
    result_overflow = num1 * num2; // Overflow!
    printf("Overflow: %d\n", result_overflow);

    // Conversioni implicite
    int int_num = 42;
    double double_num = int_num; // Conversione implicita da int a double
    printf("Conversione implicita: %lf\n", double_num);

    // Operatori con side effect
    printf("Side Effect\n");
    int side_effect_a = 5;
    int side_effect_b = side_effect_a++;
    printf("a++ = %d, b = %d\n", side_effect_a, side_effect_b);

    
    LINE_SPLITTER;
    LINE_SPLITTER;

    //inizio con le funzioni di math.h
    printf("\nUtilizzo funzioni matematiche math.h\n");

    //definisco una variabile e faccio le varie operazioni di arrotondamento
    double x = -5.5;
    printf("\nIl valore del ceil di %.1f è %.1f \n", x, ceil(x));
    //arrotondamento difetto al multiplo del valore di riferimento più vicino
    printf("Il valore del floor di %.1f è %.1f. \n", x, floor(x));
    //valore assoluto
    printf("Il valore assoluto di %.1f è %.1f. \n", x, fabs(x));

    LINE_SPLITTER;

    //definisco una variabile e faccio le varie operazioni con i logaritmi
    double y = 1000.0;
    //ln
    printf("Il valore del logaritmo naturale di %.1f è %.4f \n", y, log(y));
    //log base 10
    printf("Del logaritmo base10 di %.4f invece è %.4f \n", y, log10(y));
    LINE_SPLITTER;

    //definisco una variabile e faccio le varie operazioni con le potenze
    double z = 10.0;
    printf("La radice quadrata di %.1f è %.4f \n", z, sqrt(z));
    printf("La potenza di %.1f al quadrato è %.1f \n", z, pow(z,2));
    printf("La e elevata alla %.1f è %.4f \n", z, exp(z));
    LINE_SPLITTER;

    //definisco una variabile e faccio le varie operazioni con le
    //funzioni trigonometriche
    double k = 10.0;
    printf("Il coseno di π è %.1f \n", cos(M_PI));
    printf("Il seno di π è %.1f \n", sin(M_PI));
    printf("Tangent is %.1f \n", tan(k));

    printf("Il acoseno di π è %.1f \n", acos(1));
    printf("Il aseno di π è %.1f \n", asin(1));
    printf("aTangent is %.1f \n", atan(k));
    printf("aTangent2 is %.1f \n", atan2(k,5));

    printf("Hyperbolic tangent of %.1f is %.1f \n", k, tanh(k));
    printf("Il coseno iperbolico di π è %.1f \n", cosh(M_PI));
    printf("Il seno iperbolico di π è %.1f \n", sinh(M_PI));
    
    LINE_SPLITTER;

    return 0;
}
