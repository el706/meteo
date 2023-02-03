#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
void * alloc(int t){ // allocation memoire
    void * p = malloc(t);
    if (p==NULL){
        fprintf(stderr , "Erreur allocation memoire \n");
        exit (-1);
    }
    else{
        return p;
    }
}

typedef struct { // creation structure 
    double x ;
    char y[260] ;
} Element ;
Element * newElement(double x , char *y ){
    Element * p ;
    p= (Element *)alloc(sizeof(Element));
    p->x = x;
    strcpy(p->y , y);
    return p ;
}

void printElement( FILE * f , Element * p){
   
    if( p == NULL){
        //printf("Element NULL\n");
        ;
    }
    else{
        fprintf(f , "%lf;%s\n", p->x , p->y);
    }
}

int inf (Element * p1 , Element * p2){
	return (p1->x <= p2->x );
}
int sup (Element * p1 , Element * p2){
	return (p1->x >= p2->x );
}
