/*En main vas a cargar personas en un array dinámico con realloc hasta que el usuario decida parar. Después 
imprimís todas las personas cargadas. Agregamos dos funciones: guardar_texto que guarde 
todas las personas en un archivo .txt y guardar_binario que guarde todas las personas en un archivo .bin. 
Ambas tienen que recibir el array por referencia y la cantidad. Agregamos una función que busque todas las 
personas que tengan una edad determinada e imprima sus datos. Si no encuentra ninguna, informa que no se encontró.*/

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

void buscar_por_edad(struct persona *personas, int cantidad, short edad_buscada){
	int encontrados=0;
	
	for(int i=0;i<cantidad;i++){
		if(personas[i].edad == edad_buscada){
			printf("Nombre: %s | Edad: %hd\n",personas[i].nombre, personas[i].edad);
			encontrados++;
		}
	}
	if(encontrados == 0){
		printf("No se encontro la edad buscada.\n");
	}
}

float porcentaje_por_edad(struct persona *personas, int cantidad, short edad_porcentaje){
	int contador=0;
	
	if(cantidad==0){
		return 0;
	}
	for(int i=0;i<cantidad;i++){
		if(personas[i].edad == edad_porcentaje){
			contador ++;
		}
	}
	return ((float)contador * 100) / cantidad;
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
		
		printf("Ingrese el nombre/s: \n");
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
	
	short edad_buscada;
	printf("\nIngrese la edad a buscar: \n");
	scanf("%hd", &edad_buscada);
	buscar_por_edad(personas, cantidad, edad_buscada);
	
	short edad_porcentaje;
	printf("Ingrese la edad para calcular el porcentaje\n");
	scanf("%hd", &edad_porcentaje);
	
	float porcentaje = porcentaje_por_edad(personas, cantidad, edad_porcentaje);
	printf("El porcentaje de personas con esa edad es de %.2f%%\n", porcentaje);
	
	guardar_texto(personas, cantidad);
	guardar_binario(personas, cantidad);
	printf("\nSe generaron los archivos .txt y .bin con %d personas\n", cantidad);
	
	free(personas);
	return 0;
}
