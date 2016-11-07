#include <hal/multiboot.h>
#include <drivers/Ecran.h>
#include <Applications/SuperPong/SuperPong.h>
#include <drivers/PortSerie.h>

// TP2
#include <sextant/interruptions/idt.h>
#include <sextant/interruptions/irq.h>
#include <sextant/interruptions/handler/handler_tic.h>
#include <sextant/interruptions/handler/handler_clavier.h>
#include <drivers/timer.h>
#include <drivers/Clavier.h>
#include <Applications/Horloge/Horloge.h>
// TP3
#include <sextant/memoire/memoire.h>

// TP4
#include <sextant/ordonnancements/cpu_context.h>
#include <sextant/ordonnancements/cooperatif/coop-thread.h>
#include <sextant/types.h>


extern char __e_kernel,__b_kernel, __b_data, __e_data,  __b_stack, __e_load ;
int i;

extern vaddr_t bootstrap_stack_bottom; //Adresse de début de la pile d'exécution
extern size_t bootstrap_stack_size;//Taille de la pile d'exécution


struct cpu_state *ctxt_hello1;
struct cpu_state *ctxt_hello2;
struct cpu_state *ctxt_main;
vaddr_t hello1_stack, hello2_stack;
char tab1[1024];
char tab2[1024];

Ecran ecran;

/*** Question 1 */

void endlessfunc(Ecran *ec) {
	unsigned char tmp[]="Buffer";

	unsigned int* piRet;
	unsigned int diff=0;


	ec->afficherMot((const char*)tmp,BLANC);

	piRet=(unsigned int *)&ec;
	piRet--;
	diff=(unsigned int)piRet-(unsigned int)&(tmp[0]);


	/* Message de debug (facilitant la compr�hension)*/
	ec->sautDeLigne();
/*
	ec->afficherMot("Adresse ou est tmp : ",BLANC);
	ec->afficherBase((unsigned int)&(tmp[0]),16,BLANC);
	ec->sautDeLigne();
	ec->afficherMot("Adresse ou est piRet : ",BLANC);
	ec->afficherBase((unsigned int)&piRet,16,BLANC);
	ec->sautDeLigne();
	ec->afficherMot("Adresse pointee par piRet : ",BLANC);
	ec->afficherBase((unsigned int)piRet,16,BLANC);
	ec->sautDeLigne();
	ec->afficherMot("Adresse ou est diff :",BLANC);
	ec->afficherBase((unsigned int)&diff,16,BLANC);
	ec->sautDeLigne();
	ec->afficherMot("Difference entre piRet et tmp : ",BLANC);
	ec->afficherBase((unsigned int)diff,10,BLANC);
	ec->sautDeLigne();*/


	tmp[0]='O';
	tmp[1]='V';
	tmp[2]='E';
	tmp[3]='R';
	tmp[4]='F';
	tmp[5]='L';
	tmp[6]='O';
	tmp[7]='W';
	tmp[8]='!';

	piRet=(unsigned int*)&(tmp[diff]);
	tmp[diff]=*piRet-5;

}

/*** fin Question 1 */


static void reclaim_stack(vaddr_t stack_vaddr)
{
// Vide pour l'instant
}

static void exit_hello12(vaddr_t stack_vaddr)
{
  cpu_context_exit_to(ctxt_main, (cpu_kstate_function_arg1_t*) reclaim_stack, stack_vaddr);
}

/*** Question 2 */

static void hello1 (char *str)
{
  for ( ; *str != '\n' ; str++)
    {
	  ecran.afficherCaractere(BLANC,NOIR,*str);
	  /* Surement */
	  /* qq chose a ajouter */
}
}


static void hello2 (char *str)
{
  char temp[25];

  for ( ; *str != '\n' ; str++)
    {
	  ecran.afficherCaractere(BLANC,NOIR,*str);
	  /* Surement */
	  /* qq chose a ajouter */
    }
}


