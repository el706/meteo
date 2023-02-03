#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "element.c"


struct  chain { // creation structure 
    Element * hd;
    struct chain * suiv ; 
    struct chain * prec ;
} ;
typedef struct chain * Chainon ;
typedef struct {
    Chainon  it ;
    Chainon  debut ;
    Chainon  fin ;
    Chainon stop ;

}Liste ;

Liste * vide(){ // verification si liste vide 
    Liste * l ;
    l = (Liste * ) alloc(sizeof(Liste));
    l->it = NULL;
    l->debut = NULL;
    l->fin = NULL ;
    l->stop = NULL;

    return l ;
}

int estVide(Liste * l){
    return (l->it == NULL && l->debut == NULL && l->fin == NULL) ;
}
int enDebut(Liste * l){
    return (l->it == NULL);
}
int enFin(Liste * l){
    return (l->it == l->fin);
}
void goFin(Liste *l){
    l->it = l->fin ;
}
int avance(Liste * l){
    if (enDebut(l)){
        l->it = l->debut ;
        return 1 ;
    }
    else if (enFin(l)){
         return 0;
    }
    else{
        if(l->it->suiv == NULL){
            l->it = l->fin;
            return 1;
        }
        else{
            l->it = l->it->suiv ;
            return 1;
        }
    }
}
void goDebut(Liste *l){
    l->it = NULL ;
}

int recule(Liste * l){
    if (enDebut(l)){
        return 0;
    }
    else{
        l->it = l->it->prec ;
        return 1;
    }
}

Liste * insert(Element * x , Liste * l){ // insertion 
    Chainon ch , avant , apres;
    ch = (Chainon )alloc(sizeof(struct chain));
    ch->hd = x ;
    if(estVide(l)){
        l->it = NULL ;
        ch->prec = NULL ;
        ch->suiv = NULL ;
        l->debut = ch;
        l->fin = ch ;
    }
    else if( enDebut(l) ){
        ch->prec = NULL ;
        ch->suiv = l->debut ;
        l->debut->prec = ch ;
        l->debut = ch ;
    }
    else if (enFin(l)){
        ch->suiv = NULL ;
        ch->prec = l->fin ;
        l->fin->suiv = ch;
        l->fin = ch ;
    }
    else {
        apres = l->it->suiv ;
        avant = l->it ;
        ch->suiv = apres;
        ch->prec = avant ;
        apres->prec = ch ;
        avant->suiv = ch ;
        

    }
    return l ;
    
}

Element * get(Liste * l){
    if(l->it==NULL){
        return NULL;
    }
    else{
        return l->it->hd ;
    }

}



void printListe( Liste * l , FILE * f ){ // afficher 
    Element *p ;
    Chainon  ch ;

    if(!estVide(l)){
        ch =  l->it ;
        goDebut(l);
        while(avance(l)){
            p = get(l);
            printElement(f , p);
        
        };
        l->it = ch ;
    }
   
}
Liste * insert_ordre(Liste * l , Element * p , int (*ordre)(Element * , Element *) ){
	Element * pl;
	goDebut(l);
	if (estVide(l)){
		insert(p,l) ;
		return l ;
	}
	else{
		while(avance(l)){
			pl = get(l);
			if( (*ordre)(p , pl) ){
				recule(l);
				insert(p , l);
				return l ;
			}
		}
		insert(p, l);
		return l;
	}
}
