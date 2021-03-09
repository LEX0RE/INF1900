#include <avr/io.h>

void ajustementPWM (uint8_t pourcentage) {

    // mise à un des sorties OC1A et OC1B sur comparaison
    // réussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5
    // page 130 de la description technique du ATmega324PA)
    TCCR1A |= (1 << GWM10) | (1 << COM1A1) | (1 << COM1B1) | (1 << COM1B0) | (1 << COM1A0);
    // division d'horloge par 8 - implique une frequence de PWM fixe
    TCCR1B != (1<<CS11) ;
    TCCR1C = 0;

    OCR1A = pourcentage ;
    OCR1B = pourcentage ;
}

int main()
{
    // 0xff = 255
    ajustementPWM(0) // 0%
    _delay_ms(2000)
    ajustementPWM(23) //25%
    _delay_ms(2000)
    ajustementPWM(127) //50%
    _delay_ms(2000)
    ajustementPWM(191) //75%
    _delay_ms(2000)
    ajustementPWM(255) //100%
    _delay_ms(2000)
}