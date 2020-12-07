#include "libs.h"

void fillModel(SIR *model, int s, int i, int r, float h, float k, float b, int t){
    model->suc = s;
    model->inf = i;
    model->rem = r;

    model->h = h;
    model->k = k;
    model->b = b;
    model->t = t;
}

float *createSIRVector(int simulationTime, int hours, int operation){
    return malloc(simulationTime * hours * operation);
}