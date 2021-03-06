/*
 * memoire.cpp
 *
 *  Created on: 27 ao�t 2008
 *      Author: jmenaud
 */
#include "memoire.h"

void *debut;
int taille;
Ecran *ec;

void mem_setup(void * begin, int size,Ecran *ecran) {
	debut=begin;
	taille=size;
	ec=ecran;
}


void * getmem(long unsigned int nbytes)
{
	void *adresse;
	char *temp;
	int i = (int) debut;

	/* QUESTION 6 */

	ec->sautDeLigne();
	ec->afficherMot("Adresse de debut : ");
	ec->sautDeLigne();
	ec->afficherMot("Taille passee en param de getmem : ");
	ec->sautDeLigne();
	ec->afficherMot("Adresse de fin : ");
	ec->sautDeLigne();

	adresse = debut;
	debut = (void *) i;

	return adresse;
}

void* operator new(long unsigned int taille) {
	void * temp;

	temp = getmem(taille);

	ec->afficherMot("Entree dans constructeur, adresse :  ",BLANC);
	ec->sautDeLigne();
	ec->afficherMot("Entree dans constructeur, taille :  ",BLANC);
	ec->sautDeLigne();

	return temp;
}
