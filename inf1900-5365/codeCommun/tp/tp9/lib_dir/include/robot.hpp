#ifndef ROBOT_HPP
#define ROBOT_HPP
/**
 * Librairie robot.hpp
 * Date : 25/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */

#include <stdint.h>

// Commentaire pris du TP9 au lien suivant : https://cours.polymtl.ca/inf1900/tp/tp9/

/** Attendre 25 ms fois la valeur de l'opérande
 * 
 * Mnémonique: att
 * Code binaire: 0x02
 * Opérande: oui
 */
void attendre(uint8_t valeur);

/** Allumer la seule DEL connectée au microcontrôleur (port non précisé). Sans effet sur une DEL déjà allumée de la même couleur.
 * 
 * Mnémonique: dal
 * Code binaire: 0x44
 * Opérande: oui, Entre 0 et 127, DEL en vert. Autrement, DEL en rouge.
 * 
 * ------------------------------------------------------------------------
 * 
 * Paramètre supplémentaire:
 * 
 *  pin:    port à utiliser pour la del bicolore
 *  entree: valeur en hexadécimal de l'entrée sur le microcontrôleur
 *  sortie: valeur en hexadécimal de la sortie sur le microcontrôleur
 */
void allumerDel(uint8_t valeur, volatile uint8_t* pin, uint8_t entree, uint8_t sortie);

/** Éteindre la seule DEL connectée au microcontrôleur (port non précisé). Sans effet sur une DEL déjà éteinte.
 * 
 * Mnémonique: det
 * Code binaire: 0x45
 * Opérande: non
 * 
 * ------------------------------------------------------------------------
 * 
 * Paramètre supplémentaire:
 * 
 *  pin:    port à utiliser pour la del bicolore
 *  entree: valeur en hexadécimal de l'entrée sur le microcontrôleur
 *  sortie: valeur en hexadécimal de la sortie sur le microcontrôleur
 */
void eteindreDel(volatile uint8_t* pin, uint8_t entree, uint8_t sortie);

/** Sélectionner les rangées et colonnes de la matrice de DEL
 * 
 * Mnémonique: mon
 * Code binaire: 0x18
 * Opérande: oui, 4 premiers bits: colonne (à zéro pour être actif), 4 suivants: rangée à un pour être actif. 
 *           Donc, on a la syntaxe suivante: mon <R3..R0><C3..C0>
 * 
 * ------------------------------------------------------------------------
 * 
 * Paramètre supplémentaire:
 * 
 *  pin: port à utiliser pour la matrice de del
 */
void allumerMatriceDel(uint8_t valeur, volatile uint8_t* pin);

/** N’affiche plus rien sur la matrice de DEL. Équivalent à: mon 0. Sans effet si la matrice a déjà tous ses pixels éteints.
 * 
 * Mnémonique: mof
 * Code binaire: 0x19
 * Opérande: non
 * 
 * ------------------------------------------------------------------------
 * 
 * Paramètre supplémentaire:
 * 
 *  pin: port à utiliser pour la matrice de del
 */
void eteindreMatriceDel(volatile uint8_t* pin);

/** Arrêter les deux moteurs
 * 
 * Mnémonique: mof
 * Code binaire: 0x60 ou 0x61
 * Opérande: non
 */
void arreterMoteur();

/** Avancer en ligne droite à une vitesse donnée par (opérande / 255 * 100%)
 * 
 * Mnémonique: mav
 * Code binaire: 0x62
 * Opérande: oui
 * 
 * ------------------------------------------------------------------------
 * 
 * Paramètre supplémentaire:
 * 
 *  pin:        port à utiliser pour la direction des moteurs
 *  position:   position de la broche pour la direction des moteurs
 *  direction:  Sert de boussole pour le robot
 *  recule:     Indique si le robot était en train de reculer
 */
void avancer(uint8_t valeur, volatile uint8_t* pin, uint8_t position, 
             unsigned int& direction, bool& recule);

/** Reculer en ligne droite à la vitesse (opérande / 255 * 100%)
 * 
 * Mnémonique: mre
 * Code binaire: 0x63
 * Opérande: oui
 * 
 * ------------------------------------------------------------------------
 * 
 * Paramètre supplémentaire:
 * 
 *  pin:        port à utiliser pour les moteurs
 *  position:   position de la broche déterminant la direction des moteurs
 *  direction:  Sert de boussole pour le robot
 *  recule:     Indique si le robot était en train de reculer
 */
