/**
 * @brief Fichier C++ contenant le programme pour le projet
 * @file main.cpp
 * @date 20/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#include <avr/io.h>

#include "robot.hpp"
#include "bouton.hpp"
#include "broche.hpp"
#include "interruption.hpp"

/*
----------------------------------------------------------------------
-              Identification matérielles ATmega324A                 -
----------------------------------------------------------------------


                    ⌜￣￣￣￣\     /￣￣￣￣⌝
   On/Off CAN Ext. -| 1      \___/    40 |- Select. CAN INT./EXT.
   Output CAN Ext. -| 2               39 |- Input CAN Int.
Mux Bit 0 CAN Ext. -| 3               38 |- Mux Bit 0 Capteur
Mux Bit 1 CAN Ext. -| 4               37 |- Mux Bit 1 Capteur
Mux Bit 2 CAN Ext. -| 5               36 |- Envoie Aff. Bit 0
     Envoie Aff. 1 -| 6               35 |- Envoie Aff. Bit 1
     Envoie Aff. 2 -| 7               34 |- Envoie Aff. Bit 2
 On/Off Aff. 1 & 2 -| 8               33 |- Envoie Aff. Bit 3
                   -| 9               32 |- Source 2.5V
                   -| 10              31 |- 
                   -| 11              30 |- 
                   -| 12              29 |- Clavier Rang. 3
                   -| 13              28 |- Clavier Rang. 2
                   -| 14              27 |- Clavier Rang. 1
                   -| 15              26 |- Clavier Col. 1
   Input Bouton-P. -| 16              25 |- Clavier Col. 2
        Dir Roue G -| 17              24 |- Clavier Col. 3
        PWM Roue G -| 18              23 |- Envoie Aff. 4
        PWM Roue D -| 19              22 |- Envoie Aff. 3
        Dir Roue D -| 20              21 |- On/Off Aff. 3 & 4
                    ⌞____________________⌟

----------------------------------------------------------------------
-                       Description complète                         -
----------------------------------------------------------------------

 1      - Output    - Permet d'empêcher la sortie du multiplexeur pour le CAN externe
 2      - Output    - Réception des données du CAN externe
 3      - Output    - Permet de sélectionner le bit du CAN externe à vouloir recevoir. S'occupe du bit 0 du multiplexeur
 4      - Output    - Permet de sélectionner le bit du CAN externe à vouloir recevoir. S'occupe du bit 1 du multiplexeur
 5      - Output    - Permet de sélectionner le bit du CAN externe à vouloir recevoir. S'occupe du bit 2 du multiplexeur
 6      - Output    - Permet d'accepter le nombre via la LatchD pour l'afficher 1 (complètement à gauche)
 7      - Output    - Permet d'accepter le nombre via la LatchD pour l'afficher 2 (2eme à partir de la gauche)
 8      - Output    - Permet d'empêcher la sortie des LatchD de gauche (1 et 2) et 
                      donc de fermer ces deux afficheurs sept segments

 9      - (Non utilisé) Envoie un signal de remise à zéro au Atmel lorsqu'il reçoit une pulsation assez longue
 10     - (Non utilisé car en simulation) Entrée du courant
 11     - (Non utilisé car en simulation) Sortie du courant
 12     - (Non utilisé) Sortie pour l'amplificateur d'oscillateur
 13     - (Non utilisé) Entrée pour l'amplificateur d'oscillateur et pour l'envoie d'une clock à l'interne

 14     - Input     - (Non utilisé) Pin D0
 15     - Input     - (Non utilisé) Pin D1
 16     - Input     - Reception du bouton-poussoir. (À 0 lorsqu'il est appuyé)
 17     - Output    - Gère la direction de la roue gauche, soit avant - arrière
 18     - Output    - Envoie le PWM au Pont H pour la roue gauche. Permet de changer la vitesse de cette roue
 19     - Output    - Envoie le PWM au Pont H pour la roue droite, Permet de changer la vitesse de cette roue
 20     - Output    - Gère la direction de la roue droite, soit avant - arrière
 21     - Output    - Permet d'empêcher la sortie des LatchD de droite (3 et 4) et 
                      donc de fermer ces deux afficheurs sept segments

 22     - Output    - Permet d'accepter le nombre via la LatchD pour l'afficher 3 (2eme à partir de la droite)
 23     - Output    - Permet d'accepter le nombre via la LatchD pour l'afficher 4 (complètement à droite)
 24     - Input     - Permet la reception des touches du clavier. S'occupe de la colonne 3. À 0 de base selon le code
 25     - Input     - Permet la reception des touches du clavier. S'occupe de la colonne 2. À 0 de base selon le code
 26     - Input     - Permet la reception des touches du clavier. S'occupe de la colonne 1. À 0 de base selon le code
 27     - Output    - Permet la reception des touches du clavier. S'occupe de la rangée 1. À 1 de base selon le code
 28     - Output    - Permet la reception des touches du clavier. S'occupe de la rangée 2. À 1 de base selon le code
 29     - Output    - Permet la reception des touches du clavier. S'occupe de la rangée 3. À 1 de base selon le code

 30     - (Non utilisé car en simulation) Entrée du courant pour le Port A et son CAN
 31     - (Non utilisé car en simulation) Sortie du courant
 32     - Référence pour la CAN, nous l'avons mis à 2.5V car c'était la valeur 
          maximal obtenu par nos capteurs

 33     - Changeant - Pour envoyer le bit 3 du nombre voulant être afficher sur un des afficheurs sept segments 
 34     - Pour envoyer le bit 2 du nombre voulant être afficher sur un des afficheurs sept segments 
 35     - Pour envoyer le bit 0 du nombre voulant être afficher sur un des afficheurs sept segments 
 36     - Pour envoyer le bit 0 du nombre voulant être afficher sur un des afficheurs sept segments 
 37     - Permet de sélectionner le capteur voulu. S'occupe du bit 1 du multiplexeur
 38     - Permet de sélectionner le capteur voulu. S'occupe du bit 0 du multiplexeur
 39     - Réception des données nécessaire au fonctionnement du CAN interne
 40     - Permet de choisir le CAN à utiliser pour obtenir la distance à partir des capteurs


----------------------------------------------------------------------
-                     Tables d'états du Robot                        -
----------------------------------------------------------------------
 _______________________________________________________________________
| ÉTAT PRÉSENT  | MANOEUVRE |BOUTON-PUSSOIR | ÉTAT SUIVANT  | Sortie Z  |
|               | DÉTECTÉE  |    PRESSÉ     |               |           |
|_______________|___________|_______________|_______________|___________|
|               |           |               |               | EXECUTION |
|   DÉMARRAGE   |     X     |       X       |   DÉTECTION   | DÉMARRAGE |
|_______________|___________|_______________|_______________|___________|
|               |           |               |               |           |
|   DÉTECTION   |     0     |       X       |   DÉTECTION   |   RIEN    |
|_______________|___________|_______________|_______________|___________|
|               |           |               |               |           |
|   DÉTECTION   |     1     |       0       |   DÉTECTION   |   RIEN    |
|_______________|___________|_______________|_______________|___________|
|               |           |               |               |           |
|   DÉTECTION   |     1     |       1       |   MANOEUVRE   |   RIEN    |
|_______________|___________|_______________|_______________|___________|
|               |           |               |               | MANOEUVRE |
|   MANOEUVRE   |     1     |       X       |   DÉTECTION   | EXÉCUTÉE  |
|_______________|___________|_______________|_______________|___________|


----------------------------------------------------------------------
-                         Mode Détection                             -
----------------------------------------------------------------------
                         _______________
                        |               |
                        |   AFFICHAGE   |
                      \ | /    DE      /|\
                       \|/     LA     / | \
                        |   DÉTECTION   |
                        |               |
                        |_______________|

*/

