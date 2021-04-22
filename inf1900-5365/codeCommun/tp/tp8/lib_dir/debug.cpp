/**
 * Fonction debug.cpp
 * Date : 18/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */


#include "debug.hpp"

void printDonnee(int donnee) {
    char nombre[10];
    int i = 0;
    while(donnee){
        char chiffre = (donnee % 10) + '0';
        donnee /= 10;
        nombre[i] = chiffre;
        i++;
    }
    nombre[i] = '\0';
    printDonnee(nombre);
}

void printDonnee(const char* donnee) {
    USART0* usart = USART0::getInstance();
    int i = 0;
    while (donnee[i] != '\0')
        usart->transmettre(donnee[i++]);
}

void print_error(const char* file, int line, const char* messageErreur){
    printDonnee("Erreur a la condition: ");
    printDonnee(file);
    printDonnee(", line ");
    printDonnee(line);
    printDonnee(" | ");
    printDonnee(messageErreur);
    printDonnee("\n");
}

void print_step(const char* file, int line){
    printDonnee("Step: ");
    printDonnee(file);
    printDonnee(", line ");
    printDonnee(line);
    printDonnee("\n");
}