#ifndef HORLOGE_H
#define HORLOGE_H

#include <drivers/Ecran.h>
#include <drivers/Clavier.h>
#include <sextant/types.h>
#include <drivers/timer.h>

/**
 * @file Horloge.h
 * @class Horloge
 * @brief Une horloge digitale convertissant les secondes fournies par la methode
 * getSeconde() de la classe Timer en minutes secondes affich�e au milieu de la premi�re ligne
 */
class Horloge {
	Ecran *lEcran;
	Timer *leTimer;
public :
	/**
	 * @brief horloge comptant d'apres les interruptions générerées par l'horloge.
	 * @param e ecran pour l'affichage
	 * @param t permet d'utiliser le clavier pour arrêter l'horloge.
	 */
	Horloge(Ecran* e,Timer* t);
	void afficheHeure();

};

#endif
