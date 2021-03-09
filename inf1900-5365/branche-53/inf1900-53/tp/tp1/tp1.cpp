///////////////////////////////////////////////////////////////
//Contrôle d'un DEL et Interrupteur
//Date : 19/01/2021
//Auteur : Ioana Daria Danciu et Alexandre Gélinas
//Matricules : 2081744 et 2083465
//Groupe 02
///////////////////////////////////////////////////////////////

#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>

bool Antirebond(uint8_t PIN, uint8_t value){
  if (PIN & value){
      _delay_ms(10);
      if (PIN & value)
        return true;
  }
  return false;
}

int main(){
  DDRA = 0xff; // PORT A est en mode sortie
  DDRD = 0x00; // PORT D est en mode entrée
  uint8_t compteur = 0b00;

  for(;;)  // boucle sans fin
  {
    if (Antirebond(PIND, 0x04)){
        if (PORTA == 0b00)
          compteur = (compteur % 2) + 1;
        PORTA = compteur;
    }
    else
        PORTA = 0b00;
  }
  return 0;
}
