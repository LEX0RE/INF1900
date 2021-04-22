/**
 * @brief Fichier s'occupant des affichages pour le robot
 * @file affichage.cpp
 * @date 20/04/2021
 * @author Alexandre Gélinas ((2083465))
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#include "robot.hpp"
#include "broche.hpp"
#include "usart.hpp"

void afficherManoeuvre(uint8_t numeroManoeuvre){
    USART0* usart = USART0::obtenirInstance();

    if(numeroManoeuvre != 0){
        usart->envoyer("Manoeuvre ");
        usart->envoyer(numeroManoeuvre);
        usart->envoyer("\n");
    }
}

void afficherBouton(const char* bouton){
    USART0* usart = USART0::obtenirInstance();

    usart->envoyer("Le bouton ");
    usart->envoyer(bouton);
    usart->envoyer(" du clavier a ete appuye.\n");
}

void afficherSeptSeg(Afficheur afficheur, uint8_t valeur){
    allumerSeptSeg();
    uint8_t positionEnvoieDonnee = 0xF0, valeurNulle = 0x00;
    uint8_t positionAfficheur1 = 0x20,
            positionAfficheur2 = 0x40,
            positionAfficheur3 = 0x01,
            positionAfficheur4 = 0x02;

    // Envoie la valeur voulu pour être affiché plus tard
    changerNumerique(A, positionEnvoieDonnee, valeur);

    // Accepte la valeur selon l'afficheur sélectionné
    switch (afficheur) {
        case AFF1:
            changerBit(B, positionAfficheur1, true);
            changerBit(B, positionAfficheur1, false);
            break;

        case AFF2:
            changerBit(B, positionAfficheur2, true);
            changerBit(B, positionAfficheur2, false);
            break;
        
        case AFF3:
            changerBit(C, positionAfficheur3, true);
            changerBit(C, positionAfficheur3, false);
            break;
        
        case AFF4:
            changerBit(C, positionAfficheur4, true);
            changerBit(C, positionAfficheur4, false);
            break;
    }

    // Remet la valeur à 0 envoyer pour ne pas l'oublier plus tard
    changerNumerique(A, positionEnvoieDonnee, valeurNulle);
}

void allumerSeptSeg(){
    uint8_t positionDuReset = 0x80;

    changerBit(B, positionDuReset, false);
    changerBit(D, positionDuReset, false);
}

void eteindreSeptSeg(){
    uint8_t positionDuReset = 0x80;

    changerBit(B, positionDuReset);
    changerBit(D, positionDuReset);
}

void Robot::afficherBaudRate(){
    uint16_t baudRate = 9600;

    USART0* usart = USART0::obtenirInstance(baudRate);
    usart->envoyer(usart->obtenirBaudRate());
    usart->envoyer(" bps\n");
}

void Robot::afficherVitesse(){
    uint8_t pourcentageMax = 100, valeurMaxBase10 = 10, valeurMaxBase16 = 16;
    uint16_t pourcentDroite = (moteur_.obtenirVitesse(RDROITE)) * pourcentageMax / VITESSE_MAXIMALE;
    uint16_t pourcentGauche = (moteur_.obtenirVitesse(RGAUCHE)) * pourcentageMax / VITESSE_MAXIMALE;

    if (affichage_ == DECIMAL){
        afficherSeptSeg(AFF1, pourcentGauche / valeurMaxBase10);
        afficherSeptSeg(AFF2, pourcentGauche % valeurMaxBase10);
        afficherSeptSeg(AFF3, pourcentDroite / valeurMaxBase10);
        afficherSeptSeg(AFF4, pourcentDroite % valeurMaxBase10);
    }
    else if (affichage_ == HEXADECIMAL){
        afficherSeptSeg(AFF1, pourcentGauche / valeurMaxBase16);
        afficherSeptSeg(AFF2, pourcentGauche % valeurMaxBase16);
        afficherSeptSeg(AFF3, pourcentDroite / valeurMaxBase16);
        afficherSeptSeg(AFF4, pourcentDroite % valeurMaxBase16);
    }
}

void Robot::afficherDetection(){
    USART0* usart = USART0::obtenirInstance();
    uint8_t nombreCapteur = 3;

    // Affiche le temps
    usart->envoyer(chrono_.obtenirTimer().minute, "%02d:");
    usart->envoyer(chrono_.obtenirTimer().seconde, "%02d.");
    usart->envoyer(chrono_.obtenirTimer().centiseconde, "%02d - G:");

    // Affiche la distance
    usart->envoyer(obtenirDistance(GAUCHE));
    usart->envoyer(" C:");
    usart->envoyer(obtenirDistance(CENTRE));
    usart->envoyer(" D:");
    usart->envoyer(obtenirDistance(DROITE));
    usart->envoyer(" - ");

    // Détermine la catégorie pour la distance
    for(uint8_t i = 0; i < nombreCapteur; i++){
        switch(distance_[i]){
            case OK:
                usart->envoyer("OK ");
            break;
            case ATTENTION:
                usart->envoyer("ATTENTION ");
            break;
            case DANGER:
                usart->envoyer("DANGER ");
            break;
        }
        if ( i != uint8_t(nombreCapteur - 1)) // Simplement pour respecté l'affichage demandé
            usart->envoyer("| ");
    }

    // Regarde si la détection mène à une manoeuvre particulière
    rechargerManoeuvre();

    switch (manoeuvre_) {
        case 0: // Manoeuvre non enregistrée
            usart->envoyer("(-)");
            usart->envoyer("\n");
            break;
        default: // Manoeuvre enregistrée
            usart->envoyer("(");
            usart->envoyer(manoeuvre_);
            usart->envoyer(")\n");
            break;
    }
}

void Robot::modifierVitesseEtAffichage(int16_t vitesse, Roue roue){
    moteur_.modifierVitesse(vitesse, roue);
    
    afficherVitesse();
}

void Robot::modifierVitesseEtAffichage(int16_t gauche, int16_t droite){
    moteur_.modifierVitesse(gauche, droite);
    
    afficherVitesse();
}
