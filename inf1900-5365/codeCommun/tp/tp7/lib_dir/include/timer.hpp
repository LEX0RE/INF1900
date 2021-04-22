#ifndef TIMER_H
#define TIMER_H
/**
 * Librairie timer.hpp
 * Date : 11/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */

#include <stdint.h>

/* Enum uniteTemps
 * 
 * Détermine le type de temps à utilisé
 * 
 * --------------------------------------------------------------------
 * 
 * Type :
 *      ms : milliseconde (10^⁻3)
 *      us : microseconde (10^⁻6)
 */
enum uniteTemps {ms, us};

/* Permet d'établir un délai de temps personnalisé
 * 
 * --------------------------------------------------------------------
 * 
 * Paramètre : 
 *    delai      : valeur qui détermine la durée du délait
 *    uniteTemps : détermine quelle est l'unité de temps du délai
 */
void delaiVariable(int delai, uniteTemps unite);


/* Classe Timer
 *   Gère les minuteries
 * 
 *   P.S. Counter/Timer #3 non disponible dans atmega-324a
 */
class Timer{
  public:
    virtual void modifierTop(uint8_t top, bool x = 0);
    /* Obtenir le PWM du Timer
     * Paramètre : 
     *      x : 0 -> A, 1 -> B
     */
    virtual unsigned int obtenirPWM(bool x = 0) const;
  protected:
    unsigned int WGMn0_, WGMn1_, WGMn2_;                  // Bit : Détermine le mode de la minuterie
    unsigned int CSn0_, CSn1_, CSn2_;                     // Bit : Détermine le prescaler
    unsigned int COMnA0_, COMnA1_, COMnB0_, COMnB1_;      // Bit : Gestion du mode de comparaison de la sortie
    unsigned int OCIEnA_, OCIEnB_, TOIEn_;                // Bit : Gestion des interruption

    volatile uint8_t* OCRnA_,* OCRnB_;                    // Registre : valeur maximale du Timer
    volatile uint8_t* TCCRnA_,* TCCRnB_;                  // Registre : contrôle du Timer
    volatile uint8_t* TIMSKn_;                            // Registre : Masque d'interruption du Timer
    volatile uint8_t* TCNTn_;                             // Registre : Timer

    virtual void modifierRegistre() = 0;

    void initialiser(unsigned int modeMinuterie = 0, 
                     unsigned int modeComparaisonA = 0,
                     unsigned int modeComparaisonB = 0,
                     unsigned int prescaler = 0,
                     unsigned int modeInterruption = 0);  // Initialise le Timer, utilisé après modifierRegistre

    virtual unsigned int obtenirPrescaler() const;
    virtual void modifierModeMinuterie(unsigned int modeMinuterie);
    void modifierModeComparaison(unsigned int modeComparaison, bool x = 0);
    void modifierPrescaler(unsigned int prescaler);
    void modifierInterruption(unsigned int modeInterruption);
    virtual inline void modifierCompteur(uint8_t compteur);
};

/* Timer/Counter0 8-Bits
 *
 */
class Timer0 : public Timer{
  public:
    /* Constructeur
     * Paramètre : 
     *      modeMinuterie   : mode de fonctionnement de la minuterie
     *      modeComparaison : mode de comparaison de la sortie
     *      prescaler       : mode de prescaler de la minuterie
     * --------------------------------------------------------------------------------------------------
     *                  Mode
     * 
     *             Mode d'opération     |   Valeur Plafond      |   Mise à jour de OCRnX    |   TOVn Flag
     * 
     * Mode  0 :        Normal          |         0xFF          |           Immédiat        |      MAX
     * Mode  1 :   PWM, Phase Correct   |         0xFF          |             TOP           |     BOTTOM
     * Mode  2 :          CTC           |         0CRA          |           Immédiat        |      MAX
     * Mode  3 :    Fast PWM, 8-bit     |         0xFF          |            BOTTOM         |      TOP
     * Mode  4 :      (Réservé)         |         ---           |             ---           |      ---
     * Mode  5 :   PWM, Phase Correct   |         0CRA          |             TOP           |     BOTTOM
     * Mode  6 :      (Réservé)         |         ---           |             ---           |      ---
     * Mode  7 :       Fast PWM         |         0CRA          |            BOTTOM         |      TOP
     * 
     * MAX    = 0xFF
     * BOTTOM = 0x00
     * --------------------------------------------------------------------------------------------------
     *             Prescaler
     * 
     * Mode  0  : Pas de source de la minuterie
     * Mode  1  : clk /    1
     * Mode  2  : clk /    8
     * Mode  3  : clk /   64
     * Mode  4  : clk /  256
     * Mode  5  : clk / 1024
     * Mode  6  : Source de la minuterie sur Tn, minuterie sur front descendant
     * Mode  7  : Source de la minuterie sur Tn, minuterie sur front montant
     * 
     * --------------------------------------------------------------------------------------------------
     *             Mode de comparaison de la sortie
     * 
     * Mode  0  : Opération normal, OCnA/OCnB déconnecté
     * Mode  1  : Toggle on Match compare
     * Mode  2  : Clear on Match compare (met à 0)
     * Mode  3  : Set on Match compare (met à 1)
     * 
     * --------------------------------------------------------------------------------------------------
     *              Gestion des interruptions
     * 
     * Mode 0   : Rien
     * Mode 1   : Compare Match A
     * Mode 2   : Compare Match B
     * Mode 3   : Compare Match Overflow
     */
    Timer0(unsigned int modeMinuterie = 0, 
           unsigned int modeComparaisonA = 0,
           unsigned int modeComparaisonB = 0,
           unsigned int prescaler = 0,
           unsigned int modeInterruption = 0,
           uint8_t compteur = 0,
           uint8_t topA = 0xFF,
           uint8_t topB = 0xFF);

