#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "contours.h"
#include "image.h"
#include "geom2d.h"
#include "exemple_sequence_point.h"
#include "contours.h"  // Inclusion redondante, conservée comme demandé

int main(int argc, char *argv[]) {
    Image I = lire_fichier_image(argv[1]);

    // Extraction d’un unique contour sous forme de liste chaînée de points
    Liste_Point LP = liste_chaine_contours(I);

    unsigned int nb_point = LP.taille;
    unsigned int nb_segment = nb_point - 1;

    UINT l = largeur_image(I);
    UINT h = hauteur_image(I);

    // Affichage des informations de base
    printf("%s\n", argv[1]);
    printf("%d x %d\n", l, h);
    printf("%d segments\n\n", nb_segment);

    // printf("Il y a %d segments \n", nb_segment);  // Ligne alternative commentée

    return 0;
}
