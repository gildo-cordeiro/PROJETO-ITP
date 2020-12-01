#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>


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
    
    if(size_rem != -1)
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
    for(int i = 1; i <= size; i++)
       vetor[i] = (float) i;
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

    suc   = malloc(5040 * sizeof(float));
    inf   = malloc(5040 * sizeof(float));   
    rem   = malloc(5040 * sizeof(float));
    tempo = malloc(5040 * sizeof(float));

    int b = chooseB(c);
    int k = chooseK(c);
    float c_tb = c->b.tb;
    float c_tk = c->k.tk;
    printf("ctb %f, ctk %f, tmp %f\n", c_tb, c_tk, tmp);

    suc[0] = model->suc[69-1] - model->h * model->b * (model->suc[69-1]) * (model->inf[3-1]); 
    rem[0] = model->rem[1-1] + (model->h * model->k * model->inf[3-1]);    
    inf[0] = model->inf[3-1] + (model->h * ((model->b * model->suc[69-1] * model->inf[3-1]) - (model->k * model->inf[3-1])));

    int count = 1;
    float horas = model->t * 24;
    
    while(tmp < horas){
        suc[count] = (suc[count-1] - model->h * (c_tb == tmp && c_tb != 0 ? b : model->b) * (suc[count-1]) * (inf[count-1]));
        rem[count] = rem[count-1] + (model->h * (c_tk == tmp && c_tk != 0 ? k : model->k)  * inf[count-1]);    
        inf[count] = inf[count-1] + (model->h * (((c_tb == tmp && c_tb != 0 ? b : model->b)  * suc[count-1] * inf[count-1]) - ((c_tk == tmp && c_tk != 0  ? k : model->k) * inf[count-1])));
        
        tmp += model->h;        
        tempo[count] = tmp;
        count++; 
    }
    writeFile(suc, inf, rem, tempo, model);
    free(suc);
    free(inf);
    free(rem);
}

/**
* Função: writeFile
* Parametros:
*  - *suc:ponteira para o vetor de pessoas sucetiveis 
*  - *inf:ponteira para o vetor de pessoas infectadas
*  - *rem:ponteira para o vetor de pessoas removidas
*  - *t  :ponteiro para o vetor que armazena a variação de temo (0.1)
* Retorno: void
* Descrição: Responsável por escrever os dados calculados da equação SIR em um arquivo .csv externo
* */
void writeFile(float *suc, float *inf, float *rem, float *t, SIR *model){
    int qntLinha = 5041;
    
    FILE *saida = fopen("saida.csv", "w+");
    
    if(saida == NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    fprintf(saida, "%.1f,%.1f,%.1f,%.1f\n", model->suc[68], inf[2], rem[0], t[0]);
    for(int i = 0;i < qntLinha-1;i++){
        fprintf(saida, "%f,%f,%f,%.1f\n", suc[i], inf[i], rem[i], t[i+1]);
    }
    fclose(saida);
}

int chooseB(Cenario *c){
    int tb0, b;
    c->b.T_b2 == 0 ? tb0 = c->b.T_b : c->b.T_b2;
    b = c->b.N_b/(tb0 * c->b.S_b0 * c->b.I_b0);
    return b;
}
int chooseK(Cenario *c){
    int tk0, k;
    c->k.T_k2 == 0 ? tk0 = c->k.T_k : c->k.T_k2;
    k = c->k.m_k/(c->k.n_k * tk0);
    return k;
} 