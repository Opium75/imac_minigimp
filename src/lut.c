#include "lut.h"

unsigned char lumierePlus(unsigned char point,LUT*lut) {
	unsigned int lum = (unsigned int)(lut->parametres[0]*VAL_MAX/(float)100);
	point = tronquerOctet(point+lum,0,VAL_MAX);
	return point;
}
unsigned char lumiereMoins(unsigned char point,LUT*lut) {
	unsigned int lum = (unsigned int)(lut->parametres[0]*VAL_MAX/(float)100);
	point = tronquerOctet(point-lum,0,VAL_MAX);
	return point;
}

unsigned char contrastePlus(unsigned char point,LUT*lut,unsigned char moyenneLum) {
	unsigned int dist;
	unsigned int maxDist;
	double taux;
	unsigned int homothetie;
	dist = abs(moyenneLum - point);
	maxDist = max(VAL_MAX-moyenneLum, moyenneLum);
	taux = ((double)dist/maxDist);
	homothetie = (unsigned int )(maxDist*(sqrt(sqrt(taux)))*lut->parametres[0]/100);
	/*printf("con :%f dist : %d, point : %hhu, résultat : %hhu\n",con,dist,point,tronquerOctet(moyenneLum + homothetie,0,VAL_MAX));*/
	if(point<moyenneLum) point = tronquerOctet(point - homothetie,0,VAL_MAX);
	else point = tronquerOctet(point + homothetie,0,VAL_MAX);
	return point;
}

unsigned char contrasteMoins(unsigned char point,LUT*lut,unsigned char moyenneLum) {
	unsigned int dist;
	unsigned int maxDist;
	double taux;
	unsigned int homothetie;
	dist = abs(moyenneLum - point);
	maxDist = min((int)(VAL_MAX - moyenneLum),(int)moyenneLum);
	taux = ((double)dist/maxDist);
	if(taux>1) {
		printf("%u et %u\n",moyenneLum,point);
		printf("NOOOON %u > %u\n",dist,maxDist);
	}
	homothetie = (unsigned int) (dist*(sqrt(sqrt(taux)))*lut->parametres[0]/100);
	/*printf("con :%f dist : %d, point : %hhu, résultat : %hhu\n",con,dist,point,tronquerOctet(moyenneLum + homothetie,0,VAL_MAX));*/
	if(point<moyenneLum) point = tronquerOctet(point + homothetie,0,moyenneLum);
	else point = tronquerOctet(point - homothetie,moyenneLum,VAL_MAX);
	return point;
}

unsigned char inverser(unsigned char point) {
	return(VAL_MAX-point);
}

unsigned char noirEtBlanc(unsigned char point) {
	return point;
}

unsigned char vieillephoto(unsigned char point,LUT*lut, Couleur canal, unsigned int ligne, unsigned int colonne, unsigned int largeur, unsigned int hauteur) {
	point = lumierePlus(point,lut);
	switch(canal) {
		case rouge : point = tronquerOctet((int)(point*1.3),0,VAL_MAX);break;
		case vert : point = (unsigned char)(point*0.8);break;
		case bleu : point = (unsigned char)(point*0.2);break;
	}
	return point;
}

unsigned char flou(unsigned char point,LUT*lut, Image *img,Couleur canal,unsigned int ligne, unsigned int colonne) {
	int ci,li;
	int c = ((int) colonne);
	int l = ((int) ligne);
	int k;
	int nbVoisins=0;
	double flotPoint=0;
	unsigned int distance;
	double ecart;
	double intensite = lut->parametres[0]/100;
	int rayon = (int)lut->parametres[1];
	for(ci=c-rayon;ci<=c+rayon;ci++) {
		if(ci<=img->largeur&&ci>=0) {
			for(li=l-rayon;li<=l+rayon;li++) {
				if(li<=img->hauteur&&li>=0) {
					distance = abs(colonne-ci) + abs(ligne-li);
					if(distance<=rayon) {
						k = img->largeur*li + ci;
						flotPoint = calculMoyenne(flotPoint,*(img->canaux[canal]+k),nbVoisins);
						nbVoisins+=1;
					}
				}
			}
		}
	}
	ecart = flotPoint - (double)point;
	point = tronquerOctet((int)(point + ecart*intensite),0,VAL_MAX);
	return point;
}

