/**
 * @brief Librairie gérant les moteurs pour le Atmel
 * @file moteurs.hpp
 * @date 20/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#ifndef MOTEURS_HPP
#define MOTEURS_HPP

#define VITESSE_MAXIMALE 255

#include "timer.hpp"

/**
 * @brief Enumération pour les roues
 */
enum Roue{RGAUCHE, RDROITE};

/**
 * @brief Classe pour les fonctions des moteurs
 */
class Moteurs{
public:
    /**
     * @brief Construit un nouvel objet Moteurs
     */
    Moteurs();

    /**
     * @brief Modifie la vitesse de la roue en paramètre
     * @param vitesse vitesse de la roue à appliquer
     * @param roue roue à changer
     */
    void modifierVitesse(int16_t vitesse, Roue roue);

    /**
     * @brief Modifie la vitesse des deux roues
     * @param gauche vitesse de la roue gauche
     * @param droite vitesse de la roue droite
     */
    void modifierVitesse(int16_t gauche, int16_t droite);

    /**
     * @brief Permet d'obtenir la vitesse de la roue en paramètre
     * @param roue roue voulant avoir la vitesse
     * @return uint8_t obtient la valeur de la vitesse des roues entre 0 et 255
     */
    uint8_t obtenirVitesse(Roue roue);
private:
    Timer1* timer_; // Timer utilisé pour faire le mouvement des roues
};

#endif /* MOTEURS_HPP */