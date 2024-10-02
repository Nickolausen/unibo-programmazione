/* Nicholas Magi, 0001113915 */
/* 
 * N.B.: La prova fa riferimento al file T1.
 * Valutazione della prova: 26/30 - per un'eventuale correzione, guarda il file 'source_08-02-24.c'
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h> /* NULL check */

#define NR_PROFESSORI 200
#define NR_MATERIE 10
#define UNDEFINED_STR ""
#define UNDEFINED_INT -1

/* Struct inutilizzata - serve solo descrivere come sono disposti i dati all'interno del file */
typedef struct file_row {
    char id_studente[12 + 1];
    valutazione *voti;
} file_row;

typedef struct studente {
    char id_studente[12 + 1];
    valutazione *voti;

    /* Link al nodo successivo */
    struct studente *next;
} studente;

typedef struct valutazione {
    float voto;
    char id_materia;

    /* Link al nodo successivo */
    struct valutazione *next;
} valutazione;

typedef struct materia {
    char id_materia[12 + 1];
    char descrizione[80 + 1];
    char id_professore[12 + 1];
} materia;

typedef struct data {
    int giorno; 
    int mese;
    int anno;
} data;

typedef struct professore {
    char id_professore[12 + 1];
    char nome_e_cognome[120 + 1];
    data data_inizio;
} professore;

typedef struct media_valutazioni {
    float media;
    char id_materia[12 + 1];
} media_valutazioni; 

typedef struct pagella {
    media_valutazioni media;

    /* Link al nodo successivo */
    struct pagella *next;
} pagella;

/* HEAD INSERT nella Linked List */
void aggiungi_studente(studente **list, studente *new_stud)
{
    assert(new_stud != NULL);

    new_stud->next = *list;
    *list = new_stud;
}

/* HEAD INSERT nella Linked List */
void aggiungi_valutazione(valutazione **list, valutazione *new_grade)
{
    assert(new_grade != NULL);

    new_grade->next = *list;
    *list = new_grade;
}

/* HEAD INSERT nella Pila 'Pagella' */
void push_pagella(pagella **list, pagella *new_pagella)
{
    assert(new_pagella != NULL);

    new_pagella->next = *list;
    *list = new_pagella;
}

/* Funzione ausiliaria - ritorno l'elemento richiesto se presente in lista, NULL altrimenti */
studente *find_studente(studente *list, char *id_studente) 
{
    studente *current_node = list;

    while (current_node != NULL) /* Scorro la lista di studenti */
    {
        if (strcmp(current_node->id_studente, id_studente) == 0)
            return current_node;
        
        current_node = current_node->next;
    }

    return NULL;
}

/* Funzione ausiliaria - ritorno l'elemento richiesto se presente in lista, NULL altrimenti */
valutazione *find_materia(valutazione *list, char *id_materia) 
{
    valutazione *current_node = list; 

    while (current_node != NULL) 
    {
        if (strcmp(current_node->id_materia, id_materia) == 0)
            return current_node;
        
        current_node = current_node->next;
    }

    return NULL;
}

/* Funzione ausiliaria - chiamata in 'prepara_pagella_studente()' */
valutazione *find_all_valutazioni(valutazione *list, char *id_materia, int *nr_voti)
{
    valutazione *out_list = NULL;
    valutazione *current_node = list;

    while (current_node != NULL) 
    {
        if (strcmp(current_node->id_materia, id_materia) == 0)
        {
            aggiungi_valutazione(out_list, current_node);
            *nr_voti++;
        } 
    }

    return out_list;
}

/* Funzione ausiliaria - chiamata in 'prepara_pagella_studente()' */
float calcola_media(valutazione *voti, int nr_voti) 
{
    valutazione *current_node = voti;
    float media = 0;

    while (current_node != NULL) 
    {
        media += current_node->voto;
        current_node = current_node->next;
    }

    return media / nr_voti;
}


/* Funzione ausiliaria - ritorno l'elemento richiesto se presente in lista, NULL altrimenti */
char *find_id_professore_by_materia(materia *materie, char *id_materia) 
{
    for (int i = 0; i < NR_MATERIE; i++) 
    {
        if (strcmp(materie[i].id_materia, id_materia) == 0)
            return materie[i].id_professore;
    }

    return NULL;
}

/* Funzione ausiliaria - ritorno l'elemento richiesto se presente nel vettore, un valore di default altrimenti */
professore find_professore(professore *professori, char *id_professore) 
{
    professore output = (professore){UNDEFINED_STR, UNDEFINED_STR, (data){UNDEFINED_INT, UNDEFINED_INT, UNDEFINED_INT}};
    for (int i = 0; i < NR_PROFESSORI; i++) 
    {
        if (strcmp(professori[i].id_professore, id_professore) == 0)
            output = professori[i];
    }

    return output;
}

