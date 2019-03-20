CC=gcc
CFLAGS=-Wall -ansi
LDFLAGS=-lm
OBJ = main.o entete.o image.o option.o lut.o gestion_lut.o transformation.o gestion_transformation.o histo.o couleur.o fonctions_annexes.o

all : $(PROG)

$(PROG): $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
		@echo Édition des liens : OUI

main.o: main.c entete.h image.h option.h gestion_lut.h histo.h
	$(CC) -o $@ -c $< $(CFLAGS)

entete.o: entete.c entete.h couleur.h
	$(CC) -o $@ -c $< $(CFLAGS)

image.o: image.c image.h entete.h couleur.h fonctions_annexes.h
	$(CC) -o $@ -c $< $(CFLAGS)

option.o : option.c option.h
	$(CC) -o $@ -c $< $(CFLAGS)

lut.o : lut.c lut.h image.h entete.h couleur.h enveloppe.h fonctions_annexes.h
	$(CC) -o $@ -c $< $(CFLAGS)

gestion_lut.o : gestion_lut.c gestion_lut.h lut.h fonctions_annexes.h image.h
	$(CC) -o $@ -c $< $(CFLAGS)

transformation.o : transformation.c transformation.h image.h fonctions_annexes.h
	$(CC) -o $@ -c $< $(CFLAGS)

gestion_transformation.o : gestion_transformation.c gestion_transformation.h transformation.h
	$(CC) -o $@ -c $< $(CFLAGS)

histo.o : histo.c histo.h image.h option.h couleur.h entete.h
	$(CC) -o $@ -c $< $(CFLAGS)
	
couleur.o : couleur.c couleur.h
	$(CC) -o $@ -c $< $(CFLAGS)

fonctions_annexes.o : fonctions_annexes.c fonctions_annexes.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o
