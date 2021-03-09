/**
* Programme qui controle la carte a micro-processeur selon les directives de l'exercice 1.
* \file		pb1.cpp
* \author   Grenier et Sigouin
* \date		28 janvier 2020
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
    PORTA = 0; 

    enum etat {Init, Etat1, Etat2, Etat3, Fin};
    etat etatPresent = Init;

    for(;;) {
        /*
        Tableau d'etat
        ----------------------------------------------
        Etat Present | D2 | D3 | Etat Suivant | Port A
        ----------------------------------------------
        Init         | 0  | X  | Init         | 0 (eteint)
        Init         | 1  | X  | Etat 1       | 0 (eteint)
        Etat 1       | X  | 0  | Etat 1       | 1 (vert)
        Etat 1       | X  | 1  | Etat 2       | 1 (vert)
        Etat 2       | X  | 0  | Etat 2       | 1 (vert)
        Etat 2       | X  | 1  | Etat 3       | 1 (vert)
        Etat 3       | X  | 0  | Etat 3       | 1 (vert)
        Etat 3       | X  | 1  | Final        | 1 (vert)
        Final        | X  | X  | Init         | 2 (rouge)
        */

        switch(etatPresent) {
            case Init:
                    PORTA = 0x00;
                    if (PIND & 0x04) {
                        PORTA = 0x01;
                        while (PIND & 0x04) {
                            _delay_ms(100);
                        }
                        etatPresent = Etat1;
                    }
                    else {
                        etatPresent = Init;
                    }
                    break;
            
            case Etat1:
                if (PIND & 0x08) { 
                    while (PIND & 0x08) {
                        _delay_ms(100);
                    }
                    etatPresent = Etat2;
                }
                else {
                    etatPresent = Etat1;
                }
                break;


            case Etat2:
                if (PIND & 0x08) {
                    while (PIND & 0x08) {
                        _delay_ms(100);
                    }
                    etatPresent = Etat3;
                }
                else {
                    etatPresent = Etat2;
                }
                break;
            
            case Etat3:
                if (PIND & 0x08) {
                    while (PIND & 0x08) {
                        _delay_ms(100);
                    } 
                    etatPresent = Fin;
                }
                else {
                    etatPresent = Etat3;
                }
                break;

            case Fin:
                PORTA = 0x02; 
                _delay_ms(1000);
                etatPresent = Init;
                break;

        }
    }
    return 0;
}