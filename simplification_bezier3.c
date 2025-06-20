#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "contours.h"
#include "image.h"
#include "geom2d.h"
#include "exemple_sequence_point.h"
#include "bezier.h"

int main (int argc, char* argv[]){
    Image I = lire_fichier_image(argv[1]);
    double distance_seuil = atof(argv[3]);

    // Extraction des contours de l'image sous forme de listes de points
    Liste_Liste_Point LP = calcul_contours(I);

    int nb_segment = LP.nb_points - LP.nb_contours;

    printf("nombre de contours de LP =%d\n", LP.nb_contours);
    printf("Nombre de segment avant simplification est de %d\n", nb_segment);

    // Liste contenant tous les contours simplifiés en courbes de Bézier cubiques
    Liste_Liste_Bezier3 result = creer_liste_liste_Bezier3_vide();

    Cellule_Cellule_Liste_Point *cel = LP.first;

    // Parcours de chaque contour pour le transformer en une liste de courbes de Bézier cubiques
    while (cel != NULL) {
        Liste_Bezier3 resultat = creer_liste_Bezier3_vide(); 
        Tableau_Point tab = sequence_points_liste_vers_tableau(cel->LP);
        resultat = simplification_douglas_peucker_bezier3(tab, 0, cel->LP.taille - 1, distance_seuil); 
        result = ajouter_element_liste_liste_Bezier3(result, resultat);
        cel = cel->suiv;
    }

    UINT l = largeur_image(I);
    UINT h = hauteur_image(I);

    int nb_courbe = 0;
    Cellule_Cellule_Liste_Bezier3 *cel1 = result.first;

    // Comptage du nombre total de courbes de Bézier produites après simplification
    while (cel1 != NULL) {
        nb_courbe += cel1->LB.taille;
        cel1 = cel1->suiv;
    }

    printf("Avec seuil %.lf ,On est passé de %d segments à %d courbe de bezier\n",
           distance_seuil, LP.nb_points - LP.nb_contours, nb_courbe);

    // Écriture des courbes de Bézier dans un fichier EPS
    ecrire_EPS_mode_pls_contours_bezier3(result, argv[2], l, h);

    return 0;
}
