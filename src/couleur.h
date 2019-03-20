#ifndef __FONCTIONS_COULEURS

#define __FONCTIONS_COULEURS

#include <stdio.h>
#include <stdlib.h>

#define MONOCHROME 1
#define TRICHROME 3


typedef enum {
	rouge,
	gris=rouge, /*iMPORTANT : POUR LE PARCOURS DES CANAUX*/
	vert,
	bleu,
	
} Couleur;

typedef enum {RVB,NDG,NEB} FormatCouleur;

int nbCanaux(FormatCouleur format);

#endif