#ifndef csv_h
#define csv_h

#include "libs.h"

typedef struct{
    float *suc, *inf, *rem, *tempo;
}CSV;

void writeFile(CSV *csv, SIR *model);

void readFile(SIR *model, Cenario *cenario, FILE *f);

float calculateB(Cenario *c);

float calculateK(Cenario *c);

void fillCenario(Cenario *cenario, float N_b, float T_b, float S_b0, float I_b0, float T_b2, float tb, float m_k, float n_k, float T_k, float T_k2, float tk);

#endif