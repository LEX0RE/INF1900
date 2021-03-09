///////////////////////////////////////////////////////////////
// Jeu de réflexe avec l'utilisation d'une minuterie
// Date : 09/02/2021
// Auteur : Ioana Daria Danciu et Alexandre Gélinas
// Matricules : 2081744 et 2083465
// Groupe 02
///////////////////////////////////////////////////////////////

#define F_CPU 8000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir;

ISR ( TIMER1_COMPA_vect ) {
  minuterieExpiree = 1;
}

ISR ( INT0_vect ) {
  boutonPoussoir = 1;
  // anti-rebond
  _delay_ms ( 30 );
}

void partirMinuterie ( uint16_t duree ) {
  minuterieExpiree = 0;
  // mode CTC du timer 1 avec horloge divisée par 1024
  // interruption après la durée spécifiée
  TCNT1 = 0 ;
  OCR1A = duree;

  TCCR1A = TCCR1A & ~(1 << COM1A0) & ~(1 << COM1A1); // Pour ISR
  TCCR1A = TCCR1A & ~(1 << WGM11) & ~(1 << WGM10); // Set à CTC

  TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler 1024
  TCCR1B &= ~(1 << CS11); // Prescaler 1024
  TCCR1B |= (1 << WGM12); // Set à CTC
  TCCR1B &= ~(1 << WGM13); // Set à CTC

  TCCR1C = 0;
  TIMSK1 |= (1 << OCIE1A);
}

void initialisation ( void ) {
  cli ();
  DDRA = 0xff; // PORT A est en mode sortie
  DDRD = 0x00; // PORT D est en mode entrée

  EIMSK |= (1 << INT0) ;
  EICRA |= (1 << ISC00);
  EICRA = EICRA & ~(1 << ISC01);

  boutonPoussoir = 0;

  sei ();
}

int main(){
  initialisation();
  cli();

  PORTA = 0b00;
  _delay_ms(10000);
  PORTA = 0b10;
  _delay_ms(100);
  PORTA = 0b00;
  
  partirMinuterie(7812);
  sei();
  // attendre qu'une des deux variables soit modifiée
  // par une ou l'autre des interruptions.
  while (minuterieExpiree == 0 && boutonPoussoir == 0 ){}

  // Une interruption s'est produite. Arrêter toute
  // forme d'interruption. Une seule réponse suffit.
  
  // Verifier la réponse
  if (boutonPoussoir == 1)
    PORTA = 0b01;
  else
    PORTA = 0b10;
  return 0;
}