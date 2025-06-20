#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "contours.h"
#include "image.h"
#include "geom2d.h"
#include "exemple_sequence_point.h"
#include "contours.h"  // Inclusion redondante, mais laissée inchangée comme demandé

int main(int argc,char *argv[]){
    // Lecture de l'image à partir du fichier dont le nom est donné en argument (argv[1])
    Image I = lire_fichier_image(argv[1]);

    // Affichage de l'image en console (probablement pour vérification ou debug)
    ecrire_image(I);

    // Extraction des contours présents dans l'image sous forme de liste chaînée de points
    Liste_Point LP = liste_chaine_contours(I);

    // Récupération de la largeur et de la hauteur de l'image
    UINT l = largeur_image(I);
    UINT h = hauteur_image(I);

    // Écriture des contours extraits dans un fichier EPS (mode 1), dont le nom est donné en argument (argv[2])
    ecrire_EPS_mode_1(LP, argv[2], l, h);

    return 0;
}
