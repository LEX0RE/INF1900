/**
* Programme qui controle la carte a micro-processeur selon les directives de l'exercice 2.
* \file		pb1.cpp
* \author   Grenier et Sigouin
* \date		09 février 2020
* Créé le 09 février 2020
*/

#define F_CPU 8000000
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>


enum etat {Init, Etat1, Etat2};
volatile uint8_t etatPresent = 0;


void initialisation ( void ) {
// cli est une routine qui bloque toutes les interruptions.
// Il serait bien mauvais d'être interrompu alors que
// le microcontroleur n'est pas prêt...
cli ();
// configurer et choisir les ports pour les entrées
// et les sorties. DDRx... Initialisez bien vos variables
   DDRD = 0x00;
   DDRA = 0xff;
   PORTA = 0x00;
// cette procédure ajuste le registre EIMSK
// de l’ATmega324PA pour permettre les interruptions externes
EIMSK |= (1 << INT0) ;
// il faut sensibiliser les interruptions externes aux
// changements de niveau du bouton-poussoir
// en ajustant le registre EICRA
EICRA |= (1 << ISC00);
// sei permet de recevoir à nouveau des interruptions.
sei ();
}


// placer le bon type de signal d'interruption

// à prendre en charge en argument
ISR (INT0_vect) {

// laisser un delai avant de confirmer la réponse du

// bouton-poussoir: environ 30 ms (anti-rebond)

   _delay_ms ( 30 );

// se souvenir ici si le bouton est pressé ou relâché

   if(PIND) {

// changements d'états tels que ceux de la

// semaine précédente

      for(;;){
         switch(etatPresent) {
            case Init:
               PORTA = 0x00;
               if (PIND & 0x04) {
                  while (PIND & 0x04) {
                     PORTA = 0x02;
                     _delay_ms(100);
                     etatPresent = Etat1;
                  }
               } 
               break;

            case Etat1:
               if (PIND & 0x04) {
                  while (PIND & 0x04) {
                     PORTA = 0x01;
                     _delay_ms(100);
                     etatPresent = Etat2;
                  }
               }

            case Etat2:
               if (PIND) {
                  while (PIND) {
                     PORTA = 0x00;
                     _delay_ms(100);
                     etatPresent = Init;
                  }
               }
               break;       
         }
      }
// Voir la note plus bas pour comprendre cette instruction et son rôle
      EIFR |= (1 << INTF0);
   }
}


int main(){
   initialisation();
}