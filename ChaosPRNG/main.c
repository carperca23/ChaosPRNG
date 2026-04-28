#include "ChaosPRNG.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
	//Ejemplo de uso del PRNG
	PRNG_context ctx;
	uint32_t s_0[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
	uint32_t R1_0 = 12345;
	uint32_t R2_0 = 67890;
	double x_0 = 0.5;
	double y_0 = -0.49;

	PRNG_init(&ctx, s_0, R1_0, R2_0, x_0, y_0);
	//Descartar los proimeros 100 números
	for (int i = 0; i < 100; i++) {
		uint32_t random_number = PRNG_next(&ctx);
	}

	for (int i = 0; i < 10; i++) {
		uint32_t random_number = PRNG_next(&ctx);
		printf("%u\n", random_number);
	}
	return 0;
}