/**
 * @brief Librairie pour la gestion des Timer du Atmel
 * @file timer.hpp
 * @date 21/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#ifndef TIMER_HPP
#define TIMER_HPP

#include <stdint.h>

/**
 * @brief Enumération pour les multiples de temps
 */
enum TypeTemps{MS, US};

/**
 * @brief Enumération pour les regitres de comparaison des Timers
 */
enum RegistreComparaison{TCA, TCB};

/**
 * @brief Enumération des modes pour les Timers à 8 bit. Voir p103 & p153:
 * http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8272-8-bit-AVR-microcontroller-ATmega164A_PA-324A_PA-644A_PA-1284_P_datasheet.pdf
 */
enum ModeTimer8Bit{T8M0, T8M1, T8M2, T8M3, T8M4, T8M5, T8M6, T8M7};

/**
 * @brief Enumération des modes pour les Timers à 16 bit. Voir p130: 
 * http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8272-8-bit-AVR-microcontroller-ATmega164A_PA-324A_PA-644A_PA-1284_P_datasheet.pdf
 */
enum ModeTimer16Bit{T16M0, T16M1, T16M2, T16M3, T16M4, T16M5, T16M6, T16M7, 
                    T16M8, T16M9, T16M10, T16M11, T16M12, T16M13, T16M14, T16M15};

/**
 * @brief Enumération des modes de comparaisons pour les Timers à 16 bit. Voir p128-129 pour un exemple: 
 * http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8272-8-bit-AVR-microcontroller-ATmega164A_PA-324A_PA-644A_PA-1284_P_datasheet.pdf
 */
enum ModeComparaison{NORMAL, BASCULER, COMPARAISON0, COMPARAISON1};

/**
 * @brief Enumération des modes de prescaler pour les Timers. Voir p131 & 154: 
 * http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8272-8-bit-AVR-microcontroller-ATmega164A_PA-324A_PA-644A_PA-1284_P_datasheet.pdf
 */
enum Prescaler{AUCUN, P1, P2, P3, P4, P5, P6, P7};

/**
 * @brief Enumération des modes d'interruptions pour les Timer. Voir p156 pour un exemple: 
 * http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8272-8-bit-AVR-microcontroller-ATmega164A_PA-324A_PA-644A_PA-1284_P_datasheet.pdf
 */
enum MatchInterruption{RIEN, MATCHA, MATCHB, MATCHDEBORDEMENT};

/**
 * @brief Permet d'établir un délai de temps personnalisé
 * @param delai valeur qui détermine la durée du délai
 * @param unite détermine quelle est l'unité de temps du délai
 */
void delaiVariable(unsigned int delai = 1000, TypeTemps unite = MS);

/**
 * @brief Classe abstraite permettant de gérer les Timer du Atmel
 */
class Timer{
public:

    /**
     * @brief Remet le compteur à 0
     */
    void remiseAZero();

    /**
     * @brief Permet d'obtenir la valeur actuel du Timer en question
     * @return uint8_t valeur du Timer présentement
     */
    uint8_t obtenirTimer() const;

   /**
    * @brief Force le Timer à comparer les valeurs si le mode n'est pas PWM
    * @param registre indique si on force la comparaison du top A ou du B
    */
    void forcerComparaison(RegistreComparaison registre = TCA);

    /**
     * @brief Obtenir la valeur maximale des registres de comparaison du Timer
     * @param registre indique si on obtient le top du A ou du B
     * @return uint8_t retourne la valeur du Top du registre de comparaison sélectionné
     */
    uint8_t obtenirTop(RegistreComparaison registre = TCA) const;

    /**
     * @brief Modifier la valeur du TOP pour le PWM pour le resgistre sélectionné
     * @param top valeur à mettre au top
     * @param registre indique si on modifie le top du A ou du B
     */
    void modifierTop(uint8_t top, RegistreComparaison registre = TCA);

    /**
     * @brief Permet d'arrêter le Timer
     */
    void arreter();

    /**
     * @brief Permet de démarrer le Timer
     */
    void demarrer();

    /**
     * @brief Permet de savoir si le Timer est arrêté ou est démarré
     * @return bool Vrai si en marche
     */
    bool alimentation() const;

    /**
     * @brief Initialiser le Timer
     * @param modeComparaison mode de comparaison pour les deux registres
     * @param prescaler prescaler du Timer
     * @param modeInterruption mode d'interruption du Timer
     */
    void initialiser(ModeComparaison modeComparaison = NORMAL,
                     Prescaler prescaler = AUCUN,
                     MatchInterruption modeInterruption = RIEN);

