#ifndef __FONCTIONS_ENVELOPPE

#define __FONCTIONS_ENVELOPPE

#include <stdio.h>
#include <stdlib.h>

#define NB_PARAMETRES_MAX_ENVELOPPE 3

typedef struct {
	enum {PARDEFAUT,ELLIPSE,RELLIPSE} forme;
	int nombreParametres;
	double parametres[NB_PARAMETRES_MAX_ENVELOPPE];
} Enveloppe;

#endif