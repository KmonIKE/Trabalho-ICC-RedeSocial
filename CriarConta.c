#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CriarConta.h"

void CriarConta(dados user, int k){
  // Abertura das FILES Dados e Nomes para controle do número de usuários
    FILE *dadosin; 
    dadosin = fopen("Dados.txt", "a+");
    if (dadosin == NULL){
      printf("Não foi possível abir o arquivo Dados\n");
      exit(0);
    }

    FILE *nomesin;
    nomesin = fopen("Nomes.txt", "a+");
    if (nomesin == NULL){
      printf("Não foi possível abir o arquivo Nomes\n");
      exit(0);
    }

    int cont;
    for (cont = 0 ; cont <= k ; cont++){
      fread(&k, sizeof(int), 1, dadosin);
      fread(user.login, sizeof(char), 16, dadosin);
      fread(&k, sizeof(int), 1, nomesin);
      fread(user.nome, sizeof(char), 32, nomesin);
    }
    k++;
    fwrite(&k, sizeof(int), 1, dadosin);
    fwrite(&k, sizeof(int), 1, nomesin);

    printf("\nSeja bem vindo à VS, aqui você disperdiçará horas do seu dia com pessoas que você nunca viu na vida, com o único objetivo de ficar triste com a falsa felicidade alheia.\n");
    printf("\nSe você ainda deseja isso para a sua vida, entao vamo lá!\n");

    // Cadastro de usuário:
 
    FILE *fdin;   
    char strbin[32];
    sprintf(strbin, "Perfil%d", k); 
    fdin = fopen (strbin, "w");
    if (fdin == NULL){
      printf("Não foi possível abrir o arquivo do perfil desejado.\n");
      exit(0);
    }
    
    for(int i = 0; i < 50; i++){
      user.seguindo[i] = 0; 
      fwrite(&user.seguindo[i], sizeof(int), 1, fdin);
    }

    
    printf("\nPrimeiramente digite seu nome\n");
    getchar();
    fgets(user.nome, 32, stdin);
    fwrite(user.nome, sizeof(char), 32, fdin);
    fwrite(user.nome, sizeof(char), 32, nomesin);
    
    fclose(nomesin);

    printf("\nEscolha agora um login\nEle será usado para você entrar nesta formosura\n");

    fgets(user.login, 16, stdin);
    fwrite(user.login, sizeof(char), 16, dadosin);
    fwrite(user.login, sizeof(char), 16, fdin);

    fclose(dadosin);
   
    printf("\nDigite sua data de nascimento\nApenas para você ter a falsa sensação de ser amado com parabéns falsos no seu aniversário, se ganhar...\n");
    printf("Dia de nascimento: ");
    scanf("%d", &user.nasc.dia);
    fwrite(&user.nasc.dia, sizeof(int), 1, fdin);
    printf("Mês de nascimento: ");
    scanf("%d", &user.nasc.mes);
    fwrite(&user.nasc.mes, sizeof(int), 1, fdin);
    printf("Ano de nascimento: ");
    scanf("%d", &user.nasc.ano);
    fwrite(&user.nasc.ano, sizeof(int), 1, fdin);
    
    printf("\nPor fim, digite seus interesses\n");
    printf("\nSeus interesses são apenas para seus seguidores te conhecerem melhor, não sei de onde tirou que vamos vender essas informações ... \n");
    
    getchar();
    fgets(user.interesses, 128, stdin);
    fwrite(user.interesses, sizeof(char), 128, fdin); 

    printf("\nNa real, vamos vender suas informações sim, ninguém se importa com o que você gosta kkk\n");
  
    fclose(fdin);

}



