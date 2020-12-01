#ifndef funcoes_h
#define funcoes_h

#include <stdio.h>
#include "tipos.h" 

void fillVector(float *vetor, int size);

SIR *allocateMemory(int size_suc, int size_inf, int size_rem);

void calcModelSIR(SIR *model, Cenario *c);

void writeFile(float *suc, float *inf, float *rem, float *t, SIR *model);

FILE *selectFileToOpen(int c);

int chooseB(Cenario *c);

int chooseK(Cenario *c);

#endif