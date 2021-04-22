/**
 * @brief Librairie pour l'échange avec la mémoire interne du Atmel (Eeprom)
 * @file eeprom.hpp
 * @date 20/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#ifndef EEPROM_HPP
#define EEPROM_HPP

#include <stdint.h>
#include <stdio.h>

/**
 * @brief Classe gérant l'utilisation du Eeprom
 */
class Eeprom{
public:
    /**
     * @brief Empêche la copie de la classe
     */
    Eeprom(Eeprom&) = delete;

    /**
     * @brief Empêche l'assignation de la classe
     */
    void operator=(const Eeprom&) = delete;

    /**
     * @brief Permet d'obtenir l'instance du Eeprom ou de le créer
     * @return Eeprom* instance de la classe Eeprom
     */
    static Eeprom* obtenirInstance();

    /**
     * @brief Lire la mémoire du Eeprom selon la grandeur sélectionnée à l'adresse stockée dans la classe
     * @param destination pointeur à utilisé pour stocker ce qui est lu
     * @param grandeur nombre de bit à lire sur la mémoire
     */
    void lire(void* destination, size_t grandeur);

    /**
     * @brief Écrire sur la mémoire du Eeprom en fonction de l'adresse stockée dans la classe Eeprom
     * @param source pointeur vers la valeur à stocker dans la mémoire
     */
    void ecrire(const void* source);

    /**
     * @brief Remet à 255 toute les cases mémoires du Eeprom
     */
    void remiseAZero();

    /**
     * @brief Retourne l'adresse de la classe Eeprom en fonction de l'adresse stockée dans la classe Eeprom
     * @return uint8_t adresse de la classe
     */
    uint8_t obtenirAdresse() const;

    /**
     * @brief Change l'adresse de la classe Eeprom
     * @param adresse nouvelle adresse pour la classe Eeprom
     */
    void changerAdresse(uint8_t adresse);

    /**
     * @brief Permet d'ajouter directement à l'adresse de la classe
     * @param nombre nombre à ajouter à l'adresse
     * @return Eeprom& l'instance de la classe
     */
    Eeprom& operator+=(uint8_t nombre);

    /**
     * @brief Incrémente l'adresse de la classe
     * @return Eeprom& instance de la classe
     */
    Eeprom& operator++();

    /**
     * @brief Permet de soustraire directement à l'adresse de la classe
     * @param nombre nombre à soustraire de l'adresse
     * @return Eeprom& instance de la classe
     */
    Eeprom& operator-=(uint8_t nombre);

    /**
     * @brief Décrémente l'adresse de la classe
     * @return Eeprom& instance de la classe
     */
    Eeprom& operator--();
private:
    static Eeprom* eeprom_; // Instance de la classe

    static uint8_t adresse_; // Adresse où nous écrirons nos données
    static uint8_t* pAdresse_; // Adresse utilisé pour l'échange avec le Eeprom
protected:
    /**
     * @brief Empêche la création d'instance externe
     */
    Eeprom() = default;

    /**
     * @brief Empêche la destruction externe de l'instance
     */
    ~Eeprom();
};
#endif /* EEPROM_HPP */