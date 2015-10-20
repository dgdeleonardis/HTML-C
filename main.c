#include "library.h"

int main(int argc, char** argv){
    FILE *p_txt, *p_html; //puntatore a file lista.txt e puntatore a file index.html
    lista *p_lista; //puntatori per gestione della lista
    
    p_lista = popolamentoLista();
    
    p_html = fopen("index.html", "w"); //Apro il file .html e controllo
        if(p_html == NULL)
        exit(3);
      
    fprintf(p_html, "<html>\n" //Genero il file .html tramite funzione fprintf fino al popolamento del <select>
            "<head>\n"
            "</head>\n"
            "<body>\n"
            "<select id=\"lista_ruoli\" autofocus onchange=\"funzione()\">\n");
      
    p_html = popolamentoSelect(p_lista, p_html);
         
    fprintf(p_html, "</select>\n" //Concludo il file .html con i restanti tag e script necessari per il funzionamento della pagina
            "<p id=\"demo\"></p>\n"
            "<script>\n"
            "function funzione() {\n"
            "var x = document.getElementById(\"lista_ruoli\").value;\n"
            "document.getElementById(\"demo\").innerHTML = \"Nomi : \" + x;}\n"
            "</script>\n"
            "</body>\n"
            "</html>");

    svuotaLista(p_lista);
    return (EXIT_SUCCESS);
}

