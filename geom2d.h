#ifndef _GEOM2D_H_
#define _GEOM2D_H_


typedef struct Vecteur_{
    double x,y;/*Coordonnées*/
}Vecteur;

typedef struct Point_{
    double x,y;/*Coordonnées*/
}Point;

typedef struct Segment_{
    Point x,y;/*Coordonnées*/
}Segment;

/*##############################*/
/*           POINTS             */
/*##############################*/


/*Créer le point de coordonnées (x,y)*/
Point set_point(double x, double y);

/*somme P1+P2*/
Point add_point(Point P1,Point P2);

/*soustraction P1-P2*/
Point sous_point(Point P1,Point P2);

/*Multiplique aP1*/
Point mult_point(Point P1, double a);

/* Diviser P/a */
Point div_point(Point P1,double a);

/*Distance entre deux point*/
double distance(Point P1, Point P2);

/*##############################*/
/*           VECTEURS           */
/*##############################*/

/*Créer une vecteur de coordonné x et y*/
Vecteur set_vecteur(double x, double y);

/*vecteur correspondant au bipoint AB^(->)*/
Vecteur vect_bipoint(Point A,Point B);

/*Somme V1+V2*/
Vecteur add_vecteur(Vecteur V1,Vecteur V2);

/*Multiplié aV1*/
Vecteur mult_vecteur(Vecteur V1,double a);

/*Produit scalaire de V1 et V2*/
double produit_scalaire(Vecteur V1,Vecteur V2);

/*Norme euclidienne du vecteur V*/
double norme_eucli(Vecteur V);

/*##############################*/
/*           SEGMENTS           */
/*##############################*/

/*Créer le segment S=[A,B]*/
Segment set_segment(Point A, Point B);

/*calcul la distance entre le Point P ET Segment S*/
double distance_point_segment(Point P, Segment S);

/*Calcul le lamba dans le cas où on doit Q la projection orthogonale de P sur delta*/
double lambda(Point A, Point B, Point P);

/*Calcul Q comme dit dans le Poly avec le Point A , B et le réel lambda*/
Point calcul_Q(Point A, Point B , double lambda);



#endif
