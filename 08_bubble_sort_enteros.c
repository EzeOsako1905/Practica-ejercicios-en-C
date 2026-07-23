/*Ordenamiento burbuja. La idea es simple: recorrés el array comparando elementos de a pares. Si el de la izquierda 
es mayor que el de la derecha, los intercambiás. Repetís eso hasta que no haya más intercambios.*/

#include <stdio.h>
#include <stdlib.h>

void ordenar_por_anio(int *array, int cantidad){
	int temporal=0;
	for(int i=0;i<cantidad-1;i++){
		for(int j=0;j<cantidad-i-1;j++){
			if(array[j]>array[j+1]){
				temporal=array[j];
				array[j]=array[j+1];
				array[j+1]=temporal;
			}
		}
	}
}

int main(void){
	int numeros[]={23,26,13,2,3,20,5,24,9,15,10};
	int cantidad=11;
	
	printf("Array sin ordenar: ");
	for(int i=0;i<cantidad;i++){
		printf("%d ", numeros[i]);	
	}
	printf("\n");
	
	ordenar_por_anio(numeros,cantidad);
	
	printf("Array ordenado: ");
	for(int i=0;i<cantidad;i++){
		printf("%d ", numeros[i]);
	}
	printf("\n");
	
	return 0;
}
