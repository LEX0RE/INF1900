/**
 * Librairie timer.h
 * Date : 09/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */

#include <avr/io.h>
#include <util/delay.h>

#include "timer.hpp"

void delaiVariable(int delai, uniteTemps unite)
{
    while(delai--)
        if (unite == us)
            _delay_us(1);
        else
            _delay_ms(1);
}

void Timer::initialiser(unsigned int modeMinuterie, 
                   unsigned int modeComparaisonA, 
                   unsigned int modeComparaisonB, 
                   unsigned int prescaler,
                   unsigned int modeInterruption){
    modifierModeMinuterie(modeMinuterie);
    modifierModeComparaison(modeComparaisonA, 0);
    modifierModeComparaison(modeComparaisonB, 1);
    modifierPrescaler(prescaler);
    modifierInterruption(modeInterruption);
}

unsigned int Timer::obtenirPrescaler() const{
    uint8_t modePrescaler = (*TCCRnB_ & CSn0_) | (*TCCRnB_ & CSn1_) | (*TCCRnB_ & CSn2_);
    switch(modePrescaler){
        case 1:
            return 1;
        break;
        case 2:
            return 8;
        break;
        case 3:
            return 64;
        break;
        case 4:
            return 256;
        break;
        case 5:
            return 1024;
        break;
        default:
            return 0;
    }
}

void Timer::modifierTop(uint8_t top, bool x){
    if (x == 0)
        *OCRnA_ = top;
    else
        *OCRnA_ = top;
}

unsigned int Timer::obtenirPWM(bool x) const{
    uint8_t modeMinueterie = (*TCCRnA_ & WGMn0_) | (*TCCRnA_ & WGMn1_) | (*TCCRnB_ & WGMn2_);
    int prescaler = obtenirPrescaler();
    if(prescaler == 0)
        return 0;
    unsigned int freq = 0;

    switch(modeMinueterie){
        case 1: case 5:// Phase Correct PWM
            freq = (F_CPU / (prescaler * 510));
        break;
        case 3: case 7:// Fast PWM
            freq = (F_CPU / (prescaler * 256));;
        break;
        default: // Normal / CTC
            return 0;
        break;
    }

    if (x == 1) // A
        return freq / *OCRnA_;
    else // B
        return freq / *OCRnB_;
}

void Timer::modifierModeMinuterie(unsigned int modeMinuterie){
    if(modeMinuterie < 8){
        bool WGMn0 = modeMinuterie & 0x1;
        bool WGMn1 = modeMinuterie & 0x2;
        bool WGMn2 = modeMinuterie & 0x4;
        *TCCRnA_ |= (WGMn0 << WGMn0_);
        *TCCRnA_ |= (WGMn1 << WGMn1_);
        *TCCRnB_ |= (WGMn2 << WGMn2_);
    }
}

void Timer::modifierModeComparaison(unsigned int modeComparaison, bool x){
    if(modeComparaison < 4){
        if(x == 1){
            bool COMnA0 = modeComparaison & 0x1;
            bool COMnA1 = modeComparaison & 0x2;
            *TCCRnA_ |= (COMnA0 << COMnA0_);
            *TCCRnA_ |= (COMnA1 << COMnA1_);
        }
        else{
            bool COMnB0 = modeComparaison & 0x1;
            bool COMnB1 = modeComparaison & 0x2;
            *TCCRnA_ |= (COMnB0 << COMnB0_);
            *TCCRnA_ |= (COMnB1 << COMnB1_);
        }
    }
}

void Timer::modifierPrescaler(unsigned int prescaler){
    if(prescaler < 8){
        bool CSn0 = prescaler & 0x1;
        bool CSn1 = prescaler & 0x2;
        bool CSn2 = prescaler & 0x4;
        *TCCRnB_ |= (CSn0 << CSn0_);
        *TCCRnB_ |= (CSn1 << CSn1_);
        *TCCRnB_ |= (CSn2 << CSn2_);
    }
}

