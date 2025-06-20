#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bezier.h"
#include "geom2d.h"
#include "image.h"
#include "contours.h"
#include "exemple_sequence_point.h"


//Permet de calculer C(t) à partir des point de controle de la courbe de bézier de degré 2
Point calcul_bezier2(Bezier2 B,double t){
    double E0=(1-t)*(1-t);
    double E1=2*t*(1-t);
    double E2=t*t;

    Point P0=mult_point(B.C0,E0);
    Point P1=mult_point(B.C1,E1);
    Point P2=mult_point(B.C2,E2);

    Point intermediaire=add_point(P0,P1);
    Point P=add_point(intermediaire,P2);

    return P;
}

//Permet de calculer C(t) pour une courbe de Bézier de degré 3 et un réel t
Point  calcul_bezier3(Bezier3 B,double t){
    double E0=(1-t)*(1-t)*(1-t);
    double E1=3*t*(1-t)*(1-t);
    double E2=3*t*t*(1-t);
    double E3=t*t*t;

    Point P0=mult_point(B.C0,E0);
    Point P1=mult_point(B.C1,E1);
    Point P2=mult_point(B.C2,E2);
    Point P3=mult_point(B.C3,E3);

    Point P=add_point(add_point(P0,P1),add_point(P2,P3));

    return P;
}

//Elevation de degré de courbe de Bézier
Bezier3 B2toB3 (Bezier2 B){
    Bezier3 B3;
    B3.C0=B.C0;
    B3.C1=div_point(add_point(B.C0,mult_point(B.C1,2.0)),3.0);
    B3.C2=div_point(add_point(B.C2,mult_point(B.C1,2.0)),3.0);
    B3.C3=B.C2;
    return B3;
}

// Permet de faire une élévation de degré sur une liste de Courbe de Bézier de degré 2 
Liste_Bezier3 *Liste_B2toB3(Liste_Bezier2 B) {
    Cellule_Bezier2 *cel = B.first;
    Liste_Bezier3 *B3 = (Liste_Bezier3 *)malloc(sizeof(Liste_Bezier3));
    *B3 = creer_liste_Bezier3_vide();
    while (cel != NULL) {
        *B3 = ajouter_element_liste_Bezier3(*B3, B2toB3(cel->b));
        cel = cel->suiv;
    }
    return B3;
}


//On approxime le contour initial par une courbe de Bezier
Bezier2 approx_bezier2(Tableau_Point Tab, int j1,int j2){
    Bezier2 B;
    B.C0=Tab.tab[j1];
    B.C2=Tab.tab[j2];
    int n=j2-j1;
    if (n==1){
        B.C1=div_point(add_point(Tab.tab[j1],Tab.tab[j2]),2);
    }
    else {
        double n1=(double)(n);
        double alpha=(3*n1)/((n1*n1)-1);
        double beta=(1-(2*n1))/(2*(n1+1));
        Point P=set_point(0,0);
        for (int i=1;i<n;i++){
            P=add_point(P,Tab.tab[i+j1]);
        }
        B.C1=add_point(
            mult_point(P,alpha),
            mult_point(
                add_point(Tab.tab[j1],Tab.tab[j2]),
                beta)
        );
    }
    return B;
}

//Est une fonction intermédaire pour faire gamma en approx_bezier3
double gamma(double k,double n){
    return (6*k*k*k*k)-(8*n*k*k*k)+(6*k*k)-(4*n*k)+(n*n*n*n)-(n*n);
}



