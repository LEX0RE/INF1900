///////////////////////////////////////////////////////////////
// Capteurs et convertion analogique/numérique
// Date : 23/02/2021
// Auteur : Ioana Daria Danciu et Alexandre Gélinas
// Matricules : 2081744 et 2083465
// Groupe 02
///////////////////////////////////////////////////////////////

#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include "can.cpp"


void initialisation ( void ) {
  DDRA = 0x00;
  DDRB = 0xFF;
  DDRD = 0xFF;
}

int main(){
  initialisation();
  can convertisseur;
  unsigned char lumiere = 0;
  

  for (;;) {
    PORTB = lumiere;
    uint16_t donnee = convertisseur.lecture(PORTA);
    uint8_t donnee_8bit = (donnee >> 2);
    PORTD = donnee_8bit;
  
    if (donnee_8bit <= 0b01111001)
      lumiere = 0b01;
    else if (donnee_8bit >= 0b10110110)
      lumiere = 0b10;
    else {
      lumiere = lumiere % 2;
      lumiere += 1;
    }
  }

  //convertisseur.~can();
  return 0;
}