#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logar.h"

int logar(dados user){

  char login[16];
  getchar();
  printf("Informe seu login para entrar na VS:\n");
  fgets(login, 16, stdin);

  FILE *dadosin; // Abrir a FILE Dados para chegar a validade do login informado pelo usuário na hora de efetuar o Login.
  dadosin = fopen("Dados.txt", "r");
  if (dadosin == NULL){
    printf("Não foi possível abrir o arquivo Dados.txt\n");
    exit(0);
  }
  int w; // Índice do perfil que vai logar
  while (!feof(dadosin)) {
    fread(&w, sizeof(int), 1, dadosin);
    fread(user.login, sizeof(char), 16, dadosin);

    if (strcmp(login, user.login) == 0){ // Strings iguais -> login válido
      fclose(dadosin);
      return w; // Índice do perfil logado
      
    }else{
      continue;
    }
  }
  fclose(dadosin); 
  return -1; // Perfil inválido
}
