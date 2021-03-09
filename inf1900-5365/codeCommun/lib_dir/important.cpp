/*
Librairie important.h
Date : 09/03/2021
Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
Matricules : 2081744, 2083465, 2087199 et 2087987
Groupe 02
*/

#include "important.h"
#include <avr/io.h>
#include <util/delay.h>

void changerBit(volatile uint8_t* pin, uint8_t position, bool value){
    if (value == true)
        *pin |= position;
    else
        *pin &= ~position;
}

bool antirebond(volatile const uint8_t& pin, uint8_t position){
  if (pin & position){
      _delay_ms(10);
      if (pin & position)
        return true;
  }
  return false;
}

bool relachement(volatile const uint8_t& pin, uint8_t position){
  while (pin & position){}
  return true;
}

void delaiVariable(int delai) {
    while(delai--)
        _delay_us(1);
}

#endif //IMPORTANT_CPP