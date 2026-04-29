#include "utils.h"

static void read_seeds(const char* filename, uint32_t* s_0, uint32_t* R1_0, uint32_t* R2_0, double* x_0, double* y_0)
{
	FILE* file = fopen(filename, "r");
	if (!file)
	{
		printf("Error al abrir el archivo de semillas.\n");
		exit(1);
	}

	if (fscanf(file, " s = [") != 1) {
		printf("Error al leer las semillas del LFSR.\n");
		exit(1);
	}
	for (int i = 0; i < 16; i++)
	{
		if (fscanf(file, " %u%*[,]", &s_0[i]) != 1)
		{
			printf("Error al leer la semilla %d del LFSR.\n", i);
			exit(1);
		}
	}
	if (fscanf(file, " ] ") != 1)
	{
		printf("Error al leer el cierre del vector de semillas del LFSR.\n");
	}
	if (fscanf(file, " R1 = %u ", R1_0) != 1)
	{
		printf("Error al leer la semilla R1.\n");
		exit(1);
	}
	if (fscanf(file, " R2 = %u ", R2_0) != 1)
	{
		printf("Error al leer la semilla R2.\n");
		exit(1);
	}
	if (fscanf(file, " x = %lf ", x_0) != 1)
	{
		printf("Error al leer la semilla x.\n");
		exit(1);
	}
	if (fscanf(file, " y = %lf ", y_0) != 1)
	{
		printf("Error al leer la semilla y.\n");
		exit(1);
	}

	fclose(file);
}