#include "config.h"

FILE *selectFileToOpen(int c){
    /** Carregando arquivo **/
  	FILE *arquivo;
    if (c == 0){
        arquivo = fopen("cenario.txt","r");
    }else if(c == 1){
        arquivo = fopen("cenario_2.txt","r");
    }else if(c == 2){
        arquivo = fopen("cenario_3.txt","r");
    }else{
        arquivo = NULL;
    }
    return arquivo;
}

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
    float *suc, *inf, *rem, *tempo, tmp = 0;

    suc   = malloc((model->t * 24 * 10) * sizeof(float));
    inf   = malloc((model->t * 24 * 10) * sizeof(float));   
    rem   = malloc((model->t * 24 * 10) * sizeof(float));
    tempo = malloc((model->t * 24 * 10) * sizeof(float));

    float b = calculateB(c), k = calculateK(c);

    suc[0] = (float) model->suc - (model->h * (model->b * (float) model->suc * (float) model->inf)); 
    rem[0] = (float) model->rem + (model->h * model->k * (float) model->inf);    
    inf[0] = (float) model->inf + (model->h * ((model->b * (float) model->suc * (float) model->inf) - (model->k * (float) model->inf)));

    float horas = model->t * 24;

    float tmp_b = model->b, tmp_k = model->k;

    int count = 1;
    while(tmp < horas){
        if(compare_float(c->b.tb, tmp) == 1 && tmp != 0)
            tmp_b = b;

        if(compare_float(c->k.tk, tmp) == 1 && tmp != 0)
            tmp_k = k;

        suc[count] = (suc[count-1] - model->h * tmp_b * (suc[count-1]) * (inf[count-1]));
        rem[count] = rem[count-1] + (model->h * tmp_k  * inf[count-1]);    
        inf[count] = inf[count-1] + (model->h * ((tmp_b  * suc[count-1] * inf[count-1]) - (tmp_k * inf[count-1])));
        
        tmp += model->h;        
        tempo[count] = tmp;
        count++; 
    }
    writeFile(suc, inf, rem, tempo, model);
    free(suc);
    free(inf);
    free(rem);
}
