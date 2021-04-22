#ifndef USART_HPP
#define USART_HPP
/**
 * Librairie usart.hpp
 * Date : 11/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */

#include <stdint.h>

/** Classe USART
 *  Permet de gérer les UARTs
 */
class USART {
  public:

    /** Transmet un caractère dans le UART
     * 
     * -----------------------------------------
     *
     * Paramètre:
     *
     *  donnee: donne à envoyer
     */
    void transmettre(uint8_t donnee);

    /** Transmet un caractère dans le UART
     * 
     * -----------------------------------------
     *
     * Valeur de retour:
     *
     *  unsigned char: valeur reçu dans le UART
     */
    unsigned char recevoir();

    // Active la reception de message via le UART
    void activerReception();

    // Désactive la reception de message via le UART
    void desactiverReception();

    // Active la transmission de message via le UART
    void activerTransmission();

    // Désactive la transmission de message via le UART
    void desactiverTransmission();
  protected:
    unsigned int UDREn_, RXCn_;                       // Bit : Pour indiquer que le UART est prêt à recevoir/transmettre
    unsigned int RXENn_, TXENn_;                      // Bit : Pour activer/désactiver la transmission/réception
    unsigned int USBSn_, UCSZn0_, UCSZn1_, UCSZn2_;   // Bit : Pour la modification du nombre de bit à envoyer
    
    volatile uint8_t* UCSRnA_,* UCSRnB_,* UCSRnC_;    // Regsitre : Stockage des options
    volatile uint8_t* UBRRnH_,* UBRRnL_;              // Regsitre : Stockage du nombre de baud
    volatile uint8_t* UDRn_;                          // Regsitre : Stockage du message

    /** Initialisation du USART
     * 
     *  Paramètre :
     * 
     *      baud          : nombre de baud pour le USART pour la transmission de message
     *      modeStopBit   : mode sélectionné pour le nombre de stop bit
     *      modeBitEnvoye : mode sélectionné pour le nombre de bit à envoyé à la fois
     * ------------------------------------------------------------------------------------
     *         Stop Bit(s)
     * 
     *  Mode 0 : 1-bits
     *  Mode 1 : 2-bits
     * 
     * ----------------------------------------------------------
     *         Nombre de Bits
     * 
     *  Mode 0 : 5-bits
     *  Mode 1 : 6-bits
     *  Mode 2 : 7-bits
     *  Mode 3 : 8-bits
     *  Mode 4 : Réservé
     *  Mode 5 : Réservé
     *  Mode 6 : Réservé
     *  Mode 7 : 9-bits
     */
    void initialiser(int baud, bool modeStopBit, unsigned int modeBitEnvoye);

    // Permet de modifier les registres pour utiliser les fonctions de l'interface USART
    virtual void modifierRegistre() = 0;

    /** Détermine le nombre de stop bit
     * 
     *  Paramètre :
     * 
     *      mode : mode sélectionné pour le nombre de stop bit
     * 
     * ----------------------------------------------------------
     *         Stop Bit(s)
     * 
     *  Mode 0 : 1-bits
     *  Mode 1 : 2-bits
     */
    void modifierStopBit(bool mode);

    /** Modifie le nombre de bit à envoyer à la fois
     * 
     *  Paramètre :
     * 
     *      mode : mode sélectionné pour le nombre de bit à envoyé à la fois
     * 
     * ----------------------------------------------------------
     *         Nombre de Bits
     * 
     *  Mode 0 : 5-bits
     *  Mode 1 : 6-bits
     *  Mode 2 : 7-bits
     *  Mode 3 : 8-bits
     *  Mode 4 : Réservé
     *  Mode 5 : Réservé
     *  Mode 6 : Réservé
     *  Mode 7 : 9-bits
     */
    void modifierNombreBits(unsigned int mode);
};

class USART0 : public USART{
  public:
    // Empêche la copie
    USART0(USART0& autre) = delete;

    // Empêche l'assignation
    void operator=(const USART0&) = delete;
    
    // Permet d'obtenir l'instance du USART0 ou de le créer
    static USART0* obtenirInstance(int baud = 2400, bool modeStopBit = 0, unsigned int modeBitEnvoye = 3);

  private:
    static USART0* usart_; // instance du UART

    // Permet de modifier les registres pour utiliser les fonctions de l'interface USART
    void modifierRegistre() override;
  protected:
    USART0() = default;
    ~USART0();
};

class USART1 : public USART{
  public:
    // Empêche la copie
    USART1(USART1& autre) = delete;

    // Empêche l'assignation
    void operator=(const USART1&) = delete;

    // Permet d'obtenir l'instance du USART1 ou de le créer s'il ne l'est pas
    static USART1* obtenirInstance(int baud = 2400, bool modeStopBit = 0, unsigned int modeBitEnvoye = 3);

  private:
    static USART1* usart_; // instance du UART

    // Permet de modifier les registres pour utiliser les fonctions de l'interface USART
    void modifierRegistre() override;
  protected:
    USART1() = default;
    ~USART1();
};

#endif /* USART_HPP */