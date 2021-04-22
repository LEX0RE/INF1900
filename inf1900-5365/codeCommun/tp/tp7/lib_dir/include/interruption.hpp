#ifndef INTERRUPTION_H
#define INTERRUPTION_H
/**
 * Librairie interruption.hpp
 * Date : 11/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */

/* Classe Interruption
 *   Gère les paramètres pour les interruptions
 */
class Interruption{
  public:
    /* Constructeur
     * --------------------------------------------------------------------
     *
     * Mode 0 : Bas niveau = Interruption
     * Mode 1 : Tout front = Interruption
     * Mode 2 : Front descendant = Interruption
     * Mode 3 : Front montant = Interruption
     * 
     * --------------------------------------------------------------------
     * Paramètre : 
     *      numero : numéro de l'interruption externe, 0 à 2, autre -> 0
     */
    Interruption(unsigned int numero = 0, unsigned int mode = 0);

    // Active les interruptions
    void activer();

    // Désactive les interruptions
    void desactiver();

    /* Contrôle des Flags d'insterruption externe
     */
    void modifierFlagInterruption();

  private:
    unsigned int numero_ = 0; // numero_ : numéro de l'interruption externe, 0 à 2, autre -> 0

    /* Contrôle des détection d'interruption
     *   Utilisé à l'initialisation
     * --------------------------------------------------------------------
     *
     * Mode 0 : Bas niveau = Interruption
     * Mode 1 : Tout front = Interruption
     * Mode 2 : Front descendant = Interruption
     * Mode 3 : Front montant = Interruption
     * 
     * --------------------------------------------------------------------
     * 
     * Paramètre : 
     *      mode : mode désiré, 0 à 3, autre -> 0
     */
    void initialiserDetectionInterruption(unsigned int mode);

    /* Contrôle du registre de masque d'insterruption externe
     *   Utilisé à l'initialisation
     */
    void initialiserMasqueInterruption();
};
#endif /* INTERRUPTION_H */