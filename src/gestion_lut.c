#include "gestion_lut.h"


LUT* preparationLUT(int*tailleVect, int argc,char *argv[],typeSortie *type) {
	unsigned int nbChoixLUT=9;
	unsigned int nbChoixEnveloppe=3;
	char *choixLUT[] = {"ADDLUM","DIMLUM","ADDCON","DIMCON","FLOU","FLOU2","INVERT","NOIRETBLANC","SEPIA"};
	char *choixEnveloppe[] = {"PARDEFAUT","ELLIPSE","RELLIPSE"};
	/*Il est important de garder le même ordre que l'énumération.*/	
	int nbParametresLUT[] = {1,1,1,1,2,2,0,0,1};
	int nbParametresEnveloppe[] = {0,3,3};
	*tailleVect = compterLUT(argc,argv,choixLUT,nbChoixLUT);
	if(tailleVect>0) *type = estModifiee;
	return creerVectLUT(*tailleVect,argc,argv,choixLUT,choixEnveloppe,nbChoixLUT,nbParametresLUT,nbChoixEnveloppe,nbParametresEnveloppe);
}

void generalLUT(LUT*vectLUT,int tailleVect,Image*img) {
	int i=gris;
	int j,k;
	int kCoucheDebut=0;/*Joli*/
	int kCoucheFin = tailleVect;
	unsigned int colonne,ligne;
	unsigned char point;
	int nouvelleCouche=0;
	int appliquerCouche=0;
	nomLUT LUTPlanche[] = {FLOU,FLOU2};
	unsigned int nbLUTPlanche = 2;
	Image*imgCopie = creerImage(img->largeur,img->hauteur,img->lumMax,img->format);
	for(k=0;k<tailleVect;k++) {
		if(vectLUT[k].nom==NOIRETBLANC||vectLUT[k].nom==SEPIA) {
			RVBversNDG(img);
			if(vectLUT[k].nom==SEPIA) NDGversRVB(img);
			break;
		}
	}
	copierImage(imgCopie,img);
	afficherVectLUT(tailleVect,vectLUT);
	do {
			if(nouvelleCouche) {
				kCoucheDebut = kCoucheFin-1;
				appliquerCouche=1;
				nouvelleCouche=0;
			}
			if(img->format == RVB) {
				for(i=0;i<3;i++) {
					for(j=0;j<img->largeur*img->hauteur;j++) {
						colonne = (j%img->largeur);
						ligne = (j/img->largeur);
						for(k=kCoucheDebut;k<kCoucheFin;k++) {
							if(estElement(vectLUT[k].nom,LUTPlanche,nbLUTPlanche)&&!(appliquerCouche)) { /* Comparaison entre entiers, renvoie un avertissement mais est plus générale*/
								kCoucheFin = k+1;
								nouvelleCouche=1;
								break;
							}
							point = *(img->canaux[i]+j);
							if(appliquerCouche) {
								*(img->canaux[i]+j) = appliquerEnveloppe(imgCopie,img,point,i,ligne,colonne,&(vectLUT[k]));
							}
							else {
								*(img->canaux[i]+j) = appliquerEnveloppe(img,imgCopie,point,i,ligne,colonne,&(vectLUT[k]));
								*(imgCopie->canaux[i]+j) = *(img->canaux[i]+j);
							}		
						}
					}
				}
			}
			if(img->format == NDG) {
				for(j=0;j<img->largeur*img->hauteur;j++) {
						colonne = (j%img->largeur);
						ligne = (j/img->largeur);
						for(k=kCoucheDebut;k<kCoucheFin;k++) {
							if(estElement(vectLUT[k].nom,LUTPlanche,nbLUTPlanche)&&!(appliquerCouche)) {
								kCoucheFin = k+1;
								nouvelleCouche=1;
								break;
							}
							point = *(img->canaux[gris]+j);
							if(appliquerCouche) {
								*(img->canaux[gris]+j) = appliquerEnveloppe(imgCopie,img,point,gris,ligne,colonne,&(vectLUT[k]));
							}
							else {
								*(img->canaux[gris]+j) = appliquerEnveloppe(img,imgCopie,point,gris,ligne,colonne,&(vectLUT[k]));
								*(imgCopie->canaux[gris]+j) = *(img->canaux[gris]+j);
							}		
						}
					}
			}
			if(appliquerCouche) {
				if(kCoucheFin<tailleVect) {
					copierImage(imgCopie,img);
					kCoucheDebut = kCoucheFin;
					kCoucheFin = tailleVect;
					nouvelleCouche = 1;
				}
				appliquerCouche=0;
			}
	} while(nouvelleCouche);
	libererImage(imgCopie);
	libererVectLUT(vectLUT);
}

unsigned char appliquerLUT(Image*img,Image *imgFloue,unsigned char point, Couleur canal, unsigned int ligne, unsigned int colonne, LUT*lut) {
	/*printf("%d ",point);*/
	switch(lut->nom) {
		case ADDLUM: point = lumierePlus(point,lut);break;
		case DIMLUM: point = lumiereMoins(point,lut);break;
		case ADDCON: point = contrastePlus(point,lut,img->lumMoyCanaux[canal]);break;
		case DIMCON: point = contrasteMoins(point,lut,img->lumMoyCanaux[canal]);break;
		case FLOU : point = flou(point,lut,img,canal,ligne,colonne); break;
		case FLOU2 : point = flou2(point,lut,img,imgFloue,canal,ligne,colonne); break;
		case INVERT : point = inverser(point);break;
		case NOIRETBLANC : break;
		case SEPIA : point = vieillephoto(point,lut,canal,ligne,colonne, img->largeur, img->hauteur) ;break;
		default : {
			printf("Erreur d'application d'une LUT.\n" );
			exit(EXIT_FAILURE);
		}
	}
	/*printf("%d\n",point);*/
	return point;
}

