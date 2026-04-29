#pragma once
#include <stdint.h>


#define MOD31 2147483647 //2^31 - 1

//Estado interno del PRNG
typedef struct {
	
	//Estado LFSR, hay que aplicar lógica para asegurar que cada elemento es de 31 bits en vez de 32.
	uint32_t s[16]; 
	
	//Unidades de memoria de 32 bits para la función no lineal F
	uint32_t R1;	
	uint32_t R2;

	//Variables para los dos mapas caóticos que operan en el intervalo [-1,1]
	double x;
	double y;
} PRNG_context;


//Funcón de inicalización del PRNG, recibe las semillas y ejecuta 32 ronda
// como de descrbe en el paper
void PRNG_init(PRNG_context* ctx, 
	uint32_t s_0[16],	//Estado inicial del LFSR
	uint32_t R1_0,		//Valor inicial de R1
	uint32_t R2_0,		//Valor inicial de R2
	double x_0,			//Semilla para la función caótica F1
	double y_0);		//Semilla para la funcón caótica F2

uint32_t PRNG_next(PRNG_context* ctx);	//Función para generar el siguiente número pseudoaleatorio, actualiza el estado interno del PRNG

