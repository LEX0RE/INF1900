/**
 * Fonction usart.cpp
 * Date : 11/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */

#include <avr/eeprom.h>
#include <stdlib.h> 

#include "include/usart.hpp"

void USART::transmettre(uint8_t donnee) {
  while (!(*UCSRnA_ & (1 << UDREn_))){}

  *UDRn_ = donnee;
}

unsigned char USART::recevoir() {
  while (!(*UCSRnA_ & (1 << RXCn_))){}
  
  return *UDRn_;
}

void USART::activerReception(){
  *UCSRnB_ |= (1 << RXENn_);
}

void USART::desactiverReception(){
  *UCSRnB_ &= ~(1 << RXENn_);
}

void USART::activerTransmission(){
  *UCSRnB_ |= (1 << TXENn_);
}

void USART::desactiverTransmission(){
  *UCSRnB_ &= ~(1 << TXENn_);
}

void USART::initialiser(int baud, bool modeStopBit, unsigned int modeBitEnvoye){
  uint16_t value = F_CPU / (16 * baud);

  *UBRRnH_ = (unsigned char)(value >> 8);
  *UBRRnL_ = (unsigned char)value;

  modifierStopBit(modeStopBit);
  modifierNombreBits(modeBitEnvoye);
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

USART0* USART0::usart_{nullptr};

USART0::~USART0(){
  free(usart_);
}

USART0* USART0::obtenirInstance(int baud, bool modeStopBit, unsigned int modeBitEnvoye){
  if(usart_ == nullptr){
    usart_ = (USART0*)malloc(sizeof(USART0));
    usart_->USART0::modifierRegistre();
    usart_->USART0::initialiser(baud, modeStopBit, modeBitEnvoye);
    usart_->USART0::activerReception();
    usart_->USART0::activerTransmission();
  }
  return usart_;
}

void USART0::modifierRegistre(){
    RXENn_ = RXEN0;
    TXENn_ = TXEN0;
    RXCn_ = RXC0;
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

USART1* USART1::usart_{nullptr};

USART1::~USART1(){
  free(usart_);
}

USART1* USART1::obtenirInstance(int baud, bool modeStopBit, unsigned int modeBitEnvoye){
  if(usart_ == nullptr){
    usart_ = (USART1*)malloc(sizeof(USART1));
    usart_->USART1::modifierRegistre();
    usart_->USART1::initialiser(baud, modeStopBit, modeBitEnvoye);
    usart_->USART1::activerReception();
    usart_->USART1::activerTransmission();
  }
  return usart_;
}

void USART1::modifierRegistre(){
    RXENn_ = RXEN1;
    TXENn_ = TXEN1;
    RXCn_ = RXC1;
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