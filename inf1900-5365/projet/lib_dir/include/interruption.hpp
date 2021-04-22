/**
 * @brief Libraire gérant les interruptions du Atmel
 * @file interruption.hpp
 * @date 20/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#ifndef INTERRUPTION_HPP
#define INTERRUPTION_HPP

#include <avr/interrupt.h>

/**
 * @brief Enumération des interruptions externes
 */
enum InterruptionExterne{ID2, ID3, IB3};

/**
 * @brief Enumération des interruptions de changement de Pin
 */
enum InterruptionPinChange{PA, PB, PC, PD};

/**
 * @brief Enumération des modes d'interruptions
 */
enum ModeInterruption{BasNiveau, ToutFront, FrontDescendant, FrontMontant};

/**
 * @brief Fonction de base pour les interruptions
 */
struct Interruption{
  public:
    /**
     * @brief Active les interruptions
     */
    virtual void activer() = 0;

    /**
     * @brief Désactive les interruptions
     */
    virtual void desactiver() = 0;
};

/**
 * @brief Gère les paramètres pour les interruptions externes
 */
class Externe : public Interruption{
  public:

    /**
     * @brief Construit un nouvel objet Externe
     * @param pin numéro de l'interruption externe (INT0 - D2, INT1 - D3, INT2 - B3)
     * @param mode mode des interruptions
     */
    Externe(InterruptionExterne pin, ModeInterruption mode = FrontMontant);

    /**
     * @brief Active les interruptions externe
     */
    void activer() override;

    /**
     * @brief Désactive les interruptions externe
     */
    void desactiver() override;

    /**
     * @brief Contrôle des Flags d'interruption externe
     */
    void modifierFlag();

  private:
    InterruptionExterne pin_; // Pin de l'Atmel pour l'interruption

    /**
     * @brief Contrôle des détection d'interruption
     * @param mode mode des interruptions
     */
    void initialiserModeDetection(ModeInterruption mode = FrontMontant);

    /**
     * @brief Contrôle du registre de masque d'insterruption extern
     */
    void initialiser();
};

/**
 * @brief Gère les paramètres pour les interruptions de changement de Pin
 */
class PinChange : public Interruption{
  public:
    /**
     * @brief Construit un nouvel objet Pin Change
     * @param numero numéro de l'interruption externe (PCINTxx)
     */
    PinChange(uint8_t numero);

    /**
     * @brief Active les interruptions de changement de pin
     */
    void activer() override;

    /**
     * @brief Désactive les interruptions de changement de pin
     */
    void desactiver() override;

    /**
     * @brief Contrôle des Flags d'interruption externe
     */
    void modifierFlag();

    /**
     * @brief Permet de repartir tout interruption de PinChange
     */
    static void reprendre();

    /**
     * @brief Permet d'arrêter les interruption de PinChange
     */
    static void arret();

  private:
    InterruptionPinChange pin_; // Pin de l'Atmel pour l'interruption

    volatile uint8_t* PCMSKn_; // Indique quel port et broche du Atmel est activé
    uint8_t PCINTn_; // Sauvegarde la valeur du numéro de la Pin Change
    static uint8_t temporaire_; // Sauvegarde du PCICR pour l'arrêt des interruptions

    /**
     * @brief Contrôle du registre de masque d'interruption externe
     */
    void initialiser();
};

#endif /* INTERRUPTION_HPP */