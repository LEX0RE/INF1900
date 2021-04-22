/**
 * Fonction debug.cpp
 * Date : 18/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */

#include <stdio.h>
#include "include/debug.hpp"
#include "include/usart.hpp"

void afficherDonnee(int donnee) {
    char* message = (char*)"0";
    sprintf(message, "%d", donnee);
    afficherDonnee(message);
}

void afficherDonnee(const char* donnee) {
    USART0* usart = USART0::obtenirInstance();
    int i = 0;
    
    while (donnee[i] != '\0')
        usart->transmettre(donnee[i++]);
}

void afficherDonnee(unsigned char donnee) {
    USART0* usart = USART0::obtenirInstance();
    usart->transmettre(donnee);
}

void afficherDonnee(uint8_t* donnee){
    char* message = (char*)"0";
    sprintf(message, "%p", donnee);
    afficherDonnee(message);
}

void afficherErreur(const char* fichier, int ligne, const char* messageErreur){
    afficherDonnee("Erreur a la condition: ");
    afficherDonnee(fichier);
    afficherDonnee(", ligne ");
    afficherDonnee(ligne);
    afficherDonnee(" | ");
    afficherDonnee(messageErreur);
    afficherDonnee("\n");
}

void afficherPas(const char* fichier, int ligne){
    afficherDonnee("Pas: ");
    afficherDonnee(fichier);
    afficherDonnee(", ligne ");
    afficherDonnee(ligne);
    afficherDonnee("\n");
}