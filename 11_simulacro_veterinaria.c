/*Una veterinaria registrará los animales que atiende. Por cada animal se registrará:
Nombre del animal, hasta 40 caracteres
Edad (número entero sin decimales)
Especie (puede ser Perro, Gato o Conejo)
Se sabe que no se conoce de antemano cuántos animales habrá.
Se pide:
Almacenar en memoria todos los animales
Una función que genere un archivo de texto con todos los datos de cada animal
Una función que genere un archivo binario con todos los datos
Una función que busque todos los animales de una determinada especie e imprima los encontrados, informando si no 
se encontró ninguno
Una función que calcule el porcentaje de animales por especie — se piden los tres porcentajes, impresos desde main
Bonus (opcional): ordenar los animales por edad antes de imprimirlos.
Restricciones:
No se permiten variables globales
La carga y la impresión de resultados solo en main()
Cada función debe tener al menos un parámetro por referencia
Solo C, debe compilar sin errores*/

#include <stdio.h>
#include <stdlib.h>

struct animal{
	char nombre[40];
	short edad;
	char especie; // Perro (P) | Gato (G) | Conejo (C)
};

void guardar_texto(struct animal *animales, int cantidad){
	FILE *archivo=fopen("datos.txt", "w");
	if(archivo!=NULL){
		for(int i=0;i<cantidad;i++){
			fprintf(archivo, "Nombre: %s | Edad: %hd | Especie: %c\n", animales[i].nombre, animales[i].edad, animales[i].especie);
		}
	fclose(archivo);	
	}
	else{
		printf("Error al guardar el archivo de texto.\n");
	}
}

void guardar_binario(struct animal *animales, int cantidad){
	FILE *archivo=fopen("datos.bin", "wb");
	if(archivo!=NULL){
		fwrite(animales, sizeof(struct animal), cantidad, archivo);
		fclose(archivo);
	}
	else{
		printf("Error al guardar el archivo binario.\n");
	}
}

void buscar_por_especie(struct animal *animales, int cantidad, char especie_buscada){
	int encontrados=0;
	for(int i=0;i<cantidad;i++){
		if(animales[i].especie==especie_buscada){
			printf("Nombre: %s | Edad: %hd | Especie:%c\n", animales[i].nombre, animales[i].edad, animales[i].especie);
			encontrados++;
		}
	}
	if(encontrados==0){
		printf("No se encontraron mascotas registradas.\n");
	}
}

float porcentaje_por_especie(struct animal *animales, int cantidad, char especie_porcentaje){
	int contador=0;
	if(cantidad==0){
		return 0;
	}
	for(int i=0;i<cantidad;i++){
		if(animales[i].especie==especie_porcentaje){
			contador++;
		}
	}
	return ((float)contador * 100) / cantidad;
}

void ordenar_por_edad(struct animal *animales, int cantidad){
	struct animal temporal;
	for(int i=0;i<cantidad-1;i++){
		for(int j=0;j<cantidad-i-1;j++){
			if(animales[j].edad>animales[j+1].edad){
				temporal=animales[j];
				animales[j]=animales[j+1];
				animales[j+1]=temporal;
			}
		}
	}
}

int main(void){
	struct animal *animales=NULL;
	short cantidad=0;
	int capacidad=0;
	char respuesta;
	
	do{
		struct animal *temporal=realloc(animales, (capacidad+1) * sizeof(struct animal));
		if(temporal==NULL){
			free(animales);
			return 1;
		}
		animales=temporal;
		capacidad++;
		
		printf("Ingrese el nombre de la mascota:");
		scanf(" %39[^\n]",animales[cantidad].nombre);
		
		printf("Ingrese la edad de la mascota:");
		scanf("%hd", &animales[cantidad].edad);
		
		printf("Ingrese la especie de la mascota:");
		scanf(" %c", &animales[cantidad].especie);
		
		cantidad++;
		
		printf("Quiere registrar una nueva mascota? (s/n):");
		scanf(" %c", &respuesta);
		
	}while(respuesta=='s');
	
	ordenar_por_edad(animales,cantidad);
	
	printf("Mascotas registradas\n");
	for(int i=0;i<cantidad;i++){
		printf("Nombre: %s | Edad: %hd | Especie: %c\n", animales[i].nombre, animales[i].edad, animales[i].especie);
	}
	
	char especie_buscada;
	printf("Indique la especie a buscar:");
	scanf(" %c", &especie_buscada);
	buscar_por_especie(animales,cantidad,especie_buscada);
	
	char especie_porcentaje;
	printf("Indique una especie para saber el porcentaje registrado:");
	scanf(" %c", &especie_porcentaje);
	float porcentaje=porcentaje_por_especie(animales,cantidad,especie_porcentaje);
	printf("El porcentaje de mascotas calculado es de %.2f%%\n", porcentaje);
	
	guardar_texto(animales,cantidad);
	guardar_binario(animales,cantidad);
	printf("Se generaron los archivos .txt y .bin de %hd animales.\n", cantidad);
	
	free(animales);
	
	return 0;
}
