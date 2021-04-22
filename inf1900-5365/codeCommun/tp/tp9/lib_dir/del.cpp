/**
 * Fonction del.cpp
 * Date : 11/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */

#include <avr/io.h>
#include "include/del.hpp"

void changerBit(volatile uint8_t* pin, uint8_t position, bool value){
    if (value == true)
        *pin |= position;
    else
        *pin &= ~position;
}

bool obtenirBit(volatile uint8_t* pin, uint8_t position){
    return *pin & position;
}

void changerPin(volatile uint8_t* pin, uint8_t valeur){
    *pin = valeur;
}

void modifierNumerique(volatile uint8_t* pin, uint8_t position, uint8_t valeur){
    changerBit(pin, position, valeur & 0x1);
    changerBit(pin, position << 1, valeur & 0x2);
    changerBit(pin, position << 2, valeur & 0x4);
    changerBit(pin, position << 3, valeur & 0x8);
}