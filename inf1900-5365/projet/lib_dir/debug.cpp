/**
 * @brief Définition des fonction pour le fichier debug.cpp
 * @file debug.cpp
 * @date 21/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#include <stdio.h>
#include "include/debug.hpp"
#include "include/usart.hpp"

void afficherDonnee(uint8_t donnee){
    char message[TABLEAU_ALLOUE];
    sprintf(message, "%u", donnee);
    afficherDonnee(message);
}

void afficherDonnee(uint16_t donnee){
    char message[TABLEAU_ALLOUE];
    sprintf(message, "%u", donnee);
    afficherDonnee(message);
}

void afficherDonnee(uint32_t donnee){
    char message[TABLEAU_ALLOUE];
    sprintf(message, "%lu", donnee);
    afficherDonnee(message);
}

void afficherDonnee(int donnee) {
    char message[TABLEAU_ALLOUE];
    sprintf(message, "%d", donnee);
    afficherDonnee(message);
}

void afficherDonnee(float donnee) {
    double nombre = donnee;
    char message[TABLEAU_ALLOUE];
    sprintf(message, "%.1f", nombre);
    afficherDonnee(message);
}

void afficherDonnee(const char* donnee) {
    USART0* usart = USART0::obtenirInstance();
    uint16_t i = 0;
    
    while (donnee[i] != '\0')
        usart->transmettre(uint8_t(donnee[i++]));
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
    afficherDonnee("Etape: ");
    afficherDonnee(fichier);
    afficherDonnee(", ligne ");
    afficherDonnee(ligne);
    afficherDonnee("\n");
}