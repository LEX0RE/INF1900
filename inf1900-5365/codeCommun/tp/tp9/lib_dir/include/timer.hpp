#ifndef TIMER_HPP
#define TIMER_HPP
/**
 * Librairie timer.hpp
 * Date : 11/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */

#include <stdint.h>

/* Permet d'établir un délai de temps personnalisé
 * 
 * --------------------------------------------------------------------
 * 
 * Paramètre : 
 *    delai      : valeur qui détermine la durée du délait
 *    uniteTemps : détermine quelle est l'unité de temps du délai
 * 
 * --------------------------------------------------------------------
 * 
 * Type :
 *      0 : ms - milliseconde (10^⁻3)
 *      1 : us - microseconde (10^⁻6)
 */
void delaiVariable(int delai, unsigned int unite);


/* Classe Timer
 *   Gère les minuteries
 * 
 *   P.S. Counter/Timer #3 non disponible dans atmega-324a
 */
class Timer{
  public:
    /** Obtenir la valeur maximale du Timer
     * 
     * --------------------------------------------------------------------
     *  On doit caster le type du timer selon celui-ci pour bien utilisé la donnée après
     * --------------------------------------------------------------------
     * 
     * Paramètre:
     * 
     *  bool:   indique si on obtient le top du A (0) ou du B (1)
     * 
     * --------------------------------------------------------------------
     *
     * Valeur de retour:
     *
     *  void*: top
     */
    volatile void* obtenirTop(bool x = 0) const;

    /** Modifier la valeur du TOP pour le PWM
    * 
    * --------------------------------------------------------------------
    * 
    * Paramètres:
    * 
    *  top:   valeur à mettre au top
    *  bool:  indique si on modifie le top du A (0) ou du B (1)
    */
    void modifierTop(uint8_t top, bool x = 0);

    /** Modifie le mode de comparaison du Timer
    * 
    * --------------------------------------------------------------------
    * 
    * Paramètre:
    * 
    *  modeComparaison: mode de comparaison souhaité
    *  bool:            indique si on obtient le top du A (0) ou du B (1)
    *
    * --------------------------------------------------------------------------------------------------
    * Voir le constructeur pour plus de détails
    */
    void modifierModeComparaison(unsigned int modeComparaison, bool x = 0);

    /** Permet d'arrêter le PWM
     *  
     * --------------------------------------------------------------------
     * 
     * Paramètre:
     * 
     *  bool:            indique si on obtient le top du A (0) ou du B (1)
     */
    void arreterPWM(bool x);

    /** Permet de repartir le PWM après l'avoir arrêté
     *  
     * --------------------------------------------------------------------
     * 
     * Paramètre:
     * 
     *  bool:            indique si on obtient le top du A (0) ou du B (1)
     */
    void demarrerPWM(bool x);
  protected:
    uint8_t WGMn0_, WGMn1_, WGMn2_;                     // Bit : Détermine le mode de la minuterie
    uint8_t CSn0_, CSn1_, CSn2_;                        // Bit : Détermine le prescaler
    uint8_t COMnA0_, COMnA1_, COMnB0_, COMnB1_;         // Bit : Gestion du mode de comparaison de la sortie
    uint8_t OCIEnA_, OCIEnB_, TOIEn_;                   // Bit : Gestion des interruption

    volatile uint8_t* OCRnA_,* OCRnB_;                  // Registre : valeur maximale du Timer
    volatile uint8_t* TCCRnA_,* TCCRnB_;                // Registre : contrôle du Timer
    volatile uint8_t* TIMSKn_;                          // Registre : Masque d'interruption du Timer
    volatile uint8_t* TCNTn_;                           // Registre : Timer

    unsigned int modeComparaison_;                      // Sert à se souvenir du mode de comparaison pour l'arrêt

    uint8_t OCnA_, OCnB_;                               // Bit : Permet de savoir où se trouve les pin de sortie
    volatile uint8_t* PORT_;                            // Port : Permet de savoir où se trouve le port de OCnA et OCnB

