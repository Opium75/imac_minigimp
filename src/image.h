#ifndef __FONCTIONS_IMAGE

#define __FONCTIONS_IMAGE

#include <stdio.h>
#include <stdlib.h>
#include "entete.h"
#include "couleur.h"
#include "fonctions_annexes.h"

/*Si l'image est en NDG, seul le canal rouge (=gris) est utilisé.*/
/*J'ai choisi d'intégrer les moyennes de luminosité à la structure par commodité, ça mange pas de pain.*/


typedef struct {
	FormatCouleur format;
	unsigned int largeur;
	unsigned int hauteur;
	unsigned char lumMax;
	unsigned char *canaux[3];
	unsigned char lumMoyCanaux[3];
} Image;

/*Créer une Image RVB dynamiquement de largeur largeur et hauteur hauteur, 
initialisée en noir, et renvoie son adresse mémoire.*/
Image* creerImage(unsigned int largeur,unsigned int hauteur, unsigned char lumMax, FormatCouleur format);

/*Convertit une image RVB en NDG, en utilisant le canal rouge (devient gris), et change la moyenne de luminosité*/
void RVBversNDG(Image *img);
void NDGversRVB(Image *img);

/*Suppose que imgDest est de même dimension que imgSrc.*/
void copierImage(Image*imgDest,Image*imgSrc);

void afficherImage(Image *img);
void libererImage(Image *img);

void lireCanaux(FILE *src,Image *img);
void ecrireCanaux(FILE *dest,Image *img);
Image* lireImage(FILE *src);

void ecrireImage(FILE*dest,Image*img);

#endif