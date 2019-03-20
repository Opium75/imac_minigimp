#ifndef __FONCTIONS_ENTETE

#define __FONCTIONS_ENTETE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLEMAX 3
#define VAL_MAX 255
#define TAILLE_TAMPON 10

#include "couleur.h"

/*Pour pallier le problème de décalage.*/
typedef enum {estNonModifiee,estModifiee,estHistogramme} typeSortie;

typedef enum {P4,P5,P6} FormatPBM;

typedef struct {
	FormatPBM format;
	unsigned char lumMax;
} Entete;

/* Retourne une erreur et arrête le programme si l'en-tête du fichier 
n'est pas conforme au format du projet.*/

void lireEntete(FILE *src,unsigned int*largeur,unsigned int*hauteur, unsigned char* lumMax, FormatCouleur *format);

void ecrireEntete(FILE*dest,unsigned int largeur, unsigned int hauteur, unsigned char lumMax, FormatCouleur format);

void lireCommentaire(FILE *src);
int correspondancePBM(char *choixFormatPBM[], unsigned int nbChoixFormatPBM, char chaineFormat[]);
FormatCouleur PBMaCouleur(FormatPBM formatPBM);

FormatCouleur couleuraPBM(FormatCouleur format);

#endif