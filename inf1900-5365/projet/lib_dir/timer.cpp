/**
 * @brief Fonction pour les Timers
 * @file timer.cpp
 * @date 21/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h> 

#include "include/timer.hpp"

void delaiVariable(unsigned int delai, TypeTemps unite) {
    while(delai--)
        if (unite == MS)
            _delay_ms(1);
        else
            _delay_us(1);
}

void Timer::remiseAZero(){
    modifierCompteur(0x00);
}

uint8_t Timer::obtenirTimer() const{
    return *TCNTn_;
}

void Timer::initialiser(ModeComparaison modeComparaison, 
                        Prescaler prescaler,
                        MatchInterruption modeInterruption){
    int8_t valeurMaximal = 0xFF;
    modifierModeComparaison(modeComparaison, TCA);
    modifierModeComparaison(modeComparaison, TCB);
    modifierInterruption(modeInterruption);
    alimentation_ = true;
    modifierPrescaler(prescaler);
    modifierCompteur(0);
    modifierTop(valeurMaximal, TCA);
    modifierTop(valeurMaximal, TCB);
}

void Timer::forcerComparaison(RegistreComparaison registre){
    if(registre == TCA)
        *TCCRnC_ |= (1 << FOCnA_);
    else
        *TCCRnC_ |= (1 << FOCnB_);
}

uint8_t Timer::obtenirTop(RegistreComparaison registre) const{
    if(registre == TCA)
        return *OCRnA_;
    else
        return *OCRnB_;
}

void Timer::arreter(){
    uint8_t modeActuel = (*TCCRnB_ & CSn0_) | (*TCCRnB_ & CSn1_) | (*TCCRnB_ & CSn2_);

    if(modeActuel != AUCUN){
        // Changement du prescaler
        prescaler_ = Prescaler(modeActuel);
        modifierPrescaler(AUCUN);

        // Reset des ports
        *PORT_ &= ~(1 << OCnA_);
        *PORT_ &= ~(1 << OCnB_);

        // Sauvegarde de l'état
        alimentation_ = false;
    }
}

void Timer::demarrer(){
    uint8_t modeActuel = (*TCCRnB_ & CSn0_) | (*TCCRnB_ & CSn1_) | (*TCCRnB_ & CSn2_);

    if(modeActuel == AUCUN){

        // Changement du prescaler
        modifierPrescaler(prescaler_);

        // Sauvegarde de l'état
        alimentation_ = true;
    }
}

bool Timer::alimentation() const { return alimentation_; }

void Timer::modifierTop(uint8_t top, RegistreComparaison registre){
    if (registre == TCA)
        *OCRnA_ = top;
    else
        *OCRnB_ = top;
}

void Timer::modifierModeComparaison(ModeComparaison modeComparaison, RegistreComparaison registre){
    uint8_t bitCOMnX0 = 0x1, bitCOMnX1 = 0x2;

    // Modification pour le A
    if(registre == TCA){
        // Transformation en bit pour le sauvegarder
        bool COMnA0 = modeComparaison & bitCOMnX0;
        bool COMnA1 = modeComparaison & bitCOMnX1;

        // Enregistrement du mode
        *TCCRnA_ |= (COMnA0 << COMnA0_);
        *TCCRnA_ |= (COMnA1 << COMnA1_);
        *TCCRnA_ &= ~((!COMnA0) << COMnA0_);
        *TCCRnA_ &= ~((!COMnA1) << COMnA1_);
    }
    else{ // Modification pour le B
        // Transformation en bit pour le sauvegarder
        bool COMnB0 = modeComparaison & bitCOMnX0;
        bool COMnB1 = modeComparaison & bitCOMnX1;

        // Enregistrement du mode
        *TCCRnA_ |= (COMnB0 << COMnB0_);
        *TCCRnA_ |= (COMnB1 << COMnB1_);
        *TCCRnA_ &= ~((!COMnB0) << COMnB0_);
        *TCCRnA_ &= ~((!COMnB1) << COMnB1_);
    }
}

void Timer::modifierPrescaler(Prescaler prescaler){
    // Transformation en bit pour le sauvegarder
    bool CSn0 = prescaler & 0x1;
    bool CSn1 = prescaler & 0x2;
    bool CSn2 = prescaler & 0x4;

    // Enregistrement du mode
    *TCCRnB_ |= (CSn0 << CSn0_);
    *TCCRnB_ |= (CSn1 << CSn1_);
    *TCCRnB_ |= (CSn2 << CSn2_);
    *TCCRnB_ &= ~((!CSn0) << CSn0_);
    *TCCRnB_ &= ~((!CSn1) << CSn1_);
    *TCCRnB_ &= ~((!CSn2) << CSn2_);
}

void Timer::modifierInterruption(MatchInterruption modeIterruption){
    // Transformation en bit pour le sauvegarder
    bool OCIEnA = modeIterruption == 1;
    bool OCIEnB = modeIterruption == 2;
    bool TOIEn = modeIterruption == 3;

    // Enregistrement du mode
    *TIMSKn_ |= (OCIEnA << OCIEnA_);
    *TIMSKn_ |= (OCIEnB << OCIEnB_);
    *TIMSKn_ |= (TOIEn << TOIEn_);
    *TIMSKn_ &= ~((!OCIEnA) << OCIEnA_);
    *TIMSKn_ &= ~((!OCIEnB) << OCIEnB_);
    *TIMSKn_ &= ~((!TOIEn) << TOIEn_);
}

void Timer::modifierCompteur(uint8_t compteur){ *TCNTn_ = compteur; }

Timer0* Timer0::timer_{nullptr};

Timer0::~Timer0(){
    free(timer_);
}

Timer0* Timer0::obtenirInstance(ModeTimer8Bit modeMinuterie, ModeComparaison modeComparaison, 
                                Prescaler prescaler, MatchInterruption modeInterruption){
    if(timer_ == nullptr){
        timer_ = (Timer0*)malloc(sizeof(Timer0));
        timer_->Timer0::modifierRegistre();
        timer_->Timer0::modifierModeMinuterie(modeMinuterie);
        timer_->Timer0::initialiser(modeComparaison, prescaler, modeInterruption);
    }
    return timer_;
}

void Timer0::modifierRegistre(){
    // Affectation des bits pour sauvegarder l'emplacement
    WGMn0_ = WGM00; WGMn1_ = WGM01; WGMn2_ = WGM02;
    CSn0_ = CS00; CSn1_ = CS01; CSn2_ = CS02;
    COMnA0_ = COM0A0; COMnA1_ = COM0A1; COMnB0_ = COM0B0; COMnB1_ = COM0B1;
    OCIEnA_ = OCIE0A; OCIEnB_ = OCIE0B; TOIEn_ = TOIE0;
    FOCnA_ = FOC0A; FOCnB_ = FOC0B;

    // Affectation des registres pour pouvoir les utiliser plus tard
    OCRnA_ = &OCR0A; OCRnB_ = &OCR0B;
    TCCRnA_ = &TCCR0A; TCCRnB_ = &TCCR0B; TCCRnC_ = &TCCR0B;
    TIMSKn_ = &TIMSK0;
    TCNTn_ = &TCNT0;
    OCnA_ = OC0A_BIT; OCnB_ = OC0B_BIT;
    PORT_ = &OC0A_PORT;
}

uint16_t Timer0::obtenirPrescaler() const{
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

void Timer0::modifierModeMinuterie(ModeTimer8Bit modeMinuterie){
    // Transformation en bit pour le sauvegarder
    bool WGMn0 = modeMinuterie & 0x1;
    bool WGMn1 = modeMinuterie & 0x2;
    bool WGMn2 = modeMinuterie & 0x4;
    
    // Enregistrement du mode
    *TCCRnA_ |= (WGMn0 << WGMn0_);
    *TCCRnA_ |= (WGMn1 << WGMn1_);
    *TCCRnB_ |= (WGMn2 << WGMn2_);
    *TCCRnA_ &= ~((!WGMn0) << WGMn0_);
    *TCCRnA_ &= ~((!WGMn1) << WGMn1_);
    *TCCRnB_ &= ~((!WGMn2) << WGMn2_);
}

void Timer1::remiseAZero(){
    modifierCompteur(0x0000);
}

Timer1* Timer1::timer_{nullptr};

uint16_t Timer1::obtenirTimer() const{
    return *TCNTn_;
}

Timer1::~Timer1(){
    free(timer_);
}

Timer1* Timer1::obtenirInstance(ModeTimer16Bit modeMinuterie, ModeComparaison modeComparaison, 
                                Prescaler prescaler, MatchInterruption modeInterruption){
    if(timer_ == nullptr){
        int16_t valeurMaximale = 0xFFFF;
        timer_ = (Timer1*)malloc(sizeof(Timer1));
        timer_->Timer1::modifierRegistre();
        timer_->Timer1::modifierModeMinuterie(modeMinuterie);
        timer_->Timer1::initialiser(modeComparaison, prescaler, modeInterruption);
        timer_->Timer1::modifierTop(valeurMaximale, TCA);
        timer_->Timer1::modifierTop(valeurMaximale, TCB);
    }
    return timer_;
}

void Timer1::modifierRegistre(){
    // Affectation des bits pour sauvegarder l'emplacement
    WGMn0_ = WGM10; WGMn1_ = WGM11; WGMn2_ = WGM12;
    CSn0_ = CS10; CSn1_ = CS11; CSn2_ = CS12;
    COMnA0_ = COM1A0; COMnA1_ = COM1A1; COMnB0_ = COM1B0; COMnB1_ = COM1B1;
    OCIEnA_ = OCIE1A; OCIEnB_ = OCIE1B; TOIEn_ = TOIE1;
    FOCnA_ = FOC1A; FOCnB_ = FOC1B;

    // Affectation des registres pour pouvoir les utiliser plus tard
    OCRnA_ = &OCR1A; OCRnB_ = &OCR1B;
    TCCRnA_ = &TCCR1A; TCCRnB_ = &TCCR1B; TCCRnC_ = &TCCR1C;
    TIMSKn_ = &TIMSK1;
    TCNTn_ = &TCNT1;
    OCnA_ = OC1A_BIT; OCnB_ = OC1B_BIT;
    PORT_ = &OC1A_PORT;
}

void Timer1::modifierModeMinuterie(ModeTimer16Bit modeMinuterie){
    // Transformation en bit pour le sauvegarder
    bool WGMn0 = modeMinuterie & 0x1;
    bool WGMn1 = modeMinuterie & 0x2;
    bool WGMn2 = modeMinuterie & 0x4;
    bool WGMn3 = modeMinuterie & 0x8;

    // Enregistrement du mode
    *TCCRnA_ |= (WGMn0 << WGMn0_);
    *TCCRnA_ |= (WGMn1 << WGMn1_);
    *TCCRnB_ |= (WGMn2 << WGMn2_);
    *TCCRnB_ |= (WGMn3 << WGM13_);
    *TCCRnA_ &= ~((!WGMn0) << WGMn0_);
    *TCCRnA_ &= ~((!WGMn1) << WGMn1_);
    *TCCRnB_ &= ~((!WGMn2) << WGMn2_);
    *TCCRnB_ &= ~((!WGMn3) << WGM13_);
}

void Timer1::modifierCompteur(uint16_t compteur){ 
    *TCNTn_ = compteur; 
}

uint16_t Timer1::obtenirTop(RegistreComparaison registre) const{
    if(registre == TCA)
        return *OCRnA_;
    else // B
        return *OCRnB_;
}

void Timer1::modifierTop(uint16_t top, RegistreComparaison registre){
    if (registre == TCA)
        *OCRnA_ = top;
    else
        *OCRnB_ = top;
}

uint16_t Timer1::obtenirPrescaler() const{
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

Timer2* Timer2::timer_{nullptr};

Timer2::~Timer2(){
    free(timer_);
}

Timer2* Timer2::obtenirInstance(ModeTimer8Bit modeMinuterie, ModeComparaison modeComparaison,
                                Prescaler prescaler, MatchInterruption modeInterruption){
    if(timer_ == nullptr){
        timer_ = (Timer2*)malloc(sizeof(Timer2));
        timer_->Timer2::modifierRegistre();
        timer_->Timer2::modifierModeMinuterie(modeMinuterie);
        timer_->Timer2::initialiser(modeComparaison, prescaler, modeInterruption);
    }
    return timer_;
} 

void Timer2::modifierRegistre(){
    // Affectation des bits pour sauvegarder l'emplacement
    WGMn0_ = WGM20; WGMn1_ = WGM21; WGMn2_ = WGM22;
    CSn0_ = CS20; CSn1_ = CS21; CSn2_ = CS22;
    COMnA0_ = COM2A0; COMnA1_ = COM2A1; COMnB0_ = COM2B0; COMnB1_ = COM2B1;
    OCIEnA_ = OCIE2A; OCIEnB_ = OCIE2B; TOIEn_ = TOIE2;
    FOCnA_ = FOC2A; FOCnB_ = FOC2B;
    
    // Affectation des registres pour pouvoir les utiliser plus tard
    OCRnA_ = &OCR2A; OCRnB_ = &OCR2B;
    TCCRnA_ = &TCCR2A; TCCRnB_ = &TCCR2B; TCCRnC_ = &TCCR2B;
    TIMSKn_ = &TIMSK2;
    TCNTn_ = &TCNT2;
    OCnA_ = OC2A_BIT; OCnB_ = OC2B_BIT;
    PORT_ = &OC2A_PORT;
}

uint16_t Timer2::obtenirPrescaler() const{
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

void Timer2::modifierModeMinuterie(ModeTimer8Bit modeMinuterie){
    // Transformation en bit pour le sauvegarder
    bool WGMn0 = modeMinuterie & 0x1;
    bool WGMn1 = modeMinuterie & 0x2;
    bool WGMn2 = modeMinuterie & 0x4;

    // Enregistrement du mode
    *TCCRnA_ |= (WGMn0 << WGMn0_);
    *TCCRnA_ |= (WGMn1 << WGMn1_);
    *TCCRnB_ |= (WGMn2 << WGMn2_);
    *TCCRnA_ &= ~((!WGMn0) << WGMn0_);
    *TCCRnA_ &= ~((!WGMn1) << WGMn1_);
    *TCCRnB_ &= ~((!WGMn2) << WGMn2_);
}
