///////////////////////////////////////////////////////////////
//Machine à états de Moore contrôlant l'allumage d'une LED
//Date : 26/01/2021
//Auteur : Ioana Daria Danciu et Alexandre Gélinas
//Matricules : 2081744 et 2083465
//Groupe 02
///////////////////////////////////////////////////////////////

/*

Ce circuit est composé d’un DEL bicolore ainsi que de deux boutons-poussoirs : D2 et D3. 
Dans chacun des problèmes, le DEL doit être d’une certaine couleur selon le bouton qui est appuyé. 
Ainsi, dans le problème 1, le DEL est initialement éteint (état INIT), puis il passe au vert 
(état VERT1) lorsqu’on appuie sur D2, peu importe la valeur de D3. Ensuite, si l’on appuie trois 
fois sur D3, le DEL devient rouge. Il passe alors par trois états : VERT2, VERT3 et ROUGE. 
Lorsque atteint, ce dernier état ne reste affiché qu’une seconde avant de retourner à l’état INIT. 

*/

////////////////////////////////////////////////////////////////
//État présent   Entrée D2   Entrée D3   État suivant     Sortie D
//INIT              0           X             INIT          noir
//INIT              1           X             VERT1         noir
//VERT1             X           0             VERT1         vert
//VERT1             X           1             VERT2         vert
//VERT2             X           0             VERT2         vert
//VERT2             X           1             VERT3         vert
//VERT3             X           0             VERT3         vert
//VERT3             X           1             ROUGE         vert
//ROUGE             X           X             INIT          rouge (pendant de 1 seconde)
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
  enum Etat {init, vert, rouge};
  Etat present = init;
  int count = 0;

  for(;;)  // boucle sans fin
  {
    switch(present){
      case init:
        if (Antirebond(PIND, 0x04)){
          present = vert;
          PORTA = 0b01;
        }
      break;
      case vert:
        if (Antirebond(PIND, 0x08))
          count++;
        if (count == 3){
          present = rouge;
          count = 0;
        }
      break;
      case rouge:
        PORTA = 0b10;
        _delay_ms(1000);
        PORTA = 0b00;
        present = init;
      break;
    }
  }
  return 0;
}