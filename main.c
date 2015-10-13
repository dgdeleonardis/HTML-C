#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

int main(int argc, char** argv){
    char temporaneo[MAX_STRLEN]; //stringa temporanea
    int flag = 0; //flag che segnala se un elemento è già presente in lista-ruoli
    FILE *p_txt; //puntatore a file lista.txt
    FILE *p_html; //puntatore a file index.html
    lista *p_first, *p_temp, *p_scroll; //puntatori per gestione della lista
    stampa value; //record che va ad essere stampato nel value
    
    p_txt = fopen("lista.txt", "r"); //Apertura file .txt

    p_first = (lista*)malloc(sizeof(lista)); //Creazione primo blocco della lista-ruoli e controllo
    if(p_first == NULL)
        exit(1);
    
    fscanf(p_txt, "%[^-]-%[^\n]\n", temporaneo, p_first->ruolo); //Salvataggio su puntatoreLista->ruolo del ruolo del primo nome-ruolo
    p_scroll = p_first; //Assegnazione al puntatore adibito allo scorrimento lista dell'indirizzo del primo elemento
    
       while(!feof(p_txt)) { //Condizione : Finchè il file non arriva al termine
        p_temp = (lista*)malloc(sizeof(lista)); //Alloca un elemento temporaneo con controllo
        if(p_temp == NULL)
            exit(2);
           
           fscanf(p_txt, "%[^-]-%[^\n]\n", temporaneo, p_temp->ruolo); //Salvataggio su puntatoreLista->ruolo del ruolo del nome-ruolo in lettura
           flag = 0;
           while((p_scroll != NULL) && (flag != 1)) { //Condizione : Finché non finisce la lista e il flag di controllo non è vero
               if(!(strcmp(p_scroll->ruolo, p_temp->ruolo))) //Compara il ruolo dell'elemento puntato dallo scorritore con l'elemento temporaneo
                    flag = 1; //Se sono uguali poni il flag = 1
                    
               p_scroll = p_scroll->next; //Assegni al puntatore di scorrimento l'indirizzo del prossimo elemento della lista (in modo da scorrere)
           }

           if(!flag) { //Quando viene comparata tutta la lista con il blocco temporaneo viene controllato il valore di flag
               p_temp->next = p_first; //Se è falso (quindi si tratta di un nuovo ruolo, ancora non immesso nella lista) viene
               p_first = p_temp; // aggiunto il blocco temporaneo nella lista
            }
           p_scroll = p_first;
        }
    fclose(p_txt); //Chiudo il file .txt
      
    p_html = fopen("index.html", "w"); //Apro il file .html e controllo
        if(p_html == NULL)
        exit(3);
      
      fprintf(p_html, "<html>\n" //Genero il file .html tramite funzione fprintf fino al popolamento del <select>
            "<head>\n"
            "</head>\n"
            "<body>\n"
            "<select id=\"lista_ruoli\" onchange=\"funzione()\">\n");
      
      p_scroll = p_first; //Assegnazione al puntatore adibito allo scorrimento lista dell'indirizzo del primo elemento
      p_txt = fopen("lista.txt", "r");
      while(!(p_scroll == NULL)) { //Condizione : finchè non finisce la lista (finché i ruoli non sono finiti)
           //Apro il file .txt che andrò a scansionare
          if(p_txt == NULL)
            exit(4);
          
          fprintf(p_html ,"<option value=\""); //Scrivo fino a value =" sul file .html
          
          while(!(feof(p_txt))) { //Condizione : finchè non finisce il file scansiono i nome-ruolo
              fscanf(p_txt, "%[^-]-%[^\n]\n", value.nome, value.ruolo); 
              if(!(strcmp(value.ruolo, p_scroll->ruolo))) //e in base al ruolo di riferimento
                  fprintf(p_html, "%s; ", value.nome); //stampo i nomi che hanno quel determinato ruolo
          } 
          rewind(p_txt); //Riavvolgo il file
          fprintf(p_html, "\"> %s </option>\n", p_scroll->ruolo); //Completo l'ultima parte del <option>
          p_scroll = p_scroll->next; //e passo al prossimo ruolo
          }
         
    fprintf(p_html, "</select>\n" //Concludo il file .html con i restanti tag e script necessari per il funzionamento della pagina
            "<p id=\"demo\"></p>\n"
            "<script>\n"
            "function funzione() {\n"
            "var x = document.getElementById(\"lista_ruoli\").value;\n"
            "document.getElementById(\"demo\").innerHTML = \"Nomi : \" + x;}\n"
            "</script>\n"
            "</body>\n"
            "</html>");
    
    return (EXIT_SUCCESS);
}