void Timer::modifierInterruption(unsigned int modeIterruption){
    bool OCIEnA = modeIterruption == 1;
    bool OCIEnB = modeIterruption == 2;
    bool TOIEn = modeIterruption == 3;
    *TIMSKn_ |= (OCIEnA << OCIEnA_);
    *TIMSKn_ |= (OCIEnB << OCIEnB_);
    *TIMSKn_ |= (TOIEn << TOIEn_);
}

void Timer::modifierCompteur(uint8_t compteur){ *TCNTn_ = compteur; }

Timer0::Timer0(unsigned int modeMinuterie, 
               unsigned int modeComparaisonA, 
               unsigned int modeComparaisonB, 
               unsigned int prescaler,
               unsigned int modeInterruption,
               uint8_t compteur,
               uint8_t topA,
               uint8_t topB){
    modifierRegistre();
    initialiser(modeMinuterie, modeComparaisonA, modeComparaisonB, prescaler, modeInterruption);
    modifierCompteur(compteur);
    modifierTop(topA, 0);
    modifierTop(topB, 1);
}

void Timer0::modifierRegistre(){
    WGMn0_ = WGM00; WGMn1_ = WGM01; WGMn2_ = WGM02;
    CSn0_ = CS00; CSn1_ = CS01; CSn2_ = CS02;
    COMnA0_ = COM0A0; COMnA1_ = COM0A1; COMnB0_ = COM0B0; COMnB1_ = COM0B1;
    OCIEnA_ = OCIE0A; OCIEnB_ = OCIE0B; TOIEn_ = TOIE0;
    *OCRnA_ = OCR0A; *OCRnB_ = OCR0B;
    *TCCRnA_ = TCCR0A; *TCCRnB_ = TCCR0B;
    *TIMSKn_ = TIMSK0;
    *TCNTn_ = TCNT0;
}

uint8_t Timer0::obtenirTop(bool x) const{
    if(x == 0) // A
        return OCR0A;
    else // B
        return OCR0B;
}

Timer1::Timer1(unsigned int modeMinuterie, 
               unsigned int modeComparaisonA,
               unsigned int modeComparaisonB,
               unsigned int prescaler,
               unsigned int modeInterruption,
               uint16_t compteur,
               uint16_t topA,
               uint16_t topB){
    modifierRegistre();
    initialiser(modeMinuterie, modeComparaisonA, modeComparaisonB, prescaler, modeInterruption);
    modifierCompteur(compteur);
    modifierTop(topA, 0);
    modifierTop(topB, 1);
}

void Timer1::modifierRegistre(){
    WGMn0_ = WGM10; WGMn1_ = WGM11; WGMn2_ = WGM12;
    CSn0_ = CS10; CSn1_ = CS11; CSn2_ = CS12;
    COMnA0_ = COM1A0; COMnA1_ = COM1A1; COMnB0_ = COM1B0; COMnB1_ = COM1B1;
    OCIEnA_ = OCIE1A; OCIEnB_ = OCIE1B; TOIEn_ = TOIE1;
    *OCRnA_ = OCR1A; *OCRnB_ = OCR1B;
    *TCCRnA_ = TCCR1A; *TCCRnB_ = TCCR1B;
    *TIMSKn_ = TIMSK1;
    *TCNTn_ = TCNT1;
}

