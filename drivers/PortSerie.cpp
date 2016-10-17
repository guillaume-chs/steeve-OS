#include "PortSerie.h"

PortSerie::ecrireMot(const char *mot) {
	int i=0;

	while(mot[i]!='\0'){ // '\0' : caract�re de fin
		ecrireOctet(mot[i], SERIAL_PORT);
		i++;
	}
}