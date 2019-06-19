#include "transformation.h"

Transformation* creerTransfo(nomTransformation nom, int nombresParametres, unsigned int parametres[NB_PARAMETRES_MAX_TRANSFORMATION]) {
	int i;
	Transformation* transfo = malloc(sizeof(Transformation));
	if(!transfo) {
		printf("Échec de l'allocation dynamique pour une création de transformation !\n");
		exit(EXIT_FAILURE);
	}
	transfo->nom = nom;
	transfo->nombreParametres = nombresParametres;
	for(i=0 ; i < nombresParametres ; i++ ) {
		transfo->parametres[i] = parametres[i];
	}
	return transfo;
}

void miroirVertical(Image* img) {
	int i,k,m;
	unsigned char transfert;
	int colonne, ligne;
	for(i=0;i<3;i++) {
		for(ligne = 0; ligne < img->hauteur; ligne++) {
			for(colonne = 0; colonne < img->largeur/2; colonne++) {
				k = img->largeur*ligne + colonne;
				m = img->largeur*ligne + (img->largeur-colonne);
			transfert = *(img->canaux[i]+k);
			*(img->canaux[i]+k) = *(img->canaux[i]+m);
			*(img->canaux[i]+m) = transfert;
			}
		}
	}
}
void miroirHorizontal(Image *img) {
	int i,k,m;
	unsigned char transfert;
	int colonne, ligne;
	for(i=0;i<3;i++) {
		for(ligne = 0; ligne < img->hauteur/2; ligne++) {
			for(colonne = 0; colonne < img->largeur; colonne++) {
				k = img->largeur*ligne + colonne;
				m = img->largeur*(img->hauteur - ligne) + colonne;
			transfert = *(img->canaux[i]+k);
			*(img->canaux[i]+k) = *(img->canaux[i]+m);
			*(img->canaux[i]+m) = transfert;
			}
		}
	}
}