    /**
     * @brief Modifie le mode de comparaison du Timer
     * @param modeComparaison mode de comparaison souhaité
     * @param registre registre à modifier
     */
    void modifierModeComparaison(ModeComparaison modeComparaison, RegistreComparaison registre = TCA);

    /**
     * @brief Modfie le mode du prescaler
     * @param prescaler mode souhaité pour le prescaler
     */
    void modifierPrescaler(Prescaler prescaler);

    /**
     * @brief Modfie le mode des interruptions
     * @param modeInterruption mode d'interruption souhaité
     */
    void modifierInterruption(MatchInterruption modeInterruption);

    /**
     * @brief Modfie la valeur actuelle du compteur
     * @param compteur nouvelle valeur du compteur souhaité
     */
    void modifierCompteur(uint8_t compteur);

protected:
    uint8_t WGMn0_, WGMn1_, WGMn2_;                     // Bit : Détermine le mode de la minuterie
    uint8_t CSn0_, CSn1_, CSn2_;                        // Bit : Détermine le prescaler
    uint8_t COMnA0_, COMnA1_, COMnB0_, COMnB1_;         // Bit : Gestion du mode de comparaison de la sortie
    uint8_t OCIEnA_, OCIEnB_, TOIEn_;                   // Bit : Gestion des interruption
    uint8_t FOCnA_, FOCnB_;                             // Bit : Pour les Force output Compare

    volatile uint8_t* OCRnA_,* OCRnB_;                  // Registre : valeur maximale du Timer
    volatile uint8_t* TCCRnA_,* TCCRnB_,* TCCRnC_;      // Registre : contrôle du Timer
    volatile uint8_t* TIMSKn_;                          // Registre : Masque d'interruption du Timer
    volatile uint8_t* TCNTn_;                           // Registre : Timer

    Prescaler prescaler_;                                 // Sauvegarde du prescaler pour l'arrêt du Timer

    uint8_t OCnA_, OCnB_;                               // Bit : Permet de savoir où se trouve les pin de sortie
    volatile uint8_t* PORT_;                            // Port : Permet de savoir où se trouve le port de OCnA et OCnB

    bool alimentation_;                                 // Bool : Permet de savoir si le Timer est arrêté ou en fonction

    virtual void modifierRegistre() = 0;                // Méthode à réimplémenter dans chaque héritié pour modifier les registres
                                                        // de la classe abstraire
};

/**
 * @brief Gestion du Timer0 à 8-Bits
 */
class Timer0 : public Timer{
public:
    /**
     * @brief Constructeur empêchant la copie
     */
    Timer0(Timer0&) = delete;

    /**
     * @brief Empêche l'assignation
     */
    void operator=(const Timer0&) = delete;

    /**
     * @brief Permet d'obtenir l'instance et de la créer si elle ne l'est pas du Timer0
     * @param modeMinuterie mode de fonctionnement de la minuterie
     * @param modeComparaison mode de comparaison des deux registres
     * @param prescaler mode de prescaler de la minuterie
     * @param modeInterruption mode d'interruption souhaité
     * @return Timer0* instance du Timer0
     */
    static Timer0* obtenirInstance(ModeTimer8Bit modeMinuterie = T8M0, ModeComparaison modeComparaisonA = NORMAL,
                                   Prescaler prescaler = AUCUN, MatchInterruption modeInterruption = RIEN);

    /**
     * @brief Obtenir le prescaler du Timer
     * @return uint16_t valeur du prescaler
     */
    uint16_t obtenirPrescaler() const;
private:
    static Timer0* timer_; // instance du Timer

    /**
     * @brief Modifie les variables de la classe Timer pour utiliser les fonctions de celle-ci
     */
    void modifierRegistre() override;

    /**
     * @brief Modifie le mode de la minuterie
     * @param modeMinuterie indique le mode de la minuterie
     */
    void modifierModeMinuterie(ModeTimer8Bit modeMinuterie);
protected:

    /**
     * @brief Construit un nouvel objet Timer 0
     */
    Timer0() = default;

    /**
     * @brief Détruit l'objet Timer 0
     */
    ~Timer0();
};

/**
 * @brief Classe gérant le Timer/Counter1 16-Bits
 */
class Timer1 : public Timer{
public:

    /**
     * @brief Remet le compteur à 0
     */
    void remiseAZero();

