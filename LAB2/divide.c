#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int main()
{
	int num, den, cociente = 0;
	float div;

	// Entrada de datos
	printf("Ingrese el dividendo:\n");
	scanf("%d",&num);
	printf("Ingrese el divisor:\n");
	scanf("%d",&den);

	// Verificación del divisor
	if (den == 0) {

		printf("Error: No se puede dividir por cero. \n");

		return 1;
	}

	// Manejo de signos
	int signo = 1;

	if((num < 0 && den > 0) || (num > 0 && den <0)){

		signo = -1;
	}

	// Dividenod sin modificar

	int dividendo_original = num;

	// Dar valores absolutos a los numeros
	num = abs(num);
	den = abs(den);

	//Algoritmo de división usando restas y potencia
	while (num >= den){
		int temp = den, i = 0;

		//Encuentra el mayor multiplo 
		while(num >= temp * 2){
			temp *=2;
			i++; // Contamos la potencia de 2
		}

		num -= temp; //Resta entre el multiplo y numerador
		cociente += (int)pow(2,i); // Suma de la potencia 2 correspondiente
	}
	// Ajuste del signo
	cociente *= signo;

	div = (float)dividendo_original / den;

	printf("cociente: %d\n", cociente);

	printf("La operación divisora entre %d/%d es: %.3f \n", dividendo_original, den, div);
	printf("La operación sin usar el operando divisor es: %d\n", cociente);

	return 0;
}