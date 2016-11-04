#include "Grille.h"


Grille::Grille(){
}


Grille::Grille(Ecran* e){
	//Initialisation de la grille
	for(int x=0 ; x<HAUTEUR ; x++) {
		for(int y=0 ; y<LARGEUR ; y++) {
			tab[x][y].init(x,y);
			tab[x][y].setEcran(e);
			if(x==0 || x==(HAUTEUR-1))//Installation des bords
				tab[x][y].setCaseBord();
			if(y==0)
				if(x > HAUTEUR/3 && x< HAUTEUR*2/3)
					tab[x][y].setCaseTrou();//Installation du trou à gauche
				else
					tab[x][y].setCaseBord();
			if(y==(LARGEUR-1))
				if(x > HAUTEUR/3 && x< HAUTEUR*2/3)
					tab[x][y].setCaseTrou();//Installation du trou à droite
				else
					tab[x][y].setCaseBord();

		}
	}
	initRaquette(3,4);
};

void Grille::init(Ecran* e){
	//Initialisation de la grille
	for(int x=0 ; x<HAUTEUR ; x++) {
		for(int y=0 ; y<LARGEUR ; y++) {
			tab[x][y].init(x,y);
			tab[x][y].setEcran(e);
			if(x==0 || x==(HAUTEUR-1))//Installation des bords
				tab[x][y].setCaseBord();
			if(y==0)
				if(x > HAUTEUR/3 && x< HAUTEUR*2/3)
					tab[x][y].setCaseTrou();//Installation du trou à gauche
				else
					tab[x][y].setCaseBord();
			if(y==(LARGEUR-1))
				if(x > HAUTEUR/3 && x< HAUTEUR*2/3)
					tab[x][y].setCaseTrou();//Installation du trou à droite
				else
					tab[x][y].setCaseBord();

		}
	}
	initRaquette(3,4);
};

void Grille::monterRaquette(int gd){

	/***************************/
	/* A FAIRE POUR QUESTION 2 */
	/***************************/

	// il faut mettre a jour les cases de la grille
	// le parametre gd défini quelle est la raquette a deplacer
	// Dans config.h a été défini GAUCHE et DROITE
}

void Grille::descendreRaquette(int gd){
	/***************************/
	/* A FAIRE POUR QUESTION 2 */
	/***************************/
}

void Grille::initRaquette(int y,int lg){ // colonne, taille

	raqg.init(lg,y);
	raqd.init(lg,LARGEUR -1 - y);

	for(int i=0;i<=lg;i++) {
		tab[raqg.getHaut()+i][raqg.getY()].setCaseBord();
		tab[raqd.getHaut()+i][raqd.getY()].setCaseBord();
	}
}

Case* Grille::getCase(int x,int y) {
	return &tab[x][y];
}

void Grille::affiche(){
	for (int x=0 ; x<HAUTEUR ; x++) {
		for (int y=0 ; y<LARGEUR ; y++) {
			tab[x][y].paint();
		}
	}
};
