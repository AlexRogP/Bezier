#include<stdio.h>
#include<stdlib.h> 
#include <stdbool.h>
#include "exemple_sequence_point.h"
#include "geom2d.h"
#include "image.h"
#include "contours.h"


/* creer une cellule de liste avec l'element v 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_Point *creer_element_liste_Point(Point v)
{
	Cellule_Liste_Point *el;
	el = (Cellule_Liste_Point *)malloc(sizeof(Cellule_Liste_Point));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste_Point : allocation impossible\n");
		exit(-1);
	}
	el->data = v;
	el->suiv = NULL;
	return el;
}
/* creer une liste vide */
Liste_Point creer_liste_Point_vide()
{
	Liste_Point L = {0, NULL, NULL};
	return L;
}

/* ajouter l'element e en fin de la liste L, renvoie la liste L modifiee */
Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e)
{
	Cellule_Liste_Point *el;
	
	el = creer_element_liste_Point(e);
	if (L.taille == 0)
	{
		/* premier element de la liste */
		L.first = L.last = el;
	}
	else
	{
		L.last->suiv = el;
		L.last = el;
	}
	L.taille++;
	return L;
}

/* supprimer tous les elements de la liste, renvoie la liste L vide */
Liste_Point supprimer_liste_Point(Liste_Point L)
{
	Cellule_Liste_Point *el=L.first;
	
	while (el) 
	{		
		Cellule_Liste_Point *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL; L.taille = 0;
	return L;
}

/* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */
Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2)
{
	/* cas o� l'une des deux listes est vide */
	if (L1.taille == 0) return L2; 
	if (L2.taille == 0) return L1;
	
	/* les deux listes sont non vides */
	L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
	L1.last = L2.last;        /* le dernier element de L1 est celui de L2 */
	L1.taille += L2.taille;   /* nouvelle taille pour L1 */
	return L1;
}

/* si la liste est non vide, la fonction supprime le premier element de L 
   si la liste est vide, la fonction ne fait rien 
   la fonction renvoie la liste (eventuellement) modifiee */
Liste_Point supprimer_premier_element_liste_Point(Liste_Point L)
{
	/* cas d'une liste L vide : ne rien faire */
	if (L.taille == 0) return L;
	
	Cellule_Liste_Point *e1=L.first;  /* pointeur vers le premier element  */ 
	Cellule_Liste_Point *e2=e1->suiv; /* pointeur vers le deuxieme element */ 
	
	/* supprimer l'element pointe par e1 */
	free(e1);
	
	/* mettre a jour la structure L */
	L.first = e2;
	if (e2 == NULL)    /* cas d'une liste L avec un seul element */
		L.last = NULL; /* --> la liste L devient une liste vide  */
	L.taille--;
	return L;
}


/* creer une sequence de points sous forme d'un tableau de points 
   a partir de la liste de points L */
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L)
{
	Tableau_Point T;
	
	/* taille de T = taille de L */
	T.taille = L.taille;
	
	/* allocation dynamique du tableau de Point */
	T.tab = malloc(sizeof(Point) * T.taille);
	if (T.tab == NULL)
	{
		/* allocation impossible : arret du programme avec un message */
		fprintf(stderr, "sequence_points_liste_vers_tableau : ");
		fprintf(stderr, " allocation impossible\n");
		exit(-1);
	}
	
	/* remplir le tableau de points T en parcourant la liste L */
	int k = 0; /* indice de l'element dans T.tab */
	Cellule_Liste_Point *el = L.first; /* pointeur sur l'element dans L */
	while (el) 
	{
		T.tab[k] = el->data;
		k++; /* incrementer k */
		el = el->suiv; /* passer a l'element suivant dans la liste chainee */
	}
	
	return T;
}

/* ecrire le contour L a l'ecran 
   cette fonction montre un exemple de conversion d'une liste de points en
   tableau de points afin de pouvoir par la suite acceder aux elements d'une
   sequence de points par indice */
void ecrire_contour(Liste_Point L)
{
	Tableau_Point TP = sequence_points_liste_vers_tableau(L);
	int k;
	int nP = TP.taille;
	
	printf("Contour avec %d points\n[", nP);
	for (k = 0; k < nP; k++)
	{	
		Point P = TP.tab[k]; /* recuperer le point d'indice k */
		printf(" (%5.1f,%5.1f)", P.x, P.y);
	} 
	printf("]\n");
	
	free(TP.tab); /* supprimer le tableau de point TP */
}