studente *leggi_file(char *fileName) 
{
    studente *out_list = NULL;
    FILE *pFile = fopen(fileName, "r");
    assert(pFile != NULL);

    while (!feof(pFile)) /* Il ciclo continua finché il cursore in lettura del file non ha raggiunto la fine del file */
    {
        char id_studente[12 + 1];
        fscanf(pFile, "%s", id_studente);

        /* Cerco se lo studente è già stato inserito nella lista */
        studente *stud = find_studente(out_list, id_studente);
        if (stud == NULL) /* Se non esiste, allora lo creo e lo aggiungo */
        {
            stud = (studente *)malloc(sizeof(studente));
            assert(stud != NULL); /* NULL check - controllo che la memory allocation sia andata a buon fine */

            strcpy(stud->id_studente, id_studente);
            stud->next = NULL;
            stud->voti = NULL;

            aggiungi_studente(&out_list, stud);
        }

        /* Da qui in poi lavoro su un elemento 'studente' che può essere già stato inserito in lista, oppure un nuovo studente che ho appena creato */

        /* Leggo le 'n' coppie 'materia - valutazione' */
        /* Il ciclo continua finché il carattere successivo alla coppia di valori è ' '; se incontra il \n, il ciclo superiore inizia una nuova iterazione*/
        while (fgetc(pFile) == ' ') 
        {
            /* Creo la nuova valutazione */
            valutazione *new_valutazione = (valutazione *)malloc(sizeof(valutazione));
            assert(new_valutazione != NULL);

            fscanf(pFile, "%s %.2f", new_valutazione->id_materia, &(new_valutazione->voto));
            new_valutazione->next = NULL;

            /* La inserisco nella lista delle sue valutazioni */
            aggiungi_valutazione(&(stud->voti), new_valutazione);
        }
    }

    fclose(pFile);
    return out_list;
}

pagella *prepara_pagella_studente(studente *elenco_studenti, char *id_studente) 
{
    studente *stud = find_studente(elenco_studenti, id_studente);
    assert(stud != NULL); /* mi assicuro che lo studente esista, altrimenti esco dal programma */

    pagella *out_pagella = NULL;

    /* Scorro tutte le sue valutazioni */
    valutazione *current_node = stud->voti;
    valutazione *materie_viste = NULL;

    while (current_node != NULL)
    {
        int nr_voti = 0;
        valutazione *current_materia = find_materia(materie_viste, current_node->id_materia);
        if (current_materia == NULL) /* Se non è una materia che avevo già incontrato, allora calcolo la media per quella materia e la segno come 'già vista' */
        {
            /* Ottengo tutte le valutazioni per una determinata materia */
            current_materia = find_all_valutazioni(elenco_studenti, current_materia->id_materia, &nr_voti);

            /* Preparo un elemento della pagella */
            pagella *new_element = (pagella *)malloc(sizeof(pagella));
            assert(new_element != NULL);

            strcpy(new_element->media.id_materia, current_materia->id_materia);
            new_element->media.media = calcola_media(current_materia, nr_voti);

            /* segno la materia corrente come 'già vista' */
            aggiungi_valutazione(&materie_viste, current_materia);
            
            /* aggiungo un nuovo elemento alla pagella */
            push_pagella(&out_pagella, new_element);
        }

        current_node = current_node->next;
    }

    /* elimino la lista di supporto */
    free(materie_viste);
    return out_pagella;
}

void stampa_pagella_studente(pagella *pagella_da_stampare, professore *professori, materia *materie) 
{
    pagella *current_node = pagella_da_stampare;

    while (current_node != NULL) /* Scorro tutti gli elementi della pagella */
    {
        /* Cerco il professore che insegna quella determinata materia (con funzioni ausiliarie per migliorare la leggibilità del codice) */
        professore prof = 
            find_professore(professori, find_id_professore_by_materia(materie, current_node->media.id_materia));

        /* Error check - mi assicuro che il prof in questione esista nel 'database' */
        assert(strcmp(prof.id_professore, UNDEFINED_STR) != 0);

        puts("------");
        printf("Materia: %s - Media: %.2f\n", current_node->media.id_materia, current_node->media.media);
        printf("Insegnata da: %s - in servizio dal: %d/%d/%d.\n", prof.nome_e_cognome, 
            prof.data_inizio.giorno,
            prof.data_inizio.mese,
            prof.data_inizio.anno);
        puts("------");

        current_node = current_node->next;
    }
}

int main() 
{
    professore professori[NR_PROFESSORI]; /* Vettore dato e ordinato */
    materia materie[NR_MATERIE]; /* Vettore dato e ordinato */

    studente *elenco_studenti = leggi_file("studenti.txt");
    pagella *pagella_stud1 = prepara_pagella_studente(elenco_studenti, "2-221");
    stampa_pagella_studente(pagella_stud1, professori, materie);

    pagella *pagella_stud2 = prepara_pagella_studente(elenco_studenti, "2-145");
    stampa_pagella_studente(pagella_stud2, professori, materie);

    return EXIT_SUCCESS;
}
