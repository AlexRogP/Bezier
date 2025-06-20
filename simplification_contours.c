#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "contours.h"
#include "image.h"
#include "geom2d.h"
#include "exemple_sequence_point.h"

int main(int argc,char *argv[]){
    Image I = lire_fichier_image(argv[1]);
    double distance_seuil = atof(argv[3]);

    // Extraction des contours de l'image (un contour = une liste de points)
    Liste_Liste_Point LP = calcul_contours(I);

    int nb_segment = LP.nb_points - LP.nb_contours;

    printf("nombre de contours de LP =%d\n", LP.nb_contours);
    printf("Nombre de segment avant simplification est de %d\n", nb_segment);
    // ecrire_contours_Liste_Liste(LP);  // Ligne commentée, peut servir pour debug ou visualisation texte

    Liste_Liste_Point result = creer_liste_liste_Point_vide();
    Cellule_Cellule_Liste_Point *cel = LP.first;

    // Parcours de chaque contour pour le simplifier avec Douglas-Peucker
    while (cel != NULL) {
        Liste_Point resultat = creer_liste_Point_vide(); 
        Tableau_Point tab = sequence_points_liste_vers_tableau(cel->LP);
        resultat = simplification_douglas_peucker(tab, 0, cel->LP.taille - 1, distance_seuil); 
        result = ajouter_element__liste_liste_Point(result, resultat);
        cel = cel->suiv;
    }

    UINT l = largeur_image(I);
    UINT h = hauteur_image(I);

    printf("Avec seuil %lf ,On est passé de %d segments à %d segments\n",
           distance_seuil, LP.nb_points - LP.nb_contours, result.nb_points / 2);

    ecrire_EPS_mode_pls_contours(result, argv[2], l, h);

    return 0;
}