//On approxime le contour initial par une courbe de Bezier de degré 3
Bezier3 approx_bezier3(Tableau_Point Tab, int j1,int j2){
    Bezier3 B;
    B.C0=Tab.tab[j1];
    B.C3=Tab.tab[j2];
    int n=j2-j1;
    if (n==1){
        Bezier2 B1;
        B1.C0=Tab.tab[j1];
        B1.C1=div_point(add_point(Tab.tab[j1],Tab.tab[j2]),2);
        B1.C2=Tab.tab[j2];
        B=B2toB3(B1);
    }
    else if (n==2) {
        Bezier2 B1;
        B1.C0=Tab.tab[j1];
        B1.C2=Tab.tab[j2];
        double n1=(double)(n);
        double alpha=(3*n1)/((n1*n1)-1);
        double beta=(1-(2*n1))/(2*(n1+1));
        Point P=set_point(0,0);
        for (int i=1;i<n;i++){
            P=add_point(P,Tab.tab[i+j1]);
        }
        B1.C1=add_point(
            mult_point(P,alpha),
            mult_point(
                add_point(Tab.tab[j1],Tab.tab[j2]),
                beta)
        );
        B=B2toB3(B1);
    }else{
        B.C0=Tab.tab[j1];
        B.C3=Tab.tab[j2];
        double n1=(double)(n);
        double alpha=(((-15)*n1*n1*n1)+(5*n1*n1)+(2*n1)+4)/(3*(n1+2)*(3*n1*n1+1));
        double beta=(10*n1*n1*n1-15*n1*n1+n1+2)/(3*(n1+2)*(3*n1*n1+1));
        double lamda=(70*n1)/(3*(n1*n1-1)*(n1*n1-4)*(3*n1*n1+1));
        Point P1=set_point(0,0);
        Point P2=set_point(0,0);
        for(int i=1;i<n;i++){
            P1=add_point(P1,mult_point(Tab.tab[j1+i],gamma(i,n1)));
        }
        for(int i=1;i<n;i++){
            P2=add_point(P2,mult_point(Tab.tab[j1+i],gamma(n1-i,n1)));
        }
        Point alpha_C0=mult_point(Tab.tab[j1],alpha);
        Point beta_C3=mult_point(Tab.tab[j2],beta);
        Point lamda_P1=mult_point(P1,lamda);
        B.C1=add_point(add_point(alpha_C0,lamda_P1),beta_C3);

        Point beta_C0=mult_point(Tab.tab[j1],beta);
        Point alpha_C3=mult_point(Tab.tab[j2],alpha);
        Point lamda_P2=mult_point(P2,lamda);
        B.C2=add_point(add_point(beta_C0,lamda_P2),alpha_C3);
    }
    return B;
}

//Calcule la distance entre un point et une courbe de Bezier de degré 2
double distance_bezier2(Point p, Bezier2 b, double t){
    return distance(p,calcul_bezier2(b,t));
}

//Calcule la distance entre un point et une courbe de Bezier de degré 3
double distance_bezier3(Point p, Bezier3 b, double t){
    return distance(p,calcul_bezier3(b,t));
}

/* creer une liste de courbe de Bézier de degré 2 vide */
Liste_Bezier2 creer_liste_Bezier2_vide()
{
	Liste_Bezier2 B = {0, NULL, NULL};
	return B;
}

/* Permet de créer un une Cellule de courbe de Bézier de degré 2*/
Cellule_Bezier2 *creer_element_liste_Bezier2(Bezier2 v){
	Cellule_Bezier2 *el;
	el = (Cellule_Bezier2 *)malloc(sizeof(Cellule_Bezier2));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste_Point : allocation impossible\n");
		exit(-1);
	}
	el->b = v;
	el->suiv = NULL;
	return el;
}

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Bezier2 ajouter_element_liste_Bezier2(Liste_Bezier2 B, Bezier2 e)
{
	Cellule_Bezier2 *el;
	
	el = creer_element_liste_Bezier2(e);
	if (B.taille == 0)
	{
		/* premier element de la liste */
		B.first = B.last = el;
	}
	else
	{
		B.last->suiv = el;
		B.last = el;
	}
	B.taille++;
	return B;
}

/* concatener B2 a la suite de B1, renvoie la liste B1 modifiee */
Liste_Bezier2 concatener_liste_Bezier2(Liste_Bezier2 B1, Liste_Bezier2 B2){
	/* cas où l'une des deux listes est vide */
	if (B1.taille == 0) return B2; 
	if (B2.taille == 0) return B1;
	
	/* les deux listes sont non vides */
	B1.last->suiv = B2.first; /* lien entre B1.last et B2.first */
	B1.last = B2.last;        /* le dernier element de B1 est celui de B2 */
	B1.taille += B2.taille;   /* nouvelle taille pour B1 */
	return B1;
}

/* Il s'agit de l'implantation de la fonction "simplification douglas becker" adapté au courbe de Bézier de degré 2*/
Liste_Bezier2 simplification_douglas_peucker_bezier2(Tableau_Point Tab,int j1,int j2,double distance_seuil){
    Liste_Bezier2 L=creer_liste_Bezier2_vide();
    double n=(double)(j2-j1);
    Bezier2 B=approx_bezier2(Tab,j1,j2);
    double dmax=0;
    int k=j1;
    for(int j=j1+1;j<=j2;j++){
        double i=(double)(j-j1);
        double t=i/n;
        double dj=distance_bezier2(Tab.tab[j],B,t);
        if (dmax<dj){
            dmax=dj;
            k=j;
        }
    }
    if (dmax<=distance_seuil){
        L=ajouter_element_liste_Bezier2(L,B);
    }else{
        Liste_Bezier2 L1=simplification_douglas_peucker_bezier2(Tab,j1,k,distance_seuil);
        Liste_Bezier2 L2=simplification_douglas_peucker_bezier2(Tab,k,j2,distance_seuil);
        L=concatener_liste_Bezier2(L1,L2);
    }
    return L;
}
/* Je créer une Liste de Liste de courbe de Bézier de degré 2*/
Liste_Liste_Bezier2 creer_liste_liste_Bezier2_vide()
{
	Liste_Liste_Bezier2 L = {0,NULL,NULL};
	return L;
}

