/**
 * @brief Fichier s'occupant des manoeuvres pour le robot
 * @file manoeuvre.cpp
 * @date 20/04/2021
 * @author Alexandre Gélinas ((2083465))
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#include "robot.hpp"

int16_t enVitesse(int16_t vitessePourcent) {
    int16_t vitesseMax = 255;
    int16_t pourcentageMax = 100;
    int16_t resultat = ((vitessePourcent * vitesseMax) / pourcentageMax);

    // Pour revenir à une vitesse plus semblable de celle voulu avec les décimales en raison du calcul
    float decimal = (float(vitessePourcent) / float(pourcentageMax));

    if (decimal < 0)
        resultat--;
    else if(decimal > 0)
        resultat++;

    return resultat;
}

void Robot::manoeuvreUn() {
    int16_t pourcentage = 35;
    int16_t vitesse1 = enVitesse(-pourcentage);
    int16_t vitesse2 = -vitesse1; // 35
    uint8_t iteration = (95 - 35) / 5;
    uint8_t changement = 5;

    // (-35, 35)
    modifierVitesseEtAffichage(vitesse1, vitesse2);
    delaiVariable(DELAI_1500_MS);

    // (35, 35)
    modifierVitesseEtAffichage(vitesse2, RGAUCHE);
    delaiVariable(DELAI_2_SECONDE);

    // (35, -35)
    modifierVitesseEtAffichage(vitesse1, RDROITE);
    delaiVariable(DELAI_1500_MS);

    // (35, 35)
    modifierVitesseEtAffichage(vitesse2, RDROITE);

    // (35, 35) à (95, 95) par bon de +5
    for (uint8_t i = 0; i < iteration; i++) {
        pourcentage += changement;
        vitesse2 = enVitesse(pourcentage);
        modifierVitesseEtAffichage(vitesse2, vitesse2);
        delaiVariable(DELAI_125_MS);
    }

    delaiVariable(DELAI_2_SECONDE);
}

void Robot::manoeuvreDeux() {
    int16_t pourcentage = 35;
    int16_t vitesse1 = enVitesse(-pourcentage);
    int16_t vitesse2 = -vitesse1; // 35
    uint8_t iteration = (95 - 35) / 5;
    uint8_t changement = 5;

    // (35, -35)
    modifierVitesseEtAffichage(vitesse2, vitesse1);
    delaiVariable(DELAI_1500_MS);

    // (35, 35)
    modifierVitesseEtAffichage(vitesse2, RDROITE);
    delaiVariable(DELAI_2_SECONDE);

    // (-35, 35)
    modifierVitesseEtAffichage(vitesse1, RGAUCHE);
    delaiVariable(DELAI_1500_MS);

    // (35, 35)
    modifierVitesseEtAffichage(vitesse2, RGAUCHE);

    // (35, 35) à (95, 95) par bon de +5
    for (uint8_t i = 0; i < iteration; i++) {
        pourcentage += changement;
        vitesse2 = enVitesse(pourcentage);
        modifierVitesseEtAffichage(vitesse2, vitesse2);
        delaiVariable(DELAI_125_MS);
    }

    delaiVariable(DELAI_2_SECONDE);
}

void Robot::manoeuvreTrois() {
    int16_t pourcentage = -50;
    int16_t vitesse = enVitesse(pourcentage);
    uint8_t nIteration1 = (99 - 0) / 3;
    uint8_t nIteration2 = (99 - 74) / 5;
    int8_t bond1 = 3, bond2 = -5;
    uint8_t vitesse70pourcent = 70, vitesseNulle = 0;

    // (-50, -50)
    modifierVitesseEtAffichage(vitesse, vitesse);
    delaiVariable(DELAI_1_SECONDE);

    // (-70, 70)
    pourcentage = vitesse70pourcent;
    vitesse = enVitesse(pourcentage);
    modifierVitesseEtAffichage(-vitesse, vitesse);
    delaiVariable(DELAI_1500_MS);

    // (0, 0)
    pourcentage = vitesseNulle;
    vitesse = enVitesse(pourcentage);
    modifierVitesseEtAffichage(vitesse, vitesse);

    // (0, 0) à (99, 99) par bond de +3
    for (uint8_t i = 0; i < nIteration1; i++) {
        pourcentage += bond1;
        vitesse = enVitesse(pourcentage);
        modifierVitesseEtAffichage(vitesse, vitesse);
        delaiVariable(DELAI_50_MS);
    }

    // (99, 99) à (74, 74) par bond de -3
    for (uint8_t i = 0; i < nIteration2; i++) {
        pourcentage += bond2;
        vitesse = enVitesse(pourcentage);
        modifierVitesseEtAffichage(vitesse, vitesse);
        delaiVariable(DELAI_500_MS);
    }

    delaiVariable(DELAI_2_SECONDE);
}

void Robot::manoeuvreQuatre() {
    int16_t pourcentage = 78;
    int16_t vitesse = enVitesse(pourcentage);
    uint8_t nIteration = (78 - 48) / 2;
    int8_t negationBondDepart = -1, changementBond = 2, maxChangementBond = 2;


    // (78, 78)
    modifierVitesseEtAffichage(vitesse, vitesse);

    // (78, 78) à (48, 48) puis (48, 48) à (78, 78)
    for(int8_t i = negationBondDepart; i < maxChangementBond; i += changementBond){
        if (i != negationBondDepart)
            delaiVariable(DELAI_1500_MS);

        for (uint8_t j = 0; j < nIteration; j++) {
            pourcentage += 2 * i;
            vitesse = enVitesse(pourcentage);
            modifierVitesseEtAffichage(vitesse, RGAUCHE);
            delaiVariable(DELAI_250_MS);
        }
    }

    delaiVariable(DELAI_2_SECONDE);
}

void Robot::manoeuvreCinq() {
    int16_t pourcentage = 78;
    int16_t vitesse = enVitesse(pourcentage);
    uint8_t nIteration = (78 - 48) / 2;
    int8_t negationBondDepart = -1, changementBond = 2, maxChangementBond = 2;


    // (78, 78)
    modifierVitesseEtAffichage(vitesse, vitesse);

    // (78, 78) à (48, 48) puis (48, 48) à (78, 78)
    for(int8_t i = negationBondDepart; i < maxChangementBond; i += changementBond){
        if (i != negationBondDepart)
            delaiVariable(DELAI_1500_MS);

        for (uint8_t j = 0; j < nIteration; j++) {
            pourcentage += 2 * i;
            vitesse = enVitesse(pourcentage);
            modifierVitesseEtAffichage(vitesse, RDROITE);
            delaiVariable(DELAI_250_MS);
        }
    }
    
    delaiVariable(DELAI_2_SECONDE);
}