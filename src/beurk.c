/*beurk*/

	/*Calculer décalage éventuel*/
					/*	for(jLargeur=0;jLargeur<resteLargeur;jLargeur++) {
							v = imgRedim->largeur*ligne*resteHauteur + colonne*resteLargeur+ jLargeur;
							*(imgRedim->canaux[i]+v) = *((*img)->canaux[i]+h);
						}
						for(jHauteur=0;jHauteur<resteHauteur;jHauteur++) {
							v = imgRedim->largeur*(ligne*resteHauteur +jHauteur) + colonne*resteLargeur;
							*(imgRedim->canaux[i]+v) = *((*img)->canaux[i]+h);
						}*/

						if(!(resteHauteur%2)) /* PAIR*/{
							if((abs((*img)->hauteur/2 - (ligne))%((*img)->hauteur/2)) < ((resteHauteur+1)/2)  && (ligne+1) != (*img)->hauteur) {
								/*for(jLargeur=0;jLargeur<quotientLargeur;jLargeur++) {
									lj = ligne*quotientHauteur +jHauteur + vectDecalageLigne[colonne] ;
									cj = colonne*quotientLargeur + jLargeur + decalageColonne;
									v = imgRedim->largeur*lj + cj;
									*(imgRedim->canaux[i] + v ) = *((*img)->canaux[i]+h);
								}*/
								vectDecalageLigne[colonne]+=1;
							}
						}
						else {
							if((abs((*img)->hauteur/2 - (ligne+1))%((*img)->hauteur/2)) < ((resteHauteur+1)/2) && (ligne+1) != (*img)->hauteur) {
								/*for(jLargeur=0;jLargeur<quotientLargeur;jLargeur++) {
									lj = ligne*quotientHauteur +jHauteur + vectDecalageLigne[colonne] ;
									cj = colonne*quotientLargeur + jLargeur + decalageColonne;
									v = imgRedim->largeur*lj + cj;
									*(imgRedim->canaux[i] + v ) = *((*img)->canaux[i]+h);
								}*/
								vectDecalageLigne[colonne]+=1;
							}
						}
						if(!(resteLargeur%2)) {
							if((abs((*img)->largeur/2 - (colonne))%((*img)->largeur/2)) < ((resteLargeur+1)/2) && (colonne+1) != (*img)->largeur) {
							/*	for(jHauteur=0;jHauteur<quotientHauteur;jHauteur++) {
									lj = ligne*quotientHauteur +jHauteur + vectDecalageLigne[colonne];
									cj = colonne*quotientLargeur + jLargeur + decalageColonne;
									v = imgRedim->largeur*lj + cj;
									*(imgRedim->canaux[i] + v ) = *((*img)->canaux[i]+h);
								}*/
								decalageColonne+=1;
							}
						}
						else {
							if((abs((*img)->largeur/2 - (colonne+1))%((*img)->largeur/2)) < ((resteLargeur+1)/2) && (colonne+1) != (*img)->largeur) {
								/*for(jHauteur=0;jHauteur<quotientHauteur;jHauteur++) {
									lj = ligne*quotientHauteur +jHauteur + decalageLigne;
									cj = colonne*quotientLargeur + jLargeur + decalageColonne;
									v = imgRedim->largeur*lj + cj;
									*(imgRedim->canaux[i] + v ) = *((*img)->canaux[i]+h);
								}*/
								decalageColonne+=1;
							}
						}


else {
			printf("Inverse Quotient largeur : %d, hauteur : %d\n",inverseQuotientLargeur,inverseQuotientHauteur);
					printf("Reste largeur : %d, hauteur : %d\n",inverseResteLargeur,inverseResteHauteur);
					printf("Prop largeur : %lf, hauteur : %lf\n",propLargeur,propHauteur);
			/*RAPETISSEMENT*/
			for(ligne = 0; ligne< imgRedim->hauteur ; ligne++) {
				if(quotientLargeur>=1) {
					for(colonne = 0; colonne < (*img)->largeur; colonne++) {

					}
				}
				else {
					for(colonne = 0; colonne < imgRedim->largeur; colonne++) {
							h = imgRedim->largeur*ligne + colonne;
							/*quotient*/
							for(jLargeur=0;jLargeur<inverseQuotientLargeur;jLargeur++) {
								for(jHauteur=0;jHauteur<inverseQuotientHauteur;jHauteur++) {
									lj = ligne*inverseQuotientHauteur + jHauteur + vectDecalageLigne[colonne];
									cj = colonne*inverseQuotientLargeur + jLargeur + decalageColonne;
									v = (*img)->largeur*lj + cj;
									flotPoint = calculMoyenne(flotPoint,*((*img)->canaux[i]+v),(jLargeur+1)*(jHauteur+1)-1);
								}
							}
							compte = (jLargeur+1)*(jHauteur+1)-1;
							if((ligne+1)>(inversePropHauteur)*(vectDecalageLigne[colonne]+1)) {
								lj = (ligne+1)*inverseQuotientHauteur + vectDecalageLigne[colonne];
								for(jLargeur=0;jLargeur<=inverseQuotientLargeur;jLargeur++) {
									cj = colonne*inverseQuotientLargeur + decalageColonne+jLargeur;
									v = (*img)->largeur*lj + cj;
									flotPoint = calculMoyenne(flotPoint,*((*img)->canaux[i]+v),compte + (jLargeur+1));
								}
								vectDecalageLigne[colonne]+=1;
								
							}
						if((colonne+1)>(inversePropLargeur)*(decalageColonne+1)) {
							cj = (colonne+1)*inverseQuotientLargeur + decalageColonne;
							for(jHauteur=0;jHauteur<=inverseQuotientHauteur;jHauteur++) {
								lj = ligne*inverseQuotientHauteur + vectDecalageLigne[colonne+1] + jHauteur;
								v = (*img)->largeur*lj + cj;
								flotPoint = calculMoyenne(flotPoint,*((*img)->canaux[i]+v),compte + (jHauteur+1));
							}
							decalageColonne += 1;
						}

							*(imgRedim->canaux[i] + h) = (unsigned char)flotPoint;
					}
				}

			}
		}