    virtual void modifierRegistre() = 0;

    // Initialiser le Timer, voir le constructeur pour plus de détail
    void initialiser(unsigned int modeComparaisonA = 0,
                     unsigned int modeComparaisonB = 0,
                     unsigned int prescaler = 0,
                     unsigned int modeInterruption = 0);

    /** Modfie le mode du prescaler
     *  
     * --------------------------------------------------------------------
     * 
     * Paramètre:
     * 
     *  prescaler:  mode souhaité pour le prescaler
     *  
     * --------------------------------------------------------------------
     * Voir le constructeur pour plus de détails
     */
    void modifierPrescaler(unsigned int prescaler);

    /** Modfie le mode des interruptions
     *  
     * --------------------------------------------------------------------
     * 
     * Paramètre:
     * 
     *  modeInterruption:  mode d'interruption souhaité
     *  
     * --------------------------------------------------------------------
     * Voir le constructeur pour plus de détails
     */
    void modifierInterruption(unsigned int modeInterruption);

    /** Modfie la valeur actuelle du compteur
     *  
     * --------------------------------------------------------------------
     * 
     * Paramètre:
     * 
     *  compteur:  nouvelle valeur du compteur souhaité
     */
    void modifierCompteur(uint8_t compteur);
};

/* Timer/Counter0 8-Bits
 *
 */
class Timer0 : public Timer{
  public:
    // Empêche la copie
    Timer0(Timer0& autre) = delete;

    // Empêche l'assignation
    void operator=(const Timer0&) = delete;

    /* Permet d'obtenir l'instance ou de la créer
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
    static Timer0* obtenirInstance(unsigned int modeMinuterie = 0, unsigned int modeComparaisonA = 0,
                                   unsigned int modeComparaisonB = 0, unsigned int prescaler = 0,
                                   unsigned int modeInterruption = 0, uint8_t compteur = 0, 
                                   uint8_t topA = 0xFF, uint8_t topB = 0xFF);

    /** Obtenir le PWM du Timer
    * 
    * --------------------------------------------------------------------
    * 
    * Paramètre:
    * 
    *  bool:  indique si on obtient le top du A (0) ou du B (1)
    *
    * --------------------------------------------------------------------
    * 
    * Valeur de retour:
    * 
    *  unsigned int:  valeur du PWM
    */
    unsigned int obtenirPWM(bool x = 0) const;

    /** Obtenir le prescaler du Timer
    * 
    * --------------------------------------------------------------------
    * 
    * Valeur de retour:
    * 
    *  unsigned int:  valeur du prescaler
    */
    unsigned int obtenirPrescaler() const;
  private:
    static Timer0* timer_; // instance du Timer

    // Modifie les variables de la classe Timer pour utiliser les fonctions de celle-ci
    void modifierRegistre() override;

    /** Modfie le mode de la minuterie
     *  
     * --------------------------------------------------------------------
     * 
     * Paramètre:
     * 
     *  modeMinuterie:  indique le mode de la minuterie
     *  
     * --------------------------------------------------------------------
     * Voir le constructeur pour plus de détails
     */
    void modifierModeMinuterie(unsigned int modeMinuterie);
  protected:
    Timer0() = default;
    ~Timer0();
};

/* Timer/Counter1 16-Bits
 *
 */
class Timer1 : public Timer{
  public:
    // Empêche la copie
    Timer1(Timer1& autre) = delete;
    
    // Empêche l'assignation
    void operator=(const Timer1&) = delete;

    /* Permet d'obtenir l'instance ou de la créer
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
    static Timer1* obtenirInstance(unsigned int modeMinuterie = 0, unsigned int modeComparaisonA = 0,
                                   unsigned int modeComparaisonB = 0, unsigned int prescaler = 0,
                                   unsigned int modeInterruption = 0, uint16_t compteur = 0,
                                   uint16_t topA = 0xFFFF, uint16_t topB = 0xFFFF);

    /** Modifier la valeur du TOP pour le PWM
    * 
    * --------------------------------------------------------------------
    * 
    * Paramètres:
    * 
    *  top:   valeur à mettre au top
    *  bool:  indique si on modifie le top du A (0) ou du B (1)
    */
    void modifierTop(uint16_t top, bool x = 0);
    /* Obtenir le PWM du Timer
     * Paramètre : 
     *      x : 0 -> A, 1 -> B
     */
    unsigned int obtenirPWM(bool x = 0) const;

