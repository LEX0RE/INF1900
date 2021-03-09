/**
* Programme qui controle la carte a micro-processeur selon les directives de l'exercice 2 du tp3.
* \file		pb2.cpp
* \author   Grenier et Sigouin
* \date		04 février 2020
* Créé le 02 février 2020
*/
#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



void DelayMsCustom(int n) {
    for(int i = 0; i < n; i++){
        _delay_ms(0.1);
    }
}

void WpgCustom(const int tempsAllume, const int tempsEteint, int direction, int iterations) {
    for (int i = 0; i < iterations; i++) {
            PORTA = direction;
            DelayMsCustom(tempsAllume);
            PORTA = 00;
            DelayMsCustom(tempsEteint);
        }
}


int main() {
    DDRA = 0xff;
    while (1){
        WpgCustom(0, 167, 03, 120);
        WpgCustom(42, 125, 03, 120);
        WpgCustom(84, 83, 03, 120);
        WpgCustom(126, 41, 03, 120);
        WpgCustom(167, 0, 03, 120);

        WpgCustom(0, 25, 03, 800);
        WpgCustom(6, 19, 03, 800);
        WpgCustom(12, 13, 03, 800);
        WpgCustom(18, 7, 03, 800);
        WpgCustom(25, 0, 03, 800);
    }
}