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
PROJECTNAME=libstatique

# Fichiers sources
PRJSRC= atmel.cpp bouton.cpp can.cpp broche.cpp eeprom.cpp \
		interruption.cpp timer.cpp usart.cpp debug.cpp \
		robot.cpp clavier.cpp moteurs.cpp chrono.cpp \
		temps.cpp manoeuvre.cpp affichage.cpp

# Inclusions additionnels
INC= -I include/

# Libraires a lier
LIBS=

# Niveau d'optimization
OPTLEVEL=s

# Programmer ID
AVRDUDE_PROGRAMMERID=usbasp


####### variables #######


#compilateur utilisé
CC=avr-gcc
#compilateur pour librairie
CLIB=ar
#pour copier le contenu d'un fichier objet vers un autre
OBJCOPY=avr-objcopy
#pour permettre le transfert vers le microcontroleur
AVRDUDE=avrdude
#pour supprimer les fichiers lorsque l'on appel make clean
REMOVE=rm -f
# HEXFORMAT -- format pour les fichiers produient .hex
HEXFORMAT=ihex


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
LDFLAGS=-crs


####### Cible (Target) #######


#Nom des cibles par defaut
TRG=$(PROJECTNAME).a
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
.PHONY: all install clean 

# Make all permet simplement de compiler le projet
all: $(TRG)
	@echo "La librairie a ete cree"

# Implementation de la cible
$(TRG): $(OBJDEPS)
	$(CLIB) $(LDFLAGS) $(TRG) $(OBJDEPS)

# Production des fichiers object
# De C a objet
%.o: %.c
	$(CC) $(CFLAGS) -c $< 
# De C++ a objet
%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

# Verification des dependances (header dependencies)
-include *.d

# Make install permet de compiler le projet puis
# d'ecrire le programme en memoire flash dans votre
# microcontroleur. Celui-ci doit etre branche par cable USB
install: $(HEXROMTRG)				
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMERID)   \
	-p $(MCU) -P -e -U flash:w:$(HEXROMTRG)
	@echo "confirmation commande make install"

# Make clean permet d'effacer tout les fichiers generes
# lors de la compilation
clean:
	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) $(HEXTRG) *.d *.o *.a
	@echo "Les fichiers objets ont ete effaces"

#####                    EOF                   #####