///////////////////////////////////////////////////////////////
//DEL qui s'éteint en environ 3 secondes
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
  DDRA = 0xff; // PORT A est en mode sortie
  int b = 516, a = b, wait = 0, max = 5;
  bool color = 0;

  for(;;)  // boucle sans fin
  {
    Delay(a);
    PORTA = 0b00 << color;
    Delay(b - a);
    PORTA = 0b01 << color;
    if (a > 0){
      if (wait == (max - 1))
        a -= 1;
      wait += 1;
      wait %= max;
    }
  }
  return 0;
}
