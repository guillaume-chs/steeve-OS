#include "Horloge.h"

	/****************************************************/
	/* Question 1 : Implementation de la classe Horloge */
	/****************************************************/

Horloge::Horloge(Ecran* ecr,Timer *timer) {
	lEcran=ecr;
	leTimer=timer;
}

void Horloge::afficheHeure() {
// Recuperez les secondes courantes via la m�thode getSeconde de leTimer
// Convertissez ces secondes en minutes secondes
// Affichez le r�sultat au milieu de la premi�re ligne
}