void redimensionner(Image **img, Transformation *transfo) {
	int colonne,ligne;
	int colonne2, ligne2;
	int i,jHauteur,jLargeur,h,v,w;
	unsigned int lj,cj;
	unsigned int *vectDecalageLigne;
	unsigned int decalageColonne=0;
	Image*imgRedim;
	unsigned int nouvelleLargeur = (unsigned int) transfo->parametres[0];
	unsigned int nouvelleHauteur = (unsigned int) transfo->parametres[1];
	imgRedim = creerImage(nouvelleLargeur,nouvelleHauteur,(*img)->lumMax,(*img)->format);
	int quotientLargeur = imgRedim->largeur/(*img)->largeur;
	int quotientHauteur = imgRedim->hauteur/(*img)->hauteur;
	int inverseQuotientLargeur = (*img)->largeur/imgRedim->largeur;
	int inverseQuotientHauteur = (*img)->hauteur/imgRedim->hauteur;
	int inverseResteLargeur = (*img)->largeur%imgRedim->largeur;
	int inverseResteHauteur = (*img)->hauteur%imgRedim->hauteur;
	double inversePropLargeur = (imgRedim->largeur)/(double)(inverseResteLargeur+1);
	double inversePropHauteur = (imgRedim->hauteur)/(double)(inverseResteHauteur+1);
	double flotPoint;
	int compte;
	int resteLargeur = imgRedim->largeur%(*img)->largeur;
	int resteHauteur = imgRedim->hauteur%(*img)->hauteur;
	double propLargeur = ((*img)->largeur)/(double)(resteLargeur+1);
	double propHauteur = ((*img)->hauteur)/(double)(resteHauteur+1);
	if(quotientHauteur>=1){
		
		printf("Quotient largeur : %d, hauteur : %d\n",quotientLargeur,quotientHauteur);
		printf("Reste largeur : %d, hauteur : %d\n",resteLargeur,resteHauteur);
		printf("Prop largeur : %lf, hauteur : %lf\n",propLargeur,propHauteur);
		if(quotientLargeur>=1) {
			vectDecalageLigne = malloc((*img)->largeur*sizeof(unsigned int));
			if(!vectDecalageLigne) {
				printf("Échec de l'allocation dynamique pour la redimension !\n");
				exit(EXIT_FAILURE);
			}
			for(i=0;i<3;i++) {
				for(colonne = 0; colonne < (*img)->largeur ; colonne ++) {
					vectDecalageLigne[colonne] = 0;
				}
			
				for(ligne = 0; ligne < (*img)->hauteur; ligne++) {
					decalageColonne=0;
					
						for(colonne = 0; colonne < (*img)->largeur; colonne++) {
							h = (*img)->largeur*ligne + colonne;
							/*quotient*/
							for(jLargeur=0;jLargeur<quotientLargeur;jLargeur++) {
								for(jHauteur=0;jHauteur<quotientHauteur;jHauteur++) {
									lj = ligne*quotientHauteur +jHauteur + vectDecalageLigne[colonne];
									cj = colonne*quotientLargeur + jLargeur + decalageColonne;
									v = imgRedim->largeur*lj + cj;
									*(imgRedim->canaux[i] + v ) = *((*img)->canaux[i]+h);
								}
							}
							if((ligne+1)>(propHauteur)*(vectDecalageLigne[colonne]+1)) {
								lj = (ligne+1)*quotientHauteur + vectDecalageLigne[colonne];
								for(jLargeur=0;jLargeur<quotientLargeur;jLargeur++) {
									cj = colonne*quotientLargeur + decalageColonne+jLargeur;
									v = imgRedim->largeur*lj + cj;
									*(imgRedim->canaux[i] + v ) = *((*img)->canaux[i]+h);
								}

								vectDecalageLigne[colonne] += 1;
							}
							if((colonne+1)>(propLargeur)*(decalageColonne+1)) {
								cj = (colonne+1)*quotientLargeur + decalageColonne;
								for(jHauteur=0;jHauteur<=quotientHauteur;jHauteur++) {
									lj = ligne*quotientHauteur + vectDecalageLigne[colonne+1] + jHauteur;
									if(lj<imgRedim->hauteur) {
										v = imgRedim->largeur*lj + cj;
									*(imgRedim->canaux[i] + v ) = *((*img)->canaux[i]+h);
									}
								}
								decalageColonne += 1;
							}
							/*printf("Ligne : %u Colonne : %u, distance ligne : %u, distance colonne : %u, décalage ligne: %u, décalage colonne : %u !\n",ligne+1,colonne+1,(ligne+1)%((*img)->hauteur/(resteHauteur+1)+1),(colonne+1)%((*img)->largeur/(resteLargeur+1)+1),vectDecalageLigne[colonne],decalageColonne);*/
						}
					}
				
			}
		}
		else {
			/*AGRANDIR HAUTEUR, RÉDUIRE LARGEUR*/
			vectDecalageLigne = malloc(imgRedim->largeur*sizeof(unsigned int));
			if(!vectDecalageLigne) {
				printf("Échec de l'allocation dynamique pour la redimension !\n");
				exit(EXIT_FAILURE);
			}
			for(i=0;i<3;i++) {
				for(colonne = 0; colonne < imgRedim->largeur ; colonne ++) {
					vectDecalageLigne[colonne] = 0;
				}
			
				for(ligne = 0; ligne < (*img)->hauteur ; ligne++) {
					decalageColonne = 0;
					for(colonne2 = 0; colonne2 < imgRedim->largeur; colonne2++) {
						compte = 0;

							/*Inverse quotient1 colonne*/
						for(jLargeur=0;jLargeur<inverseQuotientLargeur;jLargeur++) {
								lj = ligne;
								cj = colonne2*inverseQuotientLargeur + jLargeur + decalageColonne;
								w = (*img)->largeur*lj + cj;
								flotPoint = calculMoyenne(flotPoint,*((*img)->canaux[i]+w),compte);
								compte+=1;
						}
							/* Inverse reste colonne*/
						if((colonne2+1)>(inversePropLargeur)*(decalageColonne+1)) {
							cj = (colonne2+1)*inverseQuotientLargeur + decalageColonne;
							lj = ligne;
								
									w = (*img)->largeur*lj + cj;
									flotPoint = calculMoyenne(flotPoint,*((*img)->canaux[i]+w),compte);
									compte+=1;
							
							decalageColonne += 1;
						}
							/*Quotient ligne*/
						for(jHauteur=0;jHauteur<quotientHauteur;jHauteur++) {
									lj = ligne*quotientHauteur +jHauteur + vectDecalageLigne[colonne2];
									cj = colonne2;
									v = imgRedim->largeur*lj + cj;
									*(imgRedim->canaux[i] + v ) = (unsigned char)flotPoint;;
						}
							/*Reste ligne*/
						if((ligne+1)>(propHauteur)*(vectDecalageLigne[colonne2]+1)) {
								lj = (ligne+1)*quotientHauteur + vectDecalageLigne[colonne2];
									cj = colonne2;
									v = imgRedim->largeur*lj + cj;
									*(imgRedim->canaux[i] + v ) = (unsigned char)flotPoint;
								

								vectDecalageLigne[colonne2] += 1;
						}
						/**(imgRedim->canaux[i] + h) = (unsigned char)flotPoint;*/
					}
				}

			}
		}
	}
	else {
		if(quotientLargeur>=1) {
			vectDecalageLigne = malloc((*img)->largeur*sizeof(unsigned int));
			if(!vectDecalageLigne) {
				printf("Échec de l'allocation dynamique pour la redimension !\n");
				exit(EXIT_FAILURE);
			}
			/*RÉDUIRE HAUTEUR, ADRANDIR LARGEUR*/
			for(i=0;i<3;i++) {
				for(colonne = 0; colonne < (*img)->largeur ; colonne ++) {
					vectDecalageLigne[colonne] = 0;
				}
			
				for(ligne2 = 0; ligne2 < imgRedim->hauteur ; ligne2++) {
					decalageColonne = 0;
					for(colonne = 0; colonne < (*img)->largeur; colonne++) {
						compte = 0;

							/*Inverse quotient1 ligne*/
						for(jHauteur=0 ; jHauteur<inverseQuotientHauteur ; jHauteur++) {
								lj = ligne2*inverseQuotientHauteur + jHauteur + vectDecalageLigne[colonne];
								cj = colonne;
								w = (*img)->largeur*lj + cj;
								flotPoint = calculMoyenne(flotPoint,*((*img)->canaux[i]+w),compte);
								compte+=1;
						}
							/* Inverse reste colonne*/
						if( (ligne2+1)>(inversePropHauteur)*(vectDecalageLigne[colonne]+1) ) {
							cj = colonne;
							lj = (ligne2+1)*inverseQuotientHauteur + vectDecalageLigne[colonne];
								
									w = (*img)->largeur*lj + cj;
									flotPoint = calculMoyenne(flotPoint,*((*img)->canaux[i]+w),compte);
									compte+=1;
							
							vectDecalageLigne[colonne] += 1;
						}
							/*Quotient ligne*/
						for(jLargeur = 0 ; jLargeur < quotientLargeur ; jLargeur++) {
									lj = ligne2;
									cj = colonne*quotientLargeur + jLargeur + decalageColonne;
									v = imgRedim->largeur*lj + cj;
									*(imgRedim->canaux[i] + v ) = (unsigned char)flotPoint;;
						}
							/*Reste ligne*/
						if( (colonne+1)>(propLargeur)*(decalageColonne+1) ) {
								lj = ligne2;
									cj = (colonne+1)*quotientLargeur + decalageColonne;
									v = imgRedim->largeur*lj + cj;
									*(imgRedim->canaux[i] + v ) = (unsigned char)flotPoint;
								

								decalageColonne += 1 ;
						}
						/**(imgRedim->canaux[i] + h) = (unsigned char)flotPoint;*/
					}
				}

			}
		 }

		else {
			printf("Inverse Quotient largeur : %d, hauteur : %d\n",inverseQuotientLargeur,inverseQuotientHauteur);
			printf("Inverse Reste largeur : %d, hauteur : %d\n",inverseResteLargeur,inverseResteHauteur);
			printf("Inverse Prop largeur : %lf, hauteur : %lf\n",inversePropLargeur,inversePropHauteur);
			vectDecalageLigne = malloc(imgRedim->largeur*sizeof(unsigned int));
			if(!vectDecalageLigne) {
				printf("Échec de l'allocation dynamique pour la redimension !\n");
				exit(EXIT_FAILURE);
			}
			/*RAPETISSEMENT*/
			for(i=0;i<3;i++) {
				for(colonne = 0; colonne < imgRedim->largeur ; colonne ++) {
					vectDecalageLigne[colonne] = 0;
				}
				for(ligne = 0; ligne < imgRedim->hauteur ; ligne++) {
					decalageColonne = 0;
					for(colonne = 0; colonne < imgRedim->largeur; colonne++) {
						compte = 0;
						h = imgRedim->largeur*ligne + colonne;
							/*quotient*/
						for(jLargeur=0;jLargeur<inverseQuotientLargeur;jLargeur++) {
							for(jHauteur=0;jHauteur < inverseQuotientHauteur;jHauteur++) {
								lj = ligne*inverseQuotientHauteur + jHauteur + vectDecalageLigne[colonne];
								cj = colonne*inverseQuotientLargeur + jLargeur + decalageColonne;
								v = (*img)->largeur*lj + cj;
								flotPoint = calculMoyenne(flotPoint,*((*img)->canaux[i]+v),compte);
								compte+=1;
							}
						}
						if((ligne+1) > (inversePropHauteur)*(vectDecalageLigne[colonne]+1)) {
							lj = (ligne+1)*inverseQuotientHauteur + vectDecalageLigne[colonne];
							for(jLargeur=0 ; jLargeur <  inverseQuotientLargeur ; jLargeur++) {
								cj = colonne*inverseQuotientLargeur + decalageColonne + jLargeur;
								v = (*img)->largeur*lj + cj;
								flotPoint = calculMoyenne(flotPoint,*((*img)->canaux[i]+v),compte);
								compte+=1;
							}
							vectDecalageLigne[colonne]+=1;
						}
						if(colonne<imgRedim->largeur&&(colonne+1)>(inversePropLargeur)*(decalageColonne+1)) {
							cj = (colonne+1)*inverseQuotientLargeur + decalageColonne;
							for(jHauteur=0;jHauteur <= inverseQuotientHauteur; jHauteur++) {
								lj = ligne*inverseQuotientHauteur + vectDecalageLigne[colonne+1] + jHauteur;
								if(lj<(*img)->hauteur) {
									v = (*img)->largeur*lj + cj;
									flotPoint = calculMoyenne(flotPoint,*((*img)->canaux[i]+v),compte);
									compte+=1;
								}
							}
							decalageColonne += 1;
						}
						*(imgRedim->canaux[i] + h) = (unsigned char)flotPoint;
						
					}
				}
			}
			/* Normalement pas de problème.*/
			for(colonne = 0; colonne < imgRedim->largeur ; colonne ++) {
					if(vectDecalageLigne[colonne] > resteHauteur) {
							printf("NON Ligne : %u, colonne : %u\n",ligne,colonne);
						}
			}
		}
	}
	printf("Décalage colonne : %u, ligne : %u\n",decalageColonne,vectDecalageLigne[colonne-1]);
	free(vectDecalageLigne);
	libererImage(*img);
	*img = imgRedim;
}

