#ifndef EEPROM_H
#define EEPROM_H
/**
 * Librairie eeprom.hpp
 * Date : 11/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */

#include <stdint.h>

class Eeprom{
  public:
    Eeprom(uint8_t* adresse = 0x00);

    inline void lire(void* destination, size_t grandeur) const;
    inline void ecrire(const void* source) const;
    inline void mettreAJour(const void* source) const;

    void changerAdresse(uint8_t* adresse);
    inline Eeprom& operator+(uint8_t nombre);
    Eeprom& operator-(uint8_t nombre);
    inline friend Eeprom& operator+(const uint8_t nombre, const Eeprom& eeprom);
    inline friend Eeprom& operator-(const uint8_t nombre, const Eeprom& eeprom);
  private:
    uint8_t* adresse_; // Adresse où nous écrirons nos données
};

Eeprom& operator+(uint8_t nombre, Eeprom& eeprom){ return eeprom + nombre;}
Eeprom& operator-(uint8_t nombre, Eeprom& eeprom){ return eeprom - nombre;}

#endif /* EEPROM_H */