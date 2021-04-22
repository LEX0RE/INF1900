/**
 * @brief Fonction pour les moteurs du robot
 * @file moteurs.cpp
 * @date 21/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#define PORT_DIRECTION_GAUCHE 0x08
#define PORT_DIRECTION_DROITE 0x40

#include "moteurs.hpp"
#include "broche.hpp"

Moteurs::Moteurs(){
    // Initialisation des directions vers l'avant
    changerBit(D, PORT_DIRECTION_GAUCHE | PORT_DIRECTION_DROITE, false);

    timer_ = Timer1::obtenirInstance(T16M1, COMPARAISON0, P1);
    timer_->arreter();
}

void Moteurs::modifierVitesse(int16_t vitesse, Roue roue){
    uint16_t vitesseArret = 0xFFFF;
    vitesse = vitesse % (VITESSE_MAXIMALE + 1);
    uint8_t portDirection = PORT_DIRECTION_DROITE;
    RegistreComparaison registre = TCA;

    if(roue == RGAUCHE){
        portDirection = PORT_DIRECTION_GAUCHE;
        registre = TCB;
    }

    if(vitesse < 0){ // Vitesse négative
        vitesse++;
        timer_->demarrer();
        changerBit(D, portDirection, false);
        timer_->modifierTop(vitesse * -1, registre);
    }
    else if(vitesse == 0){ // Vitesse nulle
        timer_->arreter();
        timer_->modifierTop(vitesseArret, registre);
    }
    else{ // Vitesse positive
        vitesse--;
        timer_->demarrer();
        changerBit(D, portDirection, true);
        timer_->modifierTop(vitesse, registre);
    }
}

void Moteurs::modifierVitesse(int16_t gauche, int16_t droite){
    modifierVitesse(gauche, RGAUCHE);
    modifierVitesse(droite, RDROITE);
}

uint8_t Moteurs::obtenirVitesse(Roue roue){
    RegistreComparaison registre = TCA;

    if(roue == RGAUCHE)
        registre = TCB;

    if (Timer1::obtenirInstance()->obtenirTop(registre) > VITESSE_MAXIMALE)
        return 0x0000;
    return uint8_t(Timer1::obtenirInstance()->obtenirTop(registre)) + 1;
}