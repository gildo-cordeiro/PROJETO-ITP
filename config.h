#ifndef config_h
#define config_h
#include "libs.h"

typedef struct{
    float N_b, T_b, S_b0, I_b0, T_b2, tb;
}DataB;

typedef struct{
    float m_k, n_k, T_k, T_k2, tk;
}DataK;

typedef struct{
    DataB *b;
    DataK *k;
}Cenario;

FILE *selectFileToOpen(int c);

int compare_float(float f1, float f2);

void calcModelSIR(SIR *model, Cenario *c);

#endif