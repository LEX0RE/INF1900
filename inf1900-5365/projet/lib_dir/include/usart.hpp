/**
 * @brief Libraire gérant l'intééraction avec le Uart
 * @file usart.hpp
 * @date 21/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#ifndef USART_HPP
#define USART_HPP

#define TABLEAU_ALLOUE 50

#include <stdint.h>

/**
 * @brief Enumération des modes pour le stop bit
 */
enum StopBits{SB1, SB2};

/**
 * @brief Enumération du nombre de Bits pouvant être envoyé par le USART
 */
enum BitsEnvoye{BE5, BE6, BE7, BE8, BE9};

/**
 * @brief Classe abstraite USART
 */
class USART {
public:
    /**
     * @brief Permet d'obtenir la valeur du Baud Rate
     * @param reel détermine si on prend la valeur entrée dans le registre (et donc pas celle entré par l'utilisateur)
     * @return uint32_t valeur du Baud Rate du Usart
     */
    uint32_t obtenirBaudRate(bool reel = false);

    /**
     * @brief Transmet un caractère dans le UART
     * @param donnee donnée à envoyer
     */
    void transmettre(uint8_t donnee);

    /**
     * @brief Transmet un chiffre de 8 bits à l'UART en ASCII
     * @param donnee donnée à envoyer
     * @param format format à utiliser pour le sprintf. Voir : https://www.cplusplus.com/reference/cstdio/printf/
     */
    void envoyer(uint8_t donnee, const char* format = "%u");

    /**
     * @brief Transmet un chiffre de 16 bits à l'UART en ASCII
     * @param donnee donnée à envoyer
     * @param format format à utiliser pour le sprintf. Voir : https://www.cplusplus.com/reference/cstdio/printf/
     */
    void envoyer(uint16_t donnee, const char* format = "%u");
    
    /**
     * @brief Transmet un chiffre de 32 Bits dans le UART
     * @param donnee donnée à envoyer
     * @param format format à utiliser pour le sprintf. Voir : https://www.cplusplus.com/reference/cstdio/printf/
     */
    void envoyer(uint32_t donnee, const char* format = "%lu");

    /**
     * @brief Transmet un float dans le UART en ASCII
     * @param donnee donnée à envoyer
     * @param format format à utiliser pour le sprintf. Voir : https://www.cplusplus.com/reference/cstdio/printf/
     */
    void envoyer(float donnee, const char* format = "%.1f");

    /**
     * @brief Transmet un int en ASCII dans le UART
     * @param donnee donnée à envoyer
     * @param format format à utiliser pour le sprintf. Voir : https://www.cplusplus.com/reference/cstdio/printf/
     */
    void envoyer(int donnee, const char* format = "%d");
    
    /**
     * @brief Transmet une chaîne de caractères dans le UART
     * @param donnee chaîne de caractères à envoyer
     */
    void envoyer(const char* donnee);

    /**
     * @brief Transmet un caractère dans le UART
     * @return unsigned char valeur reçu dans le UART
     */
    unsigned char recevoir();

    /**
     * @brief Active la reception de message via le UART
     */
    void activerReception();

    /**
     * @brief Désactive la reception de message via le UART
     */
    void desactiverReception();

    /**
     * @brief Active la transmission de message via le UART
     */
    void activerTransmission();

    /**
     * @brief Désactive la transmission de message via le UART
     */
    void desactiverTransmission();
protected:
    unsigned int UDREn_, RXCn_;                       // Bit : Pour indiquer que le UART est prêt à recevoir/transmettre
    unsigned int RXENn_, TXENn_;                      // Bit : Pour activer/désactiver la transmission/réception
    unsigned int USBSn_, UCSZn0_, UCSZn1_, UCSZn2_;   // Bit : Pour la modification du nombre de bit à envoyer
    
    volatile uint8_t* UCSRnA_,* UCSRnB_,* UCSRnC_;    // Regsitre : Stockage des options
    volatile uint8_t* UBRRnH_,* UBRRnL_;              // Regsitre : Stockage du nombre de baud
    volatile uint8_t* UDRn_;                          // Regsitre : Stockage du message

    uint32_t baud_;                                    // Sauvegarde le baud Rate pour prendre exactement celui qu'on veut en retour

    /**
     * @brief Initialisation du USART
     * @param baud nombre de baud pour le USART pour la transmission de message
     * @param modeStopBit mode sélectionné pour le nombre de stop bit
     * @param modeBitEnvoye mode sélectionné pour le nombre de bit à envoyé à la fois
     */
    void initialiser(uint16_t baud, StopBits modeStopBit, BitsEnvoye modeBitEnvoye);

    /**
     * @brief Permet de modifier les registres pour utiliser les fonctions de la classe abstraite USART
     */
    virtual void modifierRegistre() = 0;

    /**
     * @brief Détermine le nombre de stop bit
     * @param mode mode sélectionné pour le nombre de stop bit
     */
    void modifierStopBit(StopBits mode);

    /**
     * @brief Modifie le nombre de bit à envoyer à la fois
     * @param mode mode sélectionné pour le nombre de bit à envoyé à la fois
     */
    void modifierNombreBits(BitsEnvoye mode);
};


/**
 * @brief Classe pour gérer le Usart0
 */
class USART0 : public USART{
public:

    /**
     * @brief Constructeur empêchant la copie
     */
    USART0(USART0&) = delete;

    /**
     * @brief Empêche l'assignation
     */
    void operator=(const USART0&) = delete;
    
    /**
     * @brief Permet d'obtenir l'instance du USART0 ou de le créer
     * @param baud baud Rate voulu pour le Uart
     * @param modeStopBit nombre de stop bits voulu
     * @param modeBitEnvoye nombre de bits voulant être envoyé à la fois
     * @return USART0* instance du USART0
     */
    static USART0* obtenirInstance(uint32_t baud = 2400, StopBits modeStopBit = SB1, BitsEnvoye modeBitEnvoye = BE8);

private:
    static USART0* usart_; // instance du UART

    /**
     * @brief Permet de modifier les registres pour utiliser les fonctions de la classe abstraite USART
     */
    void modifierRegistre() override;
protected:

    /**
     * @brief Construit un nouvel objet USART0
     */
    USART0() = default;

    /**
     * @brief Détruit l'objet USART0
     */
    ~USART0();
};


/**
 * @brief Classe pour gérer le Usart1
 */
class USART1 : public USART{
public:

    /**
     * @brief Constructeur empêchant la copie
     */
    USART1(USART1&) = delete;

    /**
     * @brief Empêche l'assignation
     */
    void operator=(const USART1&) = delete;

    /**
     * @brief Permet d'obtenir l'instance du USART1 ou de le créer s'il ne l'est pas
     * @param baud baud rate voulu
     * @param modeStopBit nombre de stop bits voulu
     * @param modeBitEnvoye nombre de bits voulant être envoyé à la fois
     * @return USART1* instance du USART1
     */
    static USART1* obtenirInstance(uint32_t baud = 2400, StopBits modeStopBit = SB1, BitsEnvoye modeBitEnvoye = BE8);

private:
    static USART1* usart_; // instance du UART

    /**
     * @brief Permet de modifier les registres pour utiliser les fonctions de l'interface USART
     */
    void modifierRegistre() override;
protected:

    /**
     * @brief Construit un nouvel objet USART1
     */
    USART1() = default;

    /**
     * @brief Détruit l'objet USART1
     */
    ~USART1();
};

#endif /* USART_HPP */