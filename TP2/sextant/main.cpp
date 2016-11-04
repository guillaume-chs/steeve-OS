#include <hal/multiboot.h>
#include <drivers/Ecran.h>
#include <Applications/SuperPong/SuperPong.h>
#include <drivers/PortSerie.h>

#include <sextant/interruptions/idt.h>
#include <sextant/interruptions/irq.h>
#include <sextant/interruptions/handler/handler_tic.h>
#include <sextant/interruptions/handler/handler_clavier.h>
#include <drivers/timer.h>
#include <drivers/Clavier.h>
#include <drivers/Son.h>
#include <Applications/Horloge/Horloge.h>


extern "C" void Sextant_main(unsigned long magic, unsigned long addr){
//	char beuf[250];
	Ecran ecran;
//	PortSerie ps;
	Timer timer;
	Horloge h(&ecran,&timer);
	Clavier clavier;
	SuperPong jeux;

	idt_setup();
	irq_setup();
	//Initialisation de la frequence de l'horloge
	timer.i8254_set_frequency(1000);

	irq_set_routine(IRQ_TIMER, ticTac);
	asm volatile("sti\n");//Autorise les interruptions

	irq_set_routine(IRQ_KEYBOARD, handler_clavier);

	jeux.init(&ecran,&clavier);

	while(true) {h.afficheHeure();
					if (clavier.testChar()) jeux.start();
				}
}
