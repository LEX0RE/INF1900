/**
 * Fonction robot.cpp
 * Date : 25/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */

#include <avr/io.h>
#include "include/atmel.hpp"
#include "include/del.hpp"
#include "include/eeprom.hpp"
#include "include/robot.hpp"
#include "include/timer.hpp"

void attendre(uint8_t valeur){
    delaiVariable(valeur * 25, 0);
}

void allumerDel(uint8_t valeur, volatile uint8_t* pin, uint8_t entree, uint8_t sortie){
    if(valeur <= 127){
        changerBit(pin, entree, false);
        changerBit(pin, sortie, true);
    }
    else{
        changerBit(pin, entree, true);
        changerBit(pin, sortie, false);
    }
}

void eteindreDel(volatile uint8_t* pin, uint8_t entree, uint8_t sortie){
    changerBit(pin, entree, false);
    changerBit(pin, sortie, false);
}

void allumerMatriceDel(uint8_t valeur, volatile uint8_t* pin){
    uint8_t matrice = 0x00;

    matrice |= (valeur & 0x0F) << 4;
    matrice |= (valeur & 0x10) >> 1;
    matrice |= (valeur & 0x20) >> 3;
    matrice |= (valeur & 0x40) >> 5;
    matrice |= (valeur & 0x80) >> 7;

    changerPin(pin, matrice);
}

void eteindreMatriceDel(volatile uint8_t* pin){
    changerPin(pin, 0x00);
}

void arreterMoteur(){
    Timer1* timer = Timer1::obtenirInstance();
    timer->modifierTop(0xFFFF, 0);
    timer->modifierTop(0xFFFF, 1);

    timer->arreterPWM(0);
    timer->arreterPWM(1);
}

void avancer(uint8_t valeur, volatile uint8_t* pin, uint8_t position, 
             unsigned int& direction, bool& recule) {
    Timer1* timer = Timer1::obtenirInstance();

    valeur = 255 - valeur;

    if(recule == true){
        recule = false;
        direction = (direction + 4) % 8;
    }

    if (valeur == 255){
        arreterMoteur();
    }
    else{
        timer->modifierModeComparaison(3, 0);
        timer->modifierModeComparaison(3, 1);

        timer->demarrerPWM(0);
        timer->demarrerPWM(1);

        timer->modifierTop(valeur, 0);
        timer->modifierTop(valeur, 1);

        changerBit(pin, position, 1);
    }
}

void reculer(uint8_t valeur, volatile uint8_t* pin, uint8_t position, 
             unsigned int& direction, bool& recule) {
    Timer1* timer = Timer1::obtenirInstance();

    valeur = 255 - valeur;

    if(recule == false){
        recule = true;
        direction = (direction + 4) % 8;
    }

    if (valeur == 255){
        arreterMoteur();
    }
    else{
        timer->modifierModeComparaison(3, 0);
        timer->modifierModeComparaison(3, 1);

        timer->demarrerPWM(0);
        timer->demarrerPWM(1);

        timer->modifierTop(valeur, 0);
        timer->modifierTop(valeur, 1);

        changerBit(pin, position, 0);
    }
}

void afficherDirection(unsigned int direction, volatile uint8_t* pinMDel, uint8_t positionMDel){
    *pinMDel &= ~(positionMDel);

    uint8_t test = 0x01;
    uint8_t broche1 = 0x00;
    uint8_t colonne = 0x00, rangee = 0x00;

    while(broche1 == 0){
        if (test & positionMDel)
            broche1 = test;

        test = test << 1;
    }

    *pinMDel |= broche1;
    *pinMDel |= broche1 << 1;
    *pinMDel |= broche1 << 2;

    switch(direction){
        case 0: // Nord
            colonne = broche1 << 1;
            rangee = broche1 << 5;
        break;
        case 1: // Nord - Ouest
            colonne = broche1 << 2;
            rangee = broche1 << 5;
        break;
        case 2: // Ouest
            colonne = broche1 << 2;
            rangee = broche1 << 4;
        break;
        case 3: // Sud - Ouest
            colonne = broche1 << 2;
            rangee = broche1 << 3;
        break;
        case 4: // Sud
            colonne = broche1 << 1;
            rangee = broche1 << 3;
        break;
        case 5: // Sud - Est
            colonne = broche1;
            rangee = broche1 << 3;
        break;
        case 6: // Est
            colonne = broche1;
            rangee = broche1 << 4;
        break;
        case 7: // Nord - Est
            colonne = broche1;
            rangee = broche1 << 5;
        break;
    }

    *pinMDel &= ~colonne;
    *pinMDel |= rangee;
}

