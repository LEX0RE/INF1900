/**
 * @brief Librairie pour la gestion des port du Atmel
 * @file atmel.hpp
 * @date 20/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#ifndef ATMEL_HPP
#define ATMEL_HPP

#include <stdint.h>

/**
 * @brief Enumération des ports du Atmel
 */
enum Port{A, B, C, D};

/**
 * @brief Définition des ports en Entrée et en Sortie
 * @param portA Valeur pour le port A (1 pour sortie, 0 pour entrée) en hexadécimal pour tout le port
 * @param portB Valeur pour le port B (1 pour sortie, 0 pour entrée) en hexadécimal pour tout le port
 * @param portC Valeur pour le port C (1 pour sortie, 0 pour entrée) en hexadécimal pour tout le port
 * @param portD Valeur pour le port D (1 pour sortie, 0 pour entrée) en hexadécimal pour tout le port
 */
void modifierDDRX(const uint8_t portA = 0x00, const uint8_t portB = 0x00, 
                  const uint8_t  portC = 0x00, const uint8_t  portD = 0x00);

/**
 * @brief Permet de modifier si une broche est en lecture ou en écriture
 * @param port port à changer
 * @param valeur Valeur pour le port (1 pour sortie, 0 pour entrée) en hexadécimal pour tout le port
 */
void modifierPort(Port port, const uint8_t valeur = 0x00);

/**
 * @brief Permet d'obtenir les ports du Atmel en vue d'une écriture
 * @param port port voulu
 * @return volatile uint8_t* 
 */
volatile uint8_t* obtenirPort(Port port);

/**
 * @brief Permet d'obtenir les ports du Atmel en vue d'une lecture
 * @param port port voulu
 * @return volatile uint8_t* 
 */
volatile uint8_t* obtenirPin(Port port);

#endif /* ATMEL_HPP */