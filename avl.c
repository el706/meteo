#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "abr.c"


struct  s_avl { // on creer la structure 
    Element * racine;
    struct s_avl * g ; 
    struct s_avl * d ;
    struct s_avl * pere ;
    int profondeur ;
} ;
typedef struct s_avl * Avl ;


Avl avlVide(){ // on verifie si avl vide
	return NULL ;
}
int estAvlVide(Avl a){
	return a== NULL ;
}
int profondeur(Avl a){ // calcul de la profondeur 
	if (estAvlVide(a)){
		return 0;
	}
	else{
		return a->profondeur ;
	}
}
Avl consAvl(Element * e , Avl fg , Avl fd){
	Avl r ;
	int pg , pd;
	r = (Avl) alloc(sizeof(struct s_avl));
	r->racine = e ;
	r->g = fg;
	r->d = fd ;
	pg = profondeur(fg);
	pd = profondeur(fd);
	if (pd > pg){
		r->profondeur = pd+1;
	}
	else{
		r->profondeur = pg+1;
	}
	r->pere = NULL;
	if (!estAvlVide(fd)){
		fd->pere = r;
	}
	if (!estAvlVide(fg)){
		fg->pere = r;
	}
	return r;
	
}
Avl fislDroitAvl(Avl a){  // verifie si fils droit 
	if(estAvlVide(a)){
		return avlVide();
	}
	else{
		return a->d;
	}
}
Avl fislGaucheAvl(Avl a){
	if(estAvlVide(a)){
		return avlVide();
	}
	else{
		return a->g;
	}
}
Avl pere(Avl a){
	if(estAvlVide(a)){
		return avlVide();
	}
	else{
		return a->pere;
	}
}
void changefislGaucheAvl(Avl a , Avl g){
	int pg , pd ;
	if(estAvlVide(a)){
		fprintf(stderr,"Erreur changefislGaucheAvl : arvle vide !\n");
	}
	else{
		a->g = g ;
		g->pere = a;
	}
	pg = profondeur(a->g);
	pd = profondeur(a->d);
	if(pg > pd){
		a->profondeur = pg +1;
	}
	else{
		a->profondeur = pd +1;
	}
}
void changefislDroitAvl(Avl a , Avl d){
	int pg , pd ;
	if(estAvlVide(a)){
		fprintf(stderr,"Erreur changefislDroitAvl : arbre vide !\n");
	}
	else{
		a->d = d ;
		d->pere = a;
	}
	pg = profondeur(a->g);
	pd = profondeur(a->d);
	if(pg > pd){
		a->profondeur = pg +1;
	}
	else{
		a->profondeur = pd +1;
	}
}
int estFeuilleAvl(Avl a){ // verifie si feuille
	return estAvlVide( fislDroitAvl(a) ) && estAvlVide( fislGaucheAvl(a) ) ;
}
Element * elementAvl(Avl a){
	if( estAvlVide(a) ){
		fprintf(stderr , "Erreur elementAbr : Arbre Vide \n");
		exit(-1);
	}
	else{
		return a->racine ;
	}
}


Avl  insert_ordreAvl(Avl a , Element * p , int (*ordre)(Element * , Element *) ){ // insertion
	Element * pl;
	Avl r , f ;
	//printf("insert element\n");
	if (estAvlVide(a)){
		//printf("a vide\n");
		r = consAvl (p ,avlVide(),avlVide()) ;
		return r ;
	}
	else{
		pl = elementAvl(a);
		if( (*ordre)(p , pl) ){//insertion a gauche
			f = fislGaucheAvl(a);
			r = insert_ordreAvl(f , p , ordre);
			if(f!=r){
				changefislGaucheAvl(a,r);
			}	
		}
		else{//insertion a droite
			f = fislDroitAvl(a);
			r = insert_ordreAvl(f , p , ordre);
			if(f!=r){
				changefislDroitAvl( a, r );
			}
		}

		return a;
	}
}

Element * getPlusGauche(Avl a){
	Avl fg ;
	if(estAvlVide(a)){
		fprintf(stderr , "Erreur getPlusGauche : Avl vide !\n");
		exit (-1);
	}
	else{
		fg = fislGaucheAvl(a);
		if (estAvlVide(fg)){
			return elementAvl(a);
		}
		else{
			return getPlusGauche(fg);
		}
	}
	
}

Avl supprPlusGauche(Avl a){ // supprimer a gauche 
	Avl fg , r;
	if(estAvlVide(a)){
		fprintf(stderr , "Erreur getPlusGauche : Avl vide !\n");
		exit (-1);
	}
	else{
		if(estFeuille(a)){
			free(a);
			return avlVide();
		}
		else {
			fg = fislGaucheAvl(a);
			if (estAvlVide(fg)){
				r = fislDroitAvl(a);
				free(a);
				return r;
			}
			else{
				r = supprPlusGauche(fg);
				if (r!=fg){
					changefislGaucheAvl(a,r);
				}
				return a;
			}
		}
	}
	
}

void affAvl(Avl a){ // afficher 
	if(estAvlVide(a)){
		printf("Vide");
	}
	else{
		printf("{ " );
		
		affAvl(fislGaucheAvl(a));
		printf(" , ");
		affElement(elementAvl(a));
		printf(" , ");
		affAvl(fislDroitAvl(a));
		printf(" }");
	}
}


