#ifndef funcoes_h
#define funcoes_h

#include "tipos.h" 

// float funcTempo(float *tmp, float h, float t);

float calclModelSIR(SIR model);

void allocateMemory(SIR *model, int size, int type);

// float funcInfectados(float *I, float b, float h, float k, int t);

// float funcRemovidos(float *r, float h, float k, int t);

#endif