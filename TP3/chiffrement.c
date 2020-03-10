#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* vigenere(char* claire, char* cle);
char cesar(char clair, char clee);
char* substr(char* src, int pos, int len);
char* simplifier_chaine(char* chaine);

int main(int argc, char* agrv[]){

    //chaine à chiffrée
    char* chaine = malloc(500*sizeof(char));
    printf("Entrez un texte que vous voulez chiffrer : ");
    scanf("%[^\n]s", chaine);

    while(getchar()!='\n');

    char* cle = malloc(500*sizeof(char));
    printf("Entrez la clée de chiffrement : ");
    scanf("%s", cle);

    char* claire = simplifier_chaine(chaine);

    printf("Texte non chiffre : %s\n", claire);

    char* chiffre = vigenere(claire, cle);

    printf("Texte chiffre : %s\n", chiffre);

    return 0;
}

char* vigenere(char* claire, char* cle){
    char* chiffre = malloc(500*sizeof(char));
    strcpy(chiffre, claire);
    int i = 0;

    while(chiffre[i]){
        chiffre[i] = cesar(claire[i], cle[i%strlen(cle)]);
        i++;
    }

    return chiffre;
}

char cesar(char clair, char cle){
    if((clair+cle)%96 > 26){
        return (char)((clair+cle)%96 + 70);
    }
    else{
        return (char)((clair+cle)%96 + 96);
    }
}

char* substr(char* src, int pos, int len) {
    char* dest = NULL;
    if(len > 0) {
        dest = (char *) malloc(len+1);
        strncat(dest, src+pos, len);
    }
    return dest;
}

char* simplifier_chaine(char* chaine){

    char* resultat = malloc(500*sizeof(char));
    strcpy(resultat, chaine);
    int i = 0;
    while(resultat[i]){

        if((resultat[i] >= 'a' && resultat[i] <= 'z') || (resultat[i] <= 'Z' && resultat[i] >= 'A')){
            resultat[i] = tolower(resultat[i]);
        }

        else{
            resultat = strcat(substr(resultat, 0, i), substr(resultat, i+1, strlen(resultat)));
            i--;
        }
        i++;
    }

    return resultat;
}