/*/* Il s'agit de l'implantation de la fonction "simplification douglas becker" adapté au courbe de Bézier de degré 3*/
Liste_Bezier3 simplification_douglas_peucker_bezier3(Tableau_Point Tab,int j1,int j2,double distance_seuil){
    Liste_Bezier3 L=creer_liste_Bezier3_vide();
    double n=(double)(j2-j1);
    Bezier3 B=approx_bezier3(Tab,j1,j2);
    double dmax=0;
    int k=j1;
    for(int j=j1+1;j<=j2;j++){
        double i=(double)(j-j1);
        double t=i/n;
        double dj=distance_bezier3(Tab.tab[j],B,t);
        if (dmax<dj){
            dmax=dj;
            k=j;
        }
    }
    if (dmax<=distance_seuil){
        L=ajouter_element_liste_Bezier3(L,B);
    }else{
        Liste_Bezier3 L1=simplification_douglas_peucker_bezier3(Tab,j1,k,distance_seuil);
        Liste_Bezier3 L2=simplification_douglas_peucker_bezier3(Tab,k,j2,distance_seuil);
        L=concatener_liste_Bezier3(L1,L2);
    }
    return L;
}

/*J'ajoute une Liste de courbe de Bézier de degré 2 à une Liste de Liste de courbe de Bézier de degré 2 */
Liste_Liste_Bezier2 ajouter_element_liste_liste_Bezier2(Liste_Liste_Bezier2 L, Liste_Bezier2 L1){
	Cellule_Cellule_Liste_Bezier2 *el=(Cellule_Cellule_Liste_Bezier2 *)malloc(sizeof(Cellule_Cellule_Liste_Bezier2));
	el->LB=L1;
	el->suiv=NULL;

	if (L.nb_bezier2 == 0)
	{
		/* premier element de la liste */
		L.first = L.last = el;
	}
	else
	{
		L.last->suiv = el;
		L.last = el;
	}
	L.nb_bezier2++;
	return L;
}

/* Je crée une Liste de courbe de Bézier de degré 3*/
Liste_Bezier3 creer_liste_Bezier3_vide(){
    Liste_Bezier3 B = {0, NULL, NULL};
    return B;
    }
         
Cellule_Bezier3 *creer_element_liste_Bezier3(Bezier3 v){
    Cellule_Bezier3 *el;
    el = (Cellule_Bezier3 *)malloc(sizeof(Cellule_Bezier3));
    if (el==NULL)
        {
            fprintf(stderr, "creer_element_liste_Point : allocation impossible\n");
            exit(-1);
        }
    el->b = v;
    el->suiv = NULL;
    return el;
    }
    
/* ajouter l'element e en fin de la liste de courbe de Bézier de degré 3, renvoie la liste modifiee */
Liste_Bezier3 ajouter_element_liste_Bezier3(Liste_Bezier3 B, Bezier3 e){
    Cellule_Bezier3 *el;
    
    el = creer_element_liste_Bezier3(e);
    if (B.taille == 0)
    {
        /* premier element de la liste */
        B.first = B.last = el;
    }
    else
    {
        B.last->suiv = el;
        B.last = el;
    }
    B.taille++;
    return B;
}

/* concatener B2 a la suite de B1, renvoie la liste B1 modifiee */
Liste_Bezier3 concatener_liste_Bezier3(Liste_Bezier3 B1, Liste_Bezier3 B2){
	/* cas où l'une des deux listes est vide */
	if (B1.taille == 0) return B2; 
	if (B2.taille == 0) return B1;
	
	/* les deux listes sont non vides */
	B1.last->suiv = B2.first; /* lien entre B1.last et B2.first */
	B1.last = B2.last;        /* le dernier element de B1 est celui de B2 */
	B1.taille += B2.taille;   /* nouvelle taille pour B1 */
	return B1;
}

