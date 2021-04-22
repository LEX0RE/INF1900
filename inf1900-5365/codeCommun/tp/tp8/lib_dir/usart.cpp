/**
 * Fonction usart.cpp
 * Date : 11/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */

#include <avr/eeprom.h>

#include "usart.hpp"

void USART::initialiser(uint8_t baud, bool modeStopBit, unsigned int modeBitEnvoye){
  *UBRRnH_ = (unsigned char)(baud >> 8);
  *UBRRnL_ = (unsigned char)baud;
  modifierStopBit(modeStopBit);
  modifierNombreBits(modeBitEnvoye);
}

void USART::activerReception(){
  *UCSRnB_ |= (1 << RXENn_);
}

void USART::activerTransmission(){
  *UCSRnB_ |= (1 << TXENn_);
}

void USART::transmettre(uint8_t donnee) {
  while (!(*UCSRnA_ & (1 << UDREn_)));
  *UDRn_ = donnee;
}

void USART::modifierStopBit(bool mode){
  *UCSRnC_ |= (mode << USBSn_);
}

void USART::modifierNombreBits(unsigned int mode){
  if(mode < 8){
    *UCSRnC_ |= ((mode & 0x1) << UCSZn0_);
    *UCSRnC_ |= ((mode & 0x2) << UCSZn1_);
    *UCSRnB_ |= ((mode & 0x4) << UCSZn2_);
  }
}

USART0::USART0(uint8_t baud, bool modeStopBit, unsigned int modeBitEnvoye): USART(){
  modifierRegistre();
  initialiser(baud, modeStopBit, modeBitEnvoye);
  activerReception();
  activerTransmission();
}

void USART0::modifierRegistre(){
    numero_ = 0;
    RXENn_ = RXEN0;
    TXENn_ = TXEN0;
    UDREn_ = UDRE0;
    USBSn_ = USBS0;
    UCSZn0_ = UCSZ00;
    UCSZn1_ = UCSZ01;
    UCSZn2_ = UCSZ02;
    UCSRnA_ = &UCSR0A;
    UCSRnB_ = &UCSR0B;
    UCSRnC_ = &UCSR0C;
    UBRRnH_ = &UBRR0H;
    UBRRnL_ = &UBRR0L;
    UDRn_ = &UDR0;
}

USART1::USART1(uint8_t baud, bool modeStopBit, unsigned int modeBitEnvoye): USART(){
  modifierRegistre();
  initialiser(baud, modeStopBit, modeBitEnvoye);
  activerReception();
  activerTransmission();
}

void USART1::modifierRegistre(){
    numero_ = 1;
    RXENn_ = RXEN1;
    TXENn_ = TXEN1;
    UDREn_ = UDRE1;
    USBSn_ = USBS1;
    UCSZn0_ = UCSZ10;
    UCSZn1_ = UCSZ11;
    UCSZn2_ = UCSZ12;
    UCSRnA_ = &UCSR1A;
    UCSRnB_ = &UCSR1B;
    UCSRnC_ = &UCSR1C;
    UBRRnH_ = &UBRR1H;
    UBRRnL_ = &UBRR1L;
    UDRn_ = &UDR1;
}