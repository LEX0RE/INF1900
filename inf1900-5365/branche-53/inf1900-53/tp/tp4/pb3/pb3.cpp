///////////////////////////////////////////////////////////////
//Contrôle des moteurs du robot
//Date : 02/02/2021
//Auteur : Ioana Daria Danciu et Alexandre Gélinas
//Matricules : 2081744 et 2083465
//Groupe 02
///////////////////////////////////////////////////////////////

#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>


void ajustementPWM ( unsigned char signal) {
  // mise à un des sorties OC1A et OC1B sur comparaison
  // réussie en mode PWM 8 bits, phase correcte
  // et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5
  // page 130 de la description technique du ATmega324PA)
  OCR1A = signal;
  OCR1B = signal;
}

void initialisation(){
  DDRB = 0xff;
  DDRD = 0xff;
  TCNT1 = 0;
  PORTD = 0;

  // division d'horloge par 8 - implique une frequence de PWM fixe
  TCCR1A |= (1 << COM1B1) | (1 << COM1B0) | (1 << COM1A1) | (1 << COM1A0); // Output sur OC1A et OC1B (Set Up, Clear Down)
  TCCR1A |= (1 << WGM10); // Mode 1
  TCCR1A &= ~(1 << WGM11); // Mode 1
  TCCR1B &= ~(1 << WGM12) & ~(1 << WGM13); // Mode 1
  TCCR1B &= ~(1 << CS12) & ~(1 << CS10); // Prescaler 8
  TCCR1B |= (1 << CS11); // Prescaler 8
  TCCR1C = 0;
  ajustementPWM(254);
}

int main(){
  bool direction = 1;
  initialisation();
  PORTB = direction;

  for(unsigned pourcentage = 25; pourcentage <= 100; pourcentage += 25)
  {
    _delay_ms(2000);
    ajustementPWM(255 - (pourcentage * 255 / 100));
  }
  return 0;
}
