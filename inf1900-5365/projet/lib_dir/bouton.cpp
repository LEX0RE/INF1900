/**
 * @brief Définition des fonction pour le fichier bouton.hpp
 * @file bouton.cpp
 * @date 21/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#include <avr/io.h>
#include <util/delay.h>

#include "include/bouton.hpp"

bool antirebond(Port pin, uint8_t position, bool inverse){
  if (inverse){
    if (~(*obtenirPort(pin)) & position){
        _delay_ms(DELAI_ANTI_REBOND);
        
        if (~(*obtenirPort(pin)) & position)
          return true;
    }
    return false;
  }
  else{
    if (*obtenirPort(pin) & position){
        _delay_ms(DELAI_ANTI_REBOND);
        
        if (*obtenirPort(pin) & position)
          return true;
    }
    return false;
  }
}

void relachement(Port pin, uint8_t position){
  while (*obtenirPort(pin) & position){}
}
