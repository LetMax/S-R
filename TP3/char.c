#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char cesar(char clair, char cle){
    if((clair+cle)%96 > 26){
        return (char)((clair+cle)%96 + 70);
    }
    else{
        return (char)((clair+cle)%96 + 96);
    }
}

int main(int argc, char* agrv[]){

    char cle = 'a';
    /*char* s = malloc(50);
    strcpy(s, "texteenclair");

    char* chiffre = malloc(sizeof(s));
    strcpy(chiffre, s);

    int i = 0;
    while(chiffre[i]){
        chiffre[i] = cesar(s[i], cle);
        i++;
    }

    printf("Texte non chiffre : %s\n", s);
    printf("Texte chiffre : %s\n", chiffre);*/

    printf("%c\n", cesar('d', cle));
}
