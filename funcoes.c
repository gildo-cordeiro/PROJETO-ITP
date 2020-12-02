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

Cenario *createCenario(float T_b, float S_b0, float I_b0, float T_b2, float tb, float m_k, float n_k, float T_k, float T_k2, float tk){
    Cenario *cenario = malloc(sizeof(Cenario));

    cenario->b.T_b   = T_b;
    cenario->b.S_b0  = S_b0;
    cenario->b.I_b0  = I_b0;
    cenario->b.T_b2  = T_b2;
    cenario->b.tb    = tb;

    cenario->k.m_k   = m_k;
    cenario->k.n_k   = n_k;
    cenario->k.T_k   = T_k;
    cenario->k.T_k2  = T_k2;
    cenario->k.tk    = tk;

    return cenario;
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

    int b = chooseB(c);
    int k = chooseK(c);
    float c_tb = c->b.tb;
    float c_tk = c->k.tk;

    suc[0] = (float) model->suc - (model->h * (model->b * (float) model->suc * (float) model->inf)); 
    rem[0] = (float) model->rem + (model->h * model->k * (float) model->inf);    
    inf[0] = (float) model->inf + (model->h * ((model->b * (float) model->suc * (float) model->inf) - (model->k * (float) model->inf)));

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
    fprintf(saida, "%i,%i,%i,%.1f\n", model->suc, model->inf, model->rem, t[0]);
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