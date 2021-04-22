/**
 * @brief Librairie pouvant gérer un système de temps
 * @file temps.hpp
 * @date 21/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#ifndef TEMPS_HPP
#define TEMPS_HPP

#include <stdlib.h>
#include <avr/io.h>

#define DELAI_50_MS 50
#define DELAI_125_MS 125
#define DELAI_250_MS 250
#define DELAI_500_MS 500
#define DELAI_1500_MS 1500
#define DELAI_1_SECONDE 1000
#define DELAI_2_SECONDE 2000

/**
 * @brief Structure représentant un certain temps
 */
struct Temps{
    unsigned int minute = 0, seconde = 0, centiseconde = 0; // Valeur de temps

    /**
     * @brief Convertis en Temps les millisecondes donnés en paramètres
     * @param milliseconde temps à convertir
     * @return Temps milliseconde convertis en temps
     */
    static Temps enTemps(unsigned long milliseconde);

    /**
     * @brief Permet la comparaison entre plusieurs Temps
     * @param autre autre temps à comparer
     * @return bool Vrai si l'autre temps est plus grand
     */
    bool operator<(Temps autre);

    /**
     * @brief Permet la comparaison entre plusieurs Temps
     * @param autre autre temps à comparer
     * @return bool Vrai si l'autre temps est plus grand ou égal
     */
    bool operator<=(Temps autre);

    /**
     * @brief Permet la comparaison entre plusieurs Temps
     * @param autre autre temps à comparer
     * @return bool Vrai si l'autre temps est plus petit
     */
    bool operator>(Temps autre);

    /**
     * @brief Permet la comparaison entre plusieurs Temps
     * @param autre autre temps à comparer
     * @return bool Vrai si l'autre temps est plus petit ou égal
     */
    bool operator>=(Temps autre);

    /**
     * @brief Permet la comparaison entre plusieurs Temps
     * @param autre autre temps à comparer
     * @return bool Vrai si l'autre temps est égal à cette instance
     */
    bool operator==(Temps autre);

    /**
     * @brief Permet d'ajouter du temps
     * @param temps autre temps à ajouter
     * @return Temps temps une fois l'addition terminé
     */
    Temps operator+(Temps temps);
};

#endif /* TEMPS_HPP */