/**
 * @brief Gère l'ISR pour le clavier
 */
ISR (PCINT2_vect){
    PinChange::arret();

    if ((obtenirBit(C, 0x10)) || (obtenirBit(C, 0x8)) || (obtenirBit(C, 0x4)))
        Robot::obtenirInstance()->obtenirClavier();

    PinChange::reprendre();
}

/**
 * @brief Gère l'ISR pour le overflow du Timer2
 */
ISR(TIMER2_OVF_vect){
    Chrono::chrono_++;
}

/**
 * @brief Gère l'ISR pour le bouton-poussoir
 */
ISR (INT0_vect){
    if(antirebond(D, 0x4, true))
        Robot::obtenirInstance()->boutonAppuye();
}

int main() {
    Robot* robot = Robot::obtenirInstance();
    uint8_t modePortA = 0b11111101;
    uint8_t modePortB = 0b00011101;
    uint8_t modePortC = 0b11100011;
    uint8_t modePortD = 0b11111000;

    modifierDDRX(modePortA, modePortB, modePortC, modePortD);
    changerPin(A, 0);
    changerPin(B, 0);
    changerPin(C, 0);
    changerPin(D, 0);
    changerPin(C, 0b11100000);
    PinChange i18(18);
    PinChange i19(19);
    PinChange i20(20);
    robot->operation();
    while(1);
}