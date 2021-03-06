#include "libs.h"

int main(void) {
  int c;
  printf("Escolha qual cenario executar: \nCenario 0 (0), Cenario 1 (1), Cenario 2 (2).\n");
  scanf("%i", &c);
  
  FILE *arquivo = selectFileToOpen(c);
  
  if (arquivo == NULL){
    printf("Erro ao abrir arquivo");
    exit(1);
  }else{
    // Alocação de memoria para os objetos model e cenario.
    SIR *model = malloc(sizeof(SIR));
    Cenario *cenario = malloc(sizeof(SIR));

    readFile(model, cenario, arquivo);

    calcModelSIR(model, cenario);

    // Fechando o arquivo e liberando memoria dos objetos alocados.
    fclose(arquivo);
    free(model);
    free(cenario);
  }
	return 0;
}