#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "tipos.h"



int main(void) {
  	FILE *arquivo = fopen("parametros.txt","r");

  	if (arquivo == NULL){
		printf("Erro ao abrir arquivo");
    	exit(1);
  	}

    float t, h, b, k, N_b, T_b, S_b0, I_b0, m_k, n_k, T_k;
    int s, i, r, tempo;

    SIR *model;

    allocateMemory(model, 40, type);


  	char comando[10];
    while (fscanf(arquivo, "%s", comando) != EOF){
        if(strcmp(comando,"S(0)") == 0){
          fscanf(arquivo,"%d", &s);
          //printf("%d\n", s);
        }else if(strcmp(comando,"I(0)") == 0){
          fscanf(arquivo,"%d", &i);
          //printf("%d\n", i);
        }else if(strcmp(comando,"R(0)") == 0){
          fscanf(arquivo,"%d", &r);
          //printf("%d\n", r);
        }else if(strcmp(comando,"h") == 0){
          fscanf(arquivo,"%f", &h);
          //printf("%f\n", h);
        }else if(strcmp(comando,"N_b") == 0){
          fscanf(arquivo,"%f", &N_b);
          //printf("%f\n", N_b);
        }else if(strcmp(comando,"T_b") == 0){
          fscanf(arquivo,"%f", &T_b);
          //printf("%f\n", T_b);
        }else if(strcmp(comando,"S_b0") == 0){
          fscanf(arquivo,"%f", &S_b0);
          //printf("%f\n", S_b0);
        }else if(strcmp(comando,"I_b0") == 0){
          fscanf(arquivo,"%f", &I_b0);
          //printf("%f\n", I_b0);
        }else if(strcmp(comando,"m_k") == 0){
          fscanf(arquivo,"%f", &m_k);
          //printf("%f\n", m_k);
        }else if(strcmp(comando,"n_k") == 0){
          fscanf(arquivo,"%f", &n_k);
          //printf("%f\n", n_k);
        }else if(strcmp(comando,"T_k") == 0){
          fscanf(arquivo,"%f", &T_k);
          //printf("%f\n", T_k);
        }else if(strcmp(comando,"tempo") == 0){
          fscanf(arquivo,"%i", &tempo);
          //printf("%i\n", tempo);
        }
  	}    
    for(int k = 1; k <= s; k++){
        S[k] = k;
        //printf("S[%i] = %f\n",k, S[k]);
    }
    for(int p = 1; p <= i; p++){
        I[p] = p;
        //printf("%f", I[p]);
    }
    
    b = N_b/(T_b * S_b0 * I_b0);

    k = m_k/(n_k * T_k);

    calclModelSIR(S, I, R)(S, h, b, I, tempo, k, R);



	return 0;
}