///////////////////////////////////////////////////////////////
//Machine à états de Moore contrôlant l'allumage d'une LED
//Date : 26/01/2021
//Auteur : Ioana Daria Danciu et Alexandre Gélinas
//Matricules : 2081744 et 2083465
//Groupe 02
///////////////////////////////////////////////////////////////

/*

Dans le problème 2, le DEL est initialement éteint (état INIT) et il y 
demeure tant et aussi longtemps que le bouton D2 n’est pas appuyé. 
Donc, le DEL reste éteint si l’on appuie sur D3, mais devient rouge 
(état ROUGE) lorsque l’on appuie sur D2. Il peut alors devenir vert 
(état VERT) quand on appuie encore une fois sur D2, ou passer à l’état 
ÉTEINT si l’on appuie sur D3. Si le DEL est vert, il passe à l’état 
ÉTEINT aussitôt que l’on appuie sur l’un des deux boutons. Si le DEL 
est éteint, il le demeure quand l’on appuie sur D2, mais passe au vert 
lorsqu’on appuie sur D3.

*/

////////////////////////////////////////////////////////////////
//État présent   Entrée D2   Entrée D3   État suivant     Sortie D
//INIT              0           1             INIT          noir
//INIT              1           0             ROUGE         noir
//ROUGE             1           0             VERT          rouge
//ROUGE             0           1             ETEINT        rouge
//ETEINT            1           0             ETEINT        noir
//ETEINT            0           1             VERT          noir
//VERT              1           X             INIT          vert
//VERT              X           1             INIT          vert
///////////////////////////////////////////////////////////////

#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>

bool Relachement(volatile const uint8_t& PIN, const uint8_t& value){
  while (PIN & value){}
  return true;
}

bool Antirebond(volatile const uint8_t& PIN, const uint8_t& value){
  if (PIN & value){
      _delay_ms(10);
      if (PIN & value)
        return Relachement(PIN, value);
  }
  return false;
}

int main(){
  DDRA = 0xff; // PORT A est en mode sortie
  DDRD = 0x00; // PORT D est en mode entrée
  enum Etat {init, rouge, vert, eteint};
  Etat present = init;

  for(;;)  // boucle sans fin
  {
    switch(present){
      case init:
        PORTA = 0b00;
        if (Antirebond(PIND, 0x04))
          present = rouge;
      break;
      case rouge:
        PORTA = 0b10;
        if (Antirebond(PIND, 0x04))
          present = vert;
        if (Antirebond(PIND, 0x08))
          present = eteint;
      break;
      case vert:
        PORTA = 0b01;
        if (Antirebond(PIND, 0x04))
          present = init;
        if (Antirebond(PIND, 0x08))
          present = init;
      break;
      case eteint:
        PORTA = 0b00;
        if (Antirebond(PIND, 0x08))
          present = vert;
      break;
    }
  }
  return 0;
}