#include "csv.h"
#include "config.h"

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
void writeFile(CSV *csv, SIR *model){
    int qntLinha = model->t * 24 * 10;
    
    FILE *saida = fopen("saida.csv", "w+");
    
    if(saida == NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    fprintf(saida, "%i,%i,%i,%.1f\n", model->suc, model->inf, model->rem, csv->tempo[0]);
    for(int i = 0;i < qntLinha;i++){
        fprintf(saida, "%2.5f,%2.5f,%2.5f,%.1f\n", csv->suc[i], csv->inf[i], csv->rem[i], csv->tempo[i+1]);
    }
    fclose(saida);
}

void readFile(SIR *model, Cenario *cenario, FILE *arquivo){
    /** Variveis auxiliares para armazenar os valores do arquivo **/
    float N_b, T_b, S_b0, I_b0, m_k, n_k, T_k, T_b2, T_k2, h, tb, tk, b, k;
    int s, i, r, tempo;

    char comando[10];
    while (fscanf(arquivo, "%s", comando) != EOF){
      if(strcmp(comando,"S(0)") == 0){
        fscanf(arquivo,"%d", &s);

      }else if(strcmp(comando,"I(0)") == 0){
        fscanf(arquivo,"%d", &i);

      }else if(strcmp(comando,"R(0)") == 0){
        fscanf(arquivo,"%d", &r);

      }else if(strcmp(comando,"h") == 0){
        fscanf(arquivo,"%f", &h);

      }else if(strcmp(comando,"N_b") == 0){
        fscanf(arquivo,"%f", &N_b);

      }else if(strcmp(comando,"T_b") == 0){
        fscanf(arquivo,"%f", &T_b);

      }else if(strcmp(comando,"S_b0") == 0){
        fscanf(arquivo,"%f", &S_b0);

      }else if(strcmp(comando,"I_b0") == 0){
        fscanf(arquivo,"%f", &I_b0);

      }else if(strcmp(comando,"m_k") == 0){
        fscanf(arquivo,"%f", &m_k);

      }else if(strcmp(comando,"n_k") == 0){
        fscanf(arquivo,"%f", &n_k);

      }else if(strcmp(comando,"T_k") == 0){
        fscanf(arquivo,"%f", &T_k);

      }else if(strcmp(comando,"t") == 0){
        fscanf(arquivo,"%i", &tempo);

      }else if(strcmp(comando,"T_b2") == 0){
        fscanf(arquivo,"%f", &T_b2);

      }else if(strcmp(comando,"T_k2") == 0){
        fscanf(arquivo,"%f", &T_k2);

      }else if(strcmp(comando,"tb") == 0){
        fscanf(arquivo,"%f", &tb);

      }else if(strcmp(comando,"tk") == 0){
        fscanf(arquivo,"%f", &tk);
      }
    }
    b = N_b/(T_b * S_b0 * I_b0);
    k = m_k/(n_k * T_k);

    model = createModel(s, i, r, h, k, b, tempo);

    cenario = createCenario(N_b, T_b, S_b0, I_b0, T_b2, tb, m_k, n_k, T_k, T_k2, tk);
}

Cenario *createCenario(float N_b, float T_b, float S_b0, float I_b0, float T_b2, float tb, float m_k, float n_k, float T_k, float T_k2, float tk){
    Cenario *cenario = malloc(sizeof(Cenario));
    
    cenario->b.N_b   = N_b;
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

float calculateB(Cenario *c){
    float b = 0;
    if(c->b.T_b2 != 0)
        b = c->b.N_b/(c->b.T_b2 * c->b.S_b0 * c->b.I_b0);

    return b;
}
float calculateK(Cenario *c){
    float k;
    if(c->k.T_k2 != 0)
        k = c->k.m_k/(c->k.n_k * c->k.T_k2);      

    return k;
} 
