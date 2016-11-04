#include <hal/fonctionsES.h>

static int ControlKeys;
static char leds;
int posBuf=0;
char buf[256];
bool modifBuf=false;

/**
 * Fonction permettant d'écrire un octet (caractère non signé) sur un port d'entrées/sorties
 */


void ecrireOctet(unsigned char value, int port){
	__asm__ volatile (
			"outb %b0,%w1"
			::"a" (value),"Nd" (port)
	);
}
void ecrireMot(ui16_t value,int port) {
	__asm__ volatile (
			"outw %w0,%w1"
			::"a" (value),"Nd" (port)
	);
}

/**
 * Fonction permettant de lire un octet à partir d'un port d'entrées/sorties
 */
unsigned char lireOctet(int port){
	unsigned char result;
	__asm__ volatile (
			"inb %w1,%0"
			:"=a" (result)
			:"Nd" (port)
	);
	return result;
}

ui16_t lireMot(int port) {
	ui16_t result;
	__asm__ volatile (
			"inw %w1,%w0"
			:"=a" (result)
			:"Nd" (port)
	);
	return result;
}