void pixeliser(Image *img, Transformation *transfo) {
	int colonne, ligne, cj, lj;
	int i;
	int h,v;
	int jLargeur, jHauteur;
	double flotPoint;
	int compte;
	unsigned int tailleCelluleX = transfo->parametres[0];
	unsigned int tailleCelluleY = transfo->parametres[1];
	Image *imgPixellisee = creerImage(img->largeur/tailleCelluleX, img->hauteur/tailleCelluleY,img->lumMax,img->format);
	for( i=0 ; i < 3 ; i++ ) {
		for( ligne = 0; ligne < imgPixellisee->hauteur; ligne++ ) {
			for( colonne = 0; colonne < imgPixellisee->largeur ; colonne++ ) {
				compte = 0;
				h = imgPixellisee->largeur*ligne + colonne;
				for( jHauteur = 0 ; jHauteur < tailleCelluleY ; jHauteur++ ) {
					lj = ligne*tailleCelluleY;
					for( jLargeur = 0 ; jLargeur < tailleCelluleX ; jLargeur++ ) {
						cj = colonne*tailleCelluleX;
						v = img->largeur*lj + cj;
						flotPoint = calculMoyenne(flotPoint,*(img->canaux[i]+v),compte);
						compte+=1;
					}
				}
				*(imgPixellisee->canaux[i] + h) = (unsigned char)flotPoint;
			}
		}
	}
	/* Des choses... */


	unsigned int parametresPixel[2] = {img->largeur, img->hauteur};
	Transformation* transfoPixel = creerTransfo(REDIMENSIONNER,2,parametresPixel);
	redimensionner(&imgPixellisee, transfoPixel);
	copierImage(img,imgPixellisee);
	libererImage(imgPixellisee);
}

void changerLumMax(Image *img, Transformation *transfo) {
	unsigned char nouvelleLumMax = transfo->parametres[0];
	double propLum = nouvelleLumMax/(double)img->lumMax;
	double flotPoint;
	int i,j;
	for(i=0;i<3;i++) {
		for(j=0 ; j< img->largeur*img->hauteur ; j++) {
			flotPoint = *(img->canaux[i]+j)*propLum;
			*(img->canaux[i]+j) = (unsigned char) arrondir(flotPoint);
		}
	}
	img->lumMax = nouvelleLumMax;
}