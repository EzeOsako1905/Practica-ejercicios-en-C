/*Un ejemplo simple: una función que reciba el título, año y género como parámetros y te devuelva un struct libro, 
pero en vez de pasar los valores fijos, pedíselos al usuario con scanf y después llamás a crear_libro con esos 
valores.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct libro {
	char titulo[60];
	short anio;
	char genero;
};

struct libro crear_libro(char *titulo, short anio, char genero){
	
	struct libro nuevo;
	strcpy(nuevo.titulo,titulo);
	nuevo.anio=anio;
	nuevo.genero=genero;
	
	return nuevo;
}

int main(void){
	
	char titulo[60];
	short anio;
	char genero;
	
	printf("Ingrese el titulo:\n");
	scanf(" %59[^\n]", titulo);
	
	printf("Ingrese el anio:\n");
	scanf("%hd", &anio);
	
	printf("Ingrese el genero:\n");
	scanf(" %c", &genero);
	
	struct libro b = crear_libro(titulo, anio, genero);
	printf("Titulo: %s | Anio: %hd | Genero: %c\n", b.titulo, b.anio, b.genero);
	
	/*struct libro b = crear_libro("El Quijote", 1605, 'N');
	printf("Titulo: %s | Anio: %hd | Genero: %c\n", b.titulo, b.anio, b.genero);*/
	
	return 0;
}
