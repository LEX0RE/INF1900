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
#include "usart.hpp"

void printDonnee(int donnee);
void printDonnee(const char* donnee);

void print_error(const char* file, int line, const char* messageErreur);

void print_step(const char* file, int line);

#ifdef DEBUG
# define D_P(donnee) printDonnee(donnee)
#else
# define D_P(donnee) do {} while (0)
#endif

// Basé sur https://discord.com/channels/796832780629180476/801147508524187658/822452778004906014
#ifdef CONDITION
# define C_P(condition, message) ((condition) ? (void)0U : print_error(__FILE__, __LINE__, message))
#else
# define C_P(donnee) do {} while (0)
#endif

#ifdef STEP
# define S_P() print_step(__FILE__, __LINE__)
#else
# define S_P(donnee) do {} while (0)
#endif

#endif /* DEBUG_HPP */