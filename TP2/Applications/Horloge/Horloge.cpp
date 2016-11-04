#include "Horloge.h"

	/****************************************************/
	/* Question 1 : Implementation de la classe Horloge */
	/****************************************************/

Horloge::Horloge(Ecran* ecr,Timer *timer) {
	lEcran=ecr;
	leTimer=timer;
}

void Horloge::afficheHeure() {
// Recuperez les secondes courantes via la méthode getSeconde de leTimer
// Convertissez ces secondes en minutes secondes
// Affichez le résultat au milieu de la première ligne
}
