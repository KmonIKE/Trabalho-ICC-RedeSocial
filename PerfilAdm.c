 #include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "PerfilAdm.h"
#include "CriarConta.h"

void PerfilAdm(){
  dados user; 
/////////////////////////  
///NÚMERO DE USUÁRIOS:\\\
/////////////////////////
  FILE *dadosin; 
  dadosin = fopen("Dados.txt", "r");
  if (dadosin == NULL){
    printf("Não foi possível abrir o arquivo Dados.\n");
    exit(0);
  }

  fseek(dadosin, 0, SEEK_END);
  long posfinal = ftell(dadosin);
  int k = posfinal/20; // número total de usuários antes de o ADM deletar algum
  fclose(dadosin);

  int cont = 0;
  for (int i = 1; i <= k; i++){
    FILE *fdin;
    char str[32];
    sprintf(str, "Perfil%d", i);
    fdin = fopen(str, "r");
    while (fdin == NULL){
      cont++;
      fdin++;
    }
  }

  int total = k - cont; // número de usuários depois de o ADM revolver algum usuário

  printf("\nNÚMERO TOTAL DE USUÁRIOS DA REDE: %d\n\n", total);

  ///////////////////////////////
  // NÚMERO TOTAL DE POSTS (N)///
  //PERFIS EXCLUIDOS E ATIVOS///
  //////////////////////////////
  int N = 0;
  for (int i = 1; i <= k ; i++){
    FILE *fdin;   
    char str[32];
    sprintf(str, "Perfil%d", i); 
    fdin = fopen (str, "r");
    if (fdin == NULL){
      printf("PERFIL %d - EXCLUÍDO.\n", i);
      continue;
    }   
    
    fseek(fdin, sizeof(char)*176+sizeof(int)*53, SEEK_SET);
    long posinicial = ftell(fdin);
    fseek (fdin, 0, SEEK_END);
    long posfinal = ftell(fdin);
    int numposts = (posfinal - posinicial)/132;
    N += numposts;

    fseek(fdin, 0 , SEEK_SET);
    for (int j = 0; j < 50; j++){
      fread(&user.seguindo[j], sizeof(int), 1, fdin);
    }
    printf("\nPERFIL %d - DADOS:\n\n", i);
    
    fread(user.nome, sizeof(char), 32, fdin);
    printf("Nome: %s\n", user.nome);
    fread(user.login, sizeof(char), 16, fdin);
    printf("Login: %s\n", user.login);
    fread(&user.nasc.dia, sizeof(int), 1, fdin);
    fread(&user.nasc.mes, sizeof(int), 1, fdin);
    fread(&user.nasc.ano, sizeof(int), 1, fdin);
    printf("Data de nascimento: %d/%d/%d\n\n", user.nasc.dia, user.nasc.mes, user.nasc.ano);
    fread(user.interesses, sizeof(char), 128, fdin);
    printf("Interesses: %s\n", user.interesses);
    int flag;
    for (int j = 1; j <= numposts; j++){
      fread(user.post[j], sizeof(char), 128, fdin);
      printf("Post %d: %s\n", j , user.post[j]);
      fread(&flag, sizeof(int), 1, fdin);
    }
    fclose(fdin);
  }
  printf("\nNÚMERO TOTAL DE POSTS NA REDE: %d\n", N);

  ////////////////////////////////////////////
  //COMANDOS ADM: INSERIR,REMOVER,CONSULTAR///
  ////////////////////////////////////////////
  printf("\nCOMANDOS:\n1 - Inserir usuário\n2 - Remover usuário\n3 - Consultar usuário\n");
  int comando;
  while(scanf("%d", &comando) == 0 || (comando != 1 && comando != 2 && comando != 3)){
    printf("Comando inválido. Digite novamente: ");
    setbuf(stdin, NULL);
  }
  if (comando == 1){ // Inserir  usuário
    int u = 0;
    CriarConta(user, u);
  }
  if (comando == 2){ // Remover usuário
    printf("Digite o número do perfil que queira deletar\n");
    int num;
    while(scanf("%d", &num) == 0 || (num < 1 || num > k)){
    printf("Comando inválido. Digite novamente: ");
    setbuf(stdin, NULL);
    }
    FILE *fdin;   
    char str[32];
    sprintf(str, "Perfil%d", num); 
    remove(str);
    printf("\nPerfil %d removido com sucesso!\n", num);
    
  }
  if (comando == 3){ // Consultar usuário
    printf("\nDigite o número do perfil que queira consultar\n");
    int consultar;
    while(scanf("%d", &consultar) == 0 || (consultar < 1 || consultar > k)){
    printf("Comando inválido. Digite novamente: ");
    setbuf(stdin, NULL);
    }

    FILE *fdin; // Abrir o perfil do usuário para consulta
    char str[32];
    sprintf(str, "Perfil%d", consultar); 
    fdin = fopen (str, "r");
    if (fdin == NULL){
      printf("\nO perfil desejado foi deletado\n");
      exit(0);
    }
    fseek(fdin, sizeof(char)*176+sizeof(int)*53, SEEK_SET);
    long posinicial = ftell(fdin);
    fseek (fdin, 0, SEEK_END);
    long posfinal = ftell(fdin);
    int numposts = (posfinal - posinicial)/132;

    fseek(fdin, 0 , SEEK_SET);
    for (int j = 0; j < 50; j++){
      fread(&user.seguindo[j], sizeof(int), 1, fdin);
    }
    printf("Perfil %d - Dados:\n", consultar);
    
    fread(user.nome, sizeof(char), 32, fdin);
    printf("Nome: %s\n", user.nome);
    fread(user.login, sizeof(char), 16, fdin);
    printf("Login: %s\n", user.login);
    fread(&user.nasc.dia, sizeof(int), 1, fdin);
    fread(&user.nasc.mes, sizeof(int), 1, fdin);
    fread(&user.nasc.ano, sizeof(int), 1, fdin);
    printf("Data de nascimento: %d/%d/%d\n", user.nasc.dia, user.nasc.mes, user.nasc.ano);
    fread(user.interesses, sizeof(char), 128, fdin);
    printf("Interesses: %s\n", user.interesses);
    int flag;
    for (int j = 1; j <= numposts; j++){
      fread(user.post[j], sizeof(char), 128, fdin);
      printf("Post %d: %s\n", j , user.post[j]);
      fread(&flag, sizeof(int), 1, fdin);
    }
    fclose(fdin);
  }

  ///////////////////////////////////
  //REMOVER TODOS OS DADOS DA REDE///
  ///////////////////////////////////
  printf("\nDeseja remover todos os dados rede?\nCaso queira, pressione 1. Caso contrário, pressione 2\n");
  int rem;
  while(scanf("%d", &rem) == 0 || (rem != 1 && rem != 2)){
    printf("Comando inválido. Digite novamente: ");
    setbuf(stdin, NULL);
  }
  if (rem == 1){
    printf("Pressione 1 para confirmar a operação\nOu pressione 2 para desistir\n");
    int conf;
    while(scanf("%d", &conf) == 0 || (conf != 1 && conf != 2)){
    printf("Comando inválido. Digite novamente: ");
    setbuf(stdin, NULL);
    }
    if (conf == 1){
      for (int i = 1; i <= k; i++){
        FILE *fdin;   
        char str[32];
        sprintf(str, "Perfil%d", i); 
        remove(str);
      }
      remove("Dados.txt");
      remove("Nomes.txt");
      printf("Todos os dados da rede foram removidos com sucesso!\n");
    }
  }

  //////////////////////
  //SAIR DO PROGRAMA:///
  //////////////////////

  printf("Para sair do programa, digite 1.\n");
  int sair;
  while(scanf("%d", &sair) == 0 || sair != 1 ){
    printf("Comando inválido. Digite novamente: ");
    setbuf(stdin, NULL);
  }
  exit(0);
  
}

