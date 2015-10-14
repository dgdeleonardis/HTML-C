#include "library.h"
lista *aggiuntaTesta(lista *first, lista *temp) {
    temp->next = first; //Se è falso (quindi si tratta di un nuovo ruolo, ancora non immesso nella lista) viene
    first = temp; // aggiunto il blocco temporaneo nella lista
    return first;
}

lista *popolamentoLista() {
    
    lista *scroll, *temp, *first;
    char temporaneo[MAX_STRLEN];
    int flag = 0;
     pFile = fopen("lista.txt", "r"); //Apertura file .txt

    first = (lista*)malloc(sizeof(lista)); //Creazione primo blocco della lista-ruoli e controllo
    if(first == NULL)
        exit(1);
    
    fscanf(pFile, "%[^-]-%[^\n]\n", temporaneo, first->ruolo); //Salvataggio su puntatoreLista->ruolo del ruolo del primo nome-ruolo
    scroll = first; //Assegnazione al puntatore adibito allo scorrimento lista dell'indirizzo del primo elemento
    while(!feof(pFile)) { //Condizione : Finchè il file non arriva al termine
        temp = (lista*)malloc(sizeof(lista)); //Alloca un elemento temporaneo con controllo
        if(temp == NULL)
            exit(2);
           
           fscanf(pFile, "%[^-]-%[^\n]\n", temporaneo, temp->ruolo); //Salvataggio su puntatoreLista->ruolo del ruolo del nome-ruolo in lettura
           flag = 0;
           while((scroll != NULL) && (flag != 1)) { //Condizione : Finché non finisce la lista e il flag di controllo non è vero
               if(!(strcmp(scroll->ruolo, temp->ruolo))) //Compara il ruolo dell'elemento puntato dallo scorritore con l'elemento temporaneo
                    flag = 1; //Se sono uguali poni il flag = 1
                    
               scroll = scroll->next; //Assegni al puntatore di scorrimento l'indirizzo del prossimo elemento della lista (in modo da scorrere)
           }

           if(!flag) { //Quando viene comparata tutta la lista con il blocco temporaneo viene controllato il valore di flag
               first = aggiuntaTesta(first, temp);
               scroll = first;
           }
        }
       
    fclose(pFile); //Chiudo il file .txt
}