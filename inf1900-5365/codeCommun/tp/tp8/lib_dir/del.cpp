/**
 * Fonction del.cpp
 * Date : 11/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */

#include <avr/io.h>
#include <util/delay.h>
#include "del.hpp"

void changerBit(volatile uint8_t* pin, uint8_t position, bool value){
    if (value == true)
        *pin |= position;
    else
        *pin &= ~position;
}
