#include "Grille.h"



Grille::Grille(Ecran* e){
	//Initialisation de la grille
	for(int x=0 ; x<HAUTEUR ; x++) {
		for(int y=0 ; y<LARGEUR ; y++) {
			tab[x][y].init(x,y);
			tab[x][y].setEcran(e);
			if(x==0 || x==(HAUTEUR-1))//Installation des bords
				tab[x][y].setCaseBord();
			if(y==0) {
				if(x > HAUTEUR/3 && x< HAUTEUR*2/3)
					tab[x][y].setCaseTrou();//Installation du trou � gauche
				else
					tab[x][y].setCaseBord();
			}
			if(y==(LARGEUR-1)) {
				if(x > HAUTEUR/3 && x< HAUTEUR*2/3)
					tab[x][y].setCaseTrou();//Installation du trou � droite
				else
					tab[x][y].setCaseBord();
			}
		}
	}
};



void Grille::affiche(){
	for(int x=0 ; x<HAUTEUR ; x++) {
		for(int y=0 ; y<LARGEUR ; y++) {
		    tab[x][y].paint();
		}
	}
};
