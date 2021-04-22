/**
 * Fonction eeprom.cpp
 * Date : 16/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */

#include <avr/eeprom.h>

#include "eeprom.hpp"

Eeprom::Eeprom(uint8_t* adresse) : adresse_(adresse){
    eeprom_busy_wait();
}

void Eeprom::lire(void* destination, size_t grandeur) const{
    eeprom_read_block(destination, adresse_, grandeur);
}

void Eeprom::ecrire(const void* source) const{
    eeprom_write_block(source, adresse_, sizeof(source));
}

void Eeprom::mettreAJour(const void* source) const{
    eeprom_update_block(source, adresse_, sizeof(source));
}

void Eeprom::changerAdresse(uint8_t* adresse){
    adresse_ = adresse;
}

Eeprom& Eeprom::operator+(uint8_t nombre){
    if (adresse_ + nombre > adresse_)
        adresse_ += nombre;
    return *this;
}

Eeprom& Eeprom::operator-(uint8_t nombre){
    if (nombre < *adresse_)
        adresse_ -= nombre;
    else
        adresse_ = 0x00;
    return *this;
}