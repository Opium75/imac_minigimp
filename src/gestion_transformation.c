#include "gestion_transformation.h"

Transformation* preparationTransfo(int*tailleVectTransfo, int argc,char *argv[],typeSortie *type) {
	unsigned int nbChoixTransfo=5;
	char *choixTransfo[] = {"MIROIRHORIZONTAL","MIROIRVERTICAL","REDIMENSIONNER","PIXELLISER","COMPRESSER"};
	/*Il est important de garder le même ordre que l'énumération.*/	
	int nbParametresTransfo[] = {0,0,2,2,1};
	*tailleVectTransfo = compterTransfo(argc,argv,choixTransfo,nbChoixTransfo);
	if(tailleVectTransfo>0) *type = estModifiee;
	return creerVectTransfo(*tailleVectTransfo,argc,argv,choixTransfo,nbChoixTransfo,nbParametresTransfo);
}

void generalTransfo(Transformation *vectTransfo,int tailleVectTransfo,Image **img) {
	int k;
	/*for(k=0;k<tailleVect;k++) {
		if(vectLUT[k].nom==NOIRETBLANC||vectLUT[k].nom==SEPIA) {
			RVBversNDG(img);
			if(vectLUT[k].nom==SEPIA) NDGversRVB(img);
			break;
		}
	}*/
	afficherVectTransfo(tailleVectTransfo,vectTransfo);
	for(k=0;k<tailleVectTransfo;k++) {
		appliquerTransfo(img,&vectTransfo[k]);
	}
	libererVectTransfo(vectTransfo);
}

void appliquerTransfo(Image**img,Transformation *transfo) {
	/*printf("%d ",point);*/
	switch(transfo->nom) {
		case CONSEILLERDESGRACESHORIZONTAL : miroirHorizontal(*img); break;
		case CONSEILLERDESGRACESVERTICAL : miroirVertical(*img);break;
		case REDIMENSIONNER : redimensionner(img,transfo); break;
		case PIXELLISER : pixelliser(*img,transfo); break;
		case COMPRESSER : changerLumMax(*img,transfo); break;
		/*case NOIRETBLANC : break;
		case INVERT : break;*/
		default : {
			printf("Erreur d'application d'une transformation.\n" );
			exit(EXIT_FAILURE);
		}
	}
}


int compterTransfo(int argc, char *argv[],char *choixTransfo[],unsigned int nbChoixTransfo) {
	int i,j;
	int tailleVectTransfo=0;
	for(i=0;i<argc;i++) {
		for(j=0;j<nbChoixTransfo;j++) {
			if(!strcmp(argv[i],choixTransfo[j])) tailleVectTransfo+=1;
		}
	}
	return tailleVectTransfo;
}

Transformation* creerVectTransfo(int tailleVectTransfo,int argc, char *argv[],char *choixTransfo[], unsigned int nbChoixTransfo,int nbParametresTransfo[]) {
	Transformation *vectTransfo;
	int i,j,k;
	int l=0;
	vectTransfo = malloc(tailleVectTransfo*sizeof(Transformation));
	if(!vectTransfo) {
		printf("Échec de l'allocation dynamique pour le contenu du vecteur des Transformations !\n");
		exit(EXIT_FAILURE);
	}
	for(i=0;i<argc;i++) {
		for(j=0;j<nbChoixTransfo;j++) {
			if(!strcmp(argv[i],choixTransfo[j])) {
				vectTransfo[l].nom = j;
				for(k=0;k<nbParametresTransfo[j];k++) {
					if((i+k+1)>=argc) {
						printf("Erreur : la Transformation n°%d nécessite %d arguments.\n",l+1,nbParametresTransfo[j]);
						exit(EXIT_FAILURE);
					}
					vectTransfo[l].parametres[k]=atof(argv[i+1+k]);
				}
				vectTransfo[l].nombreParametres = nbParametresTransfo[j];
				l+=1;
			}
		}
	}
	if(l!=tailleVectTransfo) {
		printf("Erreur de comptage des Transformations, trouvé %d au lieu de %d.\n",l,tailleVectTransfo);
	}
	return(vectTransfo);
}

void afficherVectTransfo(int tailleVectTransfo, Transformation *vectTransfo) {
	int i,j;
	for(i=0;i<tailleVectTransfo;i++) {
		printf("Transformation n°%d, %d paramètres\n",vectTransfo[i].nom,vectTransfo[i].nombreParametres);
			for(j=0;j<vectTransfo[i].nombreParametres;j++) {
				printf("Paramètre n°%d : %u\n",j,(vectTransfo[i].parametres)[j]);
			}
	}	
}

void libererVectTransfo(Transformation *vectTransfo) {
	free(vectTransfo);
}