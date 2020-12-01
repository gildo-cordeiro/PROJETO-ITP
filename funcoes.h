#ifndef funcoes_h
#define funcoes_h

#include <stdio.h>
#include "tipos.h" 

SIR *createModel(int suc, int inf, int rem, float h, float k, float b, int t);

Cenario *createCenario(float T_b, float S_b0, float I_b0, float T_b2, float tb, float m_k, float n_k, float T_k, float T_k2, float tk);

void calcModelSIR(SIR *model, Cenario *c);

void writeFile(float *suc, float *inf, float *rem, float *t, SIR *model);

FILE *selectFileToOpen(int c);

int chooseB(Cenario *c);

int chooseK(Cenario *c);

#endif