#ifndef __FONCTIONS_TRANSFORMATION

#define __FONCTIONS_TRANSFORMATION

#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "fonctions_annexes.h"

#define NB_PARAMETRES_MAX_TRANSFORMATION 3

typedef enum {CONSEILLERDESGRACESHORIZONTAL,CONSEILLERDESGRACESVERTICAL,REDIMENSIONNER,PIXELISER,COMPRESSER} nomTransformation;

typedef struct {
	nomTransformation nom;
	int nombreParametres;
	unsigned int parametres[NB_PARAMETRES_MAX_TRANSFORMATION];
} Transformation;

Transformation* creerTransfo(nomTransformation nom, int nombresParametres, unsigned int parametres[NB_PARAMETRES_MAX_TRANSFORMATION]);

void miroirVertical(Image *img);
void miroirHorizontal(Image *img);

void redimensionner(Image **img, Transformation *transfo);
void pixeliser(Image *img, Transformation *transfo);

void changerLumMax(Image *img, Transformation *transfo);

#endif