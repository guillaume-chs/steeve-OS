#include "SuperPong.h"

void SuperPong::init(Ecran* e,Clavier* c) {
	ecran=e;
	clavier=c;
	e->effacerEcran(NOIR);
	laGrille.init(e);
	laGrille.affiche();
}


void SuperPong::start() {
	char buffer[256];
	int  i;
	char *src;
	Balle balle(&laGrille);


// 	while (true) balle.avance(); /* a rajouter pour question 3 */

		if(clavier->testChar()) {

			src=clavier->getString();

			for(i=0;i<256-1 && src[i]!='\0';i++)
				buffer[i]=src[i];
			buffer[i]='\0';

			for(i=0;buffer[i]!='\0';i++) {
				/***************************/
				/* A FAIRE POUR QUESTION 2 */
				/***************************/

				// Il s'agit ici de récupérer les caractères entrés au claivier
				// Puis de tester leurs valeurs et les faire correspondre aux actions des raquettes
				// Pour rappel : s,x : monter/descendre raquette gauche
				//               n,j : monter/descendre raquette droite
		}
	}
}