void tournerDroite(volatile uint8_t* pinMoteur, uint8_t positionDirection,volatile uint8_t* pinMDel, uint8_t positionMDel, 
                   unsigned int& direction, bool recule) {
    Timer1* timer = Timer1::obtenirInstance();
    
    uint16_t vitesseA = *((uint16_t*)(timer->obtenirTop(0)));
    uint16_t vitesseB = *((uint16_t*)(timer->obtenirTop(1)));

    timer->modifierTop(0xFFFF, 0);
    timer->arreterPWM(0);
    timer->modifierTop(0xFF, 1);
    timer->demarrerPWM(1);

    if (recule == false){

        for(unsigned int i = 0; i < 2; i++){

            switch(direction){
                case 0:
                    direction = 7;
                break;
                default:
                    direction--;
                break;
            }

            afficherDirection(direction, pinMDel, positionMDel);

            if(i == 0)
                delaiVariable(2000, 0);
        }
    }
    else{

        for(unsigned int i = 0; i < 2; i++){

            switch(direction){
                case 7:
                    direction = 0;
                break;
                default:
                    direction++;
                break;
            }

            afficherDirection(direction, pinMDel, positionMDel);

            if(i == 0)
                delaiVariable(2000, 0);
        }
    }

    timer->modifierTop(vitesseA, 0);
    timer->modifierTop(vitesseB, 1);
    if((*((uint16_t*)(timer->obtenirTop(0))) == 0xFFFF) && (*((uint16_t*)(timer->obtenirTop(1))) == 0xFFFF)){
        timer->arreterPWM(0);
        timer->arreterPWM(1);
    }
}

void tournerGauche(volatile uint8_t* pinMoteur, uint8_t positionDirection,volatile uint8_t* pinMDel, uint8_t positionMDel, 
                   unsigned int& direction, bool recule){
    Timer1* timer = Timer1::obtenirInstance();

    uint16_t vitesseA = *((uint16_t*)(timer->obtenirTop(0)));
    uint16_t vitesseB = *((uint16_t*)(timer->obtenirTop(1)));

    timer->modifierTop(0xFF, 0);
    timer->demarrerPWM(0);
    timer->modifierTop(0xFFFF, 1);
    timer->arreterPWM(1);

    if (recule == false){

        for(unsigned int i = 0; i < 2; i++){

            switch(direction){
                case 7:
                    direction = 0;
                break;
                default:
                    direction++;
                break;
            }

            afficherDirection(direction, pinMDel, positionMDel);

            if(i == 0)
                delaiVariable(2000, 0);

        }
    }
    else{

        for(unsigned int i = 0; i < 2; i++){

            switch(direction){
                case 0:
                    direction = 7;
                break;
                default:
                    direction--;
                break;
            }

            afficherDirection(direction, pinMDel, positionMDel);

            if(i == 0)
                delaiVariable(2000, 0);
        }
    }

    timer->modifierTop(vitesseA, 0);
    timer->modifierTop(vitesseB, 1);
    if((*((uint16_t*)(timer->obtenirTop(0))) == 0xFFFF) && (*((uint16_t*)(timer->obtenirTop(1))) == 0xFFFF)){
        timer->arreterPWM(0);
        timer->arreterPWM(1);
    }
}

void debutBoucle(uint8_t valeur, uint8_t adresseMaximale){
    Eeprom* eeprom = Eeprom::obtenirInstance();
    uint8_t adresseDebut = eeprom->obtenirAdresse();
    uint8_t boucle = 0, donnee = 0;

    eeprom->changerAdresse(adresseMaximale);
    eeprom->lire(&boucle, sizeof(unsigned char));
    eeprom -= 1;
    boucle++;

    switch(boucle){
        case 0: case 1: // Boucles simples
            donnee = 0x01;
            eeprom->ecrire(&donnee);
            eeprom->ecrire(&valeur);
            eeprom->ecrire(&adresseDebut);
        break;
        case 255: // Cap pour ne pas écrire sur la mémoire
            donnee = boucle;
            eeprom->ecrire(&donnee);
        break;
        default: // Boucles imbriquées
            donnee = boucle;
            eeprom->ecrire(&donnee);
            eeprom += (2 * (boucle - 1));
            eeprom->ecrire(&valeur);
            eeprom->ecrire(&adresseDebut);
        break;
    }

    eeprom->changerAdresse(adresseDebut);
}

