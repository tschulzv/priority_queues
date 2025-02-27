#define _CRT_SECURE_NO_WARNINGS
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
	PrioValue arr = malloc(sizeof(PrioValue) * INITIAL_CAP);
	if (arr == NULL) {
		free(pq);
		return NULL;
	}

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
		if (!_double_size(pq)) return FALSE;
	}

	// crear estructura PrioValue y verificar creación
	PrioValue pv = (PrioValue)malloc(sizeof(struct _PrioValue));
	if (pv == NULL) return FALSE;
	// asignarle los valores
	pv->value = valor;
	pv->prio = prioridad;

	// poner en el índice size + 1 y aumentar el size; luego propagar arriba
	int newIndex = pq->size + 1;
	pq->arr[newIndex] = pv;
	pq->size = newIndex;
	_percolate_up(pq, newIndex);
	
	printf("Se agrego valor %c con prioridad %d\n", *(char*)pv->value, prioridad);
	return TRUE;
}

/*
  Saca el valor de menor prioridad (cima del monticulo) y lo guarda en la posicion retVal (paso por referencia)
  retorna FALSE si tiene un error
  retorna TRUE si tuvo EXITO
*/
BOOLEAN pq_remove(PQ* pq, void** retVal) {
	if (pq == NULL || retVal == NULL) return FALSE;

	// Guardar el nodo que será eliminado
	PrioValue toRemove = pq->arr[1];
	// Devolver el puntero al nodo
	*retVal = toRemove;

	// poner el ultimo elemento en la cima
	pq->arr[1] = pq->arr[pq->size];
	// decrementar el tamaño
	pq->size--;
	// propagar hacia abajo
	_percolate_down(pq, 1);

	return TRUE;
}

/* retorna el tamanho de la cola de prioridad,
   retorna 0 si hubo error
 */
int pq_size(PQ* pq) {
	if (pq == NULL) return 0;
	return pq->size;
}

/* Destruye la cola de prioridad,
retorna TRUE si tuvo exito
retorna FALSE si tuvo error*/
BOOLEAN pq_destroy(PQ* pq) {
	if (pq == NULL) return FALSE;

	// liberar los nodos
	for (int i = 1; i <= pq->size; i++) {
		free(pq->arr[i]);  
	}
	// liberar array y pq
	free(pq->arr);
	free(pq);
	return TRUE;
}

// FUNCIONES ADICIONALES AGREGADAS -----------

/* Realiza la operación de propagar arriba*/
void _percolate_up(PQ* pq, int i) {
	if (pq == NULL || i <= 1) return; // caso base

	// calcular el padre
	int pa = i / 2;

	// si el padre tiene mayor prioridad que el nuevo, intercambiar y propagar arriba recursivamente
	if (pq->arr[pa]->prio > pq->arr[i]->prio) {
		PrioValue temp = pq->arr[pa];
		pq->arr[pa] = pq->arr[i];
		pq->arr[i] = temp;
		_percolate_up(pq, pa);
	}
}

/* Realiza la operación de propagar abajo */
void _percolate_down(PQ* pq, int i) {
	if (pq == NULL || i >= pq->size) return; // caso base
	
	// calcular hijos 
	int left = i * 2;
	int right = i * 2 + 1;
	int lowest = i; // iniciar asumiendo que el padre es el menor

	// si el hijo izq existe y es menor al padre, es lowest actual 
	if (left <= pq->size && pq->arr[left]->prio < pq->arr[lowest]->prio) {
		lowest = left;
	}
	// luego, verificar si el derecho existe y si es menor a lowest actual
	if (right <= pq->size && pq->arr[right]->prio < pq->arr[lowest]->prio) {
		lowest = right;
	}

	// si lowest es diferente al padre, intercambiamos y propagamos abajo
	if (lowest != i) {
		PrioValue temp = pq->arr[i];
		pq->arr[i] = pq->arr[lowest];
		pq->arr[lowest] = temp;
		_percolate_down(pq, lowest);
	}

	/*
	if (der <= pq->size) {

		// si el izq es el menor y también es menor al padre, si es intercambiar con él y propagar abajo recursivamente
		if (pq->arr[izq]->prio < pq->arr[der]->prio && pq->arr[izq]->prio < pq->arr[i]->prio) {
			PrioValue temp = pq->arr[i];
			pq->arr[i] = pq->arr[izq];
			pq->arr[izq] = temp;
			_percolate_down(pq, izq);
		}
		else if (){
			_percolate_down(pq, der);
		}
	}
	*/
	

}


/* Duplica el tamaño del arreglo de la PQ, copiando sus elementos existentes*/
BOOLEAN _double_size(PQ* pq) {
	if (pq == NULL) return FALSE;

	// verificar si la capacidad se desbordará antes de multiplicar
	if (pq->cap > SIZE_MAX / (2 * sizeof(PrioValue))) return FALSE;

	// crear un nuevo arreglo y verificar su creación
	PrioValue* newArr = malloc((size_t)pq->cap * 2 * sizeof(PrioValue));

	// crear un nuevo arreglo y verificar su creación
	//PrioValue* newArr = malloc(sizeof(PrioValue) * (pq->cap * 2));
	if (newArr == NULL) return FALSE;

	// copiar contenidos del arreglo viejo al nuevo
	for (int i = 1; i <= pq->size; i++) {
		newArr[i] = pq->arr[i];
	}

	// liberar arreglo viejo y asignar el nuevo arreglo a la pq
	free(pq->arr);
	pq->arr = newArr;
	pq->cap = pq->cap * 2;

	return TRUE;

}


/* Imprime un PQ */
void print_pq(PQ* pq) {
	if (pq == NULL) return;
	printf("\n");
	// recorrer la pq e imprimir cada valor
	for (int i = 1; i <= pq->size; i++) {
		printf("%c|", *(char*)(pq->arr[i]->value));
	}	
}

