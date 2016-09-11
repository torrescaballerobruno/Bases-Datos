#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo{
   char producto[20];
   int cantidad;
   float precio;
   struct nodo *sig;
} Nodo;

Nodo* lista_remover(Nodo *inicio, unsigned int indice);
Nodo* lista_borrar(Nodo *inicio);
void lista_imprimir(Nodo *inicio);
Nodo* lista_ingresar(Nodo *inicio, char prod[20], int cant, double prec);
Nodo* leer_lista(Nodo *inicio);
Nodo* guardar_lista(Nodo *inicio);


int main(int argc, char const *argv[]){
	Nodo *lista=NULL;

	lista = leer_lista(lista);
	lista_imprimir(lista);
	lista = guardar_lista(lista);
	lista_borrar(lista);

	return 0;
}

Nodo* guardar_lista(Nodo *inicio){
	FILE *apu = fopen("datos.txt","w");
	Nodo *nodoActual = inicio;

	while(nodoActual != NULL){
		fprintf(apu,"%s %d %.2lf\n",nodoActual->producto,nodoActual->cantidad,nodoActual->precio);
		nodoActual = nodoActual->sig;
	}

	return inicio;
}

Nodo* leer_lista(Nodo *inicio){
	FILE *apu = fopen("datos.txt","r");
	char prod[20];
	int cant;
	double prec;	
	
	if(!apu){
		printf("Error al abrir el archivo\n");
		return inicio;
	}
	int i=0;
	while(!feof(apu)){
		fscanf(apu,"%s %d %lf\n",prod,&cant,&prec);
		inicio=lista_ingresar(inicio,prod,cant,prec);
	}

	return inicio;
}

Nodo* lista_ingresar(Nodo *inicio, char prod[20], int cant, double prec){
	Nodo *nodoActual = inicio;
	if(inicio==NULL){
		nodoActual = malloc(sizeof(Nodo));
		nodoActual->cantidad = cant;
		nodoActual->precio = prec;
		strcpy(nodoActual->producto,prod);

		nodoActual->sig = NULL;
		inicio = nodoActual;
	}
	else{
		while(nodoActual->sig != NULL){
			nodoActual = nodoActual->sig;
		}
		Nodo *nuevoNodo = malloc(sizeof(Nodo));
		nuevoNodo->cantidad = cant;
		nuevoNodo->precio = prec;
		strcpy(nuevoNodo->producto,prod);
		nuevoNodo->sig = NULL;
		nodoActual->sig = nuevoNodo;
	}
	return inicio;
}

void lista_imprimir(Nodo *inicio){
	Nodo *nodoActual = inicio;
	int i =0;
	printf("    Producto  |  Cantidad |  Precio\n");
	printf("------------------------------------\n");
	while(nodoActual != NULL){
		printf("%d.- %s  |  %d  |  %.2lf\n",++i,nodoActual->producto,nodoActual->cantidad,nodoActual->precio);
		nodoActual = nodoActual->sig;
	}
}

Nodo* lista_borrar(Nodo *inicio){
	if(inicio==NULL){
		return NULL;
	}
	Nodo *nodoActual = inicio;
	Nodo *nodoSig = inicio->sig;
	while(nodoSig != NULL){
		free(nodoActual);
		nodoActual = nodoSig;
		nodoSig = nodoActual->sig;
	}
	free(nodoActual);
	return NULL;
}

Nodo* lista_remover(Nodo *inicio, unsigned int indice){
	Nodo *nodoActual = inicio;
	if(inicio==NULL){
		return NULL;
	}
	else if(indice == 0){
		nodoActual = inicio->sig;
		free(inicio);
		return nodoActual;
	}
	else{
		Nodo *anterior = inicio;
		int i = 0;
		while(i<indice && nodoActual->sig != NULL){
			anterior = nodoActual;
			nodoActual = nodoActual->sig;
			i++;
		}
		anterior->sig = nodoActual->sig;
		free(nodoActual);
		if(i==0){
			return NULL;
		}
	}
	return inicio;
}