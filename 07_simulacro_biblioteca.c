/*Una biblioteca registrará sus libros. Por cada libro se registrará:
Título, hasta 60 caracteres
Año de publicación (número entero sin decimales)
Género (puede ser Novela, Ciencia ficción o Historia)
Se sabe que no se conoce de antemano cuántos libros habrá.
Se pide:
Almacenar en memoria todos los libros
Una función que genere un archivo de texto con todos los datos de cada libro
Una función que genere un archivo binario con todos los datos
Una función que busque todos los libros de un determinado género e imprima los encontrados, informando si no se
encontró ninguno.
Una función que calcule el porcentaje de libros por género — se piden los tres porcentajes, impresos desde main()
Restricciones:
No se permiten variables globales
La carga y la impresión de resultados solo en main()
Cada función debe tener al menos un parámetro por referencia
Solo C, debe compilar sin errores*/

#include <stdio.h>
#include <stdlib.h>

struct libro{
	char titulo[60];
	short anio;
	char genero; //(N)Novela, (C)Ciencia ficcion, (H)Historia
};

void guardar_texto(struct libro *libros, int cantidad){
	FILE *archivo=fopen("datos.txt", "w");
	if(archivo!=NULL){
		for(int i=0;i<cantidad;i++){
			fprintf(archivo, "Titulo: %s | Anio: %hd | Genero: %c\n", libros[i].titulo, libros[i].anio, libros[i].genero);
		}
	fclose(archivo);
	}
	else{
		printf("Error al abrir el archivo de texto.\n");
	}
}

void guardar_binario(struct libro *libros, int cantidad){
	FILE *archivo=fopen("datos.bin", "wb");
	if(archivo!=NULL){
		fwrite(libros, sizeof(struct libro), cantidad, archivo);
		fclose(archivo);
	}
	else{
		printf("Error al abrir el archivo binario.\n");
	}
}

void buscar_por_genero(struct libro *libros, int cantidad, char genero_buscado){
	int encontrados=0;
	for(int i=0;i<cantidad;i++){
		if(libros[i].genero==genero_buscado){
			printf("Titulo: %s | Anio: %hd | Genero: %c\n", libros[i].titulo, libros[i].anio, libros[i].genero);
			encontrados++;
		}
	}
	if(encontrados==0){
		printf("No se encontro el genero buscado\n");
	}
}

float porcentaje_por_genero(struct libro *libros, int cantidad, char genero_porcentaje){
	int contador=0;
	if(cantidad==0){
		return 0;
	}
	for(int i=0;i<cantidad;i++){
		if(libros[i].genero==genero_porcentaje){
			contador++;
		}
	}
	return ((float)contador * 100) / cantidad;
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
	
	printf("Libros cargados\n");
	for(int i=0;i<cantidad;i++){
		printf("Titulo: %s | Anio: %hd | Genero: %c\n", libros[i].titulo, libros[i].anio, libros[i].genero);
	}
	
	char genero_buscado;
	printf("Seleccione un genero (N/C/H)\n");
	scanf(" %c", &genero_buscado);
	buscar_por_genero(libros, cantidad, genero_buscado);
	
	char genero_porcentaje;
	printf("Ingrese la categoria para calcular el porcentaje (N/C/H): \n");
	scanf(" %c", &genero_porcentaje);
	
	float porcentaje = porcentaje_por_genero(libros, cantidad, genero_porcentaje);
	printf("El porcentaje de libros por categoria es: %.2f%%\n", porcentaje);
	
	guardar_texto(libros, cantidad);
	guardar_binario(libros, cantidad);
	printf("Se generaron los archivos .txt y .bin con %d libros.\n", cantidad);
	
	free(libros);
	
	return 0;
}
