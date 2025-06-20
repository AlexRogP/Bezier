#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "contours.h"
#include "image.h"
#include "geom2d.h"
#include "exemple_sequence_point.h"
#include "contours.h"  // Redondant, mais laissé tel quel

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Voici le format demandé: < image> <fichier EPS> \n");
        return 1;
    }

    Image I = lire_fichier_image(argv[1]);
    Image M = masque(I);  // Création d'un masque à partir de l'image d'origine

    Point p = trouver_point_depart(M);  // Recherche du premier pixel noir dans le masque
    Liste_Liste_Point LP = creer_liste_liste_Point_vide();

    // Boucle principale : détection de tous les contours dans le masque
    while (p.x >= 0 && p.y >= 0) {
        Liste_Point LP2 = creer_liste_Point_vide();
        Point Position = p;
        Orientation O = Est;
        bool boucle = true;

        // Parcours du contour jusqu'à revenir au point de départ avec orientation Est
        while (boucle) {
            if (O == Est) {
                set_pixel_image(M, p.x + 1, p.y + 1, BLANC);  // Marquage du pixel dans le masque
            }

            LP2 = memoriser_position_partie_2(LP2, p);  // Ajout de la position courante au contour
            p = avancer(p, O);
            O = nouvelle_orientation(I, p, O);

            if (Position.x == p.x && Position.y == p.y && O == Est) {
                boucle = false;
            }
        }

        LP2 = memoriser_position_partie_2(LP2, p);  // Ajout du point final du contour
        LP = ajouter_element__liste_liste_Point(LP, LP2);  // Ajout du contour à la liste globale

        p = trouver_point_depart(M);  // Recherche du prochain point de départ
    }

    UINT l = largeur_image(I);
    UINT h = hauteur_image(I);

    // Écriture des contours détectés dans un fichier EPS
    ecrire_EPS_mode_pls_contours(LP, argv[2], l, h);

    return 0;
}
