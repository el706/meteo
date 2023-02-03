#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "liste.c"


struct  s_abr { // on creer une structure 
    Element * racine;
    struct s_abr * g ; 
    struct s_abr * d ;
} ;
typedef struct s_abr * Abr ;


Abr abrVide(){ // si arbre vide 
	return NULL ;
}
int estAbrVide(Abr a){
	return a== NULL ;
}

Abr cons(Element * e , Abr fg , Abr fd){
	Abr r ;
	r = (Abr) alloc(sizeof(struct s_abr));
	r->racine = e ;
	r->g = fg;
	r->d = fd ;
	return r;	
}
Abr filsDroit(Abr a){
	if(estAbrVide(a)){
		return abrVide();
	}
	else{
		return a->d;
	}
}
Abr filsGauche(Abr a){
	if(estAbrVide(a)){
		return abrVide();
	}
	else{
		return a->g;
	}
}
void changeFilsGauche(Abr a , Abr g){
	if(estAbrVide(a)){
		fprintf(stderr,"Erreur changeFilsGauche : arbre vide !\n");
	}
	else{
		a->g = g ;
	}
}
void changeFilsDroit(Abr a , Abr d){
	if(estAbrVide(a)){
		fprintf(stderr,"Erreur changeFilsDroit : arbre vide !\n");
	}
	else{
		a->d = d ;
	}
}
int estFeuille(Abr a){ // verifier si arbre est feuille
	return estAbrVide( filsDroit(a) ) && estAbrVide( filsGauche(a) ) ;
}
Element * elementAbr(Abr a){
	if( estAbrVide(a) ){
		fprintf(stderr , "Erreur elementAbr : Arbre Vide \n");
		exit(-1);
	}
	else{
		return a->racine ;
	}
}


Abr  insert_ordreAbr(Abr a , Element * p , int (*ordre)(Element * , Element *) ){ // insertion abr 
	Element * pl;
	Abr r , f ;
	if (estAbrVide(a)){
		r = cons (p ,abrVide(),abrVide()) ;
		return r ;
	}
	else{
		pl = elementAbr(a);
		if( (*ordre)(p , pl) ){//insertion a gauche
			f = filsGauche(a);
			r = insert_ordreAbr(f , p , ordre);
			if(f!=r){
				changeFilsGauche(a,r);
			}	
		}
		else{//insertion a droite
			f = filsDroit(a);
			r = insert_ordreAbr(f , p , ordre);
			if(f!=r){
				changeFilsDroit( a, r );
			}
		}

		return a;
	}
}

Element * getPlusGauche(Abr a){
	Abr fg ;
	if(estAbrVide(a)){
		fprintf(stderr , "Erreur getPlusGauche : Abr vide !\n");
		exit (-1);
	}
	else{
		fg = filsGauche(a);
		if (estAbrVide(fg)){
			return elementAbr(a);
		}
		else{
			return getPlusGauche(fg);
		}
	}
	
}

Abr supprPlusGauche(Abr a){ // suppresion 
	Abr fg , r;
	if(estAbrVide(a)){
		fprintf(stderr , "Erreur getPlusGauche : Abr vide !\n");
		exit (-1);
	}
	else{
		if(estFeuille(a)){
			free(a);
			return abrVide();
		}
		else {
			fg = filsGauche(a);
			if (estAbrVide(fg)){
				r = filsDroit(a);
				free(a);
				return r;
			}
			else{
				r = supprPlusGauche(fg);
				if (r!=fg){
					changeFilsGauche(a,r);
				}
				return a;
			}
		}
	}
	
}
void printAbr(Abr a , FILE * f){ // afficher abr 
	if(estAbrVide(a)){
		//printf("Vide");
		;
	}
	else{
		
		
		printAbr(filsGauche(a) ,  f);
		
		printElement(f , elementAbr(a));
		
		printAbr(filsDroit(a) , f);
		
	}
}
/