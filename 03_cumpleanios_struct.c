/*Escribí una función llamada cumpleanios que reciba una persona por referencia y le sume 1 a la edad. 
En main cargás los datos de una persona, imprimís la edad antes y después de llamar a la función.*/

#include <stdio.h>
#include <stdlib.h>

struct persona{
	char nombre[50];
	short edad;
};

void cumpleanios(struct persona *p){
	p->edad = p->edad + 1;
}

int main(void){
	
	struct persona p1;
	printf("Ingrese el nombre: \n");
	scanf("%49[^\n]", p1.nombre);
	
	printf("Ingrese la edad: \n");
	scanf("%hd", &p1.edad);
	
	printf("El nombre es %s y la edad es %hd \n", p1.nombre, p1.edad);
	
	cumpleanios(&p1);
	
	printf("La nueva edad es: %hd \n", p1.edad);
	
	return 0;
}