unsigned int Timer1::obtenirPWM(bool x) const{
    uint8_t mode = (*TCCRnA_ & WGMn0_) | (*TCCRnA_ & WGMn1_) | (*TCCRnB_ & WGMn2_) | (*TCCRnB_ & WGM13_);
    int prescaler = obtenirPrescaler();
    switch(mode){
        case 1: case 2: case 3: case 10: case 11:// Phase Correct PWM
            if (x == 1) // A
                return (F_CPU / (2 * prescaler * *OCRnA_)) / *OCRnA_;
            else // B
                return (F_CPU / (2 * prescaler * *OCRnB_)) / *OCRnB_;
        break;

        case 5: case 6: case 7: case 14: case 15:// Fast PWM
            if (x == 1) // A
                return (F_CPU / (prescaler * (1 + *OCRnA_))) / *OCRnA_;
            else // B
                return (F_CPU / (prescaler * (1 + *OCRnB_))) / *OCRnB_;
        break;

        case 8: case 9:// Phase and Frequency Correct PWM
            if (x == 1) // A
                return (F_CPU / (2 * prescaler * *OCRnA_)) / *OCRnA_;
            else // B
                return (F_CPU / (2 * prescaler * *OCRnB_)) / *OCRnB_;
        break;

        default: // Normal / CTC
            return 0;
        break;
    }
}

uint16_t Timer1::obtenirTop(bool x) const{
    if(x == 0) // A
        return *OCRnA_;
    else // B
        return *OCRnB_;
}

void Timer1::modifierModeMinuterie(unsigned int modeMinuterie){
    if(modeMinuterie < 16){
        bool WGMn0 = modeMinuterie & 0x1;
        bool WGMn1 = modeMinuterie & 0x2;
        bool WGMn2 = modeMinuterie & 0x4;
        bool WGMn3 = modeMinuterie & 0x8;
        *TCCRnA_ |= (WGMn0 << WGMn0_);
        *TCCRnA_ |= (WGMn1 << WGMn1_);
        *TCCRnB_ |= (WGMn2 << WGMn2_);
        *TCCRnB_ |= (WGMn3 << WGM13_);
    }
}

void Timer1::modifierCompteur(uint16_t compteur){ *TCNTn_ = compteur; }

void Timer1::modifierTop(uint16_t top, bool x){
    if (x == 0)
        *OCRnA_ = top;
    else
        *OCRnA_ = top;
}


Timer2::Timer2(unsigned int modeMinuterie, 
               unsigned int modeComparaisonA,
               unsigned int modeComparaisonB, 
               unsigned int prescaler, 
               unsigned int modeInterruption, 
               uint8_t compteur, 
               uint8_t topA, 
               uint8_t topB){
    modifierRegistre();
    initialiser(modeMinuterie, modeComparaisonA, modeComparaisonB, prescaler, modeInterruption);
    modifierCompteur(compteur);
    modifierTop(topA, 0);
    modifierTop(topB, 1);
} 

void Timer2::modifierRegistre(){
    WGMn0_ = WGM20; WGMn1_ = WGM21; WGMn2_ = WGM22;
    CSn0_ = CS20; CSn1_ = CS21; CSn2_ = CS22;
    COMnA0_ = COM2A0; COMnA1_ = COM2A1; COMnB0_ = COM2B0; COMnB1_ = COM2B1;
    OCIEnA_ = OCIE2A; OCIEnB_ = OCIE2B; TOIEn_ = TOIE2;
    *OCRnA_ = OCR2A; *OCRnB_ = OCR2B;
    *TCCRnA_ = TCCR2A; *TCCRnB_ = TCCR2B;
    *TIMSKn_ = TIMSK2;
    *TCNTn_ = TCNT2;
}

unsigned int Timer2::obtenirPrescaler() const{
    uint8_t modePrescaler = (*TCCRnB_ & CSn0_) | (*TCCRnB_ & CSn1_) | (*TCCRnB_ & CSn2_);
    switch(modePrescaler){
        case 1:
            return 1;
        break;
        case 2:
            return 8;
        break;
        case 3:
            return 32;
        break;
        case 4:
            return 64;
        break;
        case 5:
            return 128;
        break;
        case 6:
            return 256;
        break;
        case 7:
            return 1024;
        break;
        default:
            return 0;
    }
}

uint8_t Timer2::obtenirTop(bool x) const{
    if(x == 0) // A
        return *OCRnA_;
    else // B
        return *OCRnA_;
}
