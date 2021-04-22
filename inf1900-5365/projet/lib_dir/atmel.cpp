/**
 * @brief Définition des fonction pour le fichier atmel.hpp
 * @file atmel.cpp
 * @date 21/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#include <avr/io.h>
#include "include/atmel.hpp"

void modifierDDRX(const uint8_t portA, const uint8_t portB, 
                  const uint8_t portC, const uint8_t portD){
    DDRA = portA;
    DDRB = portB;
    DDRC = portC;
    DDRD = portD;
}

void modifierPort(Port port, const uint8_t valeur){
    switch(port){
        case B:
            DDRB = valeur;
        break;
        case C:
            DDRC = valeur;
        break;
        case D:
            DDRD = valeur;
        break;
        case A: default:
            DDRA = valeur;
    }
}

volatile uint8_t* obtenirPort(Port port){
    switch(port){
        case B:
            return &PORTB;
        break;
        case C:
            return &PORTC;
        break;
        case D:
            return &PORTD;
        break;
        case A: default:
            return &PORTA;
    }
}

volatile uint8_t* obtenirPin(Port port){
    switch(port){
        case B:
            return &PINB;
        break;
        case C:
            return &PINC;
        break;
        case D:
            return &PIND;
        break;
        case A: default:
            return &PINA;
    }
}