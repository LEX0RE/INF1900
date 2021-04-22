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

/** Modifie les bits désirés de pin
 * 
 * -------------------------------------------------------------
 * 
 * Paramètres:
 *
 *      pin:        valeur que prend le port
 *      position:   valeur en hexadécimale qui indique la position des bits à modifier dans la pin
 *      valeur:     décide si les bits seront remplacés par des 1 (si true) ou des 0 (si false)
 */
void changerBit(volatile uint8_t* pin, uint8_t position, bool valeur = 1);

/** Modifie les bits pour pouvoir afficher en numérique sur 4 broches
 * 
 * -------------------------------------------------------------
 * 
 * Paramètres:
 *
 *      pin:        valeur que prend le port
 *      position:   position de départ en hexadécimale pour les 4 borches
 *      valeur:     valeur en hexadécimale à afficher
 */
void modifierNumerique(volatile uint8_t* pin, uint8_t position, uint8_t valeur);


/** Retourne la valeur du bit sélectionné
 * 
 *  Peut aussi servir de comparaison avec la valeur actuelle de la pin
 *
 * -------------------------------------------------------------
 * 
 * Paramètres:
 *
 *      pin:        valeur que prend le port
 *      position:   position en hexadécimale
 *
 * -------------------------------------------------------------
 * 
 * Valeur de retour:
 *
 *      booléan: 1 si la position sélectionnée a tout ses bits à 1 sur le port
 */
bool obtenirBit(volatile uint8_t* pin, uint8_t position);

/** Change la valeur d'une pin au complet
 * 
 * -------------------------------------------------------------
 * 
 * Paramètres:
 *
 *      pin:        valeur que prend le port
 *      valeur:     valeur en hexadécimale à mettre sur la pin
 */
void changerPin(volatile uint8_t* pin, uint8_t valeur);

#endif /* DEL_HPP */