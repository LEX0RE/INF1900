/**
 * Fonction atmel.cpp
 * Date : 16/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */


#include <avr/io.h>
#include "include/atmel.hpp"


void modifierDDRX(const unsigned int portA, const unsigned int portB, 
                  const unsigned int portC, const unsigned int portD){
    if(portA == 1)
        DDRA = 0x00;
    else if(portA == 2)
        DDRA = 0xFF;

    if(portB == 1)
        DDRB = 0x00;
    else if(portB == 2)
        DDRB = 0xFF;

    if(portC == 1)
        DDRC = 0x00;
    else if(portC == 2)
        DDRC = 0xFF;

    if(portD == 1)
        DDRD = 0x00;
    else if(portD == 2)
        DDRD = 0xFF;
}