#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char cesar_inverse(char clair, char cle){
    if((clair-cle) <= 0){
        return (char)(122 + (clair-cle));
    }
    else{
        return (char)(clair-cle) + 96;
    }
}

int main(int argc, char* agrv[]){

    char c = 'd';
    char cle = 'z';
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

    char cesar = cesar_inverse(c, cle);
    printf("%c\n", cesar);
}
