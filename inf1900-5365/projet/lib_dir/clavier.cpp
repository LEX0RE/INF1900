/**
 * @brief Définition des fonction pour le fichier clavier.hpp
 * @file clavier.cpp
 * @date 21/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#include "robot.hpp"
#include "broche.hpp"

#define POSITION_COLONNE 0b11100000
#define POSITION_RANGEE 0b00011100

uint8_t Robot::colonneClavier() {
    uint8_t colonne = 3;
    char replacement = PORTC2;

    for (uint8_t i = PORTC2; i <= PORTC4; i++) {
        if(obtenirBit(C, (1 << i))){
            colonne -= i - replacement;
            break;
        }
    }
    return colonne;
}

uint8_t Robot::rangeeClavier() { 
    uint8_t  rangee = 0;
    char replacement = PORTC5 - 1;
    uint8_t remplirCote = 7;
    uint8_t configurationPort = 0b00011111;

    modifierPort(C, configurationPort);
    changerBit(C, POSITION_COLONNE, 0);
    changerBit(C, POSITION_RANGEE, remplirCote);

    for (uint8_t i = PORTC5; i <= PORTC7; i++) {
        if(obtenirBit(C, (1 << i))){
            rangee = i - replacement;
            break;
        }
    }

    return rangee;
}

void Robot::obtenirClavier() {
    uint8_t colonne = 0, rangee = 0;
    uint8_t remplirCote = 7;
    uint8_t configurationPort = 0b11100011;

    // Obtention de la colonne
    colonne = colonneClavier();

    // Obtention de la rangée
    rangee = rangeeClavier();

    // Replacement du clavier
    modifierPort(C, configurationPort);
    changerBit(C, POSITION_COLONNE, remplirCote);
    changerBit(C, POSITION_RANGEE, 0);

    switch (colonne) {
    case 1: // Colonne 1

        switch (rangee) {
        case 1:
            changement_ = "1";
            frequence_ = 1;
        break;
        case 2:
            changement_ = "R";
            frequenceAffichage_ = AR;
        break;
        case 3: default:
            changement_ = "I";
            convertisseur_ = INTERNE;
        }

    break;
    case 2: // Colonne 2

        switch (rangee) {
        case 1:
            changement_ = "2";
            frequence_ = 2;
        break;
        case 2:
            changement_ = "V";
            frequenceAffichage_ = AV;
        break;
        case 3: default:
            changement_ = "E";
            convertisseur_ = EXTERNE;
        }

    break;
    case 3: default: // Colonne 3

        switch (rangee) {
        case 1:
            changement_ = "4";
            frequence_ = 4;
        break;
        case 2:
            changement_ = "C";
            frequenceAffichage_ = AC;
        break;
        case 3: default:
            changement_ = "#";
            if(affichage_ == DECIMAL)
                affichage_ = HEXADECIMAL;
            else
                affichage_ = DECIMAL;
                
            // Raffrachissement de l'affichage si en train d'afficher
            if (obtenirBit(B, 1 << PORTB7) == false && obtenirBit(D, 1 << PORTD7) == false)
                afficherVitesse();
        }

    }
}