    /* Obtenir la valeur maximal du Timer
     * Paramètre : 
     *      x : 0 -> A, 1 -> B
     */
    uint8_t obtenirTop(bool x = 0) const;
  private:
    void modifierRegistre();
};

/* Timer/Counter1 16-Bits
 *
 */
class Timer1 : public Timer{
  public:
    /* Constructeur
     * Paramètre : 
     *      modeMinuterie   : mode de fonctionnement de la minuterie
     *      modeComparaison : mode de comparaison de la sortie
     *      prescaler       : mode de prescaler de la minuterie
     * --------------------------------------------------------------------------------------------------
     *                  Mode
     * 
     *             Mode d'opération     |   Valeur Plafond      |   Mise à jour de OCRnX    |   TOVn Flag
     * 
     * Mode  0 :        Normal          |        0xFFFF         |           Immédiat        |      MAX
     * Mode  1 :   PWM, Phase Correct   |        0x00FF         |             TOP           |     BOTTOM
     * Mode  2 :   PWM, Phase Correct   |        0x01FF         |             TOP           |     BOTTOM
     * Mode  3 :   PWM, Phase Correct   |        0x03FF         |             TOP           |     BOTTOM
     * Mode  4 :          CTC           |        0CRnA          |           Immédiat        |      MAX
     * Mode  5 :    Fast PWM, 8-bit     |        0x00FF         |            BOTTOM         |      TOP
     * Mode  6 :    Fast PWM, 9-bit     |        0x01FF         |            BOTTOM         |      TOP
     * Mode  7 :    Fast PWM, 10-bit    |        0x03FF         |            BOTTOM         |      TOP
     * Mode  8 : PWM-Phase-Frequency C. |         ICRn          |            BOTTOM         |     BOTTOM
     * Mode  9 : PWM-Phase-Frequency C. |        0CRnA          |            BOTTOM         |     BOTTOM
     * Mode 10 :   PWM, Phase Correct   |         ICRn          |             TOP           |     BOTTOM
     * Mode 11 :   PWM, Phase Correct   |        0CRnA          |             TOP           |     BOTTOM
     * Mode 12 :          CTC           |         ICRn          |           Immédiat        |      MAX
     * Mode 13 :      (Réservé)         |         ---           |             ---           |      ---
     * Mode 14 :       Fast PWM         |         ICRn          |            BOTTOM         |      TOP
     * Mode 15 :       Fast PWM         |        0CRnA          |            BOTTOM         |      TOP
     * 
     * --------------------------------------------------------------------------------------------------
     *             Prescaler
     * 
     * Mode  0  : Pas de source de la minuterie
     * Mode  1  : clk /    1
     * Mode  2  : clk /    8
     * Mode  3  : clk /   64
     * Mode  4  : clk /  256
     * Mode  5  : clk / 1024
     * Mode  6  : Source de la minuterie sur Tn, minuterie sur front descendant
     * Mode  7  : Source de la minuterie sur Tn, minuterie sur front montant
     * 
     * --------------------------------------------------------------------------------------------------
     *             Mode de comparaison de la sortie
     * 
     * Mode  0  : Opération normal, OCnA/OCnB déconnecté
     * Mode  1  : Toggle on Match compare | 0CnB déconnecté en PWM
     * Mode  2  : Clear on Match compare (met à 0)
     * Mode  3  : Set on Match compare (met à 1)
     */
    Timer1(unsigned int modeMinuterie = 0, 
           unsigned int modeComparaisonA = 0,
           unsigned int modeComparaisonB = 0,
           unsigned int prescaler = 0,
           unsigned int modeInterruption = 0,
           uint16_t compteur = 0,
           uint16_t topA = 0xFFFF,
           uint16_t topB = 0xFFFF);

