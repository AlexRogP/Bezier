#ifndef _EXEMPLE_SEQUENCE_POINT_H
#define _EXEMPLE_SEQUENCE_POINT_H

#include "geom2d.h"
#include "image.h"

/*---- le type cellule de liste de point ----*/
typedef struct Cellule_Liste_Point_
{
	Point data;    /* donnee de l'element de liste */
	struct Cellule_Liste_Point_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Point;

/*---- le type liste de point ----*/
typedef struct Liste_Point_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Point *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_Point *last;  /* pointeur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Point;

typedef Liste_Point Contour; /* type Contour = type Liste_Point */

/*---- le type tableau de point ----*/
typedef struct Tableau_Point_
{
	unsigned int taille; /* nombre d'elements dans le tableau */
	Point *tab;          /* (pointeur vers) le tableau des elements */
} Tableau_Point;

typedef struct Cellule_Cellule_Liste_Point_{
   Liste_Point LP;
   struct Cellule_Cellule_Liste_Point_ *suiv;
}Cellule_Cellule_Liste_Point;

typedef struct Liste_Liste_Point_{
   int nb_contours; //Nombre d'élément de la liste
   int nb_points;// Nombre de Point total présent dans tous les éléments 
   Cellule_Cellule_Liste_Point* first;
   Cellule_Cellule_Liste_Point* last;
}Liste_Liste_Point;

/* creer une cellule de liste avec l'element v 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_Point *creer_element_liste_Point(Point v);


/* creer une liste vide */
Liste_Point creer_liste_Point_vide();

/* ajouter l'element en fin de la liste L, renvoie la liste L modifiee */
Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e);

/* supprimer tous les elements de la liste, renvoie la liste L vide */
Liste_Point supprimer_liste_Point(Liste_Point L);

/* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */
Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2);

/* si la liste est non vide, la fonction supprime le premier element de L 
   si la liste est vide, la fonction ne fait rien 
   la fonction renvoie la liste (eventuellement) modifiee */
Liste_Point supprimer_premier_element_liste_Point(Liste_Point L);

/* creer une sequence de points sous forme d'un tableau de points 
   a partir de la liste de points L */
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L);

/* ecrire le contour L a l'ecran 
   cette fonction montre un exemple de conversion d'une liste de points en
   tableau de points afin de pouvoir par la suite acceder aux elements d'une
   sequence de points par indice */
void ecrire_contour(Liste_Point L);

/*Permet de rajouter le point p à la fin de la liste de point LP et renvoie la liste de point modifier */
Liste_Point memoriser_position_partie_2(Liste_Point LP,Point p);

/* 
   Extrait un seul contour de l'image I à partir du premier pixel noir rencontré, 
   en suivant ses bords jusqu'à revenir au point de départ.
   Retourne ce contour sous forme de Liste_Point.
*/
Liste_Point liste_chaine_contours(Image I);

/*
   Affiche un segment extrait de l'image I.
*/
void afficher_segment(Image I);


//Permet de créer une Liste de liste de point vide
Liste_Liste_Point creer_liste_liste_Point_vide();

/* ajouter l'element en fin de la liste de liste L, renvoie la liste liste L modifiee */
Liste_Liste_Point ajouter_element__liste_liste_Point(Liste_Liste_Point L, Liste_Point L1);

//Renvoie le nombre de point total de tous les élément de L
int nombre_point(Liste_Liste_Point L);

void ecrire_contours_Liste_Liste(Liste_Liste_Point LP);


#endif