#ifndef _FONCTIONS_GESTION_LUT

#define _FONCTIONS_GESTION_LUT

#include <stdio.h>
#include <stdlib.h>

#include "image.h"
#include "enveloppe.h"
#include "lut.h"
#include "fonctions_annexes.h"

/*Toujours au moins un paramètre*/




/*Les éléments de l'énumération et ceux du vecteur doivent se correspondre un à un.*/
LUT* preparationLUT(int*tailleVect, int argc,char *argv[],typeSortie *type);

void generalLUT(LUT*vectLUT,int tailleVect,Image*img);

unsigned char appliquerEnveloppe(Image*img,Image *imgFloue,unsigned char point, Couleur canal, unsigned int ligne, unsigned int colonne, LUT*lut);

unsigned char appliquerLUT(Image*img, Image *imgFloue,unsigned char point, Couleur canal, unsigned int ligne, unsigned int colonne, LUT*lut);
int compterLUT(int argc, char *argv[],char *choixLUT[],unsigned int nbChoixLUT);

LUT* creerVectLUT(int tailleVect,int argc, char *argv[],char *choixLUT[], char *choixEnveloppe[],unsigned int nbChoixLUT,int nbParametresLUT[], unsigned int nbChoixEnveloppe, int nbParametresEnveloppe[]);
void afficherVectLUT(int tailleVect, LUT*vectLUT);

void libererVectLUT(LUT*vectLUT);

#endif