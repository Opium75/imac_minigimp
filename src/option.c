#include "option.h"


void attraperOptions(int argc,char *argv[],int*aide,int*histogramme,int*changerNom,char destChemin[]
) {
	int opt;
	int optIndex = 0;
	struct option optLongues[] = {{"histo",0,NULL,'g'},{0,0,0,0}};
	while((opt = getopt_long(argc,argv,"ho:",optLongues,&optIndex))!=-1) {
		switch(opt) {
			case 'h' : *aide=1; break;
			case 'g' : *histogramme=1; break;
			case 'o' : 
				strcpy(destChemin,optarg);
				*changerNom=1;
				break;
			case '?' : 
				if (optopt == 'o') {
					printf("Option -%c nécessite un argument.\n",optopt);
				}
				else {
					if(isprint(optopt)) printf("Option '-%c' inconnue ou non supportée.\n",optopt);
					else printf("Option illisible : '\\x%x\\'.\n",optopt);
				}
			default : exit(EXIT_FAILURE);


		}
	}
}

void bouee() {
	printf("#### MINIGIMP ####\n");
	printf("## Par VALLET Gaëlle et THIEL Pierre ##\n");
	printf("Usage : $ minigimp mon_image.ppm [-h] [--histo] [<code_lut>[-<code_enveloppe>]* [_<param1>]*]* [-o Image_sortie.ppm]\n");
	printf("Options :\n");
	printf(" -h : aide;\n -o : changement de chemin du fichier de sortie; \n- -histo ou -g : enregistrement des histogrammes des fichiers d'entrée et de sortie;\n");
	printf("LUT : (intensités en pourcentage)\n");
	printf("ADDLUM et DIMLUM :  $ minigimp mon_image.ppm ADDLUM [intensité];\n");
	printf("ADDCON et DIMCON : 	$ minigimp mon_image.ppm ADDCON [intensité];\n");
	printf("INVERT : 			$ minigimp mon_image.ppm INVERT;\n");
	printf("NOIRETBLANC : 		$ minigimp mon_image.ppm NOIRETBLANC;\n");
	printf("SEPIA : 			$ minigimp mon_image.ppm SEPIA[intensité gradient(ADDLUM-ELLIPSE)] [demi-axe horizontal (ELLIPSE)] [demi-axe-vertical (ELLIPSE)];\n");
	printf("FLOU et FLOU2 : 	$ minigimp mon_image.ppm FLOU [intensité] [rayon (en nombre de pixels)]\n");
	printf("LUT :\n");
	printf("ELLIPSE et RELLIPSE :  $ inigimp mon_image.ppm LUT-ELLIPSE [intensité gradient] [[autre paramètre de LUT]* ]* [demi-axe horizontal] [demi-axe-vertical]\n");
}

void renommerChemin(int changerNom,char destChemin [],char srcChemin[],char ajout[],char extension[]) {
	char nom[TAILLE_CHEMIN_MAX];
	char cheminSans[TAILLE_CHEMIN_MAX];
	char nomSans[TAILLE_CHEMIN_MAX];
	if(!changerNom) {
		cheminVersNom(srcChemin,nom);
		retirerNom(srcChemin,cheminSans);
		retirerEx(nom,nomSans);
		/**/
		strcpy(destChemin,cheminSans);
		strcat(destChemin,nomSans);
		strcat(destChemin,ajout);
		strcat(destChemin,extension);
	}
}

void generalRenommer(int changerNom,char destChemin [],char srcChemin[],char destHistoChemin[],char srcHistoChemin[]) {
	renommerChemin(changerNom,destChemin,srcChemin,"_mg",".ppm");
	renommerChemin(0,srcHistoChemin,srcChemin,"_h",".ppm");
	renommerChemin(0,destHistoChemin,destChemin,"_h",".ppm");
}

void cheminVersNom(char chemin[],char nom[]) {
	int indice=-1;
	int i=0;
	int j=0;
	while(chemin[i]!='\0') {
		if(chemin[i]=='/') {
			indice=i;
		}
		i+=1;
	}	
	i=indice+1;
	if(indice!=-1) {
		while(chemin[i]!='\0') {
			nom[j] = chemin[i];
			i+=1;
			j+=1;
		}
		nom[j] = '\0';
	}
	else strcpy(nom,chemin);
}

void retirerNom(char chemin[],char cheminSans[]) {
	int indice=-1;
	int i=0;
	while(chemin[i]!='\0') {
		if(chemin[i]=='/') indice=i;
		i+=1;
	}
	i=0;
	if(indice!=-1) {
		while(i<=indice) {
			cheminSans[i] = chemin[i];
			i+=1;
		}
		cheminSans[i] = '\0';
	}
	else cheminSans = "";
}

void retirerEx(char nom[],char nomSans[]) {
	int indice=-1;
	int i=0;
	while(nom[i]!='\0') {
		if(nom[i]=='.') indice=i;
		i+=1;
	}
	i=0;
	if(indice!=-1) {
		while(i<indice) {
			nomSans[i] = nom[i];
			i+=1;
		}
		nomSans[i] = '\0';
	}
	else strcpy(nomSans,nom);
}