/* Crée une Liste de Liste de courbe de Bézier de degré 3 vide*/
Liste_Liste_Bezier3 creer_liste_liste_Bezier3_vide()
{
	Liste_Liste_Bezier3 L = {0,NULL,NULL};
	return L;
}

/* Ajoute une Liste de courbe de Bézier de degré 3 à la fin d'une Liste de Liste de degré 3*/
Liste_Liste_Bezier3 ajouter_element_liste_liste_Bezier3(Liste_Liste_Bezier3 L, Liste_Bezier3 L1){
	Cellule_Cellule_Liste_Bezier3 *el=(Cellule_Cellule_Liste_Bezier3 *)malloc(sizeof(Cellule_Cellule_Liste_Bezier3));
	el->LB=L1;
	el->suiv=NULL;

	if (L.nb_bezier3 == 0)
	{
		/* premier element de la liste */
		L.first = L.last = el;
	}
	else
	{
		L.last->suiv = el;
		L.last = el;
	}
	L.nb_bezier3++;
	return L;
}

/* Permet d'écrire l'image décrite par des courbes de Bézier de degré 2 */
void ecrire_EPS_mode_pls_contours_bezier2(Liste_Liste_Bezier2 LP, char nom[], UINT l, UINT h) {
    FILE *f = fopen(nom, "w");
    if (!f) {
        fprintf(stderr, "Erreur d'ouverture du fichier %s\n", nom);
        return;
    }

    // En-tête EPS
    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: %d %d %d %d\n", -5, -5, l+5, h+5);

    Cellule_Cellule_Liste_Bezier2 *T52 = LP.first;

    // Parcours de chaque contour représenté par une liste de courbes de Bézier de degré 2
    while (T52 != NULL) {
        // Conversion des courbes de degré 2 en courbes de degré 3
        Liste_Bezier3 B3 = *Liste_B2toB3(T52->LB);
        Cellule_Bezier3 *cel = B3.first;

        // Déplacement initial vers le premier point de départ de la courbe
        if (cel != NULL) {
            double x0 = cel->b.C0.x;
            double y0 = cel->b.C0.y;
            fprintf(f, "%lf %lf moveto\n", x0, h - y0);
        }

        // Écriture des courbes de Bézier cubiques (après conversion)
        while (cel != NULL) {
            double x1 = cel->b.C1.x;
            double y1 = cel->b.C1.y;
            double x2 = cel->b.C2.x;
            double y2 = cel->b.C2.y;
            double x3 = cel->b.C3.x;
            double y3 = cel->b.C3.y;
            fprintf(f, "%lf %lf %lf %lf %lf %lf curveto\n", x1, h - y1, x2, h - y2, x3, h - y3);
            cel = cel->suiv;
        }

        T52 = T52->suiv;
    }

    fprintf(f, "0 setlinewidth fill\n");
    fprintf(f, "showpage\n");
    fclose(f);
}

/* Permet d'écrire l'image décrite par des courbes de Bézier de degré 3 */
void ecrire_EPS_mode_pls_contours_bezier3(Liste_Liste_Bezier3 LP, char nom[], UINT l, UINT h) {
    FILE *f = fopen(nom, "w");
    if (!f) {
        fprintf(stderr, "Erreur d'ouverture du fichier %s\n", nom);
        return;
    }

    // En-tête EPS
    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: %d %d %d %d\n", -5, -5, l+5, h+5);

    Cellule_Cellule_Liste_Bezier3 *T52 = LP.first;

    // Parcours de chaque contour
    while (T52 != NULL) {
        Cellule_Bezier3 *cel = T52->LB.first;

        // Point de départ du tracé
        if (cel != NULL) {
            double x0 = cel->b.C0.x;
            double y0 = cel->b.C0.y;
            fprintf(f, "%lf %lf moveto\n", x0, h - y0);
        }

        // Écriture des courbes de Bézier cubiques
        while (cel != NULL) {
            double x1 = cel->b.C1.x;
            double y1 = cel->b.C1.y;
            double x2 = cel->b.C2.x;
            double y2 = cel->b.C2.y;
            double x3 = cel->b.C3.x;
            double y3 = cel->b.C3.y;
            fprintf(f, "%lf %lf %lf %lf %lf %lf curveto\n", x1, h - y1, x2, h - y2, x3, h - y3);
            cel = cel->suiv;
        }

        T52 = T52->suiv;
    }

    fprintf(f, "0 setlinewidth fill\n");
    fprintf(f, "showpage\n");
    fclose(f);
}

