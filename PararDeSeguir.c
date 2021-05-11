#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PararDeSeguir.h"

void PararDeSeguir(dados user, int w){
  printf("Para para de seguir algúem, digite 1. Agora, se você ainda quer continuar com esse embuste no seu feed, digite 2.\n");

  int parar; // flag para parar (ou não) de seguir alguém (1 para parar de seguir e 2, caso contrário)
  
  while (scanf("%d", &parar) == 0 || (parar != 1 && parar != 2 )){
    printf("Comando inválido. Digite novamente: ");
    setbuf(stdin, NULL);
  }
  
  if (parar == 1){
    FILE *fdin; // Abrir a file do perfil do usuário
    char strbin[32];
    sprintf(strbin, "Perfil%d", w); 
    fdin = fopen (strbin, "r");
    if (fdin == NULL){
      printf("Não foi possível abrir o arquivo do perfil desejado.\n");
      exit(0);
    }
    int v[50]; // transcrição do vetor seguindo[50] para o vetor v[50]
    for (int i = 0; i < 50; i++){
      fread(&user.seguindo[i], sizeof(int), 1, fdin);
      v[i] = user.seguindo[i];
    }
    fclose(fdin);
    for (int i = 0; i < 50; i++){ // Abrir todas as FILES dos perfis que o usuário segue

      if (v[i] != 0){ 
        int q = v[i]; // q é o índice de um perfil que o usuário segue
        FILE *fd; // Abrir a FILE de todas as pessoas que o usuário segue para pegar o seus respectivos nomes
        char str[32];
        sprintf(str, "Perfil%d", q); 
        fd = fopen (str, "r");
        if (fd == NULL){
          printf("Não foi possível abrir o arquivo do perfil desejado.\n");
          exit(0);
        }
        
        for (int j = 0; j < 50; j++){
          fread(&user.seguindo[j], sizeof(int), 1, fd);
        }

        char string[32];
        fread(string, sizeof(char), 32, fd);
        printf("Perfil %d: %s\n", q, string); // Listar todos os nomes de quem o usuário segue para que ele possa escolher quem ele irá parar de seguir
        fclose(fd);
      }
    }
    
    printf("Digite o número do perfil de quem você quer parar de seguir\n");
    int n; // índice do perfil que o usuário escolheu parar de seguir
    while (scanf("%d", &n) == 0 || (n != 1 && n != 2 )){
    printf("Comando inválido. Digite novamente: ");
    setbuf(stdin, NULL);
    }
  
    fdin = fopen (strbin, "r+"); // abrir a file do perfil do usuário para que o vetor que contém os perfis que ele segue seja alterado
    if (fdin == NULL){
      printf("Não foi possível abrir o arquivo do perfil desejado.\n");
      exit(0);
    }
    int i;
    for (i = 0; i < 50; i++){
      fread(&user.seguindo[i], sizeof(int), 1, fdin);
      if (user.seguindo[i] == n){ // remover o índice do perfil, no vetor seguindo[50], que o usuário deixou de seguir
        user.seguindo[i] = 0;
        break;
      }
    }
    fseek (fdin, sizeof(int)*i, SEEK_SET);
    fwrite(&user.seguindo[i], sizeof(int), 1, fdin);
    fclose(fdin);
  }
}

