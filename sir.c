#include "libs.h"

/**
* Função: fillModel
* Parametros:
*  - Cenario *cenario: Objeto que será preenchido com os valores dos parametros seguintes.
*  - int s   : variavel do tipo int com o valor de sucetiveis. 
*  - int i   : variavel do tipo int com o valor de infectados.
*  - int r   : variavel do tipo int com o valor de removidos.
*  - float h : variavel do tipo float com o do salto da simulação.
*  - float k : variavel do tipo float com o valor calculado de k.
*  - float b : variavel do tipo float com o valor calculado de b.
*  - float t : variavel do tipo float com o valor de do tempo de simulação.
* Retorno: void
* Descrição: Responsável preencher o onjeto do tipo SIR com os outros paramtros da função
* */
void fillModel(SIR *model, int s, int i, int r, float h, float k, float b, int t){
    model->suc = s;
    model->inf = i;
    model->rem = r;

    model->h = h;
    model->k = k;
    model->b = b;
    model->t = t;
}

/**
* Função: createSIRVector
* Parametros:
*  - Cenario *cenario: Objeto que será preenchido com os valores dos parametros seguintes.
*  - int simulationTime : variavel do tipo int com o valor do tempo de simulação. 
*  - int hours : variavel do tipo int com a quantidade de horas do dia.
* Retorno: void
* Descrição: Responsável por alocar memoria para os vetores suc, inf e rem de acordo com os valores
* passados por parametro
* */
float *createSIRVector(int simulationTime, int hours, int operation){
    return malloc(simulationTime * hours * operation);
}