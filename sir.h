#ifndef sir_h
#define sir_h

typedef struct{
    int suc, inf, rem, t;
    float h, b, k;
}SIR;

SIR *createModel(int suc, int inf, int rem, float h, float k, float b, int t);

#endif