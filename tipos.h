#ifndef tipos_h
#define tipos_h

typedef struct{
    int suc, inf, rem, t;
    float h, b, k;
}SIR;

typedef struct{
    float N_b, T_b, S_b0, I_b0, T_b2, tb;
}DataB;

typedef struct{
    float m_k, n_k, T_k, T_k2, tk;
}DataK;

typedef struct{
    DataB b;
    DataK k;
}Cenario;




#endif