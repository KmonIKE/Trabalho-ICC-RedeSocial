#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PrintaDadosLog.h"

void PrintaDadosLog(dados user, int w){
  // Abrir a FILE do perfil do usuário para leitura e imprimir os dados pessoais na interface
  FILE *fdin;  
  char strbin[32];
  sprintf(strbin, "Perfil%d", w); 
  fdin = fopen (strbin, "r");
  if (fdin == NULL){
    printf("Não foi possível abrir o arquivo do perfil desejado.\n");
    exit(0);
  }
  for (int i = 0; i < 50; i++){
    fread(&user.seguindo[i], sizeof(int), 1, fdin);
  }
  fread(user.nome, sizeof(char), 32,fdin);
  printf("\nNome: %s\n", user.nome);

  fread(user.login, sizeof(char), 16, fdin);

  fread(&user.nasc.dia, sizeof(int), 1, fdin);
  fread(&user.nasc.mes, sizeof(int), 1, fdin);
  fread(&user.nasc.ano, sizeof(int), 1, fdin);
  printf("Data de aniversário: %d/%d/%d\n", user.nasc.dia, user.nasc.mes, user.nasc.ano);

  fread(user.interesses, sizeof(char), 128, fdin);
  printf("\nInteresses: %s\n", user.interesses);

  fclose(fdin);
  
}