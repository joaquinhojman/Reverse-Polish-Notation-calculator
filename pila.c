#include "pila.h"
#include <stdlib.h>
#define CAPACIDAD_PILA 10
#include <stdbool.h>

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...
pila_t* pila_crear(void){
	pila_t* pila = malloc(sizeof(pila_t));
	if (pila == NULL) {
        return NULL;
    }
	pila->datos = malloc(CAPACIDAD_PILA * sizeof(void*));
    if (CAPACIDAD_PILA > 0 && pila->datos == NULL) {
        free(pila);
        return NULL;
    }
		pila->cantidad=0;
		pila->capacidad=CAPACIDAD_PILA;
		return pila;
}
bool redimensionar(pila_t* pila,size_t capacidad_nueva){
	void* datos_nuevo = realloc(pila->datos, capacidad_nueva * sizeof(void*));
    if (datos_nuevo == NULL) {
		return false;
    }
	pila->datos=datos_nuevo;
    pila->capacidad = capacidad_nueva;
	return true;
}
void pila_destruir(pila_t *pila){	
	free(pila->datos);
	free(pila);
} 
bool pila_esta_vacia(const pila_t *pila){
	if (pila->cantidad==0)
		return true;
	return false;		
}
bool pila_apilar(pila_t *pila, void* valor){
	if(pila->cantidad==pila->capacidad){
		if(!redimensionar(pila, pila->capacidad*2))
			return false;
    }
	pila->datos[pila->cantidad]=valor;
	pila->cantidad++;
	return true;
}
void* pila_ver_tope(const pila_t *pila){
	if (pila_esta_vacia(pila))
		return NULL;
	return pila->datos[pila->cantidad-1];	
}
void* pila_desapilar(pila_t *pila){
	if (pila_esta_vacia(pila))
		return NULL;
	if(pila->cantidad*4<pila->capacidad&&pila->cantidad>CAPACIDAD_PILA)          
		redimensionar(pila,pila->capacidad/2);
	pila->cantidad--;	
	return pila->datos[pila->cantidad];
}
