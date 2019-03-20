#include "couleur.h"

int nbCanaux(FormatCouleur format) {
	switch(format) {
		case NDG : return MONOCHROME;
		case RVB  : return TRICHROME;
		default :
			printf("Erreur de comptage du nombre de canaux.\n");
			exit(EXIT_FAILURE);
	}
}