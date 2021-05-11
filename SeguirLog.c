#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SeguirLog.h"

void SeguirLog(dados user, int w){
  int i = 0;
  do{
  
    int seguir; // flag para seguir algum usuário (1 para seguir e 2, caso contrário)
    printf("Para seguir algum usuário, digite 1. Caso contrário, digite 2.\n");
    while (scanf("%d", &seguir) == 0 || (seguir != 1 && seguir != 2)){
    printf("Comando inválido. Digite novamente: ");
    setbuf(stdin, NULL);
    }
    getchar();
    
    if (seguir == 1){
      char nome[32];
      printf("Digite o nome do usuário que queira seguir.\n");
      fgets(nome, 32, stdin);

      FILE *nomesin; // Verificar se o nome informado está cadastrado
      nomesin = fopen("Nomes.txt", "r");
      if (nomesin == NULL){
      printf("Não foi possível abrir o arquivo Nomes.txt\n");
      exit(0);
      }
     
      int q; // índice (ou número) do perfil a ser seguido
      while (!feof(nomesin)) {
        int a = fread(&q, sizeof(int), 1, nomesin);
        fread(user.nome, sizeof(char), 32, nomesin);
        if (a == 0){
          printf("Perfil não encontrado\n"); 
          break;
        }
        
        if (strcmp(nome, user.nome) == 0){ // achou o nome
          fclose(nomesin);
          break; 
          
        }else{
          continue;
        }   
    }
    fclose(nomesin); 
    // Neste ponto, "q" é o indice do perfil a ser seguido
  
    FILE *fdin; // Abrir a FILE do perfil do usuário com r+
    char strbin[32];
    sprintf(strbin, "Perfil%d", w); 
    fdin = fopen (strbin, "r+");
    if (fdin == NULL){
      printf("Não foi possível abrir o arquivo do perfil desejado.\n");
      exit(0);
    }
    
    for(int i = 0; i < 50; i++){
      fread(&user.seguindo[i], sizeof(int), 1, fdin);
    }
    fseek (fdin, 0, SEEK_SET);
    int j;
    for (j = 0; j <= i; j++){
      fread(&user.seguindo[j], sizeof(int), 1, fdin);

      if (user.seguindo[j] == 0){ // posição do vetor ainda não demarcada
        user.seguindo[j] = q;
        fseek (fdin, sizeof(int)*j, SEEK_SET);
        fwrite(&user.seguindo[j], sizeof(int), 1, fdin); // escrever o valor de "q" sobre o zero que estava anteriormente.
        break;
      } 
    }

    fclose(fdin);
    i++;

  } else {
    break;
  } 

  }while(i < 50);

}


