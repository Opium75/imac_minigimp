#include "entete.h"

void lireEntete(FILE *src,unsigned int*largeur,unsigned int*hauteur, unsigned char* lumMax, FormatCouleur *format) {
	char chaineFormat[2];
	int entierFormatPBM;
	unsigned int lumMaxEntree;
	unsigned int nbChoixFormatPBM = 4;
	char *choixFormatPBM[] = {"P4","P5","P6"};
	/*format[0] = fgetc(src);
	format[1] = fgetc(src);*/
	fgets(chaineFormat,3,src);
	entierFormatPBM = correspondancePBM(choixFormatPBM,nbChoixFormatPBM,chaineFormat);
	fscanf(src,"\n");
	lireCommentaire(src);
	fscanf(src,"%u %u\n",largeur,hauteur);
	lireCommentaire(src);
	fscanf(src,"%u\n",&lumMaxEntree);
	if((lumMaxEntree > VAL_MAX) || !(entierFormatPBM+1)) {
		printf("Ficher non conforme !\n");
		printf("%u x %u, %hhu, format %s.\n",*largeur,*hauteur,*lumMax,choixFormatPBM[entierFormatPBM]);
		exit(EXIT_FAILURE);
	}
	*lumMax = lumMaxEntree;
	*format = PBMaCouleur(entierFormatPBM);
	printf("%u x %u, %hhu, format %s.\n",*largeur,*hauteur,*lumMax,choixFormatPBM[entierFormatPBM]);
}

void ecrireEntete(FILE*dest,unsigned int largeur, unsigned int hauteur, unsigned char lumMax, FormatCouleur format) {
	char *choixFormatPBM[] = {"P4","P5","P6"};
	FormatPBM formatPBM = couleuraPBM(format);
	fputs(choixFormatPBM[formatPBM],dest);
	fprintf(dest,"\n%u %u\n%hhu\n",largeur,hauteur,lumMax);
}

void lireCommentaire(FILE *src) {
	char commentaireSigne;
	char commentaireTampon;
	int i=0;
	commentaireSigne = fgetc(src);
	if(commentaireSigne == '#') {
		commentaireTampon = fgetc(src);
		while(commentaireTampon != '\n') {
			commentaireTampon = fgetc(src);
			i+=1;
		}
	}
	else fseek(src,-sizeof(char),SEEK_CUR);
}

int correspondancePBM(char *choixFormatPBM[], unsigned int nbChoixFormatPBM, char chaineFormat[]) {
	int i = 0;
	while(i<nbChoixFormatPBM) {
		if(!strcmp(choixFormatPBM[i],chaineFormat)) return i;
		i++;
	}
	return -1;
}

FormatCouleur PBMaCouleur(FormatPBM formatPBM) {
	switch(formatPBM) {
		case P4 : return NEB;
		case P5 : return NDG;
		case P6 : return RVB;
		default : 
			exit(EXIT_FAILURE);
	}
}

FormatCouleur couleuraPBM(FormatCouleur format) {
	switch(format) {
		case NEB : return P4;
		case NDG : return P5;
		case RVB : return P6;
		default : 
			exit(EXIT_FAILURE);
	}
}