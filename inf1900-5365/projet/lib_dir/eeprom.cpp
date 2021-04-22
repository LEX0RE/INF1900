/**
 * @brief Définition des fonction pour le fichier eeprom.hpp
 * @file eeprom.cpp
 * @date 21/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#include <avr/eeprom.h>
#include <stdlib.h> 

#define MAX_CAPACITY 255

#include "include/eeprom.hpp"

Eeprom* Eeprom::eeprom_{nullptr};
uint8_t Eeprom::adresse_{0x00};
uint8_t* Eeprom::pAdresse_{0x00};

Eeprom::~Eeprom(){
    free(eeprom_);
}

Eeprom* Eeprom::obtenirInstance() {
    if(eeprom_ == nullptr){
        eeprom_ = (Eeprom*)malloc(sizeof(Eeprom));
        eeprom_busy_wait();
    }

    return eeprom_;
}

void Eeprom::lire(void* destination, size_t grandeur){
    eeprom_read_block(destination, pAdresse_, grandeur);

    adresse_ += grandeur;
    pAdresse_ += grandeur;
}

void Eeprom::ecrire(const void* source){
    uint8_t grandeurVTable = 1;
    int grandeur = sizeof(source) - grandeurVTable;
    
    eeprom_write_block(source, pAdresse_, grandeur);

    adresse_ += grandeur;
    pAdresse_ += grandeur;
}

void Eeprom::remiseAZero(){
    pAdresse_ = 0x00;

    // Remet chaque adresse de mémoire à 255
    for(uint16_t i = 0; i <= MAX_CAPACITY; i++){
        eeprom_write_byte(pAdresse_, MAX_CAPACITY);
        pAdresse_++;
    }

    adresse_ = 0x00;
    pAdresse_ = 0x00;
}

uint8_t Eeprom::obtenirAdresse() const{
    return adresse_;
}

void Eeprom::changerAdresse(uint8_t adresse){
    adresse_ = 0x00;
    pAdresse_ = 0x00;

    adresse_ += adresse;
    pAdresse_ += adresse;
}

Eeprom& Eeprom::operator+=(uint8_t nombre){
    adresse_ += nombre;
    pAdresse_ += nombre;

    return *this;
}

Eeprom& Eeprom::operator++(){
    adresse_++;
    pAdresse_++;

    return *this;
}

Eeprom& Eeprom::operator-=(uint8_t nombre){
    adresse_ -= nombre;
    pAdresse_ -= nombre;

    return *this;
}

Eeprom& Eeprom::operator--(){
    adresse_--;
    pAdresse_--;
    
    return *this;
}