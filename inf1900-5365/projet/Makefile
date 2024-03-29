########       AVR Project Makefile       ########
#####                                        #####
#####         Makefile modifié par           #####
#####   Alexandre Gélinas, Maxence Sigouin,  #####
#####  Ioana Daria Danciu et Vincent Grenier #####
#####           INF1900 - 2021               #####
#####                                        #####
#####      Makefile produit et ecrit par     #####
#####   Simon Barrette & Jerome Collin pour  #####
#####           INF1900 - 2016               #####
#####                                        #####
#####         Inspire de Pat Deegan -        #####
#####  Psychogenic Inc (www.psychogenic.com) #####
##################################################


#####      Details specifique a la cible       #####


# Nom du microcontroleur cible
MCU=atmega324pa

# Nom de votre projet
PROJECTNAME=exec_dir/main

# Fichiers sources
PRJSRC= exec_dir/main.cpp

# Inclusions additionnels)
INC= -I lib_dir -I lib_dir/include

# Libraires a lier
LIBS= -L lib_dir -l:libstatique.a

# Niveau d'optimization
OPTLEVEL=s

# Programmer ID
AVRDUDE_PROGRAMMERID=usbasp

LFFLAGS=-Wl,-u,vfprintf -lprintf_flt -lm


####### variables #######


#compilateur utilise
CC=avr-gcc
#pour copier le contenu d'un fichier objet vers un autre
OBJCOPY=avr-objcopy
#pour permettre le transfert vers le microcontroleur
AVRDUDE=avrdude
#pour supprimer les fichiers lorsque l'on appel make clean
REMOVE=rm -f
# HEXFORMAT -- format pour les fichiers produient .hex
HEXFORMAT=ihex

EXECDIR=exec_dir/


####### Options de compilation #######


# Flags pour le compilateur en C
CFLAGS=-I. -I/usr/include/simavr  -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-std=c++14 -fpack-struct -fshort-enums             \
	-funsigned-bitfields -funsigned-char    \
	-Wall    \
	-DF_CPU=8000000UL

# Flags pour le compilateur en C++
CXXFLAGS=-fno-exceptions     

# Linker pour lier les librairies utilisees
LDFLAGS=-Wl,-Map,$(TRG).map -mmcu=$(MCU)



####### Cible (Target) #######


#Nom des cibles par defaut
TRG=$(PROJECTNAME).elf
HEXROMTRG=$(PROJECTNAME).hex
HEXTRG=$(HEXROMTRG) $(PROJECTNAME).ee.hex


####### Definition de tout les fichiers objets #######


# Fichier C
CFILES=$(filter %.c, $(PRJSRC))
# Fichier C++
CPPFILES=$(filter %.cpp, $(PRJSRC))

# Liste de tout les fichiers objet que nous devons creer
OBJDEPS=$(CFILES:.c=.o) \
	$(CPPFILES:.cpp=.o)


####### Creation des commandes du Makefile ####### 


# Creation des cibles Phony (Phony Target)
.PHONY: all install clean streams gtkterm progeeprom

# Make all permet simplement de compiler le projet
all: $(TRG) $(HEXROMTRG)

# Implementation de la cible
$(TRG): $(OBJDEPS)
	cd lib_dir && $(MAKE)
	$(CC) $(LDFLAGS) -o $(TRG) $(OBJDEPS) \
	-lm $(LIBS) $(LFFLAGS)

# Production des fichiers object
# De C a objet
%.o: %.c
	$(CC) $(CFLAGS) -c $<
# De C++ a objet
%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

# Verification des dependances (header dependencies)
-include *.d

# Production des fichiers hex a partir des fichiers elf
%.hex: %.elf
	$(OBJCOPY) -j .text -j .data \
		-O $(HEXFORMAT) $< $@

# Make install permet de compiler le projet puis
# d'ecrire le programme en memoire flash dans votre
# microcontroleur. Celui-ci doit etre branche par cable USB
install: $(HEXROMTRG)				
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMERID)   \
	-p $(MCU) -P -e -U flash:w:$(HEXROMTRG)

# Make clean permet d'effacer tout les fichiers generes
# lors de la compilation
clean:
	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) $(HEXTRG) *.d *.o $(EXECDIR)*.d
	cd lib_dir && $(MAKE) clean

# Make streams permet d'activer les échanges via le RS-232
streams:
	gnome-terminal -- socat -d -d pty,raw,echo=0 pty,raw,echo=0

# Make gtkterm permet d'ouvrir un terminal de GTKTerm
gtkterm:
	gtkterm &

# Make progeeprom permet de compiler le fichier texte en fichier
# binaire pour les instructions du robot
progeeprom:
	$(EXECDIR)progeeprom -v -o $(EXECDIR)program $(EXECDIR)program.txt
	od -v -t x1 $(EXECDIR)program

#####                    EOF                   #####
