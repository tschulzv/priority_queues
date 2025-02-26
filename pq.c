#include "pq.h"
#include <stdlib.h>


/* Crea la cola de prioridad PQ e inicializa sus atributos
retorna un puntero a la cola de prioridad
retorna NULL si hubo error*/
PQ* pq_create() {
	// crear el PQ y verificar su creacion
	PQ *pq = (PQ*)malloc(sizeof(struct Heap));
	if (pq == NULL) return NULL;

	// crear el array y verificar su creacion
	PrioValue *arr = (PrioValue*)malloc(sizeof(PrioValue) * INITIAL_CAP);
	if (arr == NULL) return NULL;

	// asignar valores
	pq->arr = arr;
	pq->cap = INITIAL_CAP;
	pq->size = 0;
	return pq;
}

/*
Agrega un valor a la cola con la prioridad dada

retorna TRUE si tuvo exito, FALSE si no
*/
BOOLEAN pq_add(PQ* pq, void* valor, int prioridad) {
	// validar argumentos
	if (pq == NULL) return FALSE;
	if (valor == NULL) return FALSE;
	if (prioridad < 0) return FALSE; // se puede usar prioridad negativa???

	// verificar si pq esta lleno, si es asi, agrandar
	if (pq->size == pq->cap) {
		_double_size(pq);
	}

	// crear estructura PrioValue y verificar creación
	PrioValue pv = (PrioValue)malloc(sizeof(struct _PrioValue));
	if (pv == NULL) return FALSE;
	// asignarle los valores
	pv->value = valor;
	pv->prio = prioridad;

	// poner en el índice size + 1; luego propagar arriba
	int newIndex = pq->size + 1;
	pq->arr[newIndex] = pv;
	_percolate_up(pq, newIndex);
	
	return TRUE;
}

/*
  Saca el valor de menor prioridad (cima del monticulo) y lo guarda en la posicion retVal (paso por referencia)
  retorna FALSE si tiene un error
  retorna TRUE si tuvo EXITO
*/
BOOLEAN pq_remove(PQ* pq, void** retVal) {

	/* AGREGUE SU CODIGO AQUI */
	*retVal = pq->arr[1]->value;
	return TRUE;
}

/* retorna el tamanho de la cola de prioridad,
   retorna 0 si hubo error
 */
int pq_size(PQ* pq) {
	if (pq == NULL) return NULL;
	return pq->size;
}

/* Destruye la cola de prioridad,
retorna TRUE si tuvo exito
retorna FALSE si tuvo error*/
BOOLEAN pq_destroy(PQ* pq) {

	/* AGREGUE SU CODIGO AQUI */
	return TRUE;
}
