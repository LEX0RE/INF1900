/**
 * Fonction interruption.cpp
 * Date : 11/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */

#include <avr/interrupt.h>

#include "include/interruption.hpp"

Interruption::Interruption(unsigned int numero, unsigned int mode){
    if(numero <= 2)
        numero_ = numero;
    else
        numero_ = 0;
    
    initialiserMasqueInterruption();
    initialiserDetectionInterruption(mode);
}

void Interruption::activer(){ sei(); }

void Interruption::desactiver(){ cli(); }

void Interruption::initialiserDetectionInterruption(unsigned int mode){
    int ISCn0, ISCn1;
    switch(numero_){
        case 1:
            ISCn0 = ISC10;
            ISCn1 = ISC11;
        break;
        case 2:
            ISCn0 = ISC20;
            ISCn1 = ISC21;
        break;
        default:
            ISCn0 = ISC00;
            ISCn1 = ISC01;
    }
    switch(mode){
        case 1:
            EICRA |=  (1 << ISCn0);
            EICRA &= ~(1 << ISCn1);
        break;
        case 2:
            EICRA &= ~(1 << ISCn0);
            EICRA |=  (1 << ISCn1);
        break;
        case 3:
            EICRA |= (1 << ISCn0);
            EICRA |= (1 << ISCn1);
        break;
        default:
            EICRA &= ~(1 << ISCn0);
            EICRA &= ~(1 << ISCn1);
    }
}

void Interruption::initialiserMasqueInterruption(){
    switch(numero_){
        case 0:
            EIMSK |= (1 << INT0);
        break;
        case 1:
            EIMSK |= (1 << INT1);
        break;
        case 2:
            EIMSK |= (1 << INT2);
        break;
    }
}

void Interruption::modifierFlagInterruption(){
    switch(numero_){
        case 0:
            EIFR |= (1 << INTF0);
        break;
        case 1:
            EIFR |= (1 << INTF1);
        break;
        case 2:
            EIFR |= (1 << INTF2);
        break;
    }
}