    /** Obtenir le prescaler du Timer
    * 
    * --------------------------------------------------------------------
    * 
    * Valeur de retour:
    * 
    *  unsigned int:  valeur du prescaler
    */
    unsigned int obtenirPrescaler() const;

  private:
    static Timer1* timer_;                                  // instance du Timer

    uint8_t WGM13_;                                         // Bit : Détermine le mode de la minuterie
    volatile uint16_t* OCRnA_,* OCRnB_;                     // Registre : valeur maximale du Timer
    volatile uint16_t* TCNTn_;                              // Registre : Timer

    /** Modfie le mode de la minuterie
     *  
     * --------------------------------------------------------------------
     * 
     * Paramètre:
     * 
     *  modeMinuterie:  indique le mode de la minuterie
     *  
     * --------------------------------------------------------------------
     * Voir le constructeur pour plus de détails
     */
    void modifierModeMinuterie(unsigned int modeMinuterie);

    /** Modfie la valeur actuelle du compteur
     *  
     * --------------------------------------------------------------------
     * 
     * Paramètre:
     * 
     *  compteur:  nouvelle valeur du compteur souhaité
     */
    void modifierCompteur(uint16_t compteur);
    // Modifie les variables de la classe Timer pour utiliser les fonctions de celle-ci
    void modifierRegistre() override;
  protected:
    Timer1() = default;
    ~Timer1();
};

/* Timer/Counter2 8-Bits
 *
 */
class Timer2 : public Timer{ // À changer pour les registres car sauvegarder dans Timer0
  public:
    // Empêche la copie
    Timer2(Timer2& autre) = delete;
    
    // Empêche l'assignation
    void operator=(const Timer2&) = delete;

    /* Permet d'obtenir l'instance ou de la créer
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
    static Timer2* obtenirInstance(unsigned int modeMinuterie = 0, unsigned int modeComparaisonA = 0,
           unsigned int modeComparaisonB = 0, unsigned int prescaler = 0,
           unsigned int modeInterruption = 0, uint8_t compteur = 0,
           uint8_t topA = 0xFF, uint8_t topB = 0xFF);

    /** Obtenir le prescaler du Timer
    * 
    * --------------------------------------------------------------------
    * 
    * Paramètre:
    * 
    *  bool:  indique si on obtient le top du A (0) ou du B (1)
    *
    * --------------------------------------------------------------------
    * 
    * Valeur de retour:
    * 
    *  unsigned int:  valeur du prescaler
    */
    unsigned int obtenirPrescaler() const;

    /** Obtenir le PWM du Timer
    * 
    * --------------------------------------------------------------------
    * 
    * Paramètre:
    * 
    *  bool:  indique si on obtient le top du A (0) ou du B (1)
    *
    * --------------------------------------------------------------------
    * 
    * Valeur de retour:
    * 
    *  unsigned int:  valeur du PWM
    */
    unsigned int obtenirPWM(bool x = 0) const;
  private:
    static Timer2* timer_;  // instance du timer

    // Modifie les variables de la classe Timer pour utiliser les fonctions de celle-ci
    void modifierRegistre() override;

    /** Modfie le mode de la minuterie
     *  
     * --------------------------------------------------------------------
     * 
     * Paramètre:
     * 
     *  modeMinuterie:  indique le mode de la minuterie
     *  
     * --------------------------------------------------------------------
     * Voir le constructeur pour plus de détails
     */
    void modifierModeMinuterie(unsigned int modeMinuterie);
  protected:
    Timer2() = default;
    ~Timer2();
};

#endif /* TIMER_HPP */