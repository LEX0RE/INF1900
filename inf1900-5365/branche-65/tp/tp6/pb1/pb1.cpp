/**
* programme qui change la couleur de la LED selon l'intensite lumineuse
* \file		pb1.cpp
* \author   Grenier et Sigouin
* \date		23 fevrier 2020
* \travail Travail Pratique 6
* \section Section #2
* \equipe Equipe #65
* Créé le 23 fevrier 2020
* Broche entree: PORTA, pin 0
* Broche sortie: PORTB
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "can.cpp"

void DelayMsCustom(uint8_t n) {
    for(int i = 0; i < n; i++){
        _delay_ms(0.1);
    }
}

int main(){
    uint8_t pinA0 = 0;
    int lumiereRouge = 1;
    int lumiereVerte = 2;
    DDRB = 0x00;
    DDRA = 0xff;
    can convertisseur = can();
    while (1) {
        uint16_t voltage = convertisseur.lecture(pinA0);
        uint8_t voltage8b;
        voltage = voltage >> 2;
        voltage8b = voltage;
        int basseLum = 92; // selon nos experiences avec simulide, le voltage varie de 1.4V a 2.6V selon la distance de la lumiere. 
                           // Donc entre 1.4V et 1.8V on veut que la lumiere soit verte, entre 1.8 et 2.2 ambre et 2.2 a 2.6 rouge.
                           // Le voltage ne descendra jamais en dessous de 1.4 et ne montera jamais au dessus de 2.6. 92/255 est l'equivalent de 1.8V/5V
        int hauteLum = 112; // 112/255 est l'equivalent de 2.2V/5V.
        if (voltage8b < basseLum) {
            PORTB = lumiereVerte;
        }
        if (voltage8b > hauteLum) {
            PORTB = lumiereRouge;
        }
        if ((voltage8b < hauteLum) & (voltage8b > basseLum)) {
            PORTB = lumiereRouge;
            DelayMsCustom(10);
            PORTB = lumiereVerte;
            DelayMsCustom(10);
        }
    }
    convertisseur.~can();
}