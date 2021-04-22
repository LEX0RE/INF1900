/**
 * Fonction interruption.cpp
 * Date : 11/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */

#include "include/interruption.hpp"

Externe::Externe(InterruptionExterne pin, ModeInterruption mode){
    desactiver();
    pin_ = pin;

    // Initialisation des interruptions
    initialiserModeDetection(mode);
    initialiser();
    activer();
}

void Externe::activer(){ sei(); }

void Externe::desactiver(){ cli(); }

void Externe::initialiserModeDetection(ModeInterruption mode){
    uint8_t ISCn0, ISCn1;

    // Regarde la broche d'interruption
    switch(pin_){
        case ID3:
            ISCn0 = ISC10;
            ISCn1 = ISC11;
        break;
        case IB3:
            ISCn0 = ISC20;
            ISCn1 = ISC21;
        break;
        case ID2: default:
            ISCn0 = ISC00;
            ISCn1 = ISC01;
    }

    // Regarde le mode d'interruption
    switch(mode){
        case ToutFront:
            EICRA &= ~(1 << ISCn0);
            EICRA |= (1 << ISCn1);
        break;
        case FrontDescendant:
            EICRA |=  (1 << ISCn0);
            EICRA &= ~(1 << ISCn1);
        break;
        case FrontMontant:
            EICRA |= (1 << ISCn0);
            EICRA |= (1 << ISCn1);
        break;
        case BasNiveau: default:
            EICRA &= ~(1 << ISCn0);
            EICRA &= ~(1 << ISCn1);
    }
}

void Externe::initialiser(){
    switch(pin_){
        case ID3:
            EIMSK |= (1 << INT1);
        break;
        case IB3:
            EIMSK |= (1 << INT2);
        break;
        case ID2: default:
            EIMSK |= (1 << INT0);
    }
}

void Externe::modifierFlag(){
    switch(pin_){
        case ID3:
            EIFR |= (1 << INTF1);
        break;
        case IB3:
            EIFR |= (1 << INTF2);
        break;
        case ID2: default:
            EIFR |= (1 << INTF0);
        break;
    }
}

uint8_t PinChange::temporaire_ = 0;

PinChange::PinChange(uint8_t numero){
    cli();
    switch(numero){
        case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
            pin_ = PB;
            PCMSKn_ = &PCMSK1;
        break;
        case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
            pin_ = PC;
            PCMSKn_ = &PCMSK2;
        break;
        case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31:
            pin_ = PD;
            PCMSKn_ = &PCMSK3;
        break;
        case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: default:
            pin_ = PA;
            PCMSKn_ = &PCMSK0;
        break;
    }

    // Permet d'assigner la bonne interruption pour le bon pin change
    switch(numero){
        case 1: 
            PCINTn_ = PCINT1; 
            break;
        case 2: 
            PCINTn_ = PCINT2; 
            break;
        case 3: 
            PCINTn_ = PCINT3; 
            break;
        case 4: 
            PCINTn_ = PCINT4; 
            break;
        case 5: 
            PCINTn_ = PCINT5; 
            break;
        case 6: 
            PCINTn_ = PCINT6; 
            break;
        case 7: 
            PCINTn_ = PCINT7; 
            break;
        case 8: 
            PCINTn_ = PCINT8; 
            break;
        case 9: 
            PCINTn_ = PCINT9; 
            break;
        case 10: 
            PCINTn_ = PCINT10; 
            break;
        case 11: 
            PCINTn_ = PCINT11; 
            break;
        case 12: 
            PCINTn_ = PCINT12; 
            break;
        case 13: 
            PCINTn_ = PCINT13; 
            break;
        case 14: 
            PCINTn_ = PCINT14; 
            break;
        case 15: 
            PCINTn_ = PCINT15; 
            break;
        case 16: 
            PCINTn_ = PCINT16; 
            break;
        case 17: 
            PCINTn_ = PCINT17; 
            break;
        case 18: 
            PCINTn_ = PCINT18; 
            break;
        case 19: 
            PCINTn_ = PCINT19; 
            break;
        case 20: 
            PCINTn_ = PCINT20; 
            break;
        case 21: 
            PCINTn_ = PCINT21; 
            break;
        case 22: 
            PCINTn_ = PCINT22; 
            break;
        case 23: 
            PCINTn_ = PCINT23; 
            break;
        case 24: 
            PCINTn_ = PCINT24; 
            break;
        case 25: 
            PCINTn_ = PCINT25; 
            break;
        case 26: 
            PCINTn_ = PCINT26; 
            break;
        case 27: 
            PCINTn_ = PCINT27; 
            break;
        case 28: 
            PCINTn_ = PCINT28; 
            break;
        case 29: 
            PCINTn_ = PCINT29; 
            break;
        case 30: 
            PCINTn_ = PCINT30; 
            break;
        case 31: 
            PCINTn_ = PCINT31; 
            break;
        case 0: default: 
            PCINTn_ = PCINT0;
            break;
    }

    // Initialise le reste
    modifierFlag();
    initialiser();
    PCIFR = 0;
    activer();
}

void PinChange::activer(){
    *PCMSKn_ |= (1 << PCINTn_);
    sei();
}

void PinChange::desactiver(){
    *PCMSKn_ &= ~(1 << PCINTn_);
    cli();
}

void PinChange::modifierFlag(){
    switch(pin_){
        case PB:
            PCIFR |= (1 << PCIF1);
        break;
        case PC:
            PCIFR |= (1 << PCIF2);
        break;
        case PD:
            PCIFR |= (1 << PCIF3);
        break;
        case PA: default:
            PCIFR |= (1 << PCIF0);
        break;
    }
}

void PinChange::initialiser(){
    switch(pin_){
        case PB:
            PCICR |= (1 << PCIE1);
        break;
        case PC:
            PCICR |= (1 << PCIE2);
        break;
        case PD:
            PCICR |= (1 << PCIE3);
        break;
        case PA: default:
            PCICR |= (1 << PCIE0);
        break;
    }
}

void PinChange::arret(){
    if (temporaire_ == 0){
        temporaire_ = PCICR;
        PCICR = 0;
    }
    cli();
}

void PinChange::reprendre(){
    PCICR = temporaire_;
    temporaire_ = 0;
    sei();
}