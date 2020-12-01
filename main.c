#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "tipos.h"

int main(void) {
  int cenario;
  printf("Escolha qual cenario executar: \nCenario 0 (0), Cenario 1 (1), Cenario 2(2).\n");
  scanf("%i", &cenario);

  FILE *arquivo = selectFileToOpen(cenario);
  
  if (arquivo == NULL){
    printf("Erro ao abrir arquivo");
    exit(1);
  }else{
    /** Variveis auxiliares para armazenar os valores do arquivo **/
    float N_b, T_b, S_b0, I_b0, m_k, n_k, T_k, T_b2, T_k2, h, tb, tk, b, k;
    int s = -1, i = -1, r = -1, tempo;

    /** Ponteiro do tipo SIR que possui os objetos sucetiveis, infectados e removidos **/
    SIR *model;
    Cenario *cenario;

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

    cenario = createCenario(T_b, S_b0, I_b0, T_b2, tb, m_k, n_k, T_k, T_k2, tk);
    
    calcModelSIR(model, cenario);

    fclose(arquivo);
    free(model);
  }
	return 0;
}