
#ifndef SEXTANT_PROCESSEUR_BUS_PORTS_TP1_PORTSERIE_H
#define SEXTANT_PROCESSEUR_BUS_PORTS_TP1_PORTSERIE_H

/**
 * Fonctions de d'interraction avec un port-série
 */


#include <hal/fonctionsES.h>
#define SERIAL_PORT 0x3F8

class PortSerie {
public:
    void ecrireMot(const char *mot);

}

#endif