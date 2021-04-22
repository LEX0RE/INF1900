/**
 * @brief Fonction pour la gestion du temps
 * @file temps.cpp
 * @date 21/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#include "temps.hpp"

bool Temps::operator<(Temps autre){
    if(minute != autre.minute)
        return minute < autre.minute;
    else if(seconde != autre.seconde)
        return seconde < autre.seconde;
    else
        return centiseconde < autre.centiseconde;
}

bool Temps::operator<=(Temps autre){
    if(*this  == autre)
        return true;
    else
        return *this < autre;
}

bool Temps::operator>(Temps autre){
    if(minute != autre.minute)
        return minute > autre.minute;
    else if(seconde != autre.seconde)
        return seconde > autre.seconde;
    else
        return centiseconde > autre.centiseconde;
}

bool Temps::operator>=(Temps autre){
    if(*this  == autre)
        return true;
    else
        return *this < autre;
}

bool Temps::operator==(Temps autre){
    return (minute == autre.minute && seconde == autre.seconde && centiseconde == autre.centiseconde);
}

Temps Temps::enTemps(unsigned long milliseconde){
    unsigned long maxCentiseconde = 100l, maxSeconde = 60l;
    uint8_t milliDansCenti = 10;
    Temps resultat = {};

    // Convertion en centiseconde
    unsigned long temps = milliseconde / milliDansCenti;

    // Calcul des minutes
    resultat.minute = temps / (maxCentiseconde * maxSeconde);
    temps -= resultat.minute * (maxCentiseconde * maxSeconde);

    // Calcul des secondes
    resultat.seconde = temps / maxCentiseconde;
    temps -= resultat.seconde * maxCentiseconde;

    // Calcul des centisecondes
    resultat.centiseconde = temps;

    return resultat;
}

Temps Temps::operator+(Temps temps){
    uint8_t maxCentiseconde = 100, maxSeconde = 60;
    uint16_t temporaire = 0;

    // Sauvegarde du temps additionner
    Temps sauvegarde = {minute + temps.minute, 
                        seconde + temps.seconde, 
                        centiseconde + temps.centiseconde};
    
    // Correction du temps resultant

    // Correction centiseconde
    temporaire = int(sauvegarde.centiseconde / maxCentiseconde);
    sauvegarde.centiseconde = sauvegarde.centiseconde % maxCentiseconde;

    // Correction seconde
    sauvegarde.seconde += temporaire;
    temporaire = int(sauvegarde.seconde / maxSeconde);
    sauvegarde.seconde = sauvegarde.seconde % maxSeconde;

    // Correction minute
    sauvegarde.minute += temporaire;

    return sauvegarde;
}