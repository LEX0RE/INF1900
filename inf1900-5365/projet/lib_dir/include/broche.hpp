/**
 * @brief Librairie pour la gestion des broches du Atmel
 * @file broche.hpp
 * @date 20/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#ifndef BROCHE_HPP
#define BROCHE_HPP

#include "atmel.hpp"

/**
 * @brief Modifie les bits désirés de pin
 * @param pin port à utiliser
 * @param position valeur en hexadécimale qui indique la position des bits à modifier dans la pin
 * @param valeur décide si les bits seront remplacés par des 1 (si true) ou des 0 (si false)
 */
void changerBit(Port pin, uint8_t position, bool valeur = 1);

/**
 * @brief Retourne la broche du port du Atmel. Peut être aussi utilisé pour comparer la valeur en paramètre (position)
 *        avec la valeur du Atmel
 * @param pin port à utiliser
 * @param position position en hexadécimale ou valeur de comparaison
 * @return bool la comparaison entre la position/valeur et les broches du Atmel
 */
bool obtenirBit(Port pin, uint8_t position);

/**
 * @brief Change la valeur d'une pin au complet
 * @param pin port à utiliser
 * @param valeur valeur en hexadécimale à mettre sur la pin
 */
void changerPin(Port pin, uint8_t valeur);

/**
 * @brief Permet d'envoyer une valeur à des broches sélectionnées. Les broches ne doivent pas nécessairement être successives
 * @param pin port à utiliser
 * @param position position en hexadécimale pour les broches
 * @param valeur valeur en hexadécimale à mettre aux broches
 */
void changerNumerique(Port pin, uint8_t position, uint8_t valeur);

#endif /* BROCHE_HPP */