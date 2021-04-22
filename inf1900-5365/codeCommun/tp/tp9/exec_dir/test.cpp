/**
 * Fichier C++ contenant le programme pour le TP9
 * Date : 25/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */

#include <avr/io.h>

#include "atmel.hpp"
#include "eeprom.hpp"
#include "del.hpp"
#include "robot.hpp"
#include "usart.hpp"

int main() {
    modifierDDRX(2, 2, 2, 2);

    changerPin(&PORTA, 0x00);
    changerPin(&PORTB, 0x00);
    changerPin(&PORTC, 0x00);
    changerPin(&PORTD, 0x00);

    USART0* usart = USART0::obtenirInstance(2400, false, 3);
    unsigned char caractere;
    int nombre = 0;
    Eeprom* eeprom = Eeprom::obtenirInstance();
    eeprom->remiseAZero();

    nombre += usart->recevoir() * 256;
    nombre += usart->recevoir();

    for(int i = 0; i < nombre - 2; i++){
        caractere = usart->recevoir();
        eeprom->ecrire(&caractere);
    }
    
    lireMemoire();
    while(1){}
}