#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "contours.h"
#include "image.h"
#include "geom2d.h"
#include "bezier.h"

Point trouver_point_depart(Image I){
    UINT l = largeur_image(I);
    UINT h = hauteur_image(I);
    // Recherche du premier pixel noir ayant un pixel blanc juste au-dessus
    for(int i = 1; i <= h; i++){
        for (int j = 1; j <= l; j++){
            if (get_pixel_image(I, j, i) == NOIR){
                if (get_pixel_image(I, j, i - 1) == BLANC){
                    Point p = set_point(j - 1, i - 1);
                    return p;
                }
            }
        }
    }
    return set_point(-1, -1);  // Aucun point trouvé
}

void memoriser_position_partie_1(Point p){
    // Affiche les coordonnées du point au format (x, y)
    printf("(%.1f,%.1f)", p.x, p.y);
    return;
}

Orientation tourner_90(Orientation o){
    // Fait une rotation de 90° dans le sens trigonométrique
    switch(o){
        case Nord:  return Ouest;
        case Ouest: return Sud;
        case Sud:   return Est;
        case Est:   return Nord;
    }
}

Point avancer(Point p, Orientation O){
    // Avance d’un pixel dans la direction donnée
    switch (O){
        case Est:   p.x++; return p;
        case Sud:   p.y++; return p;
        case Ouest: p.x--; return p;
        case Nord:  p.y--; return p;
    }
}

Pixel valeur_pixel_gauche(Image I, Point p, Orientation o){
    // Récupère le pixel à gauche de la direction actuelle
    switch (o){
        case Nord:  return get_pixel_image(I, p.x,     p.y);
        case Est:   return get_pixel_image(I, p.x + 1, p.y);
        case Sud:   return get_pixel_image(I, p.x + 1, p.y + 1);
        case Ouest: return get_pixel_image(I, p.x,     p.y + 1);
    }
}

Pixel valeur_pixel_droit(Image I, Point p, Orientation o){
    // Récupère le pixel à droite de la direction actuelle
    switch (o){
        case Nord:  return get_pixel_image(I, p.x + 1, p.y);
        case Est:   return get_pixel_image(I, p.x + 1, p.y + 1);
        case Sud:   return get_pixel_image(I, p.x,     p.y + 1);
        case Ouest: return get_pixel_image(I, p.x,     p.y);
    }
}

Orientation nouvelle_orientation(Image I, Point p, Orientation o){
    Pixel pG = valeur_pixel_gauche(I, p, o);
    Pixel pD = valeur_pixel_droit(I, p, o);

    // Règles de mise à jour de l'orientation selon les valeurs des pixels gauche/droit
    if (pG == BLANC && pD == BLANC){
        for(int i = 0; i < 3; i++) o = tourner_90(o);
        return o;
    }
    if ((pG == NOIR && pD == NOIR) || (pG == NOIR && pD == BLANC)){
        o = tourner_90(o);
        return o;
    }
    return o;
}

void afficher_orientation(Orientation O){
    // Affiche l’orientation sous forme textuelle
    switch (O){
        case Nord:  printf("Nord,\n");  break;
        case Sud:   printf("Sud,\n");   break;
        case Est:   printf("Est,\n");   break;
        case Ouest: printf("Ouest,\n"); break;
    }
}

Image masque(Image I){
    UINT l = largeur_image(I);
    UINT h = hauteur_image(I);
    Image M = creer_image(l, h);

    // Génère un masque où seuls les pixels noirs en bas de contour sont conservés
    for(int i = 1; i <= h; i++){
        for (int j = 1; j <= l; j++){
            if (get_pixel_image(I, j, i) == NOIR && get_pixel_image(I, j, i - 1) == BLANC){
                set_pixel_image(M, j, i, NOIR);
            }
        }
    }
    return M;
}

Point existe_point_noir(Image I){
    // Vérifie s’il reste au moins un pixel noir dans l’image
    UINT l = largeur_image(I);
    UINT h = hauteur_image(I);
    for(int i = 1; i <= h; i++){
        for (int j = 1; j <= l; j++){
            if (get_pixel_image(I, j, i) == NOIR){
                return set_point(j, i);
            }
        }
    }
    return set_point(-1, -1);
}

