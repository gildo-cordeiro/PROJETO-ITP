#include "sir.h"

SIR *createModel(int s, int i, int r, float h, float k, float b, int t){
    SIR *model = malloc(sizeof(SIR));

    model->suc = s;
    model->inf = i;
    model->rem = r;

    model->h = h;
    model->k = k;
    model->b = b;
    model->t = t;

    return model;
}