void print_hello_world ()
{
  #define DEMO_STACK_SIZE 1024

  /* Allocate the stacks */

  hello1_stack = (vaddr_t) tab1;
  hello2_stack = (vaddr_t) tab2;

  /* Initialize the coroutines' contexts */
  cpu_kstate_init(&ctxt_hello1,
                      (cpu_kstate_function_arg1_t*) hello1,
                      (ui32_t) "Hlowrd\n",
                      (vaddr_t) hello1_stack, DEMO_STACK_SIZE,
                      (cpu_kstate_function_arg1_t*) exit_hello12,
                      (ui32_t) hello1_stack);

  cpu_kstate_init(&ctxt_hello2,
                      (cpu_kstate_function_arg1_t*) hello2,
                      (ui32_t) "el ol\n",
                      (vaddr_t) hello2_stack, DEMO_STACK_SIZE,
                      (cpu_kstate_function_arg1_t*) exit_hello12,
                      (ui32_t) hello2_stack);

  /* Go to first coroutine */
  cpu_context_switch(&ctxt_main, ctxt_hello1);

}
/*** fin Question 2 */

/*** Question 4 */

static void thr_hello1 (char *str)
{
  char temp[25];

  for ( ; *str != '\n' ; str++)
    {
	  ecran.afficherCaractere(BLANC,NOIR,*str);
      thread_yield();
    }
  thread_exit();

}


static void thr_hello2 (char *str)
{
  char temp[25];

  for ( ; *str != '\n' ; str++)
    {
	  ecran.afficherCaractere(BLANC,NOIR,*str);
      thread_yield();
    }
  thread_exit();
}



void thr_print_hello_world ()
{

  create_kernel_thread("YO[b]", (kernel_thread_start_routine_t) thr_hello2, (void*) "Hlowrd\n");
  create_kernel_thread("YO[b]", (kernel_thread_start_routine_t) thr_hello1, (void*) "el ol\n");

}
/*** fin Question 4 */

/*** Question 5 */

static void preemp_thr_hello1 (char *str)
{
  char temp[25];

  for ( ; *str != '\n' ; str++)
    {
	  ecran.afficherCaractere(BLANC,NOIR,*str);
    }
  thread_exit();

}


static void preemp_thr_hello2 (char *str)
{
  char temp[25];

  for ( ; *str != '\n' ; str++)
    {
	  ecran.afficherCaractere(BLANC,NOIR,*str);
    }
  thread_exit();
}



void preemp_thr_print_hello_world ()
{

  create_kernel_thread("YO[b]", (kernel_thread_start_routine_t) preemp_thr_hello2, (void*) "Hlowrd\n");
  create_kernel_thread("YO[b]", (kernel_thread_start_routine_t) preemp_thr_hello1, (void*) "el ol\n");

}

/*** fin Question 5 */

extern "C" void Sextant_main(unsigned long magic, unsigned long addr){
//	char beuf[250];
//	Ecran ecran;
//	Fax *fax;
//	SuperPong *test;
//	PortSerie ps;
	Timer timer;
//	Grille grille(&ecran);
//	Horloge h(&ecran,&timer);
//	Clavier clavier;
//	SuperPong jeux;

	endlessfunc(&ecran);

	idt_setup();
	irq_setup();
	//Initialisation de la frequence de l'horloge

	timer.i8254_set_frequency(1000);
	irq_set_routine(IRQ_TIMER, ticTac);
	asm volatile("sti\n");//Autorise les interruptions

	irq_set_routine(IRQ_KEYBOARD, handler_clavier);

	multiboot_info_t* mbi;
	mbi = (multiboot_info_t*)addr;

	mem_setup(& __e_kernel,(mbi->mem_upper<<10) + (1<<20),&ecran);

	ecran.effacerEcran(NOIR);

	ecran.afficherMot("Fin OverFlow!!!\n");

	while(true);

	/* Etude du fichier cpu_context.cpp et cpu_context_switch */
	/* changement de context 'a la main' */

	print_hello_world ();

	ecran.sautDeLigne();
	ecran.afficherMot("Genial le Hello World 'a la main'  !!!");

	while(true);

	/* Etude du fichier thread.cpp */
	/* changement de contexte cooperatif */

	thread_subsystem_setup(bootstrap_stack_bottom,bootstrap_stack_size);
	sched_subsystem_setup();

	thr_print_hello_world();

	ecran.sautDeLigne();
	/* Q4 */
	// qqchose
	// qq chose
	// qq chose
	// qq chose

	ecran.sautDeLigne();
	ecran.afficherMot("Genial le Hello World 'cooperatif'  !!!");

	while(true);

	preemp_thr_print_hello_world();

	/* Q5 */
	// THE ligne

		while (true);

}
