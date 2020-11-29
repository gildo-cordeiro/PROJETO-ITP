#ifndef tipos_h
#define tipos_h

typedef struct{
    SUC *S;
    INF *I;
    REM *R;
}SIR;

typedef struct{
  float h, b, k;
  int type;
}INF;

typedef struct{
  float h, b;
  INF i;
}SUC;

typedef struct{
  float h, k;
  int type;
  INF i;
}REM;

#endif