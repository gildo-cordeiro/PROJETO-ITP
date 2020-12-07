#ifndef sir_h
#define sir_h

typedef struct{
    int suc, inf, rem, t;
    float h, b, k;
}SIR;

void fillModel(SIR *model, int suc, int inf, int rem, float h, float k, float b, int t);

float *createSIRVector(int simulationTime, int days, int opeation);

#endif