void finBoucle(uint8_t adresseMaximale){
    Eeprom* eeprom = Eeprom::obtenirInstance();
    int boucle = 0, valeur = 0;
    uint8_t donnee = 0x00;
    uint8_t adresseDebut = eeprom->obtenirAdresse(), adresseRetour = 0x00;

    eeprom->changerAdresse(adresseMaximale);
    uint8_t adresseBoucle = eeprom->obtenirAdresse(), temporaire = 0x00;

    eeprom->lire(&boucle, sizeof(unsigned char));

    switch(boucle){
        case 1: // Boucles simples
            eeprom->lire(&valeur, sizeof(unsigned char));

            if (valeur == 0){
                eeprom -= 2;
                donnee = 0xFF;
                eeprom->mettreAJour(&donnee);
                eeprom->mettreAJour(&donnee);
                eeprom->mettreAJour(&donnee);
                eeprom->changerAdresse(adresseDebut);
                return;
            }

            valeur--;
            eeprom -= 1;
            eeprom->mettreAJour(&valeur);
        break;
        case 255: // Cap pour ne pas écrire sur la mémoire
            boucle--;
            eeprom -= 1;
            eeprom->mettreAJour(&boucle);
            eeprom->changerAdresse(adresseDebut);
            return;
        break;
        default: // Boucles imbriquées
            eeprom += (2 * (boucle - 1));
            eeprom->lire(&valeur, sizeof(unsigned char));

            if (valeur == 0){
                eeprom -= 1;
                temporaire = eeprom->obtenirAdresse();
                eeprom->changerAdresse(adresseBoucle);
                boucle--;
                donnee = boucle;
                eeprom->mettreAJour(&donnee);
                eeprom->changerAdresse(temporaire);
                donnee = 0xFF;
                eeprom->mettreAJour(&donnee);
                eeprom->mettreAJour(&donnee);
                eeprom->changerAdresse(adresseDebut);
                return;
            }

            valeur--;
            eeprom -= 1;
            eeprom->mettreAJour(&valeur);
        break;
    }

    eeprom->lire(&adresseRetour, sizeof(unsigned char));
    eeprom->changerAdresse(adresseRetour);
}

void afficherInstruction(uint8_t& instruction){
    modifierNumerique(&PORTB, 0x01, instruction & 0x0f);
    modifierNumerique(&PORTB, 0x10, (instruction & 0xf0) >> 4);
}

void lireMemoire(){
    unsigned int direction = 0;
    bool recule = false;
    bool debut = false, fin = false;
    uint8_t instruction = 0, operande = 0;
    Timer1* timer = Timer1::obtenirInstance(1, 3, 3, 2, 3);
    Eeprom* eeprom = Eeprom::obtenirInstance();
    timer->arreterPWM(0);
    timer->arreterPWM(1);
    changerBit(&PORTD, 0x80, 1); // Direction

    uint8_t adresseMaximale = eeprom->obtenirAdresse();
    eeprom->changerAdresse(0x00);

    while(fin != true){
        eeprom->lire(&instruction, sizeof(unsigned char));
        eeprom->lire(&operande, sizeof(unsigned char));

        if (instruction == 0x01){ // Début
            afficherInstruction(instruction);
            debut = true;
        }
        else if (debut == true){
            afficherInstruction(instruction);

            switch(instruction){
                case 0x02: // Attendre
                    attendre(operande);
                break;
                case 0x44: // Allumer la DEL bicolore
                    allumerDel(operande, &PORTC, 0x1, 0x2);
                break;
                case 0x45: // Éteindre la DEL bicolore
                    eteindreDel(&PORTC, 0x1, 0x2);
                break;
                case 0x18: // Allumer la matrice de DEL
                    allumerMatriceDel(operande, &PORTA);
                break;
                case 0x19: // Éteindre la matrice de DEL
                    eteindreMatriceDel(&PORTA);
                break;
                case 0x60: case 0x61: // Arrêter moteur
                    arreterMoteur();
                break;
                case 0x62: // Avancer
                    avancer(operande, &PORTD, 0x80, direction, recule);
                break;
                case 0x63: // Reculer
                    reculer(operande, &PORTD, 0x80, direction, recule);
                break;
                case 0x64: // Tourner à droite
                    tournerDroite(&PORTD, 0x80, &PORTC, 0xFC, direction, recule);
                break;
                case 0x65: // Tourner à gauche
                    tournerGauche(&PORTD, 0x80, &PORTC, 0xFC, direction, recule);
                break;
                case 0xC0: // Début de la boucle
                    debutBoucle(operande, adresseMaximale);
                break;
                case 0xC1: // Fin de boucle
                    finBoucle(adresseMaximale);
                break;
                case 0xFF: // Fin
                    fin = true;
                break;
                default:
                break;
            }
        }
        
        afficherDirection(direction, &PORTC, 0xFC);
    }
}