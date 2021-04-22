/**
 * @brief Librairie pour la gestion du robot
 * @file robot.hpp
 * @date 20/04/2021
 * @author Alexandre Gélinas (2083465)
 * @author Ioana Daria Danciu (2081744)
 * @author Maxence Sigouin (2087199)
 * @author Vincent Grenier (2087987)
 */

#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "atmel.hpp"
#include "chrono.hpp"
#include "moteurs.hpp"

/**
 * @brief Enumération de l'état de la distance avec le robot
 */
enum Distance{OK, ATTENTION, DANGER};

/**
 * @brief Enumération des capteurs de distance
 */
enum Capteur{GAUCHE, CENTRE, DROITE};

/**
 * @brief Enumération des convertisseurs analogiques-numeriques
 */
enum Convertisseur{INTERNE, EXTERNE};

/**
 * @brief Enumération des differentes opérations possibles pour le robot
 */
enum Operation{DEMARRAGE, DETECTION, MANOEUVRE};

/**
 * @brief Enumération des types d'affichages pour le robot (R V ou C)
 */
enum FrequenceAffichage{AR, AV, AC};

/**
 * @brief Enumération des types d'affichages pour la vitesse des moteurs
 */
enum Affichage{DECIMAL, HEXADECIMAL};

/**
 * @brief Enumeration des afficheurs sept segments pour la vitesse des moteurs (de gauche a droite)
 */
enum Afficheur{AFF1, AFF2, AFF3, AFF4};

/**
 * @brief Enumération des boutons du clavier
 */
enum Clavier{ BOUTON1, BOUTON2, BOUTON4, BOUTONR, BOUTONV, BOUTONC, BOUTONI, BOUTONE, BOUTONNum};

/**
 * @brief Classe gérant le robot
 */
class Robot{
public:

    /**
     * @brief Constructeur empêchant la copie
     */
    Robot(Robot&) = delete;

    /**
     * @brief Empêche l'assignation
     */
    void operator=(const Robot&) = delete;

    /**
     * @brief Si la classe n'a toujours pas été instanciée, crée un objet robot et retourne un pointeur vers celui-ci. Sinon retourne un pointeur vers l'instance
     * @return Robot* Pointeur vers l'instance de la classe
     */
    static Robot* obtenirInstance();

    /**
     * @brief Permet d'accepter la manoeuvre détectée
     */
    void boutonAppuye();

    /**
     * @brief Permet au robot de savoir quel fonction effectué en fonction de son état
     */
    void operation();

    /**
     * @brief Permet de changer les attributs du robot dépendamment du bouton du clavier qui a été appuyé
     */
    void obtenirClavier();

private:
    Convertisseur convertisseur_; // Sauvegarde l'état de la lecture des capteurs
    Operation operation_; // Sauvegarde l'état de l'opération actuel du robot
    uint8_t frequence_; // Sauvegarde de la fréquence d'affichage de la détection pour le robot
    FrequenceAffichage frequenceAffichage_; // Sauvegarde l'état du mode d'affichage de la détection
    Affichage affichage_; // Sauvegarde la manière d'afficher la vitesse des moteurs
    Moteurs moteur_; // Gère les moteurs du robot
    Chrono chrono_; // Gère le chrono du robot
    Distance distance_[3]; // Sauvegarde les catégories de détection pour chaque capteurs
    uint8_t manoeuvre_; // Indique quelle manoeuvre sera exécuté
    const char* changement_; // Sauvegarde le changement d'un mode du clavier
    static Robot* robot_; // Instance du robot

    /**
     * @brief Instancie la classe robot
     */
    Robot() = default;

    /**
     * @brief Détruit l'objet Robot
     */
    ~Robot();
    
    /**
     * @brief Permet d'initialiser les registres nécessaires pour le robot
     */
    void initialiser();

