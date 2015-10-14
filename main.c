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
    
   
    p_first = popolamentoLista();
    
    
      
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

