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

class USART {
  public:
    void transmettre(uint8_t donnee);
  protected:
    unsigned int numero_;
    unsigned int UDREn_;
    unsigned int RXENn_, TXENn_;
    unsigned int USBSn_, UCSZn0_, UCSZn1_, UCSZn2_;
    volatile uint8_t* UCSRnA_,* UCSRnB_,* UCSRnC_;
    volatile uint8_t* UBRRnH_,* UBRRnL_;
    volatile uint8_t* UDRn_;

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
    void initialiser(uint8_t baud, bool modeStopBit, unsigned int modeBitEnvoye);

    virtual void modifierRegistre() = 0;

    void activerReception();
    void activerTransmission();

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
    USART0(uint8_t baud = 0xCF, bool modeStopBit = 1, unsigned int modeBitEnvoye = 3);
  private:
    void modifierRegistre();
};

class USART1 : public USART{
  public:
    USART1(uint8_t baud = 0xCF, bool modeStopBit = 1, unsigned int modeBitEnvoye = 3);
  private:
    void modifierRegistre();
};

#endif /* USART_HPP */