unsigned char flou2(unsigned char point, LUT*lut, Image *img,Image *imgFloue, Couleur canal, unsigned int ligne, unsigned int colonne) {
	int ci,li;
	int ciGauche, ciDroite, liHaut, liBas;
	int c = ((int) colonne);
	int l = ((int) ligne);
	int k,ki;
	int nbVoisinsPrecedents, nbVoisins;
	unsigned char pointPrecedent;
	double flotPoint=0;
	double ecart;
	double intensite = lut->parametres[0]/100;
	int rayon = (int)lut->parametres[1];
	if(c==0&&l==0) {
		nbVoisins=0;
		for(ci=c;ci<=c+rayon;ci++) {
			if(ci<=img->largeur) {
				for(li=l;li<=l+rayon;li++) {
					if(li<=img->hauteur) {
						if(li +ci <= rayon) {
							ki = img->largeur*li + ci;
							flotPoint = calculMoyenne(flotPoint,*(img->canaux[canal]+ki),nbVoisins);
							nbVoisins+=1;
						}
					}
				}
			}
		}
	}
	else {
		if(c>0) {
			nbVoisinsPrecedents = nombreVoisins(rayon,ligne,colonne-1,img->largeur,img->hauteur);
			nbVoisins = nbVoisinsPrecedents;
			k = imgFloue->largeur*l + (c-1);
			flotPoint = (double)(*(imgFloue->canaux[canal]+k));
			for(li=l-rayon;li<=l+rayon;li++) {
				if(li<=img->hauteur&&li>=0) {
					ciGauche = c + abs(l-li) - (rayon+1);
					ciDroite = c + rayon - abs(l-li);
					if(ciGauche>=0) {
						ki = img->largeur*li + ciGauche;
						pointPrecedent = *(img->canaux[canal]+ki);
						flotPoint -= ((double)pointPrecedent/(double)nbVoisinsPrecedents);
						nbVoisins -= 1;
					}
					if(ciDroite<=img->largeur) {
						ki = img->largeur*li + ciDroite;
						pointPrecedent = *(img->canaux[canal]+ki);
						flotPoint += ((double)pointPrecedent/(double)nbVoisinsPrecedents);
						nbVoisins += 1;
					}
				}
			}
		}
		else /* c nul et l>0*/ {
			nbVoisinsPrecedents = nombreVoisins(rayon,ligne-1,colonne,img->largeur,img->hauteur);
			nbVoisins = nbVoisinsPrecedents;
			k = imgFloue->largeur*(l-1) + c;
			flotPoint = (double)(*(imgFloue->canaux[canal]+k));
			for(ci=c;ci<=c+rayon;ci++) {
				if(ci<=img->largeur) {
					liHaut = l + abs(c-ci) - (rayon+1);
					liBas = l + rayon - abs(c-ci);
					if(liHaut>=0) {
						ki = img->largeur*liHaut + ci;
						pointPrecedent = *(img->canaux[canal]+ki);
						flotPoint -= pointPrecedent/(double)nbVoisinsPrecedents;
						nbVoisins -= 1;
					}
					if(liBas<=img->hauteur) {
						ki = img->largeur*liBas + ci;
						pointPrecedent = *(img->canaux[canal]+ki);
						flotPoint += pointPrecedent/(double)nbVoisinsPrecedents;
						nbVoisins += 1;
					}
				}
			}
		}
		flotPoint *= (nbVoisinsPrecedents/(double)nbVoisins);
	}
	ecart = flotPoint - (double)point;
	point = tronquerOctet((int)(point + ecart*intensite),0,VAL_MAX);
	return point;
}


void ellipse(LUT*lut,unsigned int ligne, unsigned int colonne, unsigned int largeur, unsigned int hauteur,int effetBords) {
	unsigned int transfert;
	int oblongue=0;
	unsigned int a = (lut->enveloppe).parametres[1]/200*largeur;
	unsigned int b = (lut->enveloppe).parametres[2]/200*hauteur;
	unsigned int intensite = (unsigned int)(lut->enveloppe).parametres[0];
	if(a<b) {
		oblongue = 1;
		transfert = a;
		a = b;
		b = transfert;
	}
	unsigned int x = abs(colonne - largeur/2);
	unsigned int y = abs(ligne - hauteur/2);
	unsigned long int moduleCarre = x*x + y*y;
	unsigned int module = (unsigned int) sqrt(moduleCarre);
	unsigned int v = x*(1-oblongue) + y*oblongue;
	double trigoCarre = moduleCarre!=0 ? v*((double)v/moduleCarre) : 1;
	double eCarre = (1 - b*((double)b/a)/a);
	double rayonEllipse = b*sqrt(1/(1 - eCarre*trigoCarre));
	/*printf("Module : %u , cosCarre : %lf, rayonEllipse : %u\n",module,cosCarre,rayonEllipse);*/
	double maxModule = sqrt((double)(largeur*largeur + hauteur*hauteur)/4);
	double proportion = effetBords ? max(0,((module - rayonEllipse)/(maxModule - rayonEllipse))) : max(0,(rayonEllipse-module)/rayonEllipse);
	if((effetBords && module>rayonEllipse) || (!effetBords && module<rayonEllipse)) {
			lut->parametres[0] = intensite*proportion;
	}
	else lut->parametres[0] = 0;
}


unsigned char tronquerOctet(int valeur,unsigned char plancher,unsigned char plafond) {
	if(valeur<plancher) return plancher;
	if(valeur>plafond) return plafond;
	return valeur;
}
