#include "ChaosPRNG.h"

static void bit_reorganization(PRNG_context* ctx, uint32_t* res) {
	//Reorganización de bits
	//Devuelve [x0, x1, x2, x3]

	res[0] = ((ctx->s[15] >> 15) << 16) | (ctx->s[14] & 0x0000FFFF); //x0
	res[1] = ((ctx->s[11] & 0x0000FFFF) << 16) | (ctx->s[9] >> 15); // x1
	res[2] = ((ctx->s[7] >> 15) << 16) | (ctx->s[5] & 0x0000FFFF); //x2
	res[3] = ((ctx->s[2] & 0x0000FFFF) << 16) | (ctx->s[0] >> 15); //x3
}

static uint32_t F1(PRNG_context* ctx)
{
	//Calcula el siguente valor de x usando el mapa caótico F1 y lo guarda en el estado interno del PRNG
	//Devuelve el nuevo valor de x transformado en un int de 32 bits sin signo
	double x_anterior = ctx->x;
	ctx->x = 2 * x_anterior * x_anterior - 1;

	uint32_t res = (uint32_t)((ctx->x + 1.0) / 2.0 * 4294967295.0);
	return res;
}

static uint32_t F2(PRNG_context* ctx)
{
	//Calcula el siguente valor de y usando el mapa caótico F2 y lo guarda en el estado interno del PRNG
	//Devuelve el nuevo valor de y transformado en un int de 32 bits sin signo
	double y_anterior = ctx->y;
	ctx->y = 4 * y_anterior *  y_anterior * y_anterior - 3 * y_anterior;

	uint32_t res = (uint32_t)((ctx->y + 1.0) / 2.0 * 4294967295.0);
	return res;
}

static uint32_t F(PRNG_context* ctx, uint32_t variables[4])
{
	//Ejecuta la función no lineal F
	uint32_t D = (variables[0] ^ ctx->R1) + ctx->R2;
	uint32_t D1 = ctx->R1 + variables[1];
	uint32_t D2 = ctx->R2 ^ variables[2];
	ctx->R1 = D1 ^ F1(ctx);
	ctx->R2 = D2 ^ F2(ctx);

	return D;
}

void PRNG_init(PRNG_context* ctx, uint32_t s_0[16], uint32_t R1_0, uint32_t R2_0, double x_0, double y_0)
{
	//Inicialización del estado interno del PRNG con las semillas proporcionadas
	for (int i = 0; i < 16; i++) {
		ctx->s[i] = s_0[i] & 0x7FFFFFFF;
	}
	ctx->R1 = R1_0;
	ctx->R2 = R2_0;
	ctx->x = x_0;
	ctx->y = y_0;

	//Ejecuta las 32 rondas de calentamiento
	for (int i = 0; i < 32; i++){
		uint32_t variables[4] = {0, 0, 0, 0};
		bit_reorganization(ctx, variables);
		uint32_t u = (F(ctx, variables) >> 1) ;
		uint64_t suma_v = ((uint64_t)ctx->s[15] << 13) +
						((uint64_t)ctx->s[13] << 19) + 
						((uint64_t)ctx->s[10] << 17) + 
						((uint64_t)ctx->s[6] << 20) +
						((uint64_t)ctx->s[0] + ((uint64_t)ctx->s[0] << 8));
		uint32_t v = (uint32_t)(suma_v % MOD31);
		uint32_t s16 = (v + u) % MOD31;
		if (s16 == 0) {
			s16 = MOD31;
		}
		for (int i = 0; i < 15; i++) {
			ctx->s[i] = ctx->s[i + 1];
		}
		ctx->s[15] = s16;
	}

}

uint32_t PRNG_next(PRNG_context* ctx)
{
	//Genera el siguiente número pseudoaleatorio y actualiza el estado interno del PRNG
	uint32_t variables[4] = {0, 0, 0, 0};
	bit_reorganization(ctx, variables);
	uint32_t Z = F(ctx, variables) ^ variables[3];
	uint64_t suma_s16 = ((uint64_t)ctx->s[15] << 13) +
		((uint64_t)ctx->s[13] << 19) +
		((uint64_t)ctx->s[10] << 17) +
		((uint64_t)ctx->s[6] << 20) +
		((uint64_t)ctx->s[0] + ((uint64_t)ctx->s[0] << 8));
	uint32_t s16 = (uint32_t)(suma_s16 % MOD31);
	if (s16 == 0) {
		s16 = MOD31;
	}
	for (int i = 0; i < 15; i++) {
		ctx->s[i] = ctx->s[i + 1];
	}
	ctx->s[15] = s16;
	return Z;
}
