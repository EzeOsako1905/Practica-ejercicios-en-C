/*Escribí una función llamada intercambiar que reciba dos enteros por referencia y les intercambie los valores.
En main declarás dos variables, las imprimís antes y después de llamar a la función, y verificás que realmente 
cambiaron.*/

#include <stdio.h>
#include <stdlib.h>

void intercambiar(int *a, int *b){
	
	int temporal;
	
	temporal=*a;
	*a=*b;
	*b=temporal;
}

int main(void){
	
	int a = 1;
	int b = 2;
	
	printf("Valores antes del cambio: %d y %d \n", a,b);
	
	intercambiar(&a, &b); //llama a la funcion
	
	printf("Valores despues del cambio: %d y %d \n", a,b);
	
	return 0;
}
