#ifndef _FONCTIONS_HISTO

#define _FONCTIONS_HISTO

#include "entete.h"
#include "image.h"
#include "option.h"
#include "couleur.h"

#define LARGEUR_HISTO VAL_MAX+1
#define HAUTEUR_HISTO (VAL_MAX+1)*2

/*Hauteur de l'histogramme est adaptable si besoin, mais la largeur doit rester égale à VAL_MAX+1*/

typedef struct {
	FormatCouleur format;
	unsigned int largeur;
	unsigned int hauteur;
	unsigned long int lumMax;
	unsigned int valeurs[3][VAL_MAX+1];
} Histogramme;
/*Histogramme structuré différemment qu'Image, pas nécessaire de faire une alloc dynamique, mais besoin de connaître la hauteur max.*/
/*
void calculHisto(Image*img,unsigned long int*hauteurMax,unsigned long int*hauteurMoyenne,unsigned int vectHisto[]);
void ecrireCanauxHisto(Image*histo,unsigned long int hauteurMax,unsigned int vectHisto[]);
Image* lireHisto(Image*img,unsigned long int*hauteurMoyenne);
*/

void lireCanauxEtLumPourHisto(Image *img, Histogramme *histo);

void histoVersImage(Image *imgHisto,Histogramme *histo);

Histogramme* creerEtRemplirHistogramme(Image *img, unsigned int largeur, unsigned int hauteur);

void libererHistogramme(Histogramme*histo);

Image* lireHisto(Image*img);

#endif