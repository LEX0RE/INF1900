#ifndef IMPORTANT_H
#define IMPORTANT_H
/**
 * Librairie important.h
 * Date : 09/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */

#include <stdint.h>

enum uniteTemps {};

//position en hex
void changerBit(volatile uint8_t* pin, uint8_t position, bool valeur = 1);
//value en hex
bool antirebond(volatile const uint8_t& pin, uint8_t position);
//value en hex
bool relachement(volatile const uint8_t& pin, uint8_t position);

void delaiVariable(int delai);

#endif /* IMPORTANT_H */