    inline void modifierTop(uint16_t top, bool x = 0);
    /* Obtenir le PWM du Timer
     * Paramètre : 
     *      x : 0 -> A, 1 -> B
     */
    unsigned int obtenirPWM(bool x = 0) const;
    /* Obtenir la valeur maximal du Timer
     * Paramètre : 
     *      x : 0 -> A, 1 -> B
     */
    uint16_t obtenirTop(bool x = 0) const;
  private:
    unsigned int WGM13_;                                  // Bit : Détermine le mode de la minuterie
    volatile uint16_t* OCRnA_,* OCRnB_;                   // Registre : valeur maximale du Timer
    volatile uint16_t* TCNTn_;                             // Registre : Timer

    void modifierModeMinuterie(unsigned int modeMinuterie);
    inline void modifierCompteur(uint16_t commpteur);
    void modifierRegistre();
};

/* Timer/Counter2 8-Bits
 *
 */
class Timer2 : public Timer{ // À changer pour les registres car sauvegarder dans Timer0
  public:
    /* Constructeur
     * Paramètre : 
     *      modeMinuterie   : mode de fonctionnement de la minuterie
     *      modeComparaison : mode de comparaison de la sortie
     *      prescaler       : mode de prescaler de la minuterie
     * --------------------------------------------------------------------------------------------------
     *                  Mode
     * 
     *             Mode d'opération     |   Valeur Plafond      |   Mise à jour de OCRnX    |   TOVn Flag
     * 
     * Mode  0 :        Normal          |         0xFF          |           Immédiat        |      MAX
     * Mode  1 :   PWM, Phase Correct   |         0xFF          |             TOP           |     BOTTOM
     * Mode  2 :          CTC           |         0CRA          |           Immédiat        |      MAX
     * Mode  3 :    Fast PWM, 8-bit     |         0xFF          |            BOTTOM         |      TOP
     * Mode  4 :      (Réservé)         |         ---           |             ---           |      ---
     * Mode  5 :   PWM, Phase Correct   |         0CRA          |             TOP           |     BOTTOM
     * Mode  6 :      (Réservé)         |         ---           |             ---           |      ---
     * Mode  7 :       Fast PWM         |         0CRA          |            BOTTOM         |      TOP
     * 
     * MAX    = 0xFF
     * BOTTOM = 0x00
     * --------------------------------------------------------------------------------------------------
     *             Prescaler
     * 
     * Mode  0  : Pas de source de la minuterie
     * Mode  1  : clk /    1
     * Mode  2  : clk /    8
     * Mode  3  : clk /   32
     * Mode  4  : clk /   64
     * Mode  5  : clk /  128
     * Mode  6  : clk /  256
     * Mode  7  : clk / 1024
     * 
     * --------------------------------------------------------------------------------------------------
     *             Mode de comparaison de la sortie
     * 
     * Mode  0  : Opération normal, OCnA/OCnB déconnecté
     * Mode  1  : Toggle on Match compare
     * Mode  2  : Clear on Match compare (met à 0)
     * Mode  3  : Set on Match compare (met à 1)
     * 
     * --------------------------------------------------------------------------------------------------
     *              Gestion des interruptions
     * 
     * Mode 0   : Rien
     * Mode 1   : Compare Match A
     * Mode 2   : Compare Match B
     * Mode 3   : Compare Match Overflow
     */
    Timer2(unsigned int modeMinuterie = 0, 
           unsigned int modeComparaisonA = 0,
           unsigned int modeComparaisonB = 0,
           unsigned int prescaler = 0,
           unsigned int modeInterruption = 0,
           uint8_t compteur = 0,
           uint8_t topA = 0xFF,
           uint8_t topB = 0xFF);

    /* Obtenir la valeur maximal du Timer
     * Paramètre : 
     *      x : 0 -> A, 1 -> B
     */
    uint8_t obtenirTop(bool x = 0) const;
  private:
    unsigned int obtenirPrescaler() const;
    void modifierRegistre();
};

#endif /* TIMER_H */