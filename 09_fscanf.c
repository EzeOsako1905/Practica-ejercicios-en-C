/*Para practicar fscanf vamos a hacer un ejercicio nuevo donde primero guardamos con fprintf en formato simple, y 
después leemos con fscanf. Escribí una función guardar_simple que guarde los libros así, un libro por línea con 
los campos separados por espacio:*/

#include <stdio.h>
#include <stdlib.h>

struct libro{
	char titulo[60];
	short anio;
	char genero;
};

void guardar_simple(struct libro *libros, int cantidad){
	FILE *archivo=fopen("datos.txt", "w");
	if(archivo!=NULL){
		for(int i=0;i<cantidad;i++){
			fprintf(archivo, "%s %hd %c\n", libros[i].titulo, libros[i].anio, libros[i].genero);
		}
	fclose(archivo);
	}
	else{
		printf("Error al abrir el archivo de texto.\n");
	}
}

void leer_simple(char *nombre_archivo){
	FILE *archivo = fopen(nombre_archivo, "r");
	char titulo[60];
	short anio;
	char genero;
	if(archivo != NULL){
		while(fscanf(archivo, "%59s %hd %c", titulo, &anio, &genero) == 3){
			printf("%s %hd %c\n", titulo, anio, genero);	
		}
	fclose(archivo);
	}
}

int main(void){
	struct libro *libros=NULL;
	int cantidad=0;
	int capacidad=0;
	char respuesta;
	
	do{
		struct libro *temporal = realloc(libros, (capacidad + 1) * sizeof(struct libro));
		if(temporal==NULL){
			free(libros);
			return 1;
		}
		libros = temporal;
		capacidad++;
		
		printf("Ingrese el titulo del libro:\n");
		scanf(" %59[^\n]", libros[cantidad].titulo);
		
		printf("Ingrese el anio de publicacion:\n");
		scanf("%hd", &libros[cantidad].anio);
		
		printf("Ingrese el genero literario (N/C/H):\n");
		scanf(" %c", &libros[cantidad].genero);
		
		cantidad++;
		
		printf("Desea ingresar un nuevo libro? (s/n):\n");
		scanf(" %c", &respuesta);
		
	}while(respuesta=='s');
	
	guardar_simple(libros,cantidad);
	leer_simple("datos.txt");

	free(libros);
	
	return 0;
}
