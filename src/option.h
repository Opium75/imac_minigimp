#ifndef __FONCTIONS_OPTION

#define __FONCTIONS_OPTION

#include <getopt.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_CHEMIN_MAX 40

void attraperOptions(int argc,char *argv[],int*aide,int*histogramme,int*changerNom,char destNom[]);


void generalRenommer(int changerNom,char destChemin [],char srcChemin[],char destHistoChemin[],char srcHistoChemin[]);

void bouee();

void renommerChemin(int changerNom,char destChemin [],char srcChemin[],char ajout[],char extension[]);
void cheminVersNom(char chemin[],char nom[]);
void retirerNom(char chemin[],char cheminSans[]);
void retirerEx(char nom[],char nomSans[]);

#endif