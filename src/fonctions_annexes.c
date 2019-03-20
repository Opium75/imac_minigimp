#include "fonctions_annexes.h"


int comparerChainesLUT(char chaineArg[], char chaineLUT[]) {
	int i = 0;
	while(chaineLUT[i]!='\0') {
		if(chaineArg[i]!=chaineLUT[i]||chaineArg[i]=='\0') return 0;
		i+=1;
	}
	switch(chaineArg[i]) {
		case '\0' : return 1;
		case '-' : return 2;
		default : return 0;
	}
}

int correspondanceEnveloppe(char chaineArg[], char chaineEnveloppe[]) {
	int i = 0;
	int j = 0;
	while(chaineArg[i]!='-') i+=1;
	i+=1;
	while(chaineArg[i]!='\0') {
		if(chaineArg[i]!=chaineEnveloppe[j]||chaineEnveloppe[j]=='\0') return 0;
		i+=1;
		j+=1;
	}
	return 1;
}


int estElement(int e, int vecteur[], unsigned int dimension) {
	int i=0;
	while(i<dimension&&vecteur[i]!=e) i+=1;
	return(i != dimension);
}


int puissance(int a,unsigned int n) {
	int k;
	int p=1;
	if (n==0) return 1;
	for(k=0;k<n;k++) {
		p*=a;
	}
	return p;
}

int nombreVoisins(int rayon, int ligne, int colonne, unsigned int largeur, unsigned int hauteur) {
	int nbVoisins=0;
	int li,ci;
	unsigned int distance;
	for(ci=colonne-rayon;ci<=colonne+rayon;ci++) {
		if(ci<=largeur&&ci>=0) {
			for(li=ligne-rayon;li<=ligne+rayon;li++) {
				if(li<=hauteur&&li>=0) {
					distance = abs(ligne-li) +abs(colonne-ci);
					if(distance<=rayon) nbVoisins+=1;
				}
			}
		}
	}
	if(nbVoisins>(1 << (rayon+2)) - 3) printf("Non : %u\n",nbVoisins);
	return nbVoisins;
}

double calculMoyenne(double moyennePrecedente,unsigned char termeSuivant, int n) {
	double facteur = n/(double)(n+1);
	double delta = termeSuivant/(double)(n+1);
	double moyenneSuivante = facteur*moyennePrecedente + delta;
	return(moyenneSuivante);
}

int arrondir(double r) {
	int n = (int)r;
	if( r-n <= 0.5 ) return n;
	else return n+1;
}