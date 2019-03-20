#ifndef _FONCTIONS_LUT

#define _FONCTIONS_LUT

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "enveloppe.h"
#include "image.h"
#include "entete.h"
#include "couleur.h"
#include "fonctions_annexes.h"

#define NB_PARAMETRES_MAX_LUT 3

typedef enum {ADDLUM,DIMLUM,ADDCON,DIMCON,FLOU,FLOU2,INVERT,NOIRETBLANC,SEPIA} nomLUT;

typedef struct {
	nomLUT nom;
	Enveloppe enveloppe;
	int nombreParametres;
	double parametres[NB_PARAMETRES_MAX_LUT];
}
LUT;

unsigned char lumierePlus(unsigned char point,LUT*lut);
unsigned char lumiereMoins(unsigned char point,LUT*lut);
unsigned char contrastePlus(unsigned char point,LUT*lut,unsigned char moyenneLum);
unsigned char contrasteMoins(unsigned char point,LUT*lut,unsigned char moyenneLum);
/*unsigned char noirEtBlanc(unsigned char point,unsigned char valeurNDG);*/
unsigned char inverser(unsigned char point);
unsigned char vieillephoto(unsigned char point,LUT*lut, Couleur canal, unsigned int ligne, unsigned int colonne, unsigned int largeur, unsigned int hauteur);

unsigned char flou(unsigned char point,LUT*lut, Image *img,Couleur canal,unsigned int ligne, unsigned int colonne);
unsigned char flou2(unsigned char point, LUT*lut, Image *img,Image *imgFloue, Couleur canal, unsigned int ligne, unsigned int colonne);

void ellipse(LUT*lut,unsigned int ligne, unsigned int colonne, unsigned int largeur, unsigned int hauteur, int effetBords);

unsigned char tronquerOctet(int valeur,unsigned char plancher,unsigned char plafond);

#endif