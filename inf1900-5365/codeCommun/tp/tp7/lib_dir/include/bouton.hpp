#ifndef BOUTON_H
#define BOUTON_H
/**
 * Librairie bouton.hpp
 * Date : 09/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */

#include <stdint.h>

/* Annule l'effet de rebond d'un bouton
 *
 * --------------------------------------------------------------------
 * 
 * Vérifier si le bouton est actionné au moment où l'on appuie et 10ms plus tard afin d'annuler l'effet du rebond.
 * 
 * --------------------------------------------------------------------
 * 
 * Paramètre : 
 *    pin      : valeur que prend le port
 *    position : broche à modifier, en hexadécimal
 */
bool antirebond(volatile const uint8_t& pin, uint8_t position);

/* Attend le relâchement d'un bouton
 *
 * --------------------------------------------------------------------
 * 
 * Retourne True lorsque le bouton est relâché.
 * 
 * --------------------------------------------------------------------
 * 
 * Paramètre : 
 *    pin      : valeur que prend le port
 *    position : broche à modifier, en hexadécimal
 * 
 * --------------------------------------------------------------------
 * 
 * Valeur de retour :
 *    true : bouton relâché 
 *    (Pas de valeur de retour false)
 */
bool relachement(volatile const uint8_t& pin, uint8_t position);

#endif /* BOUTON_H */