unsigned char appliquerEnveloppe(Image*img,Image *imgFloue,unsigned char point, Couleur canal, unsigned int ligne, unsigned int colonne, LUT*lut) {
	switch((lut->enveloppe).forme) {
		case PARDEFAUT : break;
		case ELLIPSE : ellipse(lut, ligne, colonne,img->largeur, img->hauteur,1); break;
		case RELLIPSE : ellipse(lut, ligne, colonne,img->largeur, img->hauteur,0); break;
		default : {
			printf("Erreur d'application d'une enveloppe.\n" );
			exit(EXIT_FAILURE);
		}
	}
	return appliquerLUT(img,imgFloue,point,canal,ligne,colonne,lut);
}


int compterLUT(int argc, char *argv[],char *choixLUT[],unsigned int nbChoixLUT) {
	int i,j;
	int tailleVect=0;
	for(i=0;i<argc;i++) {
		for(j=0;j<nbChoixLUT;j++) {
			if(comparerChainesLUT(argv[i],choixLUT[j])) tailleVect+=1;
		}
	}
	return tailleVect;
}

LUT* creerVectLUT(int tailleVect,int argc, char *argv[],char *choixLUT[], char *choixEnveloppe[],unsigned int nbChoixLUT,int nbParametresLUT[], unsigned int nbChoixEnveloppe, int nbParametresEnveloppe[]) {
	LUT*vectLUT;
	int estLUT=0;
	int i,j,k,kPrime;
	int l=0;
	int m=0;
	vectLUT = malloc(tailleVect*sizeof(LUT));
	if(!vectLUT) {
		printf("Échec de l'allocation dynamique pour le contenu du vecteur des LUT !\n");
		exit(EXIT_FAILURE);
	}
	
	for(i=0;i<argc;i++) {
		for(j=0;j<nbChoixLUT;j++) {
			estLUT = comparerChainesLUT(argv[i],choixLUT[j]);
			if(estLUT) {
				vectLUT[l].nom=j;
				if(vectLUT[l].nom == SEPIA) {
					(vectLUT[l].enveloppe).forme = ELLIPSE;
				}
				else {
					(vectLUT[l].enveloppe).forme = PARDEFAUT;
				}
				if(estLUT==2) {
					if(nbParametresLUT[j] < 1) (vectLUT[l].enveloppe).forme = PARDEFAUT; /*Pas d'enveloppe si pas d'intensité.*/
					for(m=0;m<nbChoixEnveloppe;m++) {
						if(correspondanceEnveloppe(argv[i],choixEnveloppe[m])) {
							(vectLUT[l].enveloppe).forme = m;
						}
					}
				}
				for(k=0;k<nbParametresLUT[j];k++) {
					if((i+k+1)>=argc) {
						printf("Erreur : le LUT n°%d nécessite %d arguments.\n",l+1,nbParametresLUT[j]);
						exit(EXIT_FAILURE);
					}
					vectLUT[l].parametres[k]=atof(argv[i+1+k]);
				}
				vectLUT[l].nombreParametres = nbParametresLUT[j];
				if((vectLUT[l].enveloppe).forme != PARDEFAUT) {
					(vectLUT[l].enveloppe).parametres[0] = vectLUT[l].parametres[0];
					for(kPrime=1;kPrime<nbParametresEnveloppe[(vectLUT[l].enveloppe).forme];kPrime++) {
						if((i+k+kPrime)>=argc) {
							printf("Erreur : l'enveloppe n°%d nécessite %d arguments.\n",l+1,nbParametresEnveloppe[(vectLUT[l].enveloppe).forme]);
							exit(EXIT_FAILURE);
						}
						(vectLUT[l].enveloppe).parametres[kPrime]=atof(argv[i+k+kPrime]);
					}
					(vectLUT[l].enveloppe).nombreParametres = nbParametresEnveloppe[(vectLUT[l].enveloppe).forme];
				}
				l+=1;
			}
		}
	}
	if(l!=tailleVect) {
		printf("Erreur de comptage des LUT, trouvé %d au lieu de %d.\n",l,tailleVect);
	}
	return(vectLUT);
}

void afficherVectLUT(int tailleVect,LUT*vectLUT) {
	int i,j;
	for(i=0;i<tailleVect;i++) {
		printf("LUT n°%d, %d paramètres\n",vectLUT[i].nom,vectLUT[i].nombreParametres);
			for(j=0;j<vectLUT[i].nombreParametres;j++) {
				printf("Paramètre n°%d : %lf\n",j,(vectLUT[i].parametres)[j]);
			}
		if((vectLUT[i].enveloppe).forme != PARDEFAUT) {
			printf("LUT n°%d, enveloppe n°%d, %d paramètres\n",vectLUT[i].nom,(vectLUT[i].enveloppe).forme,(vectLUT[i].enveloppe).nombreParametres);
			for(j=0;j<(vectLUT[i].enveloppe).nombreParametres;j++) {
					printf("Paramètre n°%d : %lf\n",j,(vectLUT[i].enveloppe).parametres[j]);
				}
		}
		
	}	
}

void libererVectLUT(LUT*vectLUT) {
	free(vectLUT);
}