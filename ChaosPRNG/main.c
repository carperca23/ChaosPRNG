#include "ChaosPRNG.h"
#include "utils.h"

int main(int argc, char* argv[]) {
	if (argc < 5)
	{
		printf("Se necesitan los siguientes parámetros:\n");
		printf("[1] Ubicación del archivo .txt con las semillas.\n");
		printf("[2] Cantidad de números aleatorios a generar.\n");
		printf("[3] Ubicación del archivo de salida para los números generados.\n");
		printf("[4] Formato de la salida TXT ó BIN");
		return 1;
	}

	PRNG_context ctx;
	uint32_t s_0[16];
	uint32_t R1_0, R2_0;
	double x_0, y_0;

	printf("Leyendo semillas del archivo %s...\n", argv[1]);
	read_seeds(argv[1], s_0, &R1_0, &R2_0, &x_0, &y_0);

	//Inicialización y descarte de los primeros 100 números generados
	printf("Inicializando el PRNG con las semillas del archivo %s...\n", argv[1]);
	PRNG_init(&ctx, s_0, R1_0, R2_0, x_0, y_0);
	for (int i = 0; i < 100; i++)
	{
		PRNG_next(&ctx);
	}
	FILE* output_file = fopen(argv[3], "w");
	//Generación de números aleatorios y guardado en el archivo de salida
	if (strcmp(argv[4], "BIN") == 0) {
		for (long i = 0; i < atoi(argv[2]); i++) { // Generar unos 400MB mínimo
			uint32_t num = PRNG_next(&ctx);
			fwrite(&num, sizeof(uint32_t), 1, output_file);
		}
	}
	else {
		for (int i = 0; i < atoi(argv[2]); i++)
		{
			uint32_t random_number = PRNG_next(&ctx);
			fprintf(output_file, "%u\n", random_number);
		}
		fclose(output_file);
		printf("Números aleatorios generados y guardados en %s\n", argv[3]);
		return 0;
	}
}