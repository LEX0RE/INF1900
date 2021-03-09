/**
* Programme qui controle la carte a micro-processeur selon les directives de l'exercice 2.
* \file		pb2.cpp
* \author   Grenier et Sigouin
* \date		02 février 2020
* Créé le 26 janvier 2020
*/
#define F_CPU 8000000
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>

int main()
{
   DDRD = 0x00;
   DDRA = 0xff;
   PORTA = 0x00;

   enum etat {Init, Etat1, Etat2, Etat3};
   etat etatPresent = Init;

   for(;;) {  // boucle sans fin
      /*
      Tableau d'etat
      ----------------------------------------------------
      Etat Present | D2 | D3 | Etat Suivant | Port A
      ----------------------------------------------------
      Init         | X  | 1  | Init         | 0 (eteint)
      Init         | 1  | X  | Etat 1       | 2 (rouge)
      Etat 1       | X  | 1  | Etat 2       | 0 (eteint)
      Etat 1       | 1  | X  | Etat 3       | 1 (vert)
      Etat 2       | X  | 1  | Etat 3       | 1 (vert)
      Etat 3       | X  | X  | Init         | 0 (eteint)
      */

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
                  etatPresent = Etat3;
               }
            }
            if (PIND & 0x08) {
               while (PIND & 0x08) {
                  PORTA = 0x00;
                  _delay_ms(100);
                  etatPresent = Etat2;
               }
            }
            break;

         case Etat2:
            if (PIND & 0x08) {
               while (PIND & 0x08) {
                  PORTA = 0x01;
                  _delay_ms(100);
                  etatPresent = Etat3;
               }
            }
            break;

         case Etat3:
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
   return 0; 
}

