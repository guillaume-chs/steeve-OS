#include <hal/multiboot.h>
#include <drivers/Ecran.h>
#include <Applications/Fax/Fax.h>
#include <drivers/PortSerie.h>
#include <Applications/SuperPong/Grille.h>


extern "C" void Sextant_main(unsigned long magic, unsigned long addr){
	char beuf[250];
	Ecran ecran;
	Fax fax; // A d�commenter pourla question 3
	PortSerie ps; // A d�commenter pour la question 4
	// Grille grille(&ecran); // A decommenter pour la question 5

	/** Test de l'affichage **/
	/*** Affichage de chaines testant la prise en compte du défilement et '\n' ***/

	// Question 2 : Effacer l'Ecran

	ecran.effacerEcran(NOIR);

	ecran.afficherMot("Bienvenue a toi, petit terrien !\n",JAUNE);
	ecran.afficherMot("Bienvenue a toi, petit terrien !\n",JAUNE);
	ecran.afficherMot("Bienvenue a toi, petit terrien !\n",JAUNE);
	ecran.afficherMot("Bienvenue a toi, petit terrien !\n",JAUNE);

	ecran.afficherCaractere(24,72,BLEU,NOIR,'S');
	ecran.afficherCaractere(24,73,VERT,NOIR,'E');
	ecran.afficherCaractere(24,74,CYAN,NOIR,'X');
	ecran.afficherCaractere(24,75,ROUGE,NOIR,'T');
	ecran.afficherCaractere(24,76,MAGENTA,NOIR,'A');
	ecran.afficherCaractere(24,77,MARRON,NOIR,'N');
	ecran.afficherCaractere(24,78,GRIS_LEGER,NOIR,'T');

	// Question 3 : G�rer le d�filement de l'ecran en vous aidant de
	for(int i=0; i<20;i++){
		ecran.afficherMot("blabla\n",JAUNE);

	}
    ecran.defilement(2);

	// Question 3 : puis decodez le message du Fax

	fax.afficheImage(&ecran);


	// Question 4 : affichage sur port serie

	ps.ecrireMot("testtest");
//	ps.ecrireMot("tra\nlala1\nlala2\nlala3\nlala4\nlala5\nlala6\nlala7\nlala8\nlala9\nlala10\nlala11\nlala12\nlala13\nlala14\nlala15\nlala16\nlala17\nlala18\nlala19\nlala20\nlala21\nlala22\nlala23\nlala24\nlala25\nlala26\nlala27\nlala28\nlala29\nlala30\n");
//	ps.ecrireMot("testtest");
//	ps.ecrireMot("testtest");
//	ps.ecrireMot("testtest");
//	ps.ecrireMot("testtest");
//	ps.ecrireMot("testtest");

	// Question 5 : la Grille du Jeu

	// grille.affiche();

	// BONUS
	ecran.afficherChiffre(160);


	while(true);
}
