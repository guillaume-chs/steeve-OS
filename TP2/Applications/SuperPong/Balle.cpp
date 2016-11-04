#include "Balle.h"

/**
 * @file Balle.cpp
 * ImplÃ©mentation des mÃ©thodes de la classes Balle et initialisation de id Ã  0.
 */

Balle::Balle(Grille* laGrille) {

	Random random;

	grille = laGrille;
	vitesse = VITESSE;
	// Choisir une positon aleatoire hors de la zone gris'e :
	y = 1 + random.nextInt(LARGEUR);
	x = 1 + random.nextInt(HAUTEUR);

	// Occuper la case :
	grille->getCase(x,y)->occupe();
	// Choisir un deplacement aleatoire h_d, h_g, b_d, b_g:
	dx = 1 ;  if(random.nextBool()) dx = -dx ;
	dy = 1 ;  if(random.nextBool()) dy = -dy ;
};


void Balle::bouger() {
	//Avancer de (dx, dy) :
	int nx = x + dx ;
	int ny = y + dy ;
	//Deplacement : informer les cases de la presence ou non de la balle :
	grille->getCase(nx,ny)->occupe();
	grille->getCase(x,y)->libere();
	// Nouvelle position :
	x = nx ; y = ny ;
}


bool Balle::avance(){//Retourne false si la balle est perdu

	/****************************************************/
	/* Question 3 : Implementation de la méthode avance */
	/****************************************************/

	for(int i=0;i<vitesse;i++); // Attente active pour "freiner" la balle.

	/* Controler les Collisions avec les bords                                                        */
	/* la prochaine position de la balle sera en x=x+dx;y=y+dy;                                       */
	/* Il faut vérifier si la balle est en collision ou pas en x+dx et y+dy                           */
	/* (se servir des méthodes getCase et Etat de la classe grille)                                   */
	/* si c'est le cas sur un des deux voir les deux, il faut inverser le déplacement (dx=-dx etc...) */
	/* Une fois mise a jour, déplacez la balle                                                        */
	/* ne pas oublier d'afficher les cases modifiées                                                   */



}
