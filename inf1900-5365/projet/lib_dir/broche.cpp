/**
 * @brief Définition des fonction pour le fichier broche.cpp
 * @file broche.cpp
 * @date 21/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#include <avr/io.h>
#include "include/broche.hpp"

void changerBit(Port pin, uint8_t position, bool value){
    if (value)
        *obtenirPort(pin) |= position;
    else
        *obtenirPort(pin) &= ~position;
}

bool obtenirBit(Port pin, uint8_t position){
    return *obtenirPin(pin) & position;
}

void changerPin(Port pin, uint8_t valeur){
    *obtenirPort(pin) = valeur;
}

void changerNumerique(Port pin, uint8_t position, uint8_t valeur){
    // Initialisation des valeurs de test pour vérifier les paramètres
    uint8_t testPosition = position, testValeur = valeur;
    uint8_t nombreBrochePosition = 0, nombreBrocheValeur = 0;
    uint8_t premierBit = 0x1, nombreBit = 8;
    // Compte le nombre de broche utilisé par la position
    for(uint8_t i = 0; i < nombreBit; i++){
        if (testPosition & premierBit)
            nombreBrochePosition++;
        testPosition = testPosition >> 1;
    }
    // Compte le nombre de broche utilisé par la valeur en comptant les 0 moins significatifs
    while(testValeur != 0){
        nombreBrocheValeur++;
        testValeur = testValeur >> 1;
    }
    // Met la valeur dans les broches associées à la position
    if (nombreBrocheValeur <= nombreBrochePosition){
        *obtenirPort(pin) &= ~position;
        
        for(uint8_t i = 0; i < nombreBit; i++){
            if (position & premierBit){ // Détermine si on doit mettre un chiffre à la position
                *obtenirPort(pin) |= (valeur & premierBit) << i;
                valeur = valeur >> 1;
            }
            position = position >> 1;
        }
    }
}
