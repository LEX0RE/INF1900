/**
 * @brief Librairie gérant les fonctions pour un bouton
 * @file bouton.hpp
 * @date 20/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#ifndef BOUTON_HPP
#define BOUTON_HPP

#define DELAI_ANTI_REBOND 10

#include "atmel.hpp"

/**
 * @brief Annule l'effet de rebond d'un bouton
 * @param pin port du bouton
 * @param position broche du bouton, en hexadécimal
 * @param inverse indique si le bouton est à 1 lorsqu'il est relâché
 * @return bool Vrai si le bouton a été appuyé
 */
bool antirebond(Port pin, uint8_t position, bool inverse = false);

/**
 * @brief Attend le relâchement d'un bouton
 * @param pin port voulu
 * @param position broche à modifier, en hexadécimal
 */
void relachement(Port pin, uint8_t position);

#endif /* BOUTON_HPP */