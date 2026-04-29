#include "utils.h"

static void read_seeds(const char* filename, uint32_t* s_0, uint32_t* R1_0, uint32_t* R2_0, double* x_0, double* y_0)
{
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error al abrir el archivo de semillas");
        exit(1);
    }

    char line[LINE_SIZE];

    if (!fgets(line, sizeof(line), file)) {
        fprintf(stderr, "Error leyendo línea de s\n");
        exit(1);
    }

    char* start = strchr(line, '[');
    if (!start) {
        fprintf(stderr, "Formato incorrecto en s\n");
        exit(1);
    }

    start++;

    for (int i = 0; i < 16; i++) {
        if (sscanf(start, " %u", &s_0[i]) != 1) {
            fprintf(stderr, "Error leyendo s[%d]\n", i);
            exit(1);
        }

        char* comma = strchr(start, ',');
        if (comma) {
            start = comma + 1;
        }
        else if (i < 15) {
            fprintf(stderr, "Faltan valores en s\n");
            exit(1);
        }
    }

    if (!fgets(line, sizeof(line), file) ||
        sscanf(line, " R1 = %u", R1_0) != 1) {
        fprintf(stderr, "Error leyendo R1\n");
        exit(1);
    }

    if (!fgets(line, sizeof(line), file) ||
        sscanf(line, " R2 = %u", R2_0) != 1) {
        fprintf(stderr, "Error leyendo R2\n");
        exit(1);
    }

    if (!fgets(line, sizeof(line), file) ||
        sscanf(line, " x = %lf", x_0) != 1) {
        fprintf(stderr, "Error leyendo x\n");
        exit(1);
    }

    if (!fgets(line, sizeof(line), file) ||
        sscanf(line, " y = %lf", y_0) != 1) {
        fprintf(stderr, "Error leyendo y\n");
        exit(1);
    }

    fclose(file);
}