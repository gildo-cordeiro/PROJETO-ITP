#include "libs.h"

/**
* Função: compare_float;
* Parametros:
*  - float f1: Representa um numero float que será utilizado para comparação.
*  - float f2: Representa um numero float que será utilizado para comparação.
* Retorno: int
* Descrição: Responsável comparar dois numeros float e retorna um caso eles sejam iguais;
* */
int compare_float(float f1, float f2){
    // Ajustando a precisão
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
*  - SIR *model: ponteiro do tipo SIR que contempla todos os parametros e vetores necessarios para o calculo
* da equação;
*  - Cenario *c: ponteiro do tipo Cenario que possuia os valores dos cenarios que deve ser implementados
* Retorno: void;
* Descrição: Responsável por efetuar o calculo da equação que disponibilizara a quantidade de grupos de cada
* cada individuo;
* */
void calcModelSIR(SIR *model, Cenario *c){
    // Variavel auxiliar utilizada para a soma das horas.
    float tmp = 0;

    // Alocando memoria para um objeto do tipo CSV
    CSV *csv = malloc(sizeof(CSV)); 

    // Alocando memoria para os vetores que irão armazenar as populações
    csv->suc   = createSIRVector(model->t, 24, 100);
    csv->inf   = createSIRVector(model->t, 24, 100);  
    csv->rem   = createSIRVector(model->t, 24, 100);
    csv->tempo = createSIRVector(model->t, 24, 100);

    // Variveis auxiliares que irão conter os valores recalculados de b e k
    float b = calculateB(c), k = calculateK(c);

    // Calculo dos primeiros elementos, para  assim poder calcular o seguinte
    csv->suc[0] = (float) model->suc - (model->h * (model->b * (float) model->suc * (float) model->inf)); 
    csv->rem[0] = (float) model->rem + (model->h * model->k * (float) model->inf);    
    csv->inf[0] = (float) model->inf + (model->h * ((model->b * (float) model->suc * (float) model->inf) - (model->k * (float) model->inf)));

    // Varivale que inicia com o valor total de horas da simulação
    float horas = model->t * 24;

    // Variveis auxiliares que irão conter os valores base de b e k
    float tmp_b = model->b, tmp_k = model->k;

    int count = 1;
    while(tmp < horas){
        /*Verifica se o tempo de simulção é igual ao tempo de inicio da simulção do primeiro cenario,
          caso seja igual atribui o valor recalculado de b para o tmp_b*/
        if(compare_float(c->b->tb, tmp) == 1 && tmp != 0)
            tmp_b = b;

        /*Verifica se o tempo de simulção é igual ao tempo de inicio da simulção do segundo cenario,
          caso seja igual atribui o valor recalculado de k para o tmp_k*/
        if(compare_float(c->k->tk, tmp) == 1 && tmp != 0)
            tmp_k = k;

        // Calculo da simulação
        csv->suc[count] = (csv->suc[count-1] - model->h * tmp_b * (csv->suc[count-1]) * (csv->inf[count-1]));
        csv->rem[count] = csv->rem[count-1] + (model->h * tmp_k  * csv->inf[count-1]);    
        csv->inf[count] = csv->inf[count-1] + (model->h * ((tmp_b  * csv->suc[count-1] * csv->inf[count-1]) - (tmp_k * csv->inf[count-1])));
        
        // Icrementando o valor do vetor que armazena o valor das horas a cada laço
        tmp += model->h;        
        csv->tempo[count] = tmp;
        count++; 
    }
    writeFile(csv, model);
}
