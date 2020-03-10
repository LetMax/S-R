#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* dechiffrer(char* chaine, char* cle);
char cesar_inverse(char clair, char cle);

int main(int argc, char* agrv[]){
    return 0;
}

char* dechiffrer(char* chaine, char* cle){
    char* resultat = malloc(500*sizeof(char));

}

char cesar_inverse(char clair, char cle){
    if((clair-cle)%96 < 97){
        return (char)((clair-cle)%96 + 70);
    }
    else{
        return (char)((clair-cle));
    }
}
