#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PrintaPostsLog.h"

void PrintaPostsLog(dados user, int w){
  FILE *fdin; // Abrir a FILE do perfil do usuário para leitura, a fim de se ler os posts e imprimir na interface
  char strbin[32];
  sprintf(strbin, "Perfil%d", w); 
  fdin = fopen (strbin, "r");
  if (fdin == NULL){
    printf("Não foi possível abrir o arquivo do perfil desejado.\n");
    exit(0);
  }
  
  fseek(fdin, (sizeof(char)*176) + (sizeof(int)*53) , SEEK_SET); // ir para o começo do primeiro post
  int flag;
  int cont = 1;
  while(!feof(fdin)){
    int a = fread(user.post[cont], sizeof(char), 128, fdin);
    fread(&flag, sizeof(int), 1, fdin);
    if (a == 0){ // se fread == 0, a leitura do arquivo chegou ao fim
      break;
    }
    printf("Post %d: %s\n", cont, user.post[cont]);
    cont++;
  }

  fclose(fdin);
} 

