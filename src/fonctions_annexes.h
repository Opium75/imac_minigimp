#ifndef __FONCTIONS_ANNEXES

#define __FONCTIONS_ANNEXES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a,b) a-b> 0 ? a : b
#define max(a,b) min(b,a)
#define absolue(a) max(a,-a)


int comparerChainesLUT(char chaineArg[], char chaineLUT[]);
int correspondanceEnveloppe(char chaineArg[], char chaineEnveloppe[]);

/*On s'en sert avec des arguments d'énumérations, mais marche en plus générale.*/
int estElement(int e, int vecteur[], unsigned int dimension);

int puissance(int a,unsigned int n);

/*Élément inclu*/
int nombreVoisins(int rayon, int ligne, int colonne, unsigned int largeur, unsigned int hauteur);

double calculMoyenne(double moyennePrecedente,unsigned char termeSuivant, int n);

int arrondir(double r);

#endif