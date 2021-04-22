/**
 * @brief Fonction pour le robot
 * @file robot.cpp
 * @date 21/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#include <avr/io.h>
#include <stdlib.h>
#include "include/broche.hpp"
#include "include/robot.hpp"
#include "include/can.hpp"
#include "include/interruption.hpp"
#include "include/usart.hpp"

Robot* Robot::robot_ {nullptr};

void Robot::initialiser(){
    Timer0* timer = Timer0::obtenirInstance();
    timer->arreter();
    eteindreSeptSeg();
    moteur_ = {};
    chrono_ = {};
    convertisseur_ = INTERNE;
    frequence_ = 1;
    frequenceAffichage_ = AR;
    manoeuvre_ = 0;
    changement_ = "";
}

Robot* Robot::obtenirInstance(){
    if(robot_ == nullptr){
        robot_ = (Robot*) malloc(sizeof(Robot));
        Externe interruption(ID2, FrontDescendant);
    }

    return robot_;
}

Robot::~Robot(){
    free(robot_);
}

void Robot::prochaineOperation(){
    if (operation_ == DETECTION)
        operation_ = MANOEUVRE;
    else
        operation_ = DETECTION;
}

void Robot::operation(){
    while(1){
        switch(operation_){
            case DEMARRAGE:
                demarrage();
            break;
            case DETECTION:
                detection();
            break;
            case MANOEUVRE:
                manoeuvre();
            break;
            default:
            break;
        }
        prochaineOperation();
    }
}

void Robot::demarrage(){
    if(operation_ == DEMARRAGE){
        uint8_t valeurA = 0xA, valeurB = 0xB, valeurC = 0xC, valeurD = 0xD;
        initialiser();
        afficherBaudRate();

        afficherSeptSeg(AFF1, valeurA);
        afficherSeptSeg(AFF2, valeurB);
        afficherSeptSeg(AFF3, valeurC);
        afficherSeptSeg(AFF4, valeurD);
        
        chrono_.delai(Temps::enTemps(DELAI_2_SECONDE));
        eteindreSeptSeg();

        // (255, 255)
        moteur_.modifierVitesse(VITESSE_MAXIMALE, VITESSE_MAXIMALE);
        chrono_.delai(Temps::enTemps(DELAI_1_SECONDE));

        // (-255, -255)
        moteur_.modifierVitesse(- VITESSE_MAXIMALE, - VITESSE_MAXIMALE);
        chrono_.delai(Temps::enTemps(DELAI_1_SECONDE));

        moteur_.modifierVitesse(0, 0);
    }
}

void Robot::detection(){
    float distanceGauche = 0.0f;
    float distanceCentre = 0.0f;
    float distanceDroite = 0.0f;
    Distance categorieGauche = distance_[GAUCHE];
    Distance categorieCentre = distance_[CENTRE];
    Distance categorieDroite = distance_[DROITE];

    while(operation_ == DETECTION) {

        switch (frequenceAffichage_) {
            case AR:
                // Sauvegarde le délai pour bien faire la fréquence d'affichage
                chrono_.debuterDelai();
                afficherDetection();

                switch (frequence_) {
                    case 1:
                        // Attend selon le délai si aucun bouton n'est pesé
                        while((operation_ == DETECTION) && 
                                (changement_[0] == '\0') && 
                                !chrono_.delaiTermine(Temps::enTemps(DELAI_1_SECONDE))){}
                        break;

                    case 2:
                        // Attend selon le délai si aucun bouton n'est pesé
                        while((operation_ == DETECTION) &&
                                (changement_[0] == '\0') &&
                                !chrono_.delaiTermine(Temps::enTemps(DELAI_500_MS))){}
                        break;

                    case 4:
                        // Attend selon le délai si aucun bouton n'est pesé
                        while((operation_ == DETECTION) &&
                                (changement_[0] == '\0') && 
                                !chrono_.delaiTermine(Temps::enTemps(DELAI_250_MS))){}
                        break;
                    }
                break;

            case AV:
                // Si la sauvegarde de la distance est différente
                if ((obtenirDistance(GAUCHE) != distanceGauche) ||
                    (obtenirDistance(CENTRE) != distanceCentre) ||
                    (obtenirDistance(DROITE) != distanceDroite)) 
                {
                    distanceGauche = obtenirDistance(GAUCHE);
                    distanceCentre = obtenirDistance(CENTRE);
                    distanceDroite = obtenirDistance(DROITE);
                    afficherDetection();
                }
                break;

            case AC:
                obtenirDistance(GAUCHE);
                obtenirDistance(CENTRE);
                obtenirDistance(DROITE);

                if ((categorieGauche != distance_[GAUCHE]) ||
                    (categorieCentre != distance_[CENTRE]) ||
                    (categorieDroite != distance_[DROITE])) 
                {
                    categorieGauche = distance_[GAUCHE];
                    categorieCentre = distance_[CENTRE];
                    categorieDroite = distance_[DROITE];
                    afficherDetection();
                }
                break;
        }

        // Si un bouton a été pessé
        if(changement_[0] != '\0'){
            afficherBouton(changement_);
            changement_ = "";
        }
    }

    // Pour revenir sur le bon mode car le bouton-poussoir change le mode
    operation_ = DETECTION;
}

void Robot::manoeuvre(){
    USART0* usart = USART0::obtenirInstance();
    afficherManoeuvre(manoeuvre_);

    switch(manoeuvre_){
        case 1:
            manoeuvreUn();
        break;
        case 2:
            manoeuvreDeux();
        break;
        case 3:
            manoeuvreTrois();
        break;
        case 4:
            manoeuvreQuatre();
        break;
        case 5:
            manoeuvreCinq();
        break;
        default:
            usart->envoyer("Combinaison non evaluee\n");
            chrono_.delai(Temps::enTemps(DELAI_2_SECONDE));
        break;
    }

    eteindreSeptSeg();
    moteur_.modifierVitesse(0, 0);
}

void Robot::rechargerManoeuvre(){
    // Transformation de la manoeuvre en un chiffre de 6 bits
    uint8_t enChiffre = (distance_[GAUCHE] << 4) | (distance_[CENTRE] << 2) | distance_[DROITE];
    const uint8_t manoeuvre1 = 0b000101, manoeuvre2 = 0b010100, manoeuvre3 = 0b101010, 
                  manoeuvre4 = 0b000010, manoeuvre5 = 0b100000;

    switch(enChiffre){
        case manoeuvre1:
            manoeuvre_ = 1;
        break;
        case manoeuvre2:
            manoeuvre_ = 2;
        break;
        case manoeuvre3:
            manoeuvre_ = 3;
        break;
        case manoeuvre4:
            manoeuvre_ = 4;
        break;
        case manoeuvre5:
            manoeuvre_ = 5;
        break;
        default:
            manoeuvre_ = 0;
        break;
    }
}

void Robot::boutonAppuye(){
    if(operation_ == DETECTION)
        prochaineOperation();
}

float Robot::obtenirLecture(){
    float resultat = 0.0f, inverseDonnee = 0.0f;
    uint16_t donnee = 0;
    uint8_t choixConvertisseur = 0x1, desactiveExterne = 0x1;

    if(convertisseur_ == INTERNE){

        // Change les broches du Atmel pour le convertisseur interne
        changerBit(A, choixConvertisseur, false);
        changerBit(B, desactiveExterne, true);
        can convertisseur;

        // Lecture par le convertisseur interne et retourne sur 10 bits
        donnee = convertisseur.lecture(1);

        // Équation pour obtenir la distance du convertisseur interne
        inverseDonnee = 1.0f / float(donnee);
        resultat = (14739.0f * inverseDonnee) - 6.4498f;
        return resultat;
    }

    // Convertisseur externe
    uint8_t muxExterne = 0b00011100;
    uint8_t delaiPourSimulation = 3;
    uint8_t nIterationMux = 8;
    uint8_t entreeExterne = 0x02;

    // Change les broches du Atmel pour le convertisseur externe
    changerBit(A, choixConvertisseur, true);
    changerBit(B, desactiveExterne, false);

    // Lit les valeurs depuis le convertisseur externe
    for(uint8_t i = 0; i < nIterationMux; i++){

        // Modifie les broches pour le Mux
        changerNumerique(B, muxExterne, i);

        // Shift la variable de stockage
        donnee = donnee << 1;

        // Delai pour bien obtenir la valeur en raison du délai nécessaire pour mettre le courant dans le fils
        delaiVariable(delaiPourSimulation);

        // Sauvegarde la valeur
        donnee |= obtenirBit(B, entreeExterne);
    }
    // Remet les broches à 0 pour le visuel
    changerNumerique(B, muxExterne, 0);

    // Équation pour obtenir la distance pour le convertisseur externe
    inverseDonnee = 1.0f / float(donnee);
    resultat = (3648.0f * inverseDonnee) - 6.2813f;

    return resultat;
}

float Robot::obtenirDistance(Capteur capteur){
    uint8_t positionMuxCapteur = 0b00001100;
    float resultat = 0.0f;
    uint8_t maxDanger = 20, maxAttention = 50;

    // Change les broches du atmel pour obtenir le capteur voulu
    changerNumerique(A, positionMuxCapteur, capteur);
    // Obtient la lecture du convertisseur
    resultat = obtenirLecture();

    // Détermine la catégorie pour la distance obtenue et la sauvegarde
    if (resultat < maxDanger)
        distance_[capteur] = DANGER;
    else if ((maxDanger <= resultat) && (resultat < maxAttention))
        distance_[capteur] = ATTENTION;
    else 
        distance_[capteur] = OK;

    return resultat;
}