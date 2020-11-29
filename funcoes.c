#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>

void allocateMemory(SIR *model, int size, int type){
    model = malloc(sizeof(SIR));
    model->S = malloc(size * sizeof(float));
}

float funcSuscetiveis(float *S, float h, float b, float *I, int t, float k, float *R){
    float sucetivel = 0.0;
    float *suc, *inf, *rem;
    float tempo[504], tmp = 0;

    suc = calloc(504, sizeof(float));
    inf = calloc(504, sizeof(float));   
    rem = calloc(504, sizeof(float));


    suc[0] = (S[69-1] - h * b * (S[69-1]) * (I[3-1])); 
    rem[0] = R[1-1] + (h * k * I[3-1]);    
    inf[0] = I[3-1] + (h * ((b * S[69-1] * I[3-1]) - (k * I[3-1])));

    // suc[1] = (suc[1-1] - h * b * (suc[1-1]) * (inf[1-1])); 
    // rem[1] = rem[1-1] + (h * k * inf[1-1]);    
    // inf[1] = inf[1-1] + (h * ((b * suc[1-1] * inf[1-1]) - (k * inf[1-1])));

    // suc[2] = (suc[2-1] - h * b * (suc[2-1]) * (inf[2-1])); 
    // rem[2] = rem[2-1] + (h * k * inf[2-1]);    
    // inf[2] = inf[2-1] + (h * ((b * suc[2-1] * inf[2-1]) - (k * inf[2-1])));

    // printf("S %.3f\n", suc[2]);
    // printf("I %.4f\n", inf[2]);
    // printf("R %.7f\n", rem[2]);
    int count = 1;
    while(tempo[count] < 45){
        suc[count] = (suc[count-1] - h * b * (suc[count-1]) * (inf[count-1]));
        rem[count] = rem[count-1] + (h * k * inf[count-1]);    
        inf[count] = inf[count-1] + (h * ((b * suc[count-1] * inf[count-1]) - (k * inf[count-1])));
        
        tmp += h;        
        tempo[count] = tmp;
        count++; 
    }
    for(int i = 0; i < 44; i++){
        printf("suc %.3f\n", suc[i]);
        printf("inf %.4f\n", inf[i]);
        printf("rem %.7f\n", rem[i]);
        printf("tempo %.1f\n", tempo[i]);
    }
    // printf("-----------------6 min\n");
    // // {67.986, 2.0136, ??}
    // S[68] = (S[69-1] - h * b * (S[69-1]) * (I[3-1])); 
    // R[0]  = R[1-1] + (h * k * I[3-1]);    
    // I[2]  = I[3-1] + (h * ((b * S[69-1] * I[3-1]) - (k * I[3-1])));
    // printf("S %.3f\n", S[68]);
    // printf("I %.4f\n", I[2]);
    // printf("R %.7f\n", R[0]);
    // //0.0022727

    // printf("-----------------12 min\n");
    // // {67.973, 2.0136, ??}
    // S[67] = (S[69-1] - h * b * (S[69-1]) * (I[3-1]));
    // R[0]  = R[1-1] + (h * k * I[3-1]);    
    // I[1]  = I[3-1] + (h * ((b * S[69-1] * I[3-1]) - (k * I[3-1])));
    // printf("S %.3f\n", S[67]);
    // printf("I %.4f\n", I[1]);
    // printf("R %.7f\n", R[0]);

    // printf("-----------------18 min\n");
    // S[65] = (S[66-1] - h * b * (S[66-1]) * (I[1-1]));
    // I[0]  = I[1-1] + (h * ((b * S[66-1] * I[1-1]) - (k * I[1-1])));
    // printf("S %.3f\n", S[65]);
    // printf("I %.4f\n", I[0]);

    // printf("-----------------24 min\n");
    // S[65] = (S[67-1] - h * b * (S[67-1]) * (I[1-1]));
    // I[0]  = I[1-1] + (h * ((b * S[67-1] * I[1-1]) - (k * I[1-1])));
    // printf("S %.3f\n", S[65]);
    // printf("I %.4f\n", I[0]);

    
    return sucetivel;
}

float funcInfectados(float *I, float b, float h, float k, int t){
  float infectado = 0;
  
  for(int i = 0; i < t; i++){
    infectado += I[i-1] + h * (b * (I[i-1] * (I[i-1] - k * (I[i-1]))));
  }

  return infectado;
}

float funcRemovidos(float *r, float h, float k, int t){
  float removido = 0;

  for(int i = 0; i < t; i++){
    removido += r[t-1] + h * k * (r[t-1]);
  }

  return removido;
} 
