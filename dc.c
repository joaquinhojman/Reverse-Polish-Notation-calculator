#define _POSIX_C_SOURCE 200809L
#include "pila.h"
#include "strutil.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int log_(int base,int val){
	if (val<base) return 0;
	return 1+log_(base,val/base);
}

int sqrt_(int num,int ini,int fin){
	int medio=(ini+fin)/2;
	if ((medio*medio)<=num){
		if ((medio+1)*(medio+1)>num) return medio;
		return sqrt_(num,medio+1,fin);
	}else{
		return sqrt_(num,ini,medio-1);
	}
}

int pow_(int num, int exp){
	int res=1;
	for (int i=0;i<exp;i++) res*=num;
	return res;
}

bool esNum(char* elem){
	int i=0;
	if(elem[0]=='-' && strlen(elem)>1) i=1;
	for (;i<strlen(elem);i++){
		char dig=elem[i];
		if (!isdigit(dig)){
			return false;
		}
	}
	return true;
}

void liberar_memoria(pila_t* pila, char** arreglo){
	pila_destruir(pila);				
	free_strv(arreglo);
}

void eliminar_elems(int* elem1, int* elem2, int* elem3,int* res){
	free(elem1);
	free(elem2);
	free(elem3);
	free(res);
}

void fin_operaciones(pila_t* pila){	
	int* elem=pila_desapilar(pila);
	if (pila_ver_tope(pila)==NULL){
		printf("%d\n",*elem);
	}else{			
		while(!pila_esta_vacia(pila)) free(pila_desapilar(pila));
		printf("ERROR\n");
	}
	eliminar_elems(elem,NULL,NULL,NULL);
}

void dc(){
	char* linea=NULL;
	size_t tam=0;
	__ssize_t leidos=getline(&linea,&tam,stdin);
	while (leidos>=0){
		linea[strlen(linea)-1]='\0';
		char** arreglo=split(linea,' ');
		pila_t* pila=pila_crear();		
		int aux=1;
		int i=0;
		while(arreglo[i]!=NULL){
			if (strlen(arreglo[i])==0){
				i++;
				continue;
			}
			if (esNum(arreglo[i])){
				int *tmp=malloc(sizeof(int));
				*tmp=atoi(arreglo[i]);
				pila_apilar(pila,tmp);
			}else{	
				bool encontro=false;
				int* elem1=pila_desapilar(pila);
				if (elem1==NULL){					
					printf("ERROR\n");
					aux=0;
					break;
				}				
				int e1=*elem1;
				int *res=malloc(sizeof(int));
				*res=0;
				if (strcmp(arreglo[i],"sqrt")==0){	
					if (e1<0){
						printf("ERROR\n");
						aux=0;
						eliminar_elems(elem1,NULL,NULL,res);
						break;
					}
					encontro=true;
					*res=(int)sqrt_(e1,0,e1);
					eliminar_elems(elem1,NULL,NULL,NULL);
					pila_apilar(pila,res);
				}else{
					int* elem2=pila_desapilar(pila);
					if (elem2==NULL){
						aux=0;
						printf("ERROR\n");
						eliminar_elems(elem1,NULL,NULL,res);
						break;
					}
					int e2=*elem2;
					if (*arreglo[i]=='+'){
						encontro=true;
						*res=e1+e2;
						eliminar_elems(elem1,elem2,NULL,NULL);
						pila_apilar(pila,res);
					}
					if (*arreglo[i]=='-'){
						encontro=true;
						*res=e1-e2;					
						eliminar_elems(elem1,elem2,NULL,NULL);
						pila_apilar(pila,res);
					}
					if (*arreglo[i]=='*'){	
						encontro=true;
						*res=e1*e2;					
						eliminar_elems(elem1,elem2,NULL,NULL);
						pila_apilar(pila,res);
					}
					if (*arreglo[i]=='/'){	
						if (e2==0){
							printf("ERROR\n");
							aux=0;
							eliminar_elems(elem1,elem2,NULL,res);
							break;
						}
						encontro=true;
						*res=e1/e2;					
						eliminar_elems(elem1,elem2,NULL,NULL);
						pila_apilar(pila,res);	
					}
					if (*arreglo[i]=='^'){
						encontro=true;
						if (e2<0){
							printf("ERROR\n");
							eliminar_elems(elem1,elem2,NULL,res);
							aux=0;
							break;
						}
						*res=pow_(e1,e2);					
						eliminar_elems(elem1,elem2,NULL,NULL);
						pila_apilar(pila,res);	
					}
					
					if (strcmp(arreglo[i],"log")==0){
						encontro=true;
						if (e2<=1){
							printf("ERROR\n");
							eliminar_elems(elem1,elem2,NULL,res);
							aux=0;
							break;
						}	
						if (e2>e1) *res=0;
						else *res=log_(e2,e1); 					
						eliminar_elems(elem1,elem2,NULL,NULL);
						pila_apilar(pila,res);	
					}
					if (encontro==false){
						int* elem3=pila_desapilar(pila);
						if (elem3==NULL){
							printf("ERROR\n");
							aux=0;
							eliminar_elems(elem1,elem2,NULL,res);
							break;
						}
						int e3=*elem3;
						if (e1!=0){
							*res=e2;
							pila_apilar(pila,res);
						}else{
							*res=e3;
							pila_apilar(pila,res);
						}
						eliminar_elems(elem1,elem2,elem3,NULL);
					}
				}
			}
			i++;
		}
		if (aux!=0)	fin_operaciones(pila);
		liberar_memoria(pila,arreglo);
		leidos=getline(&linea,&tam,stdin);
	}
	free(linea);
}

int main(){
	dc();
	return 0;
}

