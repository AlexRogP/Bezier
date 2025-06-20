#ifndef _CONTOURS_H_
#define _CONTOURS_H_

#include "image.h"
#include "geom2d.h"
#include "exemple_sequence_point.h"
#include "bezier.h"

typedef enum {Nord, Est, Sud, Ouest} Orientation;

/* Recherche le premier point de départ pour initier la détection de contour */
Point trouver_point_depart(Image I);

/* Affiche un point sous la forme (x,y), utilisé pour la visualisation */
void memoriser_position_partie_1(Point p);

/* Effectue une rotation de 90° dans le sens trigonométrique */
Orientation tourner_90(Orientation o);

/* Avance d’un pixel dans la direction donnée */
Point avancer(Point p, Orientation O);

/* Détermine la nouvelle orientation à partir de la position et de l’image */
Orientation nouvelle_orientation(Image I, Point p, Orientation o);

/* Affiche l’orientation actuelle sous forme textuelle */
void afficher_orientation(Orientation O);

/* Renvoie la valeur du pixel situé à gauche de la direction courante */
Pixel valeur_pixel_gauche(Image I, Point p, Orientation o);

/* Renvoie la valeur du pixel situé à droite de la direction courante */
Pixel valeur_pixel_droit(Image I, Point p, Orientation o);

/* Renvoie une image contenant uniquement les pixels de bord de l’image I (détection par transition blanc → noir) */
Image masque(Image I);

/* Renvoie les coordonnées d’un point noir présent dans l’image, ou (-1, -1) s’il n’y en a pas */
Point existe_point_noir(Image I);

/* Écrit un contour unique dans un fichier EPS au format PostScript */
void ecrire_EPS_mode_1(Liste_Point LP, char nom[], UINT l, UINT h);

/* Écrit plusieurs contours dans un fichier EPS */
void ecrire_EPS_mode_pls_contours(Liste_Liste_Point LP, char nom[], UINT l, UINT h);

/* Renvoie la liste de tous les contours détectés dans l’image I (Tâche 5, partie 1) */
Liste_Liste_Point calcul_contours(Image I);

/* Applique l’algorithme de simplification de Douglas-Peucker à un ensemble de points */
Liste_Point simplification_douglas_peucker(Tableau_Point tab, int j1, int j2, double distance_seuil);

/* Convertit un tableau de points en liste chaînée de points */
Liste_Point tab_vers_Liste(Point tab[], int taille);

/* Idem que tab_vers_Liste, mais en ne considérant que les indices entre j1 et j2 inclus */
Liste_Point tab_vers_Liste_pour_indice_particulier(Point tab[], int j1, int j2);

#endif
