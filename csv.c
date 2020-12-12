#include "libs.h"

/**
* Função: selectFileToOpen;
* Parametros:
*  - int c: parametro utilizado para escolha do arquivo que será lido.
* Retorno: FILE *
* Descrição: Responsável por escolher qual arquivo, que representa o um cenario, deverá ser lido;
* */
FILE *selectFileToOpen(int c){

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
* Função: readFile;
* Parametros:
*  - SIR *model: Objeto com as variaveis com as variaveis da simulação.
*  - Cenario *cenario: Objeto com as variaveis dos cenarios para simulação.
*  - FILE *arquivo: Objeto que contem o arquivo de texto com os valores para a simulação.
* Retorno: void;
* Descrição: Responsável por ler os valores do txt e calcular o valor de b e k;
* */
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
  // Calculo de b e k para a simulação
  b = N_b/(T_b * S_b0 * I_b0);
  k = m_k/(n_k * T_k);

  // Alocação de memoria para os objetos b e k dentro do objeto Cenario
  cenario->b = malloc(sizeof(DataB));
  cenario->k = malloc(sizeof(DataK));

  fillModel(model,s, i, r, h, k, b, tempo);

  fillCenario(cenario, N_b, T_b, S_b0, I_b0, T_b2, tb, m_k, n_k, T_k, T_k2, tk);
}
/**
* Função: writeFile
* Parametros:
*  - CSV *csv: Objeto com os vetores que serão escritos no csv
*  - SIR *model: Objeto com os valores da simulação
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
    //fclose(saida);
    free(csv->suc);
    free(csv->inf);
    free(csv->rem);
    free(csv->tempo);
    free(csv);
}

/**
* Função: fillCenario
* Parametros:
*  - Cenario *cenario: Objeto que será preenchido com os valores dos parametros seguintes.
*  - float N_b  : variavel do tipo float utilizada no calculo de b. 
*  - float T_b  : variavel do tipo float utilizada no calculo de b.
*  - float S_b0 : variavel do tipo float utilizada no calculo de b.
*  - float I_b0 : variavel do tipo float utilizada no calculo de b.
*  - float T_b2 : variavel do tipo float utilizada no calculo de b.
*  - float tb   : variavel do tipo float utilizada no calculo de b.
*  - float m_k  : variavel do tipo float utilizada no calculo de k.
*  - float n_k  : variavel do tipo float utilizada no calculo de k.
*  - float T_k  : variavel do tipo float utilizada no calculo de k.
*  - float T_k2 : variavel do tipo float utilizada no calculo de k.
*  - float tk   : variavel do tipo float utilizada no calculo de k.
* Retorno: void
* Descrição: Responsável preencher os objetos b (tipo DataB) e k (Tipo DataK) do objeto pai Cenario com os outros paramtros da função
* */
void fillCenario(Cenario *cenario, float N_b, float T_b, float S_b0, float I_b0, float T_b2, float tb, float m_k, float n_k, float T_k, float T_k2, float tk){    
  cenario->b->N_b   = N_b;
  cenario->b->T_b   = T_b;
  cenario->b->S_b0  = S_b0;
  cenario->b->I_b0  = I_b0;
  cenario->b->T_b2  = T_b2;
  cenario->b->tb    = tb;

  cenario->k->m_k   = m_k;
  cenario->k->n_k   = n_k;
  cenario->k->T_k   = T_k;
  cenario->k->T_k2  = T_k2;
  cenario->k->tk    = tk;
}

/**
* Função: calculateB
* Parametros:
*  - Cenario *c: Objeto do tipo Canario que será utilizado para recalcular o valor de b. 
* Retorno: float b
* Descrição: Responsável por recalcular b caso caso a variavel T_b2 seja diferente de 0, isso quer dizer 
* que o cenario_2.txt foi escolhido.
* */
float calculateB(Cenario *c){
    float b = 0;
    if(c->b->T_b2 != 0)
        b = c->b->N_b/(c->b->T_b2 * c->b->S_b0 * c->b->I_b0);

    return b;
}
/**
* Função: calculateK
* Parametros:
*  - Cenario *c: Objeto do tipo Canario que será utilizado para recalcular o valor de k. 
* Retorno: float k
* Descrição: Responsável por recalcular k caso caso a variavel T_k2 seja diferente de 0, isso quer dizer 
* que o cenario_3.txt foi escolhido.
* */
float calculateK(Cenario *c){
    float k;
    if(c->k->T_k2 != 0)
        k = c->k->m_k/(c->k->n_k * c->k->T_k2);      

    return k;
} 
