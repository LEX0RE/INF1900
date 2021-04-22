/**
 * @brief Librairie qui simule un chronomètre
 * @file chrono.hpp
 * @date 20/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#ifndef CHRONO_HPP
#define CHRONO_HPP

#include "timer.hpp"
#include "temps.hpp"

/**
 * @brief Classe simulant un chronomètre
 */
class Chrono{
public:
    /**
     * @brief Construit un nouvel objet Chrono
     */
    Chrono();

    /**
     * @brief Détruit l'objet Chrono
     */
    ~Chrono() = default;

    /**
     * @brief (Re)Démarre le chronomètre
     */
    void demarrer();

    /**
     * @brief Arrête le chronomètre
     */
    void arreter();

    /**
     * @brief Remet à zéro le chronomètre
     */
    void reset();

    /**
     * @brief Sauvegarde le temps actuel en vue d'appeler attendreDelai pour faire des actions puis en attendant le délai voulu
     */
    void debuterDelai();

    /**
     * @brief Attend jusqu'au délai voulu. Préférablement utiliser un debuterDelai avant.
     * @param delai délai voulant avoir été complété depuis le dernier debuterDelai
     */
    void attendreDelai(Temps delai);

    /**
     * @brief Indique si le delai démarré plus tôt par debuterDelai est terminé
     * @param delai délai voulant être pris pour la comparaison
     * @return bool indique si le délai est terminé
     */
    bool delaiTermine(Temps delai);

    /**
     * @brief Attend le délai voulu
     * @param delai temps d'attente
     */
    void delai(Temps delai);

    /**
     * @brief Permet d'obtenir la valeur actuel du chronomètre
     * @return Temps valeur du chronomètre
     */
    Temps obtenirTimer() const;

    static unsigned long long chrono_; // Valeur du chronomètre à incrémenter
private:
    Timer2* timer_; // Timer utilisé pour le chrono
    Temps premiereLecture_; // Temps de référence pour les délais
};

#endif /* CHRONO_HPP */
