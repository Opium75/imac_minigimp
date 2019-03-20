#include "image.h"

Image* creerImage(unsigned int largeur,unsigned int hauteur, unsigned char lumMax, FormatCouleur format) {
	int i;
	unsigned long int taille_canal = largeur*hauteur*sizeof(unsigned char);
	Image *img = malloc(sizeof(Image));
	if(!img) {
		printf("Échec de l'allocation dynamique pour l'Image !\n");
		exit(EXIT_FAILURE);
	}
	for(i=0;i<3;i++) {
		(img->canaux)[i] = malloc(taille_canal);
		if(!(img->canaux)[i]) {
			printf("Échec de l'allocation dynamique pour les canaux !\n");
			exit(EXIT_FAILURE);
		}
	}
	img->largeur = largeur;
	img->hauteur = hauteur;
	img->lumMax = lumMax;
	img->format = format;
	return img;
}

void copierImage(Image*imgDest,Image*imgSrc) {
	int i,j;
	imgDest->lumMax = imgSrc->lumMax;
	if(imgSrc->format == RVB) {
		for(i=0;i<3;i++) {
			for(j=0;j<imgSrc->largeur*imgSrc->hauteur;j++) {
				*(imgDest->canaux[i]+j) = *(imgSrc->canaux[i]+j);
			}
			(imgDest->lumMoyCanaux)[i] = (imgSrc->lumMoyCanaux)[i];
		}
	}
	else if(imgSrc->format == NDG) {
			for(j=0;j<imgSrc->largeur*imgSrc->hauteur;j++) {
				*(imgDest->canaux[gris]+j) = *(imgSrc->canaux[gris]+j);
			}
			(imgDest->lumMoyCanaux)[gris] = (imgSrc->lumMoyCanaux)[gris];
	}
	imgDest->format = imgSrc->format;
}

void RVBversNDG(Image *img) {
	int j;
	double flotLumMoyCanaux[3];
	for(j=0;j<img->largeur*img->hauteur;j++) {
			*(img->canaux[gris]+j) = (*((img->canaux[rouge])+j) + *((img->canaux[vert])+j) + *((img->canaux[bleu])+j))/3 ;	
			flotLumMoyCanaux[gris] = calculMoyenne(flotLumMoyCanaux[gris],*(img->canaux[gris]+j),j);
	}
	img->lumMoyCanaux[gris] = (unsigned char) flotLumMoyCanaux[gris];
	printf("Moyenne de luminosité NDG : %lf\n",flotLumMoyCanaux[gris]);
	img->format = NDG;
}

void NDGversRVB(Image *img) {
	int i,j;
	for(i=0;i<3;i++) {
			if(i!=gris) {
					for(j=0;j<img->largeur*img->hauteur;j++) 
						*(img->canaux[i]+j) = *((img->canaux[gris])+j);
			}
	}
	img->format = RVB;
}

void afficherImage(Image *img) {
	int i,j;
	printf("Format : %u x %u.\n",img->largeur,img->hauteur);
	printf("Valeur de luminosité maximale : %hhu.\n",img->lumMax);
	for(i=0;i<3;i++) {
		for(j=0;j<img->largeur*img->hauteur;j++) {
			printf("%hhu ",*((img->canaux[i])+j));
		}
	}
	printf("\n");
}

void libererImage(Image *img) {
	int i;
	for(i=0;i<3;i++) {
		free(img->canaux[i]);
	}
	free(img);
}

void lireCanaux(FILE *src,Image *img) {
	int i,j;
	double flotLumMoyCanaux[3];
	for(j=0;j<img->largeur*img->hauteur;j++) {
		fread((img->canaux)[rouge]+j,sizeof(unsigned char),1,src);
		fread((img->canaux)[vert]+j,sizeof(unsigned char),1,src);
		fread((img->canaux)[bleu]+j,sizeof(unsigned char),1,src);
		flotLumMoyCanaux[rouge] = calculMoyenne(flotLumMoyCanaux[rouge],*((img->canaux)[rouge]+j),j);
		flotLumMoyCanaux[vert] = calculMoyenne(flotLumMoyCanaux[vert],*((img->canaux)[vert]+j),j);
		flotLumMoyCanaux[bleu] = calculMoyenne(flotLumMoyCanaux[bleu],*((img->canaux)[bleu]+j),j);
	}
	for(i=0;i<3;i++) {
			img->lumMoyCanaux[i] = (unsigned char) flotLumMoyCanaux[i];
			printf("Moyenne de luminosité par canaux : %lf\n",flotLumMoyCanaux[i]);
	}
}

void ecrireCanaux(FILE *dest,Image *img) {
	int j;
	if(img->format == RVB) {
		for(j=0;j<img->largeur*img->hauteur;j++) {
		/*fprintf(dest,"%c",*(img->canaux[rouge]+j));
		fprintf(dest,"%c",*(img->canaux[vert]+j));
		fprintf(dest,"%c",*(img->canaux[bleu]+j));*/
		fwrite((img->canaux)[rouge]+j,sizeof(unsigned char),1,dest);
		fwrite((img->canaux)[vert]+j,sizeof(unsigned char),1,dest);
		fwrite((img->canaux)[bleu]+j,sizeof(unsigned char),1,dest);
		}
	}
	else if (img->format == NDG) {
		for(j=0;j<img->largeur*img->hauteur;j++) {
		fwrite((img->canaux)[gris]+j,sizeof(unsigned char),1,dest);
		fwrite((img->canaux)[gris]+j,sizeof(unsigned char),1,dest);
		fwrite((img->canaux)[gris]+j,sizeof(unsigned char),1,dest);
		}
	}
}

Image* lireImage(FILE *src) {
	Image *img;
	FormatCouleur format;
	unsigned int largeur,hauteur;
	unsigned char lumMax;
	lireEntete(src,&largeur,&hauteur,&lumMax,&format);
	img = creerImage(largeur,hauteur,lumMax,format);
	lireCanaux(src,img);
	return img;
}

void ecrireImage(FILE*dest,Image*img) {
	ecrireEntete(dest,img->largeur,img->hauteur,img->lumMax,img->format);
	ecrireCanaux(dest,img);
	libererImage(img);
}