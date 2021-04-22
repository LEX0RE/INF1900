/**
 * @brief Fonction pour le Uart
 * @file usart.cpp
 * @date 21/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

// F_CPU défini dans le Makefile

#include <avr/eeprom.h>
#include <stdlib.h> 
#include <stdio.h>

#include "include/usart.hpp"

uint32_t USART::obtenirBaudRate(bool reel){
  // Permet de savoir si on prend la valeur du registre en convertion ou la valeur de l'utilisateur lorsqu'il l'a entré

  // Formule tirée de la datasheet p170 : http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8272-8-bit-AVR-microcontroller-ATmega164A_PA-324A_PA-644A_PA-1284_P_datasheet.pdf
  // Permet de bien enregistrer et reprendre le baud rate
  if(reel){
    uint16_t registre = (uint16_t(*UBRRnH_) << 8) | uint16_t(*UBRRnL_);
    uint32_t arrondi = (F_CPU / (registre + 1)) - ((F_CPU / registre) % 2);
    return arrondi / 16l;
  }
  else{
    return baud_;
  }
}

void USART::transmettre(uint8_t donnee) {
  while (!(*UCSRnA_ & (1 << UDREn_))){}

  *UDRn_ = donnee;
}

void USART::envoyer(uint8_t donnee, const char* format){
  char message[TABLEAU_ALLOUE];
  sprintf(message, format, donnee);
  envoyer(message);
}

void USART::envoyer(uint16_t donnee, const char* format){
  char message[TABLEAU_ALLOUE];
  sprintf(message, format, donnee);
  envoyer(message);
}

void USART::envoyer(uint32_t donnee, const char* format){
  char message[TABLEAU_ALLOUE];
  sprintf(message, format, donnee);
  envoyer(message);
}

void USART::envoyer(int donnee, const char* format) {
  char message[TABLEAU_ALLOUE];
  sprintf(message, format, donnee);
  envoyer(message);
}

void USART::envoyer(float donnee, const char* format) {
  double nombre = donnee;
  char message[TABLEAU_ALLOUE];
  sprintf(message, format, nombre);
  envoyer(message);
}

void USART::envoyer(const char* donnee) {
  uint16_t i = 0;
  
  while (donnee[i] != '\0')
      transmettre(donnee[i++]);
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

void USART::initialiser(uint16_t baud, StopBits modeStopBit, BitsEnvoye modeBitEnvoye){
  baud_ = baud;

  // Formule Tiré de la datasheet p170 : http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8272-8-bit-AVR-microcontroller-ATmega164A_PA-324A_PA-644A_PA-1284_P_datasheet.pdf
  // Permet de bien enregistrer et reprendre le baud rate
  uint16_t value = int(F_CPU / (16l * baud)) - 1;

  *UBRRnH_ = uint8_t(value >> 8);
  *UBRRnL_ = uint8_t(value);

  modifierStopBit(modeStopBit);
  modifierNombreBits(modeBitEnvoye);
}

void USART::modifierStopBit(StopBits mode){
  *UCSRnC_ |= (mode << USBSn_);
}

void USART::modifierNombreBits(BitsEnvoye mode){
  *UCSRnC_ |= ((mode & 0x1) << UCSZn0_);
  *UCSRnC_ |= ((mode & 0x2) << UCSZn1_);
  *UCSRnB_ |= ((mode & 0x4) << UCSZn2_);
}

USART0* USART0::usart_{nullptr};

USART0::~USART0(){
  free(usart_);
}

USART0* USART0::obtenirInstance(uint32_t baud, StopBits modeStopBit, BitsEnvoye modeBitEnvoye){
  if(usart_ == nullptr){
    usart_ = (USART0*)malloc(sizeof(USART0));

    usart_->USART0::modifierRegistre();
    usart_->USART0::transmettre(uint8_t('\0'));
    usart_->USART0::initialiser(baud, modeStopBit, modeBitEnvoye);
    usart_->USART0::activerReception();
    usart_->USART0::activerTransmission();
  }
  return usart_;
}

void USART0::modifierRegistre(){
  // Enregistrement des positions des bits pour les registres
  RXENn_ = RXEN0;
  TXENn_ = TXEN0;
  RXCn_ = RXC0;
  UDREn_ = UDRE0;
  USBSn_ = USBS0;
  UCSZn0_ = UCSZ00;
  UCSZn1_ = UCSZ01;
  UCSZn2_ = UCSZ02;

  // Enregistrement de l'adresse du registre dans le but de l'utiliser plus tard
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

USART1* USART1::obtenirInstance(uint32_t baud, StopBits modeStopBit, BitsEnvoye modeBitEnvoye){
  if(usart_ == nullptr){
    usart_ = (USART1*)malloc(sizeof(USART1));

    usart_->USART1::modifierRegistre();
    usart_->USART1::transmettre(uint8_t('\0'));
    usart_->USART1::initialiser(baud, modeStopBit, modeBitEnvoye);
    usart_->USART1::activerReception();
    usart_->USART1::activerTransmission();
  }
  return usart_;
}

void USART1::modifierRegistre(){
  // Enregistrement des positions des bits pour les registres
  RXENn_ = RXEN1;
  TXENn_ = TXEN1;
  RXCn_ = RXC1;
  UDREn_ = UDRE1;
  USBSn_ = USBS1;
  UCSZn0_ = UCSZ10;
  UCSZn1_ = UCSZ11;
  UCSZn2_ = UCSZ12;

  // Enregistrement de l'adresse du registre dans le but de l'utiliser plus tard
  UCSRnA_ = &UCSR1A;
  UCSRnB_ = &UCSR1B;
  UCSRnC_ = &UCSR1C;
  UBRRnH_ = &UBRR1H;
  UBRRnL_ = &UBRR1L;
  UDRn_ = &UDR1;
}