#ifndef funcoes_h
#define funcoes_h

#include "tipos.h" 

void fillVector(float *vetor, int size);

SIR *allocateMemory(int size_suc, int size_inf, int size_rem);

void calcModelSIR(SIR *model, Cenario *cenario);

void writeFile(float *suc, float *inf, float *rem, float *t, SIR *model);

int chooseB(float nowtime, Cenario *c);

int chooseK(float nowtime, Cenario *c);

#endif