/**
 * @brief Définition des fonction pour le fichier chrono.hpp
 * @file chrono.cpp
 * @date 21/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#include "chrono.hpp"
unsigned long long Chrono::chrono_ = 0;

Chrono::Chrono(){
    timer_ = Timer2::obtenirInstance(T8M0, NORMAL, P5, MATCHDEBORDEMENT);
}

Temps Chrono::obtenirTimer() const{
    // Initialisation
    Temps temps = {};
    uint16_t nIterationTimer = 256;
    unsigned long timerACentiseconde = 625l, maxCentiseconde = 100l, maxSeconde = 60l;
    // Sauvegarde du nombre de tick total du timer depuis le début
    unsigned long sauvegarde = (chrono_ * nIterationTimer) + timer_->obtenirTimer();

    // Calcul des minutes
    temps.minute = sauvegarde / (timerACentiseconde * maxCentiseconde * maxSeconde);
    sauvegarde -= temps.minute * (timerACentiseconde * maxCentiseconde * maxSeconde);

    // Calcul des secondes
    temps.seconde = sauvegarde / (timerACentiseconde * maxCentiseconde);
    sauvegarde -= temps.seconde * (timerACentiseconde * maxCentiseconde);

    // Calcul des centisecondes
    temps.centiseconde = sauvegarde / timerACentiseconde;

    return temps;
}

void Chrono::debuterDelai(){
    premiereLecture_ = obtenirTimer();
}

bool Chrono::delaiTermine(Temps delai){
    return (premiereLecture_ + delai) >= obtenirTimer();
}

void Chrono::delai(Temps delai){
    premiereLecture_ = obtenirTimer();
    attendreDelai(delai);
}

void Chrono::attendreDelai(Temps delai){
    Temps final = premiereLecture_ + delai;
    while(final > obtenirTimer()){}
}

void Chrono::demarrer(){
    timer_->demarrer();
}

void Chrono::arreter(){
    timer_->arreter();
}

void Chrono::reset(){
    timer_->arreter();
    chrono_ = 0;
    premiereLecture_ = {};
    timer_->remiseAZero();
    timer_->demarrer();
}