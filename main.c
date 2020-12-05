#include <stdio.h>
#include "sir.h"
#include "csv.h"

int main(void) {
  int c;
  printf("Escolha qual cenario executar: \nCenario 0 (0), Cenario 1 (1), Cenario 2(2).\n");
  scanf("%i", &c);

  FILE *arquivo = selectFileToOpen(c);
  
  if (arquivo == NULL){
    printf("Erro ao abrir arquivo");
    exit(1);
  }else{
    SIR *model;
    Cenario *cenario;

    readFile(model, cenario, arquivo);
    
    calcModelSIR(model, cenario);

    fclose(arquivo);
    free(model);
    free(cenario);
  }
	return 0;
}