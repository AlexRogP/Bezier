#ifndef _BEZIER_H_
#define _BEZIER_H_

#include "geom2d.h"
#include "image.h"
#include "contours.h"
#include "exemple_sequence_point.h"

// Représente une courbe de Bézier de degré 2 (quadratique)
typedef struct Bezier2 {
    Point C0, C1, C2;  // Points de contrôle : début, milieu, fin
} Bezier2;

// Représente une courbe de Bézier de degré 3 (cubique)
typedef struct Bezier3 {
    Point C0, C1, C2, C3;  // Points de contrôle : début, 2 intermédiaires, fin
} Bezier3;

// Élément d’une liste chaînée de courbes de Bézier quadratiques
typedef struct Cellule_Bezier2 {
    Bezier2 b;
    struct Cellule_Bezier2 *suiv;
} Cellule_Bezier2;

// Liste chaînée de courbes de Bézier de degré 2
typedef struct Liste_Bezier2 {
    unsigned int taille;
    Cellule_Bezier2 *first;
    Cellule_Bezier2 *last;
} Liste_Bezier2;

// Élément d’une liste chaînée de courbes de Bézier cubiques
typedef struct Cellule_Bezier3 {
    Bezier3 b;
    struct Cellule_Bezier3 *suiv;
} Cellule_Bezier3;

// Liste chaînée de courbes de Bézier de degré 3
typedef struct Liste_Bezier3 {
    unsigned int taille;
    Cellule_Bezier3 *first;
    Cellule_Bezier3 *last;
} Liste_Bezier3;

// Élément d’une liste de listes de courbes de Bézier de degré 2
typedef struct Cellule_Cellule_Liste_Bezier2 {
    Liste_Bezier2 LB;
    struct Cellule_Cellule_Liste_Bezier2 *suiv;
} Cellule_Cellule_Liste_Bezier2;

// Liste de contours, chacun étant une liste de Bézier2
typedef struct Liste_Liste_Bezier2 {
    int nb_bezier2;  // Nombre total de contours
    Cellule_Cellule_Liste_Bezier2 *first;
    Cellule_Cellule_Liste_Bezier2 *last;
} Liste_Liste_Bezier2;

// Élément d’une liste de listes de courbes de Bézier de degré 3
typedef struct Cellule_Cellule_Liste_Bezier3 {
    Liste_Bezier3 LB;
    struct Cellule_Cellule_Liste_Bezier3 *suiv;
} Cellule_Cellule_Liste_Bezier3;

// Liste de contours, chacun étant une liste de Bézier3
typedef struct Liste_Liste_Bezier3 {
    int nb_bezier3;  // Nombre total de contours
    Cellule_Cellule_Liste_Bezier3 *first;
    Cellule_Cellule_Liste_Bezier3 *last;
} Liste_Liste_Bezier3;



//Permet de calculer C(t) à partir des point de controle de la courbe de bézier de degré 2
Point calcul_bezier2(Bezier2 B,double t);

//Permet de calculer C(t) à partir des point de controle de la courbe de bézier de degré 2
Point calcul_bezier3(Bezier3 B,double t);

//Elevation de degré de courbe de Bézier
Bezier3 B2toB3(Bezier2 B);

//Elevation de degré de courbe de Bézier sur un courbe
Liste_Bezier3 *Liste_B2toB3(Liste_Bezier2 B);

//On approxime le contour initial par une courbe de Bezier
Bezier2 approx_bezier2(Tableau_Point Tab, int j1,int j2);

//Est une fonction intermédaire pour faire gamma en approx_bezier3
double gamma(double k,double n);

//On approxime le contour initial par une courbe de Bezier
Bezier3 approx_bezier3(Tableau_Point Tab, int j1,int j2);
//Calcule la distance entre un point et une courbe de Bezier de degré 2
double distance_bezier2(Point P,Bezier2 B,double t);

//Calcule la distance entre un point et une courbe de Bezier de degré 3
double distance_bezier3(Point P,Bezier3 B,double t);

/* creer une liste vide */
Liste_Bezier2 creer_liste_Bezier2_vide();

/* creer une cellule de liste avec l'element v 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Bezier2 *creer_element_liste_Bezier2(Bezier2 v);

/* ajouter l'element en fin de la liste B, renvoie la liste L modifiee */
Liste_Bezier2 ajouter_element_liste_Bezier2(Liste_Bezier2 B, Bezier2 e);

/* concatener B2 a la suite de B1, renvoie la liste B1 modifiee */
Liste_Bezier2 concatener_liste_Bezier2(Liste_Bezier2 B1, Liste_Bezier2 B2);

/*Simplifie le contours LP avec la distance seuil à d*/
Liste_Bezier2 simplification_douglas_peucker_bezier2(Tableau_Point tab,int j1,int j2, double distance_seuil);

//Permet de créer une Liste de liste de point vide
Liste_Liste_Bezier2 creer_liste_liste_Bezier2_vide();

/* ajouter l'element en fin de la liste de liste L, renvoie la liste liste L modifiee */
Liste_Liste_Bezier2 ajouter_element_liste_liste_Bezier2(Liste_Liste_Bezier2 L, Liste_Bezier2 L1);

/* creer une liste vide */
Liste_Bezier3 creer_liste_Bezier3_vide();

/* creer une cellule de liste avec l'element v 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Bezier3 *creer_element_liste_Bezier3(Bezier3 v);

/* ajouter l'element en fin de la liste B, renvoie la liste L modifiee */
Liste_Bezier3 ajouter_element_liste_Bezier3(Liste_Bezier3 B, Bezier3 e);

/* concatener B2 a la suite de B1, renvoie la liste B1 modifiee */
Liste_Bezier3 concatener_liste_Bezier3(Liste_Bezier3 B1, Liste_Bezier3 B2);

//Permet de créer une Liste de liste de point vide
Liste_Liste_Bezier3 creer_liste_liste_Bezier3_vide();

/* ajouter l'element en fin de la liste de liste L, renvoie la liste liste L modifiee */
Liste_Liste_Bezier3 ajouter_element_liste_liste_Bezier3(Liste_Liste_Bezier3 L, Liste_Bezier3 L1);

/*Permet d'écrire au format EPS , des courbes de Béziers de degré 2*/
void ecrire_EPS_mode_pls_contours_bezier2(Liste_Liste_Bezier2 LP, char nom[], UINT l, UINT h);

/*Permet d'écrire au format EPS , des courbes de Béziers de degré 3*/
void ecrire_EPS_mode_pls_contours_bezier3(Liste_Liste_Bezier3 LP, char nom[], UINT l, UINT h);


/*Simplifie le contours LP avec la distance seuil à d*/
Liste_Bezier3 simplification_douglas_peucker_bezier3(Tableau_Point tab,int j1,int j2, double distance_seuil);








#endif