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

void Delay(int delai) {
    while(delai--)
        _delay_us(1);
}

int main(){
  DDRB = 0xff; // PORT A est en mode sortie
  long int b = 8844, a = 0, wait = 0, max = 121; // 16 pour 40 Hz
  bool direction = 0; 

  for(;;)  // boucle sans fin
  {
    Delay(a);
    PORTB = 0b00 + (direction * 2);
    Delay(b - a);
    PORTB = 0b01 + (direction * 2);
    if (a <= b){
      if (wait++ == (max - 1)){
        if (a == b){
          max = 816;
          b = 1288;
          a = 0;
        }
        else
          a += int(b / 4);
      }
      wait %= max;
    }
  }
  return 0;
}
