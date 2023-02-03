#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "liste.c"
#include "abr.c"
#include "avl.c"
#include <string.h>
#define CROISSANT "<"
#define DECROISSANT ">"
int getElement(FILE *f  , Element ** e){
	double x ;
	char y[260];
	
	int r ;
	//printf("element");
	r = fscanf(f , "%lf;%s",&x,y);
	
	if(r==2){
	//	printf("%lf , %s\n" , x , y);
		*e =newElement(x,y);
	}
	else{
		r = fscanf(f , ";%s",y);
		//printf("champ vide , ligne ignoree\n");
		*e=NULL;
	}
	
	//printf(" Ok");
	return r;
	
}

Liste * tri_tab(FILE * f , int (*ordre)(Element * , Element *)){ // tri liste 
	Element * e;
	Liste * l ;
	l=vide();
	//printf("tris tab\n");
	while (getElement(f , &e )!=EOF){
	//	printf("dans while\n");
		if (e!=NULL){
			//printf("on insert dans l\n");
			l=insert_ordre(l , e , ordre );
			//printf("insert OK\n");
		}
	}
	return l;
}

Abr tri_abr(FILE * f , int (*ordre)(Element * , Element *)){ // tri abr
	Element * e;
	Abr a ;
	a = abrVide();
	while (getElement(f , &e )!=EOF){
		if (e!=NULL){
			a=insert_ordreAbr(a , e , ordre );
		}
	}
	return a;
}

Avl tri_avl(FILE * f , int (*ordre)(Element * , Element *)){ //tri avl 
	Element * e;
	Avl a ;
	a = avlVide();
	while (getElement(f , &e )!=EOF){
		if (e!=NULL){
			a=insert_ordreAvl(a , e , ordre );
		}
	}
	return a;
}

int main(int argc , char ** argv ){
	char * tab = "--tab" ;
	char * abr = "--abr\0" ;
	char * abv = "abv\0" ;
	char * stat = "stat\0";
	Avl av ;
	FILE * f ;
	FILE * fs;
	Liste * l;
	Abr a ;
	int (*ordre)(Element * , Element *);
	if(argc > 3 ){
		
		f = fopen(argv[2],"r");
		fs = fopen(argv[3],"w");
		ordre = &inf ;
		if (f==NULL){
			fprintf(stderr , "Erreur fichier inexistant !\n");
			exit(-1);
		}
		if(argc > 4 ){
			if (strcmp (argv[4] , CROISSANT )== 0){
				ordre = &inf ;
			} 
			else if(strcmp (argv[4] , DECROISSANT )== 0){
				ordre = &sup ;
			}
		}
		if(strcmp(argv[1],tab)==0){
			l = tri_tab(f , ordre);
			printListe(l , fs);
		}
		else if(strcmp(argv[1],abr)==0){
			a = tri_abr(f , ordre );
			printAbr( a , fs );
		}
		else{
			//printf("tri avl\n");
			av = tri_avl(f , ordre );
			printAvl( av , fs );
		}
	
		fclose(f);
		fclose(fs);
	}
	else{
		fprintf(stderr , "erreur arguments\n");
	}
	exit (0) ;
	
}

