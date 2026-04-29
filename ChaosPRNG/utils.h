#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define LINE_SIZE 256

static void read_seeds(const char* filename, uint32_t* s_0, uint32_t* R1_0, uint32_t* R2_0, double* x_0, double* y_0);
