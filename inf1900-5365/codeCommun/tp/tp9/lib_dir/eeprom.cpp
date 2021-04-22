/**
 * Fonction eeprom.cpp
 * Date : 16/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */
#include <avr/eeprom.h>
#include <stdlib.h> 

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
    int grandeurVTable = 1;
    int grandeur = sizeof(source) - grandeurVTable;
    
    eeprom_write_block(source, pAdresse_, grandeur);

    adresse_ += grandeur;
    pAdresse_ += grandeur;
}

void Eeprom::mettreAJour(const void* source){
    int grandeurVTable = 1;
    int grandeur = sizeof(source) - grandeurVTable;

    eeprom_update_block(source, pAdresse_, grandeur);

    adresse_ += grandeur;
    pAdresse_ += grandeur;
}

void Eeprom::remiseAZero(){
    pAdresse_ = 0x00;

    for(unsigned int i = 0; i < 256; i++){
        eeprom_write_byte(pAdresse_, 255);
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