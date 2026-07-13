/*En main vas a cargar personas en un array dinámico con realloc hasta que el usuario decida parar. Después 
imprimís todas las personas cargadas. Agregamos dos funciones: guardar_texto que guarde 
todas las personas en un archivo .txt y guardar_binario que guarde todas las personas en un archivo .bin. 
Ambas tienen que recibir el array por referencia y la cantidad*/

#include <stdio.h>
#include <stdlib.h>

struct persona{
	char nombre [50];
	short edad;
};

void guardar_texto(struct persona *personas, int cantidad){
	FILE *archivo = fopen("datos.txt", "w");
	if(archivo != NULL){
		for(int i=0;i<cantidad;i++){
			fprintf(archivo, "Nombre: %s | Edad: %hd\n", personas[i].nombre, personas[i].edad);
		}
		fclose(archivo);
	}
	else{
		printf("Error al abrir el archivo de texto.\n");
	}
}

void guardar_binario(struct persona *personas, int cantidad){
	FILE *archivo = fopen("datos.bin", "wb");
	if(archivo != NULL){
		fwrite(personas, sizeof(struct persona), cantidad, archivo);
		fclose(archivo);
	}else{
		printf("Error al abrir el archivo binario.\n");
	}
}

int main(void){
	
	struct persona *personas=NULL;
	int cantidad=0;
	int capacidad=0;
	char respuesta;
	
	do{
		struct persona *temp = realloc (personas, (capacidad + 1) * sizeof(struct persona));
		if(temp == NULL){
			free(personas);
			return 1;
		}
		personas=temp;
		capacidad++;
		
		printf("Ingrese el nombre: \n");
		scanf(" %49[^\n]", personas[cantidad].nombre);
		
		printf("Ingrese la edad: \n");
		scanf("%hd", &personas[cantidad].edad);
		
		cantidad ++;
		
		printf("Desea ingresar a otra persona? (s/n): \n");
		scanf(" %c", &respuesta);
		
	}while(respuesta == 's');
	
	printf("\n--- Personas cargadas ---\n");
	for(int i = 0; i < cantidad; i++){
		printf("Nombre: %s | Edad: %hd\n", personas[i].nombre, personas[i].edad);
	}
	
	guardar_texto(personas, cantidad);
	guardar_binario(personas, cantidad);
	printf("Se generaron los archivos .txt y .bin con %d personas\n", cantidad);
	
	free(personas);
	return 0;
}
