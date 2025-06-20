#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "geom2d.h"




/*##############################*/
/*           POINTS             */
/*##############################*/

/*Cree le point de coordonnées (x,y)*/
Point set_point(double x, double y){
    Point P={x,y};
    return P;
}

/*somme P1+P2*/
Point add_point(Point P1,Point P2){
    return set_point(P1.x+P2.x,P1.y+P2.y);
}

/*soustraction P1-P2*/
Point sous_point(Point P1,Point P2){
    return set_point(P1.x-P2.x,P1.y-P2.y);
}

/*Multiplique aP1*/
Point mult_point(Point P1, double a){
    Point P={a*P1.x,a*P1.y};
    return P;
}

/* Diviser P/a */
Point div_point(Point P1,double a){
    Point P={P1.x/a,P1.y/a};
    return P;
}

/*Distance entre deux point*/
double distance(Point P1, Point P2){
    double valeur=pow(P1.x-P2.x,2)+pow(P1.y-P2.y,2);
    return sqrt(valeur);
}

/*##############################*/
/*           VECTEURS           */
/*##############################*/

/*Créer une vecteur de coordonné x et y*/
Vecteur set_vecteur(double x, double y){
    Vecteur V={x,y};
    return V;
}

/*vecteur correspondant au bipoint AB^(->)*/
Vecteur vect_bipoint(Point A,Point B){
    Vecteur V={B.x-A.x,B.y-A.y};
    return V;
}

/*Somme V1+V2*/
Vecteur add_vecteur(Vecteur V1,Vecteur V2){
    Vecteur V3={V1.x+V2.x,V1.y+V2.y};
    return V3;
}

/*Multiplié aV1*/
Vecteur mult_vecteur(Vecteur V1,double a){
    Vecteur V={a*V1.x,a*V1.y};
    return V;
}

/*Produit scalaire de V1 et V2*/
double produit_scalaire(Vecteur V1,Vecteur V2){
    double valeur=(V1.x*V2.x)+(V1.y*V2.y);
    return valeur;
}

/*Norme euclidienne du vecteur V*/
double norme_eucli(Vecteur V){
    double valeur=pow(V.x,2)+pow(V.y,2);
    return sqrt(valeur);
}


/*##############################*/
/*           SEGMENTS           */
/*##############################*/

/*Créer le segment S=[A,B]*/
Segment set_segment(Point A, Point B){
    Segment S={A,B};
    return S;
}

/*calcul la distance entre le Point P ET Segment S*/
double lambda (Point A, Point B, Point P){
    Vecteur AP=vect_bipoint(A,P);
    Vecteur AB=vect_bipoint(A,B);
    double AP_AB=produit_scalaire(AP,AB);
    double AB_AB=produit_scalaire(AB,AB);
    return (AP_AB/AB_AB);
}

/*Calcul le lamba dans le cas où on doit Q la projection orthogonale de P sur delta*/
Point calcul_Q(Point A, Point B , double lambda){
    Point B_A=sous_point(B,A);
    Point lambda_B_A=mult_point(B_A,lambda);
    return add_point(A,lambda_B_A);
}

/*Calcul Q comme dit dans le Poly avec le Point A , B et le réel lambda*/
double distance_point_segment(Point P, Segment S){
    Point A=S.x;
    Point B=S.y;
    if (A.x==B.x && A.y==B.y){
        return distance(A,P);
    }
    double lambda1=lambda(A,B,P);
    if (lambda1<0){
        return distance(A,P);
    }
    if(0<=lambda1 && lambda1<=1){
        Point Q=calcul_Q(A,B,lambda1);
        return distance(Q,P);
    }
    return distance(B,P);
}
