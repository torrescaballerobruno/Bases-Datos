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
Nodo* editar_lista(Nodo *inicio);
int logueo (void);
int menu (Nodo *lista);

int main(int argc, char const *argv[]){
	Nodo *lista=NULL;


	if (logueo()==1){
		lista = leer_lista(lista);
		menu(lista);
	}else{
		printf("Demasiados intentos...\n");
	}
	return 0;
}

int menu(Nodo *lista){
	int opc,elim,agreCant;
	float agrePrec;
	char agreProd[20];
	
	do{
		system("clear");
		printf("\n\t\tBienvenido a la Prebetienda\n");
		printf("\t1) Imprimir el inventario\n");
		printf("\t2) Modificar algun producto\n");
		printf("\t3) Eliminar algun producto\n");
		printf("\t4) Agregar algun producto\n");
		printf("\t5) Salir\n");
		printf("Seleccione alguna opcion:  ");
		scanf("%d",&opc);

		switch(opc){
			case 1:
				system("clear");
				lista_imprimir(lista);
				getchar();
				getchar();
				break;
			case 2:
				system("clear");
				editar_lista(lista);
				getchar();
				getchar();
				break;
			case 3:
				system("clear");
				lista_imprimir(lista);
				printf("\n\nQue producto desea eliminar:  ");
				scanf("%d",&elim);
				lista_remover(lista,elim);
				printf("Se elimino el productor\n");
				getchar();
				getchar();
				break;
			case 4:
				system("clear");
				printf("Nombre del producto a agregar(sin espacios,puede usar guiones):  ");
				scanf("%s",agreProd);
				printf("Precio del nuevo producto:  ");
				scanf("%f",&agrePrec);
				printf("Cantidad en inventario:  ");
				scanf("%d",&agreCant);
				lista_ingresar(lista,agreProd,agreCant,agrePrec);
				printf("Se agrego satisfactoriamente el producto\n");
				getchar();
				getchar();
				break;
			case 5:
				system("clear");
				lista = guardar_lista(lista);
				lista_borrar(lista);
				printf("\n\n\n\n\n\t\t\tGracias por usar la Prebetienda");
				getchar();
				getchar();
				system("clear");
				break;
			default:
				printf("Opcion invalida\n");
				getchar();
				getchar();
		}
	}while(opc!=5);

	return 0;

}

int logueo (void){
	int cont=0;
	char usr[16], pass[16];

	do{
		system("clear");
		printf("\n\n\t\t\tInicio de sesión:");
		printf("\n\n\t\t\tUsuario: ");
		scanf(" %s", usr);
		printf("\n\t\t\tContraseña: ");
		scanf(" %s", pass);

		if (strcmp(usr,"Donaldo")==0 && strcmp(pass, "1994") == 0){
			return 1;
		}else if (strcmp(usr,"Bruno") == 0 && strcmp(pass, "1996") == 0){
			return 1;
		}else {
				printf("\n\n\t\tAcceso denegado");
				getchar();
				getchar();
		}
		cont++;
	}while(cont <4);

	return 0;
}

Nodo* editar_lista(Nodo *inicio){
	Nodo *nodoActual = inicio;
	int indice,opcion,nuevoCantidad, i=1;
	float nuevoPrecio;

	lista_imprimir(inicio);
	printf("Seleccione el articulo que quiera modificar #:  ");
	scanf("%d",&indice);

	while(i<indice && nodoActual != NULL){
		nodoActual = nodoActual->sig;
		i++;
	}
	do{
		system("clear");
		printf("\tQue desea modificar\n\n1)    Precio\n2)    Cantidad\n3)    Salir\nSeleccione una opcion:  ");
		scanf("%d",&opcion);

		switch(opcion){
			case 1:
				printf("Precio anterior:\t%.2lf\n",nodoActual->precio);
				printf("Nuevo Precio:  ");
				scanf("%f",&nuevoPrecio);
				nodoActual->precio=nuevoPrecio;
				break;
			case 2:
				printf("Cantidad anterior:\t%d\n",nodoActual->cantidad);
				printf("Nueva cantidad:	 ");
				scanf("%d",&nuevoCantidad);
				nodoActual->cantidad=nuevoCantidad;
				break;
			case 3:
				break;
			default:
				printf("Opcion no valida\n");

		}
	}while(opcion!=3);

	return inicio;
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
	system("clear");
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
