#ifndef funcoes_h
#define funcoes_h

#include "tipos.h" 

// float funcTempo(float *tmp, float h, float t);

void fillVector(float *vetor, int size);

SIR *allocateMemory(int size_suc, int size_inf, int size_rem);

void calcModelSIR(SIR *model);

// float funcInfectados(float *I, float b, float h, float k, int t);

// float funcRemovidos(float *r, float h, float k, int t);

#endif