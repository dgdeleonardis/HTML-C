#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRLEN 255

 void funzioneDiControllo(void* puntatore);

struct s_record{ //elemento della lista-ruoli
    char ruolo[MAX_STRLEN];
    struct s_record *next;
};

struct s_stampa { //struct per salvataggio da file dei nome-ruolo
    char nome[MAX_STRLEN];
    char ruolo[MAX_STRLEN];
};
//definizioni di due nuove variabili
typedef struct s_stampa voce;
typedef struct s_record record;

int main(int argc, char** argv){
    char temporaneo[MAX_STRLEN]; //stringa temporanea
    int flag = 0; //flag che segnala se un elemento è già presente in lista-ruoli
    FILE *puntatoreTxt; //puntatore a file lista.txt
    FILE *puntatoreHtml; //puntatore a file index.html
    record *puntatoreLista, *puntatoreTemp, *puntatoreScorrimento; //puntatori per gestione della lista
    voce nome_ruolo; //record
    
    puntatoreTxt = fopen("lista.txt", "r"); //Apertura file .txt

    puntatoreLista = (record*)malloc(sizeof(record)); //Creazione primo blocco della lista-ruoli e controllo
    funzioneDiControllo((void*) puntatoreLista);
    
    fscanf(puntatoreTxt, "%[^-]-%[^\n]\n", temporaneo, puntatoreLista->ruolo); //Salvataggio su puntatoreLista->ruolo del ruolo del primo nome-ruolo
    puntatoreScorrimento = puntatoreLista; //Assegnazione al puntatore adibito allo scorrimento lista dell'indirizzo del primo elemento
    
       while(!feof(puntatoreTxt)) { //Condizione : Finchè il file non arriva al termine
           puntatoreTemp = (record*)malloc(sizeof(record)); //Alloca un elemento temporaneo con controllo
           funzioneDiControllo((void*) puntatoreLista);
           
           fscanf(puntatoreTxt, "%[^-]-%[^\n]\n", temporaneo, puntatoreTemp->ruolo); //Salvataggio su puntatoreLista->ruolo del ruolo del nome-ruolo in lettura
           flag = 0;
           while((puntatoreScorrimento != NULL) && (flag != 1)) { //Condizione : Finché non finisce la lista e il flag di controllo non è vero
               if(!(strcmp(puntatoreScorrimento->ruolo, puntatoreTemp->ruolo))) //Compara il ruolo dell'elemento puntato dallo scorritore con l'elemento temporaneo
                    flag = 1; //Se sono uguali poni il flag = 1
                    
               puntatoreScorrimento = puntatoreScorrimento->next; //Assegni al puntatore di scorrimento l'indirizzo del prossimo elemento della lista (in modo da scorrere)
           }

           if(!flag) { //Quando viene comparata tutta la lista con il blocco temporaneo viene controllato il valore di flag
               puntatoreTemp->next = puntatoreLista; //Se è falso (quindi si tratta di un nuovo ruolo, ancora non immesso nella lista) viene
               puntatoreLista = puntatoreTemp; // aggiunto il blocco temporaneo nella lista
            }
           puntatoreScorrimento = puntatoreLista;
        }
      fclose(puntatoreTxt); //Chiudo il file .txt
      
      puntatoreHtml = fopen("index.html", "w"); //Apro il file .html e controllo
      funzioneDiControllo((void*) puntatoreLista);
      
      fprintf(puntatoreHtml, "<html>\n" //Genero il file .html tramite funzione fprintf fino al popolamento del <select>
            "<head>\n"
            "</head>\n"
            "<body>\n"
            "<select id=\"lista_ruoli\" onchange=\"funzione()\">\n");
      
      puntatoreScorrimento = puntatoreLista; //Assegnazione al puntatore adibito allo scorrimento lista dell'indirizzo del primo elemento
    
      while(!(puntatoreScorrimento == NULL)) { //Condizione : finchè non finisce la lista (finché i ruoli non sono finiti)
          puntatoreTxt = fopen("lista.txt", "r"); //Apro il file .txt che andrò a scansionare
          funzioneDiControllo((void*) puntatoreLista);
          
          fprintf(puntatoreHtml ,"<option value=\""); //Scrivo fino a value =" sul file .html
          
          while(!(feof(puntatoreTxt))) { //Condizione : finchè non finisce il file scansiono i nome-ruolo
              fscanf(puntatoreTxt, "%[^-]-%[^\n]\n", nome_ruolo.nome, nome_ruolo.ruolo); 
              if(!(strcmp(nome_ruolo.ruolo, puntatoreScorrimento->ruolo))) //e in base al ruolo di riferimento
                  fprintf(puntatoreHtml, "%s; ", nome_ruolo.nome); //stampo i nomi che hanno quel determinato ruolo
          } 
          fclose(puntatoreTxt); //Chiudo il file
          fprintf(puntatoreHtml, "\"> %s </option>\n", puntatoreScorrimento->ruolo); //Completo l'ultima parte del <option>
          puntatoreScorrimento = puntatoreScorrimento->next; //e passo al prossimo ruolo
          }
         
    fprintf(puntatoreHtml, "</select>\n" //Concludo il file .html con i restanti tag e script necessari per il funzionamento della pagina
            "<p id=\"demo\"></p>\n"
            "<script>\n"
            "function funzione() {\n"
            "var x = document.getElementById(\"lista_ruoli\").value;\n"
            "document.getElementById(\"demo\").innerHTML = \"Ruoli: \" + x\n;"
            "}\n"
            "</script>\n"
            "</body>\n"
            "</html>");
    
    return (EXIT_SUCCESS);
}

void funzioneDiControllo(void* puntatore) {
    if(puntatore == NULL)
        exit(1);
}
