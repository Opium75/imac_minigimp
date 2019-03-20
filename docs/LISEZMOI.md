# MINIGIMP
## Par VALLET Gaëlle et THIEL Pierre
=======

## Description générale

_minigimp_ est un programme de traitement d'image codé en C dans le cadre du cours de Programmation et Algorithmique 1 en IMAC. Il supporte en entrée les fichiers images de type PPM (P6), et renvoie un fichier image de ce même format.
Il peut être compilé et utilisé en l'état sous Linux.

Usage : $ minigimp mon_image.ppm [-h] [--histo] [|code_lut|[-|code_enveloppe|]* [_|param|]*]* [-o Image_sortie.ppm]
Les LUT peuvent êtres concaténés sans restriction

On prendra le répertoire racine du projet comme référence  dans tous les chemins indiqués.
---

##Arguments

Options :

* -h : aide;
* -o : changement de chemin du fichier de sortie;
* --histo ou -g : enregistrement des histogrammes des fichiers d'entrée et de sortie;

LUT : les intensités sont en pourcentage.  
* ADDLUM et DIMLUM : _ADDLUM [intensité]_ ;  
	$ ./bin/minigimp ./images/test.ppm ADDLUM 30 -o ./images/test_addlum_30.ppm --histo  
	$ ./bin/minigimp ./images/test.ppm DIMLUM 60 -o ./images/test_dimlum_60.ppm --histo  
* ADDCON et DIMCON : _ADDCON [intensité]_;  
	$ ./bin/minigimp ./images/test.ppm ADDCON 50 -o ./images/test_addcon_50.ppm --histo  
	$ ./bin/minigimp ./images/test.ppm DIMCON 80 -o ./images/test_dimcon_80.ppm --histo  
* INVERT : _INVERT_;  
	$ ./bin/minigimp ./images/test.ppm INVERT -o ./images/test_invert.ppm --histo  
* NOIRETBLANC : _NOIRETBLANC_;  
	$ ./bin/minigimp ./images/test.ppm NOIRETBLANC -o ./images/test_noietblanc.ppm --histo  
* SEPIA : _SEPIA [intensité gradient(ADDLUM-ELLIPSE)] [demi-axe horizontal (ELLIPSE)] [demi-axe-vertical (ELLIPSE)]_;  
	$ ./bin/minigimp ./images/test.ppm SEPIA 70 80 80 -o ./images/test_sepia_70_80_80.ppm --histo  
* FLOU et FLOU2 : _FLOU [intensité] [rayon (en nombre de pixels)]_;  
	$ ./bin/minigimp ./images/test.ppm FLOU 80 8 -o ./images/test_flou_80_8.ppm --histo  
	$ ./bin/minigimp ./images/test.ppm SEPIA 80 8 -o ./images/test_flou2_80_8.ppm --histo  
FLOU est itératif et naïf, FLOU2 est récursif et très imprécis, mais plus efficace en temps.  

Enveloppes :  
* ELLIPSE et RELLIPSE : _LUT-ELLIPSE [intensité gradient] [[autre paramètre de LUT]* ]* [demi-axe horizontal (pourcentage de largeur/2)] [demi-axe-vertical(pourcentage de hauteur/2]_;  
	$ ./bin/minigimp ./images/test.ppm FLOU-ELLIPSE 70 10 30 30 -o ./images/test_flou-ellipse_70_10_30_30.ppm --histo  
	$ ./bin/minigimp ./images/test.ppm ADDLUM-RELLIPSE 40 60 80 -o ./images/test_addlum-rellipse_40_60_80.ppm --histo  
ELLIPSE compose un gradient vers l'extérieur de l'ellipse, et RELLIPSE vers l'intérieur.  

---
