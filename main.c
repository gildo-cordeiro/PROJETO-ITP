#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "tipos.h"

int main(void) {

    /** Carregando arquivo **/
  	FILE *arquivo = fopen("cenario.txt","r");

    /** Verificando carregou o arquio corretamente **/
  	if (arquivo == NULL){
		printf("Erro ao abrir arquivo");
    	exit(1);
  	}

    /** Variveis auxiliares para armazenar os valores do arquivo **/
    float t, h, b, k, N_b, T_b, S_b0, I_b0, m_k, n_k, T_k, T_b2, T_k2, tb, tk;
    int s = -1, i = -1, r = -1, tempo;

    /** Ponteiro do tipo SIR que possui os objetos sucetiveis, infectados e removidos **/
    SIR *model;
    Cenario *cenario = malloc(sizeof(Cenario));

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
        
        // pensar em como calcular o novo e tb e tk
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
    
    /** Alocando memoria para os vetores dentro do objeto model **/
    model = allocateMemory(s, i, r);

    /** Preenchendo os vetores de acordo com o tamanho lido do arquivo **/
    fillVector(model->suc, s);

    fillVector(model->inf, i);

    fillVector(model->rem, r);

    /** Calculo das variaveis b e k da equação **/
    b = N_b/(T_b * S_b0 * I_b0);

    k = m_k/(n_k * T_k);

    model->h = h;
    model->k = k;
    model->b = b;
    model->t = t;

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

    /** 
    * Realizando o calculo da equaação e descobrindo o valores correspondentes as pessoas sucetives,
    * infectadas e removidas
    **/
    calcModelSIR(model, cenario);

    fclose(arquivo);
    free(model->suc);
    free(model->inf);
    free(model->rem);
    free(model);
	return 0;
}