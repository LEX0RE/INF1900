/**
* Programme qui controle la carte a micro-processeur selon les directives de l'exercice 1 du tp3.
* \file		pb1.cpp
* \author   Grenier et Sigouin
* \date		4 fevrier 2020
* Créé le 2 fevrier 2020
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

void WpgCustom(const int tempsAllume, const int tempsEteint, int couleur, int iterations) {
    for (int i = 0; i < iterations; i++) {
            PORTA = couleur;
            DelayMsCustom(tempsAllume);
            PORTA = 00;
            DelayMsCustom(tempsEteint);
        }
}


int main() {
    DDRA = 0xff;
    while (1){
        WpgCustom(10, 0, 01, 300);
        WpgCustom(9, 1, 01, 300);
        WpgCustom(8, 2, 01, 300);
        WpgCustom(7, 3, 01, 300);
        WpgCustom(6, 4, 01, 300);
        WpgCustom(5, 5, 01, 300);
        WpgCustom(4, 6, 01, 300);
        WpgCustom(3, 7, 01, 300);
        WpgCustom(2, 8, 01, 300);
        WpgCustom(1, 9, 01, 300);
        WpgCustom(0, 10, 01, 1000);
        WpgCustom(10, 0, 02, 300);
        WpgCustom(9, 1, 02, 300);
        WpgCustom(8, 2, 02, 300);
        WpgCustom(7, 3, 02, 300);
        WpgCustom(6, 4, 02, 300);
        WpgCustom(5, 5, 02, 300);
        WpgCustom(4, 6, 02, 300);
        WpgCustom(3, 7, 02, 300);
        WpgCustom(2, 8, 02, 300);
        WpgCustom(1, 9, 02, 300);
        WpgCustom(0, 10, 02, 1000);
    }
}