#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PrintaFeedLog.h"

void PrintaFeedLog(dados user, int w){
  FILE *pessoal; // Abrir a FILE do perfil do usuário para acessar o seu vetor seguindo[50] e transcrevê-lo para um vetor v[50]
  char strpessoal[32];
  sprintf(strpessoal, "Perfil%d", w);
  pessoal = fopen (strpessoal, "r");
  if (pessoal == NULL){
    printf("Não foi possível abrir o arquivo do perfil pessoal\n");
    exit(0);
  }
  int v[50];
  for (int i = 0; i < 50; i++){
    fread(&user.seguindo[i], sizeof(int), 1, pessoal);
    v[i] = user.seguindo[i];
  }
  fclose(pessoal);
  
  int i = 0;
  int q; // índice de um perfil que o usuário segue (q != 0)
  
  while (i < 50){

    if(v[i] != 0){
      q = v[i];
      
    FILE *fdin; // Abrir a FILE de todos os perfis, um por vez, que o usuário segue 
    char strbin[32];
    sprintf(strbin, "Perfil%d", q); 
    fdin = fopen (strbin, "r");
   
    if (fdin == NULL){
      printf("Não foi possível abrir o arquivo do perfil desejado.\n");
      exit(0);
    }
    
    for (int cont = 0; cont < 50; cont++){
      fread(&user.seguindo[cont], sizeof(int), 1, fdin);
    }
    fread(user.nome, sizeof(char), 32, fdin);
    printf("Posts de %s\n\n", user.nome);
    fread(user.login, sizeof(char), 16, fdin);
    fread(&user.nasc.dia, sizeof(int), 1, fdin);
    fread(&user.nasc.mes, sizeof(int), 1, fdin);
    fread(&user.nasc.ano, sizeof(int), 1, fdin);
    fread(user.interesses, sizeof(char), 128, fdin);

    long pos1 = ftell(fdin); // início do primeiro post 
 
    fseek(fdin, 0, SEEK_END);
    long pos2 = ftell(fdin);
 
    int numposts = (pos2 - pos1)/132; // 132 = (128 caracteres do post) + (1 inteiro de cada flag)

    fseek(fdin, sizeof(char)*176 + sizeof(int)*53, SEEK_SET); // voltar para o início do primeiro post
    
    int flag; // flag referente a cada post
    int qtd = numposts/5; // número de vezes que o laço da linha 68 será executado
    int r = numposts % 5; // se r > 0, entao o laço será executado mais 1 vez
    int x = 0; // a cada vez que o laço for executado, x é incrementado para que os posts seja impressos sempre de 5 em 5, e o valor de h sempre esteja atualizado
    int h; // contador para imprimir de 5 em 5
    int pula = 0; // flag para executar o laço mais 1 vez, caso r > 0
    int cont2 = 1;
    while(cont2 <= qtd || (r > 0 && qtd == 0)){
      for (h = 1+5*x; h <= 5+5*x && h <= numposts; h++){
        fread(user.post[h], sizeof(char), 128, fdin);
        fread(&flag, sizeof(int), 1, fdin);
        printf("Post %d: %s\n", h, user.post[h]);
      }
      x++;
      printf("Para ler mais posts, digite 1. Caso queira fazer algo de útil e ser alguém na vida, digite 2 para parar de ler essas escórias que chamam de post.\n");
      int dig;
      while (scanf("%d", &dig) == 0 || (dig != 1 && dig != 2 )){
        printf("Comando inválido. Digite novamente: ");
        setbuf(stdin, NULL);
      }
      if (dig == 1){
        pula = 0;
        continue;
      } else {
        pula = 1;
        break;
      }
      cont2++;
    }
    if (pula == 0){
      if (r > 0){
        for (int y = 1; y <= r; y++){
          int a = fread(user.post[h], sizeof(char), 128, fdin);
          fread(&flag, sizeof(int), 1, fdin);
          if (a == 0){
            break;
          }
        }
        printf("Post %d: %s\n", h, user.post[h]);
        h++;
      }
    }
    fclose(fdin);
    }
    i++;
  }
}
