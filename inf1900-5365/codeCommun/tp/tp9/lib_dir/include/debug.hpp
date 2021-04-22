#ifndef DEBUG_HPP
#define DEBUG_HPP
/**
 * Librairie debug.hpp
 * Date : 18/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */

#include <stdint.h>

/** Afficher un int à partir du usart envoyé en paramètre si DEBUG est défini
 * 
 *      Valeur affichée en ASCII
 *
 * ----------------------------------------------------------------------------
 * 
 * Paramètres:
 * 
 *      donnee: valeur int à afficher
 */
void afficherDonnee(int donnee);

/** Afficher un unsigned char à partir du usart envoyé en paramètre si DEBUG est défini
 * 
 * ----------------------------------------------------------------------------
 * 
 * Paramètres:
 * 
 *      donnee: valeur unsigned char à afficher
 */
void afficherDonnee(unsigned char donnee);

/** Afficher un string à partir du usart envoyé en paramètre si DEBUG est défini
 * 
 * ----------------------------------------------------------------------------
 * 
 * Paramètres:
 * 
 *      donnee: valeur string à afficher
 */
void afficherDonnee(const char* donnee);

/** Afficher une adresse d'un pointeur de uint8_t à partir du usart envoyé en paramètre si DEBUG est défini
 * 
 * ----------------------------------------------------------------------------
 * 
 * Paramètres:
 * 
 *      donnee: valeur d'une adresse d'un pointeur de uint8_t à afficher
 */
void afficherDonnee(uint8_t* donnee);

/** Afficher un message d'erreur à partir du usart envoyé en paramètre si CONDITION est défini
 * 
 * ----------------------------------------------------------------------------
 * 
 * Paramètres:
 * 
 *      fichier:    ficher où l'erreur s'est produite
 *      ligne:      ligne où l'erreur s'est produite
 *      donnee:     valeur d'une adresse d'un pointeur de uint8_t à afficher
 */
void afficherErreur(const char* fichier, int ligne, const char* messageErreur);

/** Afficher un pas à partir du usart envoyé en paramètre si STEP est défini
 * 
 * ----------------------------------------------------------------------------
 * 
 * Paramètres:
 * 
 *      fichier:    ficher où l'erreur s'est produite
 *      ligne:      ligne où l'erreur s'est produite
 */
void afficherPas(const char* fichier, int ligne);

#ifdef DEBUG
# define D_P(donnee) afficherDonnee(donnee) // Appelle la fonction afficherDonnee appropriée
#else
# define D_P(donnee) do {} while (0) // Ne fait rien
#endif

// Basé sur https://discord.com/channels/796832780629180476/801147508524187658/822452778004906014
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