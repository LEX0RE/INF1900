#ifndef ATMEL_HPP
#define ATMEL_HPP
/**
 * Librairie atmel.hpp
 * Date : 16/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */

/* Définition des ports en Entrée et en Sortie
 * 
 * --------------------------------------------------------------------
 * 
 * Mode 0 : Rien
 * Mode 1 : Entrée
 * Mode 2 : Sortie
 * 
 * --------------------------------------------------------------------
 * Paramètre : 
 *      portA : Mode pour le port A
 *      portB : Mode pour le port B
 *      portC : Mode pour le port C
 *      portD : Mode pour le port D
 */
void modifierDDRX(const unsigned int portA = 0, const unsigned int portB = 0, 
                  const unsigned int  portC = 0, const unsigned int  portD = 0);

#endif /* ATMEL_HPP */