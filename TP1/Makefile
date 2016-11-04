OS=$(shell uname)
COMPILATEUR=CPP_$(OS)
LIEUR=LD_$(OS)
COMPILATEUR_OPTION=COMPOP_$(OS)
LIEUR_OPTION=LIEUR_$(OS)

#-------------------
##Pour Mac
CPP_Darwin=i386-elf-g++-4.3.2
LD_Darwin=i386-elf-ld

#-------------------
##Pour Linux
CPP_Linux=g++
LD_Linux=ld
COMPOP_Linux=-fno-stack-protector -m32
LIEUR_Linux=-m elf_i386

#-------------------
##POUR WINDOWS
CPP_WindowsNT=g++
LD_WindowsNT=ld
 
#-------------------
## Partie commune a toutes les configurations

CPPFLAGS  = -gdwarf-2 -g3 -Wall -Wno-narrowing -fno-builtin -fno-rtti -fno-exceptions -nostdinc $($(COMPILATEUR_OPTION))
LDFLAGS = --warn-common -nostdlib $($(LIEUR_OPTION))

PWD :=.
DELE = rm
MV = mv -f


KERNEL_OBJ   = sextant.elf

# Main target
all: $(KERNEL_OBJ)

$(KERNEL_OBJ): multiboot.o main.o ES.o Ecran.o PortSerie.o Fax.o Case.o Grille.o
	echo 'Votre compilateur $(COMPILATEUR) et votre lieur $(LIEUR)'
	$($(LIEUR)) $(LDFLAGS) -T ./support/sextant.lds -o build/boot/$@ build/all-o/main.o build/all-o/ES.o build/all-o/multiboot.o build/all-o/Ecran.o build/all-o/PortSerie.o build/all-o/Fax.o build/all-o/Case.o build/all-o/Grille.o

multiboot.o: hal/multiboot.S
	$($(COMPILATEUR)) -I.  -c hal/multiboot.S $(CPPFLAGS) -DASM_SOURCE=1 -o build/all-o/multiboot.o

main.o: sextant/main.cpp
	$($(COMPILATEUR)) -I.  -c sextant/main.cpp $(CPPFLAGS) -o build/all-o/main.o

Ecran.o : drivers/Ecran.cpp
	$($(COMPILATEUR)) -I.  -c drivers/Ecran.cpp $(CPPFLAGS) -o build/all-o/Ecran.o

ES.o : hal/fonctionsES.cpp
	$($(COMPILATEUR)) -I.  -c hal/fonctionsES.cpp $(CPPFLAGS) -o build/all-o/ES.o

PortSerie.o : drivers/PortSerie.cpp
	$($(COMPILATEUR)) -I.  -c drivers/PortSerie.cpp $(CPPFLAGS) -o build/all-o/PortSerie.o

Fax.o : Applications/Fax/Fax.cpp
	$($(COMPILATEUR)) -I.  -c Applications/Fax/Fax.cpp $(CPPFLAGS) -o build/all-o/Fax.o

Case.o : Applications/SuperPong/Case.cpp
	$($(COMPILATEUR)) -I.  -c Applications/SuperPong/Case.cpp $(CPPFLAGS) -o build/all-o/Case.o

Grille.o : Applications/SuperPong/Grille.cpp
	$($(COMPILATEUR)) -I.  -c Applications/SuperPong/Grille.cpp $(CPPFLAGS) -o build/all-o/Grille.o

# Clean directory
clean:
	$(DELE) -rf build/all-o/*.o
	$(REM) -f *.s
	$(REM) -f build/boot/*.elf
	
