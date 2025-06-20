#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "contours.h"
#include "image.h"
#include "geom2d.h"
#include "exemple_sequence_point.h"

int main(int argc, char *argv[]) {
    Point P;
    Point A;
    Point B;

    // Saisie du point P
    printf("Donnez les coordonnées du Point :\n");
    if (scanf("%lf %lf", &P.x, &P.y) != 2) {
        printf("Erreur de saisie pour les coordonnées du point.\n");
        return 1;
    }

    // Saisie des extrémités A et B du segment
    printf("Donnez les coordonnées des points qui constituent le segment :\n");
    if (scanf("%lf %lf %lf %lf", &A.x, &A.y, &B.x, &B.y) != 4) {
        printf("Erreur de saisie pour les coordonnées du segment.\n");
        return 1;
    }

    Segment S = set_segment(A, B);
    double distance1 = distance_point_segment(P, S);

    // Affichage du résultat
    printf("Entre le Point (%.2lf,%.2lf) et le segment ((%.2lf,%.2lf),(%.2lf,%.2lf)) il y a une distance de :\n",
           P.x, P.y, A.x, A.y, B.x, B.y);
    printf("%lf \n", distance1);

    return 0;
}
