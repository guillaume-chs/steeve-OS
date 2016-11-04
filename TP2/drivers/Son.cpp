#include "Son.h"


void Son::jouer(int nFrequence){

		int Div;
	    int tmp;
	       //Set the PIT to the desired frequency
	    Div = 1193180 / nFrequence;//on defini la valeur de compte a rebours a partir de la frequence et de la vitesse de l'oscillateur


	    //on informe le timer 2 qu'on va lui envoyer une nouvelle valeur de compte a rebours

	    // ici cela consiste a faire l etape 1 du fichier Sound Generation.txt
	    // a savoir envoyer 0xb6 au port 43h

        ecrireOctet( 0xb6,0x43);
    
	    ecrireOctet((int) (Div) ,0x42);//on envoie le bit bas
	    ecrireOctet((int) (Div >> 8),0x42);//on envoie le bit haut
	       //And play the sound using the PC speaker

	    tmp = lireOctet(0x61);//on connecte le timer 2 au speaker
	     if (tmp != (tmp | 3)) {//en binaire 3 = 11
	    	 tmp = (tmp | 3);
             // QUESTION TP N-1
             // A COMPLETER
	    	 // ---->>>>> il faut crire 'tmp' dans le port du speaker. Voir etape 3 du fichier Sound Generatrion.doc du rpertoire support
	    }

}

void Son::stop(){
	int tmp = lireOctet(0x61);
	if (tmp != (tmp & 252)) {//en binaire, 252 = 11111100
		ecrireOctet(tmp & 252,0x61);//on deconnecte le timer deux du speaker en mettant les deux derniers bits a 0
		}
}

int Son::puissance(int value, int oct){
	int tmp=value;
	int j=1;
	for(int i=0;i<oct;i++){
		tmp=tmp*2+j;
		j=-j;
	}
	return tmp;
}


void Son::note(char touche){
	switch(touche){
	case 'q':
		jouer(puissance(16,octave));//C=DO grave
	break;
	case 'z':
		jouer(puissance(17,octave));//C# =DO diese
	break;
	case 's':
		jouer(puissance(18,octave));//D=RE
	break;
	case 'e':
		jouer(puissance(19,octave));//D# =re diese
	break;
	case 'd':
		jouer(puissance(21,octave));//E=MI
	break;
	case 'f':
		jouer(puissance(22,octave));//F = FA
	break;
	case 't':
		jouer(puissance(23,octave));//f#= fa diese
	break;
	case 'g':
		jouer(puissance(24,octave));//g= sol
	break;
	case 'y':
		jouer(puissance(26,octave));//g#= sol diese
	break;
	case 'h':
		jouer(puissance(27,octave));//A = LA
	break;
	case 'u':
		jouer(puissance(29,octave));//A# = la diese
	break;
	case 'j':
		jouer(puissance(31,octave));//B = SI
	break;

	case 'k':
		jouer(puissance(33,octave));//C=DO aigu
	break;

	case 'b':
		octave--;//on passe a l'octave inferieure
	break;
	case 'n':
		octave++;//on passe a l'octave superieure
	break;

	default:
		stop();
	break;
	}
}
