#ifndef EEPROM_HPP
#define EEPROM_HPP
/**
 * Librairie eeprom.hpp
 * Date : 11/03/2021
 * Auteur : Ioana Daria Danciu, Alexandre Gélinas, Maxence Sigouin et Vincent Grenier
 * Matricules : 2081744, 2083465, 2087199 et 2087987
 * Groupe 02
 */

#include <stdint.h>
#include <stdio.h>

/** Classe gérant l'utilisation du Eeprom
 */
class Eeprom{
  public:
    // Empêche la copie
    Eeprom(Eeprom& autre) = delete;

    // Empêche l'assignation
    void operator=(const Eeprom&) = delete;

    // Permet d'obtenir l'instance du Eeprom ou de le créer
    static Eeprom* obtenirInstance();

    /* Lire la mémoire du Eeprom selon la grandeur sélectionnée
    * 
    * --------------------------------------------------------------------
    *     Lis en fonction de l'adresse stockée dans la classe Eeprom
    * --------------------------------------------------------------------
    * 
    * Paramètres: 
    *    destination:   pointeur à utilisé pour stocker ce qui est lu
    *    grandeur:      nombre de bit à lire sur la mémoire
    */
    void lire(void* destination, size_t grandeur);

    /* Écrire sur la mémoire du Eeprom
    * 
    * --------------------------------------------------------------------
    *     Écrit en fonction de l'adresse stockée dans la classe Eeprom
    * --------------------------------------------------------------------
    * 
    * Paramètre: 
    *    source:   pointeur vers la valeur à stocker dans la mémoire
    */
    void ecrire(const void* source);

    /* Met à jour une partie de la mémoire du Eeprom
    * 
    * --------------------------------------------------------------------
    *     Met à jour en fonction de l'adresse stockée dans la classe Eeprom
    * --------------------------------------------------------------------
    * 
    * Paramètre: 
    *    source:   pointeur vers la valeur à stocker dans la mémoire
    */
    void mettreAJour(const void* source);

    /* Remet à 255 toute les cases mémoires du Eeprom
    */
    void remiseAZero();

    /* Retourne l'adresse de la classe Eeprom
    * 
    * --------------------------------------------------------------------
    *  Retourne l'adresse en fonction de l'adresse stockée dans la classe Eeprom
    * --------------------------------------------------------------------
    * 
    * Valeur de retour: 
    *
    *     uint8_t: Adresse de la classe
    */
    uint8_t obtenirAdresse() const;

    /* Change l'adresse de la classe Eeprom
    * 
    * --------------------------------------------------------------------
    * 
    * Paramètre: 
    *    adresse:   nouvelle adresse pour la classe Eeprom
    */
    void changerAdresse(uint8_t adresse);

    /** Permet d'ajouter directement à l'adresse de la classe
     */
    Eeprom& operator+=(uint8_t nombre);

    /** Permet d'ajouter directement à l'adresse de la classe
     */
    Eeprom& operator++();

    /** Permet de soustraire directement à l'adresse de la classe
     */
    Eeprom& operator-=(uint8_t nombre);

    /** Permet de soustraire directement à l'adresse de la classe
     */
    Eeprom& operator--();
  private:
    static Eeprom* eeprom_;

    static uint8_t adresse_; // Adresse où nous écrirons nos données
    static uint8_t* pAdresse_; // Adresse utilisé pour l'échange avec le Eeprom
  protected:
    Eeprom() = default;
    ~Eeprom();
};
#endif /* EEPROM_HPP */