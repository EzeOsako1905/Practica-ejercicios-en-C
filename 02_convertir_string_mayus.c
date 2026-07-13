/*Escribí una función llamada a_mayusculas que reciba un string y convierta todas sus letras minúsculas a 
mayúsculas. En main declarás un string, lo imprimís antes y después de llamar a la función.*/

#include <stdio.h>
#include <stdlib.h>

void a_mayus(char *s){
	
	for(int i=0; s[i] != '\0';i++){
		if(s[i] >= 'a' && s[i] <= 'z') 
			s[i] = s[i] - 32;
	}
}

int main(void){
	
	char vector[20];
	printf("Ingrese un string en minusculas:\n");
	scanf("%19[^\n]", vector);
	
	a_mayus(vector);
	
	printf("String en mayusculas: %s\n", vector);
	
	return 0;
}
