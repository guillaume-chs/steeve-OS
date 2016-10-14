/*
 * Fax.cpp
 *
 *  Created on: 4 août 2008
 *      Author: jmenaud
 */



#include "Fax.h"
#include "image_comprimee.h"

//JMMM

/*
	Décompress une chaine condee en RLE
*/
int Fax::RLEUncompress(unsigned char *output, unsigned char *input)
{
	signed char count;
	int i = 0;
	int j=0;
	int length =0;

    while (input[length] != '\0') length++;

	while (length > 0) {
		count = (signed char) *input++;
		if (count > 0) {/* replicate run */
			i += count;
			for (j=0;j<count;j++){
				*output=*input;
				output++;
			}
			input++;
			length -= 2;
		} else if (count < 0) {	/* literal run */
			i += (-count);
			count = (signed char) -count;

			for (j=0;j<count;j++){
				*output=*input;
				output++;
				input++;
			}
			length -= (count + 1);
		}		/* if */

	}			/* while */
	return i;
}

void Fax::afficheImage(Ecran* e)
{
	int i, j;
	char temp[10000];
	j = RLEUncompress((unsigned char *)temp, msg);
	e->afficherMot(temp,BLANC);

}
