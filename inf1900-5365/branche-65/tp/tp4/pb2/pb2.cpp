/**
* Programme qui controle la carte a micro-processeur selon les directives de l'exercice 2 du tp4.
* \file		pb2.cpp
* \author   Grenier et Sigouin
* \date		18 février 2020
* Créé le 16 février 2020
*/

#define F_CPU 8000000
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir;

ISR ( TIMER1_COMPA_vect ) {
minuterieExpiree = 1;
}

ISR ( PCINT2_vect ) {
boutonPoussoir = 1;
// anti-rebond
_delay_ms(30);
}

void partirMinuterie ( uint16_t duree ) {
minuterieExpiree = 0;
// mode CTC du timer 1 avec horloge divisée par 1024
// interruption après la durée spécifiée
TCNT1 = 0 ;
OCR1A = 31249;
TCCR1A |= 0 ;
TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << ICES1);
TCCR1C = 0;
TIMSK1 |= (1 << ICIE1) | (1 << OCIE1A);
}


int main() {
    DDRA = 0xff;
    DDRD = 0x00;
    _delay_ms(10000);
    PORTA = 02;
    _delay_ms(100);
    PORTA = 0;
    partirMinuterie(0);
    sei();
    do {
        // attendre qu'une des deux variables soit modifiée
        // par une ou l'autre des interruptions.
    } while ( minuterieExpiree == 0 && boutonPoussoir == 0 );

    // Une interruption s'est produite. Arrêter toute
    // forme d'interruption. Une seule réponse suffit.
    cli ();
    // Verifier la réponse
    if (boutonPoussoir == 1)
        PORTA = 01;
    else
        PORTA = 02;
}