void ecrire_EPS_mode_1(Liste_Point LP, char nom[], UINT l, UINT h){
    FILE *f = fopen(nom, "w");
    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: %d %d %d %d\n", 0, 0, l, h);

    // Écriture du contour en mode EPS (ligne continue)
    Cellule_Liste_Point *cel = LP.first;
    double x0 = cel->data.x;
    double y0 = cel->data.y;
    fprintf(f, "%lf %lf moveto ", x0, h - y0);
    cel = cel->suiv;

    while(cel != NULL){
        double x = cel->data.x;
        double y = cel->data.y;
        fprintf(f, "%lf %lf lineto \n", x, h - y);
        cel = cel->suiv;
    }

    fprintf(f, "0 setlinewidth stroke\n");
    fprintf(f, "showpage");
    fclose(f);
    return;
}

void ecrire_EPS_mode_pls_contours(Liste_Liste_Point LP, char nom[], UINT l, UINT h){
    FILE *f = fopen(nom, "w");
    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: %d %d %d %d\n", 0, 0, l, h);

    // Écrit plusieurs contours dans un seul fichier EPS
    Cellule_Cellule_Liste_Point *T52 = LP.first;
    while(T52 != NULL){
        Cellule_Liste_Point *cel = T52->LP.first;
        double x0 = cel->data.x;
        double y0 = cel->data.y;
        fprintf(f, "%lf %lf moveto ", x0, h - y0);
        cel = cel->suiv;

        while(cel != NULL){
            double x = cel->data.x;
            double y = cel->data.y;
            fprintf(f, "%lf %lf lineto \n", x, h - y);
            cel = cel->suiv;
        }

        T52 = T52->suiv;
    }

    fprintf(f, "0 setlinewidth fill\n");
    fprintf(f, "showpage");
    fclose(f);
    return;
}

Liste_Liste_Point calcul_contours(Image I){
    Image M = masque(I);
    Point p = trouver_point_depart(M);
    Liste_Liste_Point LP = creer_liste_liste_Point_vide();

    // Détection de tous les contours fermés dans l’image
    while(p.x >= 0 && p.y >= 0){
        Liste_Point LP2 = creer_liste_Point_vide();
        Point Position = p;
        Orientation O = Est;
        bool boucle = true;

        while(boucle){
            if (O == Est){
                set_pixel_image(M, p.x + 1, p.y + 1, BLANC);  // Marque comme visité
            }

            LP2 = memoriser_position_partie_2(LP2, p);
            p = avancer(p, O);
            O = nouvelle_orientation(I, p, O);

            if (Position.x == p.x && Position.y == p.y && O == Est){
                boucle = false;
            }
        }

        LP2 = memoriser_position_partie_2(LP2, p);
        LP = ajouter_element__liste_liste_Point(LP, LP2);
        p = trouver_point_depart(M);
    }

    return LP;
}

Liste_Point tab_vers_Liste(Point tab[], int taille){
    // Convertit un tableau de points en liste chaînée
    Liste_Point LP = creer_liste_Point_vide();
    for(int i = 0; i < taille; i++){
        LP = ajouter_element_liste_Point(LP, tab[i]);
    }
    return LP;
}

Liste_Point simplification_douglas_peucker(Tableau_Point tab, int j1, int j2, double distance_seuil){
    Liste_Point LP2 = creer_liste_Point_vide();
    Segment S = set_segment(tab.tab[j1], tab.tab[j2]);
    double dmax = 0;
    int k = j1;

    // Recherche du point le plus éloigné du segment [j1,j2]
    for(int j = j1 + 1; j <= j2; j++){
        double dj = distance_point_segment(tab.tab[j], S);
        if (dmax < dj){
            dmax = dj;
            k = j;
        }
    }

    if (dmax <= distance_seuil){
        // Le segment est une bonne approximation
        LP2 = ajouter_element_liste_Point(LP2, tab.tab[j1]);
        LP2 = ajouter_element_liste_Point(LP2, tab.tab[j2]);
    } else {
        // Sinon on découpe récursivement
        Liste_Point L1 = simplification_douglas_peucker(tab, j1, k, distance_seuil);
        Liste_Point L2 = simplification_douglas_peucker(tab, k, j2, distance_seuil);
        LP2 = concatener_liste_Point(L1, L2);
    }

    return LP2;
}
