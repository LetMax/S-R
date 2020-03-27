#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define TAILLE_NOMBRE 100

//operations
int* nombrePremierMersenne();
int estPremierAvec(int* a, int* b); //0 si oui, 1 sinon
int* euclideEtendu(int* a, int* b);
int* modulo(int* a, int* n);
int* exponentiationRapideSansModulo(int* a, int* b);
int* multiplier(int* a, int* b);
int* soustraire(int* a, int* b);
int* ajouter(int* a, int* b);
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
    srand(time(NULL));
    printf("Le programme ne gere pas des entiers assez grands pour assurer que les nombres soient premiers de Mersenne\n");
    for(int i = 0; i < 5; i++){
        afficher(nombrePremierMersenne());
    }
    return 0;
}

int* nombrePremierMersenne(){
    int* resultat = initialiser0();
    int* deux = initialiser1();
    deux = ajouter(deux, deux);
    int randomValue;
    randomValue = rand()%20+2;
    resultat = soustraire(exponentiationRapideSansModulo(deux,decimal_to_binary(randomValue)),initialiser1());
    return resultat;
}

int estPremierAvec(int* a, int* b){
    comparer(euclideEtendu(a,b),initialiser1());
}

int* euclideEtendu(int* a, int* b){
    int* resultat = initialiser0();
    int* zero = initialiser0();

    int* copie_a = initialiser0();
    copier_nombre(copie_a, a);

    int* copie_b = initialiser0();
    copier_nombre(copie_b, b);

    int* reste = modulo(copie_a, copie_b);

    while(comparer(reste, zero) == 1){
        afficher(reste);

        copier_nombre(resultat, reste);
        copier_nombre(copie_a, copie_b);
        copier_nombre(copie_b, reste);
        reste = modulo(copie_a, copie_b);
    }
    return resultat;
}

int* modulo(int* a, int* n){
    int quotient = 0;
    int* k = initialiser0();
    int* nFOISk = initialiser0();
    int* resultat = initialiser0();
    copier_nombre(resultat, a);

    int longueur_resultat = longueur_nombre(resultat);
    int longueur_n = longueur_nombre(n);
    int dif_longueur = longueur_resultat - longueur_n;

    while(binary_to_decimal(resultat) > binary_to_decimal(n)){
        //on calcule ce qu'on va retirer au resultat
        *(k+TAILLE_NOMBRE-dif_longueur) = 1;
        quotient += binary_to_decimal(k);
        nFOISk = multiplier(n, k);
        *(k+TAILLE_NOMBRE-dif_longueur) = 0;
        //on soustrait n * k
        resultat = soustraire(resultat, nFOISk);
        //tant que la longueur du resultat ne diminue pas, on retire n
        while(longueur_nombre(resultat) >= longueur_resultat || binary_to_decimal(resultat) >= binary_to_decimal(n)){
            resultat = soustraire(resultat, n);
            quotient++;
        }
        //on actualise les longueurs
        longueur_resultat = longueur_nombre(resultat);
        dif_longueur = longueur_resultat - longueur_n;
    }
    printf("Quotient euclidien de %d/%d = %d\n", binary_to_decimal(a), binary_to_decimal(n), quotient);
    return resultat;
}

int* exponentiationRapideSansModulo(int* a, int* b){
    int* x = initialiser1();
    int* base = malloc(TAILLE_NOMBRE*sizeof(int));
    copier_nombre(base, a);
    int i;
    for(i = TAILLE_NOMBRE-1; i >= TAILLE_NOMBRE-longueur_nombre(b); i--){
        if(*(b+i) == 1) x = multiplier(x, base);
        base = multiplier(base, base);
    }
    return x;
}

int* multiplier(int* a, int* b){
    int* resultat = initialiser0();
    int* tmp = malloc(TAILLE_NOMBRE*sizeof(int));
    copier_nombre(tmp, b);

    int i, j;
    for(i = TAILLE_NOMBRE-1; i >= 0; i--){
        if(*(a+i) == 1){
            copier_nombre(tmp, b);
            for(j = 0; j < TAILLE_NOMBRE-1-i; j++) multiplierPar2(tmp); //decalage
            resultat = ajouter(resultat, tmp);
        }
    }
    return resultat;
}

int* soustraire(int* a, int* b){
    int* resultat = initialiser0();
    copier_nombre(resultat, a);
    int i, j;
    for(i = TAILLE_NOMBRE-1; i >= 0; i--){
        //cas du 0-1
        if(*(resultat+i) - *(b+i) < 0){
            *(resultat+i) = 1;
            //gestion de la retenue
            j = i - 1;
            while(*(resultat+j) == 0){
                *(resultat+j) = 1;
                j--;
            }
            if(j < 0){
                printf("Soustraction impossible !\n");
                exit(-1);
            }
            else *(resultat+j) = 0;
        }
        //operation simple
        else *(resultat+i) = *(resultat+i) - *(b+i);
    }
    return resultat;
}

int* ajouter(int* a, int* b){
    int* resultat = initialiser0();
    copier_nombre(resultat, a);
    int retenue = 0;
    int i, tmp;
    for(i = TAILLE_NOMBRE-1; i >= 0; i--){
        tmp = *(resultat+i) + *(b+i) + retenue;
        if(i == 0 && tmp >= 2){
            printf("La somme est trop grande !\n");
            exit(-1);
        }
        if(tmp == 3){
            *(resultat+i) = 1;
            retenue = 1;
        }
        else if(tmp == 2){
            *(resultat+i) = 0;
            retenue = 1;
        }
        else{
            *(resultat+i) = tmp;
            retenue = 0;
        }
    }
    return resultat;
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
