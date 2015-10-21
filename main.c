#include "library.h"

int main(int argc, char** argv){
    FILE *p_txt, *p_html; //puntatore a file lista.txt e puntatore a file index.html
    lista *p_lista; //puntatori per gestione della lista
    
    p_lista = popolamentoLista();
    
    p_html = fopen("index.html", "w"); //Apro il file .html e controllo
        if(p_html == NULL)
        exit(3);
      
    fprintf(p_html, "<!DOCTYPE html>\n"
            "<html>\n" //Genero il file .html tramite funzione fprintf fino al popolamento del <select>
            "<head>\n"
            "</head>\n"
            "<body>\n"
            "\t<select id=\"lista\" autofocus onchange=\"stampa()\">\n");
      
    p_html = popolamentoSelect(p_lista, p_html);
         
    fprintf(p_html, "\t</select>\n"//Concludo il file .html con i restanti tag e script necessari per il funzionamento della pagina
            "\t<br>\n"
            "\t<textarea autofocus disabled id=\"nomi\"></textarea>\n"
            "\t<script>\n"
            "\t\tfunction stampa(){\n"
            "\t\t\tvar x = document.getElementById(\"lista\");\n"
            "\t\t\tvar array = JSON.parse(x.options[x.selectedIndex].value);\n"
            "\t\t\tarray = array.sort();\n"
            "\t\t\tvar i = 0;\n"
            "\t\t\tdocument.getElementById('nomi').innerHTML = \"\";\n"
            "\t\t\tfor(i=0;i<array.length;i++){\n"
            "\t\t\t\tdocument.getElementById('nomi').innerHTML += array[i]+\"&#013\";\n"
            "\t\t\t}\n"
            "\t\t}\n"
            "\t</script>\n"
            "</body>\n"
            "</html>");

    svuotaLista(p_lista);
    return (EXIT_SUCCESS);
}

