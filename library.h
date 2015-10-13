#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//lista #define
#define MAX_STRLEN 255

//struct elemento lista
struct s_elemento{ //elemento della lista-ruoli
    char ruolo[MAX_STRLEN];
    struct s_elemento *next;
};
//struct ausiliare per scrittura su file html
struct s_stampa { //struct per salvataggio da file dei nome-ruolo
    char nome[MAX_STRLEN];
    char ruolo[MAX_STRLEN];
};

//definizioni di due nuove variabili
typedef struct s_stampa stampa;
typedef struct s_elemento lista;
