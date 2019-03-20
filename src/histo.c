#include "histo.h"

void lireCanauxEtLumPourHisto(Image *img, Histogramme *histo) {
	int i,j,k,v;
	unsigned long int lumMax=0;
	if(img->format == RVB) {
		for(i=0;i<3;i++) {
			for(k=0;k<histo->largeur;k++) {
				histo->valeurs[i][k] = 0;
			}
			for(j=0;j<img->largeur*img->hauteur;j++) {
					v = *((img->canaux[i])+j);
					histo->valeurs[i][v]+=1;
					if(histo->valeurs[i][v]>lumMax) lumMax=histo->valeurs[i][v];
				
			}
		}
	}
	else if(img->format == NDG) {
		for(k=0;k<histo->largeur;k++) {
				histo->valeurs[gris][k] = 0;
			}
			for(j=0;j<img->largeur*img->hauteur;j++) {
					v = *((img->canaux[gris])+j);
					histo->valeurs[gris][v]+=1;
					if(histo->valeurs[gris][v]>lumMax) lumMax=histo->valeurs[gris][v];
				
			}
	}
	histo->lumMax = lumMax;
	histo->format = img->format;
}

void histoVersImage(Image *imgHisto,Histogramme *histo) {
	int i,j,k,l;
	int estRempli;
	float palier;
	if(histo->format == RVB) {
		for(i=0;i<3;i++) {
			for(j=0;j<histo->largeur*histo->hauteur;j++) {
				k =(j%histo->largeur);
				l =histo->hauteur - (j/histo->largeur);
				palier = histo->valeurs[i][k]/(float)histo->lumMax*histo->hauteur;
				estRempli = (l<=(int)palier);
				if(estRempli) *(imgHisto->canaux[i]+j) = VAL_MAX;
				else *(imgHisto->canaux[i]+j) = 0;
			}
		}
	}
	else if(histo->format == NDG) {
		for(j=0;j<histo->largeur*histo->hauteur;j++) {
				k =(j%histo->largeur);
				l =histo->hauteur - (j/histo->largeur);
				palier = histo->valeurs[gris][k]/(float)histo->lumMax*histo->hauteur;
				estRempli = (l<=(int)palier);
				if(estRempli) *(imgHisto->canaux[gris]+j) = VAL_MAX;
				else *(imgHisto->canaux[gris]+j) = 0;
			}
	}
	imgHisto->format = histo->format;
}

Histogramme* creerEtRemplirHistogramme(Image*img, unsigned int largeur,unsigned int hauteur) {
	Histogramme *histo = malloc(sizeof(Histogramme));
	if(!histo) {
		printf("Échec de l'allocation dynamique pour l'histogramme (type Histogramme).\n");
		exit(EXIT_FAILURE);
	}
	histo->largeur = largeur;
	histo->hauteur = hauteur;
	histo->lumMax = 0;
	lireCanauxEtLumPourHisto(img,histo);
	return histo;
}

void libererHistogramme(Histogramme*histo) {
	free(histo);
}

Image* lireHisto(Image*img) {
	Histogramme *histo;
	Image* imgHisto;
	histo = creerEtRemplirHistogramme(img,LARGEUR_HISTO, HAUTEUR_HISTO);
	imgHisto = creerImage(histo->largeur,histo->hauteur,VAL_MAX,NEB);
	printf("Lum max : %lu\n",histo->lumMax);
	histoVersImage(imgHisto,histo);
	libererHistogramme(histo);
	return imgHisto;
}