Liste_Point memoriser_position_partie_2(Liste_Point LP,Point p){
	LP=ajouter_element_liste_Point(LP,p);
	return LP;
}


Liste_Point liste_chaine_contours(Image I){
	Point p=trouver_point_depart(I);
	Liste_Point LP=creer_liste_Point_vide();
    if (p.x<0 || p.y<0){
        printf("Aucun point de départ trouver\n");
        return LP;
    }
    Point Position=p;
    Orientation O=Est;
    bool boucle=true;
    while(boucle){
       LP=memoriser_position_partie_2(LP,p);
        p=avancer(p,O);
        O=nouvelle_orientation(I,p,O);
        if (Position.x==p.x && Position.y==p.y && O==Est){
            boucle=false;
        }
    }
    LP=memoriser_position_partie_2(LP,p);
	return LP;
}

void afficher_segment(Image I){
	Point p=trouver_point_depart(I);
    if (p.x<0 || p.y<0){
        printf("Aucun point de départ trouver\n");
        return;
    }
    Point Position=p;
    Orientation O=Est;
    bool boucle=true;
    while(boucle){
        memoriser_position_partie_1(p);
        //afficher_orientation(O);
        p=avancer(p,O);
        O=nouvelle_orientation(I,p,O);
        if (Position.x==p.x && Position.y==p.y && O==Est){
            boucle=false;
        }
        printf(",");
    }
    memoriser_position_partie_1(p);
    printf("\n");
}

int nombre_point(Liste_Liste_Point L){
	Cellule_Cellule_Liste_Point *cel=L.first;
	int nb_point=0;
	while(cel!=NULL){
		nb_point=nb_point+cel->LP.taille;
		cel=cel->suiv;
	}
	return nb_point;

}

Liste_Liste_Point creer_liste_liste_Point_vide()
{
	Liste_Liste_Point L = {0,0,NULL,NULL};
	return L;
}

Liste_Liste_Point ajouter_element__liste_liste_Point(Liste_Liste_Point L, Liste_Point L1){
	Cellule_Cellule_Liste_Point *el=(Cellule_Cellule_Liste_Point *)malloc(sizeof(Cellule_Cellule_Liste_Point));
	el->LP=L1;
	el->suiv=NULL;

	if (L.nb_contours == 0)
	{
		/* premier element de la liste */
		L.first = L.last = el;
	}
	else
	{
		L.last->suiv = el;
		L.last = el;
	}
	L.nb_contours++;
	L.nb_points=nombre_point(L);
	return L;
}

void ecrire_contours_Liste_Liste(Liste_Liste_Point LP){
	Cellule_Cellule_Liste_Point *cel=LP.first;
	while(cel!=NULL){
		ecrire_contour(cel->LP);
		cel=cel->suiv;
	}
}
























// int main()
// {
// 	Contour C1,C2;
	
// 	/* initialiser C1 comme contour vide */
// 	C1 = creer_liste_Point_vide();
// 	printf("C1 : "); ecrire_contour(C1);

// 	/* ajouter les points (5,3),(3,1),(7,2) et (1,6) dans C1 */
// 	C1 = ajouter_element_liste_Point(C1, set_point(5,3));
// 	C1 = ajouter_element_liste_Point(C1, set_point(3,1));
// 	C1 = ajouter_element_liste_Point(C1, set_point(7,2));
// 	C1 = ajouter_element_liste_Point(C1, set_point(1,6));
// 	printf("C1 : "); ecrire_contour(C1);

// 	/* supprimer le premier point de C1, puis ajouter le point (4,1) dans C1 */
// 	C1 = supprimer_premier_element_liste_Point(C1);
// 	C1 = ajouter_element_liste_Point(C1, set_point(4,1));
// 	printf("C1 : "); ecrire_contour(C1);

// 	/* creer le contour C2 avec les points (9,5) et (5,7) */
// 	C2 = creer_liste_Point_vide();	
// 	C2 = ajouter_element_liste_Point(C2, set_point(9,5));
// 	C2 = ajouter_element_liste_Point(C2, set_point(5,7));
// 	printf("C2 : "); ecrire_contour(C2);

// 	/* concatener C2 a la suite de C1 */
// 	C1 = concatener_liste_Point(C1,C2);
// 	printf("C1 : "); ecrire_contour(C1);

// 	/* supprimer le contour C1 */
// 	C1 = supprimer_liste_Point(C1);
// 	printf("C1 : "); ecrire_contour(C1);
// } // fin du programme
