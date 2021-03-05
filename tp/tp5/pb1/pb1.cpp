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
#include <string.h>
//fonction à faire

int main(){
  DDRB = 0xff;
  PORTB = 0b0;

  uint8_t* adresse = 0x00;
  char MessageRecu [60] = {};
  char MessageEnvoye [] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";

  for (unsigned i = 0 ; MessageEnvoye[i] != '\0' ; i++) 
    eeprom_write_byte(adresse++, MessageEnvoye[i]);

  //eeprom_update_block((const void*) &MessageEnvoye, (void*) 0, sizeof(MessageEnvoye));
  //eeprom_read_block((void*) & MessageRecu, (const void*) 0, sizeof(MessageEnvoye));
     
  adresse = 0;  
  for (unsigned i = 0 ; MessageEnvoye[i] != '\0' ; i++)
    MessageRecu[i] = eeprom_read_byte(adresse++);
  
  if ((strcmp((char*) MessageRecu, (char*) MessageEnvoye)) == 0)
    PORTB = 0b01;  
  else
    PORTB = 0b10;
  
  return 0;
}