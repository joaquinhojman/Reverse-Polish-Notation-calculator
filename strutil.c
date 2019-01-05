#define _POSIX_C_SOURCE 200809L

#include "strutil.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char** split(const char* str, char sep){	
	size_t tam=strlen(str);
	unsigned long cant_sep=0;
	for (int i=0;i<tam;i++){
		if (str[i]==sep){
			 cant_sep++;
		}
	}
	if (cant_sep==0){
		char **strv=malloc(sizeof(char*)*2);
		strv[0]=strdup(str);
		strv[1]=NULL;
		return strv;
	}
	cant_sep+=2;
	
	char **strv=malloc(sizeof(char*)*cant_sep);
	if (!strv) return NULL;	
	char *pal;
	int cont=0;
	int cant_strv=0;
	int i=0;
	for (;i<tam;i++){
		if (str[i]==sep){
			pal=malloc(sizeof(char)*(unsigned long)(i+1-cont));
			int aux=0;
			while (cont!=i){
				pal[aux]=str[cont];
				cont++;
				aux++;
			}
			pal[aux]='\0';
			strv[cant_strv]=pal;
			cant_strv++;
			cont++;			
		}		 
	}
	
	if (str[i]!=sep){
	pal=malloc(sizeof(char)*(unsigned long)(i+1-cont));
			int aux=0;
			while (cont!=i){
				pal[aux]=str[cont];
				cont++;
				aux++;
			}
			pal[aux]='\0';
			strv[cant_strv]=pal;
			cant_strv++;	
	}	
	strv[cant_strv]=NULL;	
	
	return strv;
}

char* join(char** strv, char sep){
	size_t str_len=0;
	size_t strv_len=0;
	
	while(strv[strv_len]) {
		str_len+=strlen(strv[strv_len]);
		strv_len++;
	}
	
	char* cadena=malloc(sizeof(char)*(strv_len+str_len+1)); //se pide memoria para cada caracter que tendra el char y uno de mas para '\0'
	if(!cadena) return NULL;
	int pos_cadena=0;
	int pos_strv=0;
	while (strv[pos_strv]!=NULL) {
		for(int pos_str=0;strv[pos_strv][pos_str]!='\0';pos_str++) {
			cadena[pos_cadena]=strv[pos_strv][pos_str];
			pos_cadena++;
		}
		pos_strv++;
		if(!strv[pos_strv]) break;
		cadena[pos_cadena]=sep;
		pos_cadena++;
	}
	cadena[pos_cadena]='\0';
	
	return cadena;
}

void free_strv(char* strv[]){
	for(int i=0;strv[i]!=NULL;i++){
		free(strv[i]);
	}
	free(strv);
}