    /**
     * @brief Permet d'obtenir la valeur du Timer actuel
     * @return uint16_t valeur du Timer actuellement
     */
    uint16_t obtenirTimer() const;

    /**
     * @brief Constructeur empêchant la copie
     */
    Timer1(Timer1&) = delete;
    
    /**
     * @brief Empêche l'assignation
     */
    void operator=(const Timer1&) = delete;

    /**
     * @brief Permet d'obtenir l'instance et de la créer si elle ne l'est pas du Timer1
     * @param modeMinuterie mode de fonctionnement de la minuterie
     * @param modeComparaison mode de comparaison des deux registres
     * @param prescaler mode de prescaler de la minuterie
     * @param modeInterruption mode d'interruption souhaité
     * @return Timer1* instance du Timer1
     */
    static Timer1* obtenirInstance(ModeTimer16Bit modeMinuterie = T16M0, ModeComparaison modeComparaisonA = NORMAL,
                                   Prescaler prescaler = AUCUN, MatchInterruption modeInterruption = RIEN);

    /**
     * @brief Obtenir la valeur maximale du Timer
     * @param registre registre voulant avec le Top
     * @return uint16_t valeur du Top du registre
     */
    uint16_t obtenirTop(RegistreComparaison registre = TCA) const;

    /**
     * @brief Modifier la valeur du TOP pour le PWM
     * @param top valeur à mettre au top
     * @param registre registre à modifier
     */
    void modifierTop(uint16_t top, RegistreComparaison registre = TCA);

    /**
     * @brief Obtenir le prescaler du Timer
     * @return uint16_t valeur du prescaler
     */
    uint16_t obtenirPrescaler() const;

    /**
     * @brief Modfie le mode de la minuterie
     * @param modeMinuterie mode de la minuterie souhaité
     */
    void modifierModeMinuterie(ModeTimer16Bit modeMinuterie);

    /**
     * @brief Modifie la valeur actuelle du compteur
     * @param compteur nouvelle valeur du compteur souhaité
     */
    void modifierCompteur(uint16_t compteur);

private:
    static Timer1* timer_;                                  // instance du Timer

    uint8_t WGM13_;                                         // Bit : Détermine le mode de la minuterie
    volatile uint16_t* OCRnA_,* OCRnB_;                     // Registre : valeur maximale du Timer
    volatile uint16_t* TCNTn_;                              // Registre : Timer

    /**
     * @brief Modifie les variables de la classe Timer pour utiliser les fonctions de celle-ci
     */
    void modifierRegistre() override;
protected:
    /**
     * @brief Construit un nouvel objet Timer 1
     */
    Timer1() = default;

    /**
     * @brief Détruit l'objet Timer 1
     */
    ~Timer1();
};

/**
 * @brief Timer/Counter2 8-Bits
 */
class Timer2 : public Timer{
public:
    /**
     * @brief Constructeur empêchant la copie de l'objet Timer 2
     */
    Timer2(Timer2&) = delete;
    
    /**
     * @brief Empêche l'assignation
     */
    void operator=(const Timer2&) = delete;

    /**
     * @brief Permet d'obtenir l'instance et de la créer si elle ne l'est pas du Timer2
     * @param modeMinuterie mode de fonctionnement de la minuterie
     * @param modeComparaison mode de comparaison des deux registres
     * @param prescaler mode de prescaler de la minuterie
     * @param modeInterruption mode d'interruption souhaité
     * @return Timer2* instance du Timer2
     */
    static Timer2* obtenirInstance(ModeTimer8Bit modeMinuterie = T8M0, ModeComparaison modeComparaisonA = NORMAL,
                                   Prescaler prescaler = AUCUN, MatchInterruption modeInterruption = RIEN);

    /**
     * @brief Obtenir le prescaler du Timer 2
     * @return uint16_t valeur du prescaler
     */
    uint16_t obtenirPrescaler() const;

    /**
     * @brief Modifie le mode de la minuterie
     * @param modeMinuterie mode de la minuterie souhaité
     */
    void modifierModeMinuterie(ModeTimer8Bit modeMinuterie);

private:
    static Timer2* timer_;  // instance du timer

    /**
     * @brief Modifie les variables de la classe Timer pour utiliser les fonctions de celle-ci
     */
    void modifierRegistre() override;

protected:

    /**
     * @brief Construit un nouvel objet Timer 2
     */
    Timer2() = default;

    /**
     * @brief Détruit l'objet Timer 2
     */
    ~Timer2();
};

#endif /* TIMER_HPP */