#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TAILLE_NOMBRE 100

//operations (place le resultat dans le premier parametre)
void modulo(int* a, int* n);
void exponentiationRapideSansModulo(int* a, int* b);
void multiplier(int* a, int* b);
void soustraire(int* a, int* b);
void ajouter(int* a, int* b);
void multiplierPar2(int* nombre);
void reduireDe1(int* nombre);
void divisePar2(int* nombre);

int estPair(int* nombre);
// retourne 0 si a et b sont egaux, sinon 1
int comparer(int* a, int* b);

//fonctions pratiques
void libererNombre(int* nombre);
int* initialiser0();
int* initialiser1();
int* decimal_to_binary(int decimal);
int binary_to_decimal(int* binary);
void copier_nombre(int* a, int* b); //copie b dans a
int longueur_nombre(int* a); //nombre de bits d'un nombre sans les 0 inutiles
void afficher(int* nombre); // n'affiche pas les 0 inutiles


int main(int argc, char* agrv[]){
    /*int* un = initialiser1();
    int* zero = initialiser0();
    afficher(un);
    afficher(zero);
    if(comparer(un, zero) == 0){
        printf("Ils sont egaux\n");
    }
    if(estPair(zero)){
        printf("Le nombre est pair\n");
    }*/

    /*int* cinq = decimal_to_binary(5);
    afficher(cinq);
    reduireDe1(cinq);
    afficher(cinq);
    reduireDe1(cinq);
    afficher(cinq);*/

    /*int* sept = decimal_to_binary(7);
    afficher(sept);
    multiplierPar2(sept);
    afficher(sept);*/

    /*int* a = decimal_to_binary(3);
    int* b = decimal_to_binary(1);
    ajouter(a, b);
    afficher(a);*/

    int* a = decimal_to_binary(123);
    int* b = decimal_to_binary(13);
    modulo(a, b);
    afficher(a);

}

void modulo(int* a, int* n){
    int longueur_a = longueur_nombre(a);
    int longueur_n = longueur_nombre(n);
    int dif_longueur = longueur_a - longueur_n;
    int* k = initialiser0();
    int* nFOISk = initialiser0();

    while(dif_longueur > 0){
        //on calcule ce qu'on va retirer à a
        *(k+TAILLE_NOMBRE-dif_longueur) = 1;
        copier_nombre(nFOISk, n);
        multiplier(nFOISk, k);
        *(k+TAILLE_NOMBRE-dif_longueur) = 0;
        //on soustrait n * k
        soustraire(a, nFOISk);
        //tant que la longueur de a ne diminue pas, on retire n
        while(longueur_nombre(a) >= longueur_a){
            soustraire(a, n);
        }
        //on actualise les longueurs
        longueur_a = longueur_nombre(a);
        dif_longueur = longueur_a - longueur_n;
    }
}

void exponentiationRapideSansModulo(int* a, int* b){
    int* x = initialiser1();
    int* base = malloc(TAILLE_NOMBRE*sizeof(int));
    copier_nombre(base, a);
    int i;
    for(i = TAILLE_NOMBRE-1; i >= TAILLE_NOMBRE-longueur_nombre(b); i--){
        if(*(b+i) == 1) multiplier(x, base);
        multiplier(base, base);
    }
    copier_nombre(a, x);
}

void multiplier(int* a, int* b){
    int* result = initialiser0();
    int* tmp = malloc(TAILLE_NOMBRE*sizeof(int));
    copier_nombre(tmp, b);

    int i, j;
    for(i = TAILLE_NOMBRE-1; i >= 0; i--){
        if(*(a+i) == 1){
            copier_nombre(tmp, b);
            for(j = 0; j < TAILLE_NOMBRE-1-i; j++) multiplierPar2(tmp); //decalage
            ajouter(result, tmp);
        }
    }
    copier_nombre(a, result);
}

void soustraire(int* a, int* b){
    int i, j;
    for(i = TAILLE_NOMBRE-1; i >= 0; i--){
        //cas du 0-1
        if(*(a+i) - *(b+i) < 0){
            *(a+i) = 1;
            //gestion de la retenue
            j = i - 1;
            while(*(a+j) == 0){
                *(a+j) = 1;
                j--;
            }
            if(j < 0){
                printf("Soustraction impossible !\n");
                exit(-1);
            }
            else *(a+j) = 0;
        }
        //operation simple
        else *(a+i) = *(a+i) - *(b+i);
    }
}

void ajouter(int* a, int* b){
    int retenue = 0;
    int i, tmp;
    for(i = TAILLE_NOMBRE-1; i >= 0; i--){
        tmp = *(a+i) + *(b+i) + retenue;
        if(i == 0 && tmp >= 2){
            printf("La somme est trop grande !\n");
            exit(-1);
        }
        if(tmp == 3){
            *(a+i) = 1;
            retenue = 1;
        }
        else if(tmp == 2){
            *(a+i) = 0;
            retenue = 1;
        }
        else{
            *(a+i) = tmp;
            retenue = 0;
        }
    }
}

void multiplierPar2(int* nombre){
    if(*nombre == 1){
        afficher(nombre);
        printf(" est trop grand pour etre multiplier par 2\n");
        exit(-1);
    }
    int i;
    for(i = 0; i<TAILLE_NOMBRE-1; i++){
        *(nombre+i) = *(nombre+i+1);
    }
    *(nombre+TAILLE_NOMBRE-1) = 0;
}

void reduireDe1(int* nombre){
    int i = TAILLE_NOMBRE-1;
    while(i>=0){
        if(*(nombre+i) == 0) *(nombre+i) = 1;
        else{
            *(nombre+i) = 0;
            break;
        }
        i--;
    }
}

void divisePar2(int* nombre){
    int i;
    for(i=TAILLE_NOMBRE-1; i > 0; i--){
        *(nombre+i) = *(nombre+i-1);
    }
    *nombre = 0;
}

int estPair(int* nombre){
    return *(nombre+TAILLE_NOMBRE-1) == 0;
}

int comparer(int* a, int* b){
    for(int i = 0; i<TAILLE_NOMBRE; i++){
        if(*(a+i) != *(b+i)){
            return 1;
        }
    }
    return 0;
}

void libererNombre(int* nombre){
}

int* initialiser0(){
    int* tab = malloc(TAILLE_NOMBRE*sizeof(int));
    for(int i = 0; i<TAILLE_NOMBRE; i++){
        *(tab+i) = 0;
    }
    return tab;
}

int* initialiser1(){
    int* tab = malloc(TAILLE_NOMBRE*sizeof(int));
    for(int i = 0; i<TAILLE_NOMBRE-1; i++){
        *(tab+i) = 0;
    }
    *(tab+TAILLE_NOMBRE-1) = 1;
    return tab;
}

int* decimal_to_binary(int decimal){
    int* binary = malloc(TAILLE_NOMBRE*sizeof(int));
    int n = decimal;
    int i = 0;
    while(n > 0){
        *(binary+TAILLE_NOMBRE-1-i) = n%2;
        n = n/2;
        i++;
    }
    return binary;
}

int binary_to_decimal(int* binary){
    int decimal = 0;
    int i;
    for(i = TAILLE_NOMBRE-1; i >= 0; i--){
        decimal += *(binary+i) * pow(2,TAILLE_NOMBRE-1-i);
    }
    return decimal;
}

void copier_nombre(int* a, int* b){
    int i;
    for(i = 0; i<TAILLE_NOMBRE; i++){
        *(a+i) = *(b+i);
    }
}

int longueur_nombre(int* a){
    int i = 0;
    while(i < TAILLE_NOMBRE-1 && *(a+i) == 0) i++;
    return TAILLE_NOMBRE-i;
}

void afficher(int* nombre){
    int i = 0;
    while(i < TAILLE_NOMBRE-1 && *(nombre+i) == 0) i++;
    int j;
    for(j = i; j<TAILLE_NOMBRE; j++){
        printf("%d", *(nombre+j));
    }
    printf(" (%d)\n", binary_to_decimal(nombre));
}
