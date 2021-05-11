#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DeletaPostLog.h"

void DeletaPostLog(dados user, int w){
  int del; // flag para deletar posts (del = 1 -> deletar ; deel = 2 -> não deletar)
  printf("\nPara deletar alguma besteira que tenha postado, digite 1. Se você ainda tem coragem de continuar com essa vergonha no seu perfil, digite 2.\n");
  while (scanf("%d", &del) == 0 || (del != 1 && del != 2)){
  printf("Comando inválido. Digite novamente: ");
  setbuf(stdin, NULL);
  }
  getchar();
  if (del == 1){ // Deletar post
    FILE *fdin; // Abrir a FILE do usuário para leitura   
    char strbin[32];
    sprintf(strbin, "Perfil%d", w); 
    fdin = fopen (strbin, "r");
    if (fdin == NULL){
      printf("Não foi possível abrir o arquivo do perfil desejado.\n");
      exit(0);
    }

    for(int i = 0; i < 50; i++){
      fread(&user.seguindo[i], sizeof(int), 1, fdin);
    }
    fread(user.nome, sizeof(char), 32, fdin);
    fread(user.login, sizeof(char), 16, fdin);
    fread(&user.nasc.dia, sizeof(int), 1, fdin);
    fread(&user.nasc.mes, sizeof(int), 1, fdin);
    fread(&user.nasc.ano, sizeof(int), 1, fdin);
    fread(user.interesses, sizeof(char), 128, fdin);
    
    long posinicial; // posição do primeiro post
    posinicial = ftell(fdin);

    fseek(fdin, 0, SEEK_END); 
    long posfinal;
    posfinal = ftell(fdin); // posição do final do arquivo
  
    int numposts = (posfinal - posinicial) / 132;
    
    printf("\nEscolha o número do post que queira deletar.\nSe é que isso pode ser chamada de post...\n");
    int num; // número do post a ser deletado
    while (scanf("%d", &num) == 0 || num < 1 || num > numposts ){
        printf("Comando inválido. Digite novamente: ");
        setbuf(stdin, NULL);
    }

    FILE *fd; // Abertura de uma nova FILE para ser igual à do perfil do usuário, porém sem o post que foi deletado.
    char s[32];
    sprintf(s, "Perfil%d.1", w); 
    fd = fopen (s, "w+");
    if (fd == NULL){
      printf("Não foi possível abrir o arquivo do perfil desejado.\n");
      exit(0);
    }
    for(int i = 0; i < 50; i++){
      fwrite(&user.seguindo[i], sizeof(int), 1, fd);
    }
    fwrite(user.nome, sizeof(char), 32, fd);
    fwrite(user.login, sizeof(char), 16, fd);
    fwrite(&user.nasc.dia, sizeof(int), 1, fd);
    fwrite(&user.nasc.mes, sizeof(int), 1, fd);
    fwrite(&user.nasc.ano, sizeof(int), 1, fd);
    fwrite(user.interesses, sizeof(char), 128, fd);
      
    fseek(fdin, (sizeof(char)*176) + (sizeof(int)*53), SEEK_SET);
    
    int flag; 
    int i;

    for (i = 1; i <= numposts; i++){
      fread(user.post[i], sizeof(char), 128, fdin);
      fread(&flag, sizeof(int), 1, fdin);
      if (i == num){ // Não escreve esse post na nova FILE.
        printf("Post %d: Deletado\n\n",i);
      } else {
        fwrite(user.post[i], sizeof(char), 128, fd);
        fwrite(&flag, sizeof(int), 1, fd);
        printf("Post %d: %s\n", i, user.post[i]);
      }
    }
    
    fclose(fdin);

    remove(strbin); // Deletar a FILE antiga que continha o post a ser deletado

    fseek(fd, 0, SEEK_SET); // Voltar para o início da nova FILE para que seja feita a transcrição para a FILE original, que será recriada.

    sprintf(strbin, "Perfil%d", w); 
    fdin = fopen (strbin, "w");
    if (fdin == NULL){
      printf("Não foi possível abrir o arquivo do perfil desejado.\n");
      exit(0);
    }

    for(int i = 0; i < 50; i++){
      fread(&user.seguindo[i], sizeof(int), 1, fd);
      fwrite(&user.seguindo[i], sizeof(int), 1, fdin);
    }
    
    fread(user.nome, sizeof(char), 32, fd);
    fwrite(user.nome, sizeof(char), 32, fdin);

    fread(user.login, sizeof(char), 16, fd);
    fwrite(user.login, sizeof(char), 16, fdin);

    fread(&user.nasc.dia, sizeof(int), 1, fd);
    fwrite(&user.nasc.dia, sizeof(int), 1, fdin);

    fread(&user.nasc.mes, sizeof(int), 1, fd);
    fwrite(&user.nasc.mes, sizeof(int), 1, fdin);

    fread(&user.nasc.ano, sizeof(int), 1, fd);
    fwrite(&user.nasc.ano, sizeof(int), 1, fdin);

    fread(user.interesses, sizeof(char), 128, fd);
    fwrite(user.interesses, sizeof(char), 128, fdin);

    for (int i = 1; i <= (numposts - 1); i++){
      fread(user.post[i], sizeof(char), 128, fd);
      fwrite(user.post[i], sizeof(char), 128, fdin);
      fread(&flag, sizeof(int), 1, fd);
      fwrite(&flag, sizeof(int), 1, fdin);
    }

    fclose(fd);
    fclose(fdin);

    remove(s); // Após a transcrição, remove-se a FILE que foi usada para isso, ficando, assim, apenas com o arquivo do perfil sempre atualizado do usuário.
  }
}