#ifndef DEL_HPP
#define DEL_HPP
/**
 * Librairie del.hpp
 * Date : 11/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */

#include <stdint.h>

/*
    définition:
    * Modifie les bits désirés de pin
    paramètres:
    * pin est la valeur que prend le port
    * position est une valeur qui indique la position des bits à modifier dans pin
    * valeur est le bool qui décide si les bits seront remplacés par des 1 (si true) ou des 0 (si false)
*/
void changerBit(volatile uint8_t* pin, uint8_t position, bool valeur = 1);

#endif /* DEL_HPP */