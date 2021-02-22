///////////////////////////////////////////////////////////////
// Contrôle d'une DEL par interruption
// Date : 09/02/2021
// Auteur : Ioana Daria Danciu et Alexandre Gélinas
// Matricules : 2081744 et 2083465
// Groupe 02
///////////////////////////////////////////////////////////////

#define F_CPU 8000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


enum Etat {init, rouge, vert};
volatile Etat present = init; // selon le nom de votre variable

// placer le bon type de signal d'interruption
// à prendre en charge en argument
ISR ( INT0_vect ) {
  // laisser un delai avant de confirmer la réponse du
  // bouton-poussoir: environ 30 ms (anti-rebond)
  _delay_ms ( 30 );
  // se souvenir ici si le bouton est pressé ou relâché
  if (!(PIND & 0x04))
    return;

  // changements d'états tels que ceux de la
  // semaine précédente
  switch(present){
    case init:
      present = rouge;
    break;
    case rouge:
      present = vert;
    break;
    case vert:
      present = init;
    break;
  }
  // Voir la note plus bas pour comprendre cette instruction et son rôle
  EIFR |= (1 << INTF0) ;
}

void initialisation ( void ) {
  // cli est une routine qui bloque toutes les interruptions.
  // Il serait bien mauvais d'être interrompu alors que
  // le microcontroleur n'est pas prêt...
  cli ();

  // configurer et choisir les ports pour les entrées
  // et les sorties. DDRx... Initialisez bien vos variables
  DDRA = 0xff; // PORT A est en mode sortie
  DDRD = 0x00; // PORT D est en mode entrée

  // cette procédure ajuste le registre EIMSK
  // de l’ATmega324PA pour permettre les interruptions externes
  EIMSK |= (1 << INT0) ;

  // il faut sensibiliser les interruptions externes aux
  // changements de niveau du bouton-poussoir
  // en ajustant le registre EICRA
  EICRA |= (1 << ISC00);
  EICRA &= ~(1 << ISC01);

  // sei permet de recevoir à nouveau des interruptions.
  sei ();
}

int main(){
  initialisation();

  for(;;)  // boucle sans fin
  {
    switch(present){
      case init:
        PORTA = 0b00;
      break;
      case rouge:
        PORTA = 0b10;
      break;
      case vert:
        PORTA = 0b01;
      break;
    }
  }
  return 0;
}