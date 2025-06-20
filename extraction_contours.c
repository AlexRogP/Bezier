#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "contours.h"
#include "image.h"
#include "geom2d.h"
#include "exemple_sequence_point.h"
#include "contours.h"  // Doublon volontairement laissé

int main(int argc, char *argv[]) {
    Image I = lire_fichier_image(argv[1]);
    // ecrire_image(I);  // Ligne commentée, utile pour debug visuel éventuel

    Image M = masque(I);  // Création d’un masque binaire de l’image
    Point p = trouver_point_depart(M);  // Recherche du premier pixel noir non encore traité

    Liste_Liste_Point LP = creer_liste_liste_Point_vide();  // Initialisation de la liste des contours

    // Boucle principale : tant qu’on trouve un nouveau point de départ, on extrait un contour
    while (p.x >= 0 && p.y >= 0) {
        Liste_Point LP2 = creer_liste_Point_vide();
        Point Position = p;
        Orientation O = Est;
        bool boucle = true;

        // Parcours d’un contour complet
        while (boucle) {
            if (O == Est) {
                // Marque le pixel comme traité dans le masque
                set_pixel_image(M, p.x + 1, p.y + 1, BLANC);
            }

            LP2 = memoriser_position_partie_2(LP2, p);
            p = avancer(p, O);
            O = nouvelle_orientation(I, p, O);

            // Condition d’arrêt : retour au point de départ avec orientation initiale
            if (Position.x == p.x && Position.y == p.y && O == Est) {
                boucle = false;
            }
        }

        LP2 = memoriser_position_partie_2(LP2, p);  // Ajout du dernier point du contour
        LP = ajouter_element__liste_liste_Point(LP, LP2);  // Ajout du contour à la liste globale

        p = trouver_point_depart(M);  // Recherche d’un nouveau contour
    }

    ecrire_contours_Liste_Liste(LP);  // Affichage des contours en console

    int nb_contours = LP.nb_contours;
    int nb_points = LP.nb_points;
    int nb_segments = nb_points - nb_contours;

    printf("%d contours \n", nb_contours);
    printf("%d points \n", nb_points);
    printf("%d segments \n", nb_segments);

    return 0;
}
