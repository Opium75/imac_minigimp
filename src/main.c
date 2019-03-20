#include "main.h"

int main(int argc,char *argv[]) {
	time_t secondes = clock();
	int aide=0;
	int histogramme=0;
	int changerNom=0;
	typeSortie type=estNonModifiee;
	LUT *vectLUT;
	int tailleVect;
	Transformation* vectTransfo;
	int tailleVectTransfo;
	char destChemin[TAILLE_CHEMIN_MAX];
	char srcChemin[TAILLE_CHEMIN_MAX];
	char destHistoChemin[TAILLE_CHEMIN_MAX];
	char srcHistoChemin[TAILLE_CHEMIN_MAX];
	Image *img;
	Image *imgDestHisto;
	Image *imgSrcHisto;
	if (argc<2) {
		printf("Entrez au moins un argument. (chemin du fichier source).\n");
		printf("Usage : $ minigimp mon_image.ppm [-h] [--histo] [<code_lut>[-<code_enveloppe>]* [_<param1>]*]* [-o Image_sortie.ppm]\n");
		exit(EXIT_FAILURE);
	}
	strcpy(srcChemin,argv[1]);
	attraperOptions(argc,argv,&aide,&histogramme,&changerNom,destChemin);
	if(aide) {
		bouee();
	}
	vectLUT = preparationLUT(&tailleVect,argc,argv,&type);
	vectTransfo = preparationTransfo(&tailleVectTransfo,argc,argv,&type);
	generalRenommer(changerNom,destChemin,srcChemin,destHistoChemin,srcHistoChemin);
	/*for(i=0;i<argc;i++) {
		printf("%s\n",argv[i]);
	}*/
	FILE *src=fopen(srcChemin,"rb");
	if (src==NULL) {
		printf("Erreur d'ouverture du fichier source ! Chemin non valide ?\n");
		exit(EXIT_FAILURE);
	}
	img = lireImage(src);
	fclose(src);
	/*afficherImage(img);*/
	if(histogramme) {
		FILE *srcHisto = fopen(srcHistoChemin,"wb");
		if (srcHisto==NULL) {
			printf("Erreur d'ouverture de l'histogramme d'entrée !\n");
			exit(EXIT_FAILURE);
		}
		imgSrcHisto = lireHisto(img);
		/*créer et enregistrer l'histogramme*/
		ecrireImage(srcHisto,imgSrcHisto);
		fclose(srcHisto);
	}
	generalLUT(vectLUT,tailleVect,img);
	generalTransfo(vectTransfo,tailleVectTransfo,&img);
	/*afficherImage(img);*/
	if(histogramme&&(type==estModifiee)) {
		FILE *destHisto = fopen(destHistoChemin,"wb");
		if (destHisto==NULL) {
			printf("Erreur d'ouverture de l'histogramme de sortie !\n");
			exit(EXIT_FAILURE);
		}
		imgDestHisto = lireHisto(img);
		ecrireImage(destHisto,imgDestHisto);
		fclose(destHisto);
	}
	FILE *dest =fopen(destChemin,"wb");
	if (dest==NULL) {
		printf("Erreur d'ouverture du fichier de destination !\n");
		exit(EXIT_FAILURE);
	}
	ecrireImage(dest,img);
	fclose(dest);
	secondes -= clock();
	printf("Temps d'opération : %lf secondes\n",-(double)secondes/CLOCKS_PER_SEC);
	return EXIT_SUCCESS;
}