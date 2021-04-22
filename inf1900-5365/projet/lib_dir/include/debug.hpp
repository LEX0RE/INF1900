/**
 * @brief Librairie qui permet d'afficher depuis le Uart0 des informations de débogages
 * @file debug.hpp
 * @date 20/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <stdint.h>

/**
 * @brief Afficher un int en ASCII
 * @param donnee valeur à afficher
 */
void afficherDonnee(int donnee);

/**
 * @brief Afficher un uint8_t en ASCII
 * @param donnee valeur à afficher
 */
void afficherDonnee(uint8_t donnee);

/**
 * @brief Afficher un uint16_t en ASCII
 * @param donnee valeur à afficher
 */
void afficherDonnee(uint16_t donnee);

/**
 * @brief Afficher un uint32_t en ASCII
 * @param donnee valeur à afficher
 */
void afficherDonnee(uint32_t donnee);

/**
 * @brief Afficher un float en ASCII
 * @param donnee valeur à afficher
 */
void afficherDonnee(float donnee);

/**
 * @brief Afficher un const char* (string) en ASCII
 * @param donnee donnée à afficher
 */
void afficherDonnee(const char* donnee);

/**
 * @brief Afficher un uint8_t* (adresse de pointeur) en ASCII
 * @param donnee donnée à afficher
 */
void afficherDonnee(uint8_t* donnee);

/**
 * @brief Afficher un message d'erreur
 * @param fichier ficher où l'erreur s'est produite
 * @param ligne ligne où l'erreur s'est produite
 * @param messageErreur valeur d'une adresse d'un pointeur de uint8_t à afficher
 */
void afficherErreur(const char* fichier, int ligne, const char* messageErreur);

/**
 * @brief Afficher l'endroit où le programme a passé
 * @param fichier ficher où le programme a passé
 * @param ligne ligne où le programme a passé
 */
void afficherPas(const char* fichier, int ligne);

#ifdef DEBUG
# define D_P(donnee) afficherDonnee(donnee) // Appelle la fonction afficherDonnee appropriée
#else
# define D_P(donnee) do {} while (0) // Ne fait rien
#endif

// Basé sur https://discord.com/channels/796832780629180476/801147508524187658/822452778004906014
// Utile pour obtenir la ligne où le programme est passé
#ifdef CONDITION
# define C_P(condition, message) ((condition) ? (void)0U : afficherErreur(__FILE__, __LINE__, message)) // Appelle la fonction afficherErreur
#else
# define C_P(condition, message) do {} while (0) // Ne fait rien
#endif

#ifdef STEP
# define S_P() afficherPas(__FILE__, __LINE__) // Appelle la fonction afficherPas
#else
# define S_P() do {} while (0) // Ne fait rien
#endif

#endif /* DEBUG_HPP */