    /**
     * @brief Change la vitesse d'un seul moteur et affiche sa vitesse sur les afficheurs correspondants
     * @param vitesse La nouvelle vitesse (de 0 a 255) du moteur
     * @param roue Le moteur dont on veut changer la vitesse
     */
    void modifierVitesseEtAffichage(int16_t vitesse, Roue roue);

    /**
     * @brief Change la vitesse des deux moteurs et affiche leurs vitesses sur les afficheurs
     * @param gauche La nouvelle vitesse (de 0 a 255) du moteur gauche
     * @param droite La nouvelle vitesse (de 0 a 255) du moteur droit
     */
    void modifierVitesseEtAffichage(int16_t gauche, int16_t droite);

    /**
     * @brief Affiche la vitesse des moteurs sur les afficheurs à sept segments
     */
    void afficherVitesse();

    /**
     * @brief Affiche le baud rate du USART
     */
    void afficherBaudRate();

    /**
     * @brief Affiche les diverses informations pour le mode détection
     */
    void afficherDetection();

    /**
     * @brief Détermine la manoeuvre à effecteur dépendamment de la categorie des trois distances mesurées par les capteurs
     */
    void rechargerManoeuvre();

    /**
     * @brief Obtient la distance du capteur déjà sélectionné
     * @param capteur capteur voulu
     * @return float distance obtenue par le capteur
     */
    float obtenirDistance(Capteur capteur);

    /**
     * @brief Obtient la lecture du capteur
     * @return float valeur lu par le convertisseur
     */
    float obtenirLecture();

    /**
     * @brief Effectue la sequence du mode démarrage
     */
    void demarrage();

    /**
     * @brief Effectue la sequence du mode détection
     */
    void detection();

    /**
     * @brief Effectue la manoeuvre correspondante aux distances mesurées par les capteurs
     */
    void manoeuvre();

    /**
     * @brief Détermine la prochaine operation à effectuer dépendamment de l'opération actuelle
     */
    void prochaineOperation();

    /**
     * @brief Effectue la séquence de la manoeuvre 1
     */
    void manoeuvreUn();

    /**
     * @brief Effectue la séquence de la manoeuvre 2
     */
    void manoeuvreDeux();

    /**
     * @brief Effectue la séquence de la manoeuvre 3
     */
    void manoeuvreTrois();

    /**
     * @brief Effectue la séquence de la manoeuvre 4
     */
    void manoeuvreQuatre();

    /**
     * @brief Effectue la séquence de la manoeuvre 5
     */
    void manoeuvreCinq();

    /**
     * @brief Obtient la lecture des colonnes du clavier
     * @return uint8_t colonne choisie
     */
    uint8_t colonneClavier();

    /**
     * @brief Obtient la lecture des rangées du clavier
     * @return uint8_t rangée choisie
     */
    uint8_t rangeeClavier();
};

/**
 * @brief Permet de convertir un poucentage de vitesse en vitesse
 * @param vitessePourcent vitesse en pourcentage
 * @return int16_t vitesse sur 255
 */
int16_t enVitesse(int16_t vitessePourcent);

/**
 * @brief Affiche le bouton du clavier qui a été appuyé
 * @param bouton Caractère du bouton qui a été appuyé
 */
void afficherBouton(const char* bouton);

/**
 * @brief Affiche le numéro de la manoeuvre qui est effectuée
 * @param numeroManoeuvre Numero de la manoeuvre effectuée
 */
void afficherManoeuvre(uint8_t numeroManoeuvre);

/**
 * @brief Active l'affichage des 4 afficheurs sept segments
 */
void allumerSeptSeg();

/**
 * @brief Désacctive l'affichage des 4 afficheurs sept segments
 */
void eteindreSeptSeg();

/**
 * @brief Permet d'afficher un nombre sur 4 bit sur l'un des 4 afficheurs 7 segments
 * @param afficheur afficheur qu'on veut modifier
 * @param valeur valeur en hexadécimale à afficher sur l'afficheur
 */
void afficherSeptSeg(Afficheur afficheur, uint8_t valeur);

#endif /* ROBOT_HPP */