#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>

/**
* Função: allocateMemory
* Parametros:
*  - s: quantidade de elementos sucetiveis
*  - i: quantidade de elementos infectados
*  - r: quantidade de elementos removidos
* Retorno: SIR *
* Descrição: Responsável por alocar memoria para os vetores das populações que se encontram dentro do
* objeto model, assim como alicar memoria para o mesmo
**/
SIR *allocateMemory(int size_suc, int size_inf, int size_rem){
    SIR *model = malloc(sizeof(SIR));

    if(size_suc != -1)
        model->suc = malloc(size_suc * sizeof(float));
    
    if(size_inf != -1)   
        model->inf = malloc(size_inf * sizeof(float));
    
    if(size_rem != 1)
        model->rem = malloc(size_inf * sizeof(float));

    return model;
}

/**
* Função: fillVector
* Parametros:
*  - *vetor: ponteiro do tipo float referente ao vetor que deve ser preenchido
*  - size: quantidade de elementos que irão popular o vetor
* Retorno: void
* Descrição: Responsável por preencher o vetor que foi recebido no paramtro *vetor
* */
void fillVector(float *vetor, int size){
    for(int i = 1; i <= size; i++){
       vetor[i] = (float) i;
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
void calcModelSIR(SIR *model){
    float *suc, *inf, *rem;
    float tempo[504], tmp = 0;

    suc = calloc(504, sizeof(float));
    inf = calloc(504, sizeof(float));   
    rem = calloc(504, sizeof(float));


    suc[0] = (model->suc[69-1] - model->h * model->b * (model->suc[69-1]) * (model->inf[3-1])); 
    rem[0] = model->rem[1-1] + (model->h * model->k * model->inf[3-1]);    
    inf[0] = model->inf[3-1] + (model->h * ((model->b * model->suc[69-1] * model->inf[3-1]) - (model->k * model->inf[3-1])));

    // printf("S %.3f\n", suc[0]);
    // printf("I %.4f\n", inf[0]);
    // printf("R %.7f\n", rem[0]);
    int count = 1;
    while(tempo[count] < 45){
        suc[count] = (suc[count-1] - model->h * model->b * (suc[count-1]) * (inf[count-1]));
        rem[count] = rem[count-1] + (model->h * model->k * inf[count-1]);    
        inf[count] = inf[count-1] + (model->h * ((model->b * suc[count-1] * inf[count-1]) - (model->k * inf[count-1])));
        
        tmp += model->h;        
        tempo[count] = tmp;
        count++; 
    }
    for(int i = 0; i < 44; i++){
        printf("%.3f, %.4f, %f, %.1f\n", suc[i], inf[i], rem[i], tempo[i+1]);
    }
}

