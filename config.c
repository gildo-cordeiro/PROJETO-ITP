#include "libs.h"

int compare_float(float f1, float f2){
    float precision = 0.00001;
    if (((f1 - precision) < f2) && ((f1 + precision) > f2)){
        return 1;
    }else{
        return 0;
    }
}

/**
* Função: calcModelSIR;
* Parametros:
*  - *model: ponteiro do tipo SIR que contempla todos os parametros e vetores necessarios para o calculo
* da equação;
* Retorno: void;
* Descrição: Responsável por efetuar o calculo da equação que disponibilizara a quantidade de grupos de cada
* cada individuo;
* */
void calcModelSIR(SIR *model, Cenario *c){
    float tmp = 0;
    CSV *csv = createCSV(); 

    csv->suc   = createSIRVector(model->t, 24, 10);
    csv->inf   = createSIRVector(model->t, 24, 10);  
    csv->rem   = createSIRVector(model->t, 24, 10);
    csv->tempo = createSIRVector(model->t, 24, 10);

    float b = calculateB(c), k = calculateK(c);

    csv->suc[0] = (float) model->suc - (model->h * (model->b * (float) model->suc * (float) model->inf)); 
    csv->rem[0] = (float) model->rem + (model->h * model->k * (float) model->inf);    
    csv->inf[0] = (float) model->inf + (model->h * ((model->b * (float) model->suc * (float) model->inf) - (model->k * (float) model->inf)));

    float horas = model->t * 24;

    float tmp_b = model->b, tmp_k = model->k;

    int count = 1;
    while(tmp < horas){
        if(compare_float(c->b->tb, tmp) == 1 && tmp != 0)
            tmp_b = b;

        if(compare_float(c->k->tk, tmp) == 1 && tmp != 0)
            tmp_k = k;

        csv->suc[count] = (csv->suc[count-1] - model->h * tmp_b * (csv->suc[count-1]) * (csv->inf[count-1]));
        csv->rem[count] = csv->rem[count-1] + (model->h * tmp_k  * csv->inf[count-1]);    
        csv->inf[count] = csv->inf[count-1] + (model->h * ((tmp_b  * csv->suc[count-1] * csv->inf[count-1]) - (tmp_k * csv->inf[count-1])));
        
        tmp += model->h;        
        csv->tempo[count] = tmp;
        count++; 
    }
    writeFile(csv, model);
}
