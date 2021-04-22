#ifndef EEPROM_HPP
#define EEPROM_HPP
/**
 * Librairie eeprom.hpp
 * Date : 11/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */

#include <stdint.h>
#include <stdio.h>

class Eeprom{
  public:
    Eeprom(uint8_t* adresse = 0x00);

    void lire(void* destination, size_t grandeur) const;
    void ecrire(const void* source) const;
    void mettreAJour(const void* source) const;

    void changerAdresse(uint8_t* adresse);
    Eeprom& operator+(uint8_t nombre);
    Eeprom& operator-(uint8_t nombre);
    //friend Eeprom& operator+(uint8_t nombre, Eeprom& eeprom){ return eeprom + nombre;}
    //friend Eeprom& operator-(uint8_t nombre, Eeprom& eeprom){ return eeprom - nombre;}
  private:
    uint8_t* adresse_; // Adresse où nous écrirons nos données
};

#endif /* EEPROM_HPP */