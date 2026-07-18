/*Una tienda registrará su inventario de productos. Por cada producto se registrará:

Nombre, hasta 50 caracteres
Precio (número con decimales)
Categoría (puede ser Limpieza, Alimentación o Electrónica)

Se sabe que no se conoce de antemano cuántos productos habrá.
Se pide:

Almacenar en memoria todos los productos.
Una función que genere un archivo de texto con todos los datos de cada producto.
Una función que genere un archivo binario con todos los datos.
Una función que busque todos los productos de una determinada categoría e imprima los encontrados, informando si 
no se encontró ninguno.
Una función que calcule el porcentaje de productos por categoría — se piden los tres porcentajes, impresos desde 
main.

Restricciones:

No se permiten variables globales.
La carga y la impresión de resultados solo en main.
Cada función debe tener al menos un parámetro por referencia.
Solo C, debe compilar sin errores.

Agregamos dos funciones nuevas: leer_texto que lea el archivo datos.txt e imprima los productos en pantalla y 
leer_binario que lea el archivo datos.bin y también imprima los productos*/

#include <stdio.h>
#include <stdlib.h>

struct producto{
	char nombre[50];
	float precio;
	char categoria; //(L) Limpieza, (A) Alimentación, (E) Electrónica
};

void guardar_texto(struct producto *productos, int cantidad){
	FILE *archivo = fopen("datos.txt", "w");
	if(archivo != NULL){
		for(int i=0;i<cantidad;i++){
			fprintf(archivo, "Nombre: %s | Precio: %.2f | Cat: %c \n", productos[i].nombre, productos[i].precio, productos[i].categoria);
		}
	fclose(archivo);	
	}
	else{
		printf("Error en abrir el archivo de texto.\n");
	}
}

void guardar_binario(struct producto *productos, int cantidad){
	FILE *archivo = fopen("datos.bin", "wb");
	if(archivo != NULL){
		fwrite(productos, sizeof(struct producto), cantidad, archivo);
		fclose(archivo);
	}
	else{
		printf("Error en abrir el archivo binario\n");
	}
}

void buscar_por_cat(struct producto *productos, int cantidad, char cat_buscada){
	int encontrados = 0;
	for(int i=0;i<cantidad;i++){
		if(productos[i].categoria == cat_buscada){
			printf("Nombre: %s | Precio: %.2f | Cat: %c\n", productos[i].nombre, productos[i].precio, productos[i].categoria);
			encontrados ++;
		}
	}
	if(encontrados == 0){
		printf("No se encontro ningun producto de la categoria buscada\n");
	}
}

float porcentaje_por_categoria(struct producto *productos, int cantidad, char cat_porcentaje){
	int contador = 0;
	if(cantidad == 0){
		return 0;
	}
	for(int i=0;i<cantidad;i++){
		if(productos[i].categoria == cat_porcentaje){
			contador ++;
		}
	}
	return ((float)contador * 100) / cantidad;
}

void leer_texto(char *nombre_archivo){
	FILE *archivo = fopen(nombre_archivo, "r");
	char linea [100];
	if(archivo != NULL){
		while(fgets(linea, sizeof(linea), archivo) != NULL){
		printf("%s", linea);
		}
	fclose(archivo);
	}	
}

void leer_binario(char *nombre_archivo){
	FILE *archivo = fopen(nombre_archivo, "rb");
	struct producto p;
	if(archivo != NULL){
		while(fread(&p, sizeof(struct producto), 1, archivo) == 1){
			printf("Nombre: %s | Precio: %.2f | Cat: %c\n", p.nombre, p.precio, p.categoria);
		}
	fclose(archivo);
	}
}

int main(void){
	
	struct producto *productos = NULL;
	int cantidad=0;
	int capacidad=0;
	char respuesta;
	
	do{
		struct producto *temp = realloc (productos, (capacidad + 1) * sizeof(struct producto));
		if(temp == NULL){
			free(productos);
			return 1;
		}
		productos = temp;
		capacidad ++;
		
		printf("Ingrese el nombre del producto: \n");
		scanf(" %49[^\n]", productos[cantidad].nombre);
		
		printf("Ingrese el precio del producto en pesos: \n");
		scanf("%f", &productos[cantidad].precio);
		
		printf("Ingrese la primer letra de la categoria del producto (L) Limpieza, (A) Alimentacion, (E) Electronica): \n");
		scanf(" %c", &productos[cantidad].categoria);
		
		cantidad ++;
		
		printf("Desea ingresar un nuevo producto? (s/n): \n");
		scanf(" %c", &respuesta);
		
	}while(respuesta == 's');
	
	printf("\n--- Productos cargados ---\n");
	for(int i = 0; i < cantidad; i++){
		printf("Nombre: %s | Precio: %.2f | Categoria: %c \n", productos[i].nombre, productos[i].precio, productos[i].categoria);
	}
	
	char cat_buscada;
	printf("Seleccione una categoria (A/E/L): \n");
	scanf(" %c", &cat_buscada);
	buscar_por_cat(productos, cantidad, cat_buscada);
	
	char cat_procentaje;
	printf("Ingrese la categoria para calcular el porcentaje (A/E/L): \n");
	scanf(" %c", &cat_procentaje);
	
	float porcentaje = porcentaje_por_categoria(productos, cantidad, cat_procentaje);
	printf("El porcentaje de productos por categoria es: %.2f%%\n", porcentaje);
	
	guardar_texto(productos, cantidad);
	guardar_binario(productos, cantidad);
	printf("Se generaron los archivos .txt y .bin con %d productos.\n", cantidad);
	
	printf("\n--- Leyendo archivo de texto ---\n");
	leer_texto("datos.txt");
	
	printf("\n--- Leyendo archivo binario ---\n");
	leer_binario("datos.bin");
	
	free(productos);
	return 0;
}
