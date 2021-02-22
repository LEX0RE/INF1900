///////////////////////////////////////////////////////////////
// Lecture et écriture en mémoire
// Date : 18/02/2021
// Auteur : Ioana Daria Danciu et Alexandre Gélinas
// Matricules : 2081744 et 2083465
// Groupe 02
///////////////////////////////////////////////////////////////

#define F_CPU 8000000L

#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>

//fonction à faire

int main(){
  DDRB = 0xff;
  PINB = 0b0;

  uint8_t* adresse = 0x00;
  uint8_t MessageRecu;
  uint8_t MessageEnvoye = '*';
  eeprom_write_byte(adresse, MessageEnvoye);
  MessageRecu = eeprom_read_byte(adresse);
  
  if (MessageEnvoye == MessageRecu)
    PINB = 0b1;  return 0;
}