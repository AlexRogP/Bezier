#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "contours.h"
#include "image.h"
#include "exemple_sequence_point.h"



int main(int argc, char* argv[]){
    Image I=lire_fichier_image(argv[1]);
    ecrire_image(I);
    afficher_segment(I);
    return 0;
}
