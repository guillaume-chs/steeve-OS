/*
 * Fax.h
 *
 *  Created on: 4 ao�t 2008
 *      Author: jmenaud
 */

#ifndef FAX_H_
#define FAX_H_

#include <drivers/Ecran.h>

class Fax {
public :
	/**
	 * @brief horloge comptant d'après les interruptions générerées par l'horloge.
	 * @param e écran pour l'affichage
	 * @param c permet d'utiliser le clavier pour arrêter l'horloge.
	 */
	void afficheImage(Ecran*);
	int RLEUncompress(unsigned char *output, unsigned char *input);

};

#endif /* FAX_H_ */