void reculer(uint8_t valeur, volatile uint8_t* pin, uint8_t position, 
             unsigned int& direction, bool& recule);

/** Virage du robot de 90 degrés à droite
 * 
 * Mnémonique: trd
 * Code binaire: 0x64
 * Opérande: non
 * 
 * ------------------------------------------------------------------------
 * 
 * Paramètre supplémentaire:
 * 
 *  pinMoteur:      port à utiliser pour les moteurs
 *  positionMoteur: position de la direction des moteurs
 *  pinMDel:        port à utiliser pour la matrice de Del 4x4
 *  positionMDel:   position des broches connectées à la matrice 4x4 de Del
 *  direction:      Sert de boussole pour le robot
 *  recule:         Indique si le robot était en train de reculer
 */
void tournerDroite(volatile uint8_t* pinMoteur, uint8_t positionDirection,volatile uint8_t* pinMDel, uint8_t positionMDel, 
                   unsigned int& direction, bool recule);

/** Virage du robot de 90 degrés à gauche
 * 
 * Mnémonique: trg
 * Code binaire: 0x65
 * Opérande: non
 * 
 * ------------------------------------------------------------------------
 *
 * Paramètre supplémentaire:
 * 
 *  pinMoteur:      port à utiliser pour les moteurs
 *  positionMoteur: position de la direction des moteurs
 *  pinMDel:        port à utiliser pour la matrice de Del 4x4
 *  positionMDel:   position des broches connectées à la matrice 4x4 de Del
 *  direction:      Sert de boussole pour le robot
 *  recule:         Indique si le robot était en train de reculer
 */
void tournerGauche(volatile uint8_t* pinMoteur, uint8_t positionDirection,volatile uint8_t* pinMDel, uint8_t positionMDel, 
                   unsigned int& direction, bool recule);

/** Emmagasiner l'adresse du présent point d'exécution du code dans une variable pour pouvoir y revenir. 
 *  De plus, créer une variable qui conservera l'état du compteur de boucle. La boucle s'exécutera une fois de plus que 
 *  la valeur précisée par l'opérande. Donc, si l'opérande est zéro, le code ne s'exécutera qu'une seule fois. 
 *  Il ne peut y avoir deux boucles imbriquées (actives au même moment).
 * 
 * Mnémonique: dbc
 * Code binaire: 0xC0
 * Opérande: oui
 * 
 * ------------------------------------------------------------------------
 *
 * Paramètre supplémentaire:
 * 
 *  adresseMaximale:    adresse maximale suivant les instructions sur la mémoire
 */
void debutBoucle(uint8_t valeur, uint8_t adresseMaximale);

/** Si le compteur n'est pas égal à 0, retourner à l'adresse de début de boucle et décrémenter le compteur de boucle. 
 *  Sinon, ne rien faire.
 * 
 * Mnémonique: fbc
 * Code binaire: 0xC1
 * Opérande: non
 * 
 * ------------------------------------------------------------------------
 *
 * Paramètre supplémentaire:
 * 
 *  adresseMaximale:    adresse maximale suivant les instructions sur la mémoire
 */
void finBoucle(uint8_t adresseMaximale);

/** Afficher la direction sur la matrice 3x3
 * 
 * Paramètre supplémentaire:
 * 
 *  pinMDel: port à utiliser pour la matrice de Del
 *  positionMDel: position de la matrice de Del 3x3 en hexadécimal
 * 
 * --------------------------------------------------------------------
 * 
 * Direction:
 * 
 *      0 = Haut
 *      1 = Gauche
 *      2 = Bas
 *      3 = Droite
 */
void afficherDirection(unsigned int direction, volatile uint8_t* pinMDel, uint8_t positionMDel);

/** Affiche les instructions en cours
 * 
 * --------------------------------------------------------------------
 *
 * Paramètre:
 *      instruction: instructions en cours d'exécution
 */
void afficherInstruction(uint8_t& instruction);

/** Lire la mémoire pour les instructions du robot et les exécute
 */
void lireMemoire();

#endif /* ROBOT_HPP */