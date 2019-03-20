#ifndef __FONCTIONS_GESTION_TRANSFORMATION

#define __FONCTIONS_GESTION_TRANSFORMATION

#include <stdio.h>
#include <stdlib.h>

#include "image.h"
#include "transformation.h"

/*Les éléments de l'énumération et ceux du vecteur doivent se correspondre un à un.*/
Transformation* preparationTransfo(int*tailleVectTransfo, int argc,char *argv[],typeSortie *type);

void generalTransfo(Transformation *vectTransfo,int tailleVectTransfo,Image **img);
void appliquerTransfo(Image **img,Transformation *transfo);

int compterTransfo(int argc, char *argv[],char *choixTransfo[],unsigned int nbChoixTransfo);

Transformation* creerVectTransfo(int tailleVectTransfo,int argc, char *argv[],char *choixTransfo[], unsigned int nbChoixTransfo,int nbParametresTransfo[]);

void afficherVectTransfo(int tailleVectTransfo, Transformation *vectTransfo);

void libererVectTransfo(Transformation *vectTransfo);

#endif