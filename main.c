#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "struct.h"
#include "CriarConta.h"
#include "logar.h"
#include "PrintaDadosLog.h"
#include "CriaPostLog.h"
#include "PrintaPostsLog.h"
#include "DeletaPostLog.h"
#include "SeguirLog.h"
#include "PrintaFeedLog.h"
#include "PararDeSeguir.h"
#include "PerfilAdm.h"

// "q" É A VARIÁVEL DO ÍNDICE DOS PERFIS QUE O USUÁRIO SEGUE.
// "k" É O PARÂMETRO UTILIZADO PARA SE CRIAR UMA CONTA.
// "w" É A VARIÁVEL QUE LOGA NOS PERFIL COM OS INDICES.

int main(void){

  dados user;
  
  printf("Seja bem vindo à VERGONHA SOCIAL!\nPara fazer login, digite 1.\nPara criar uma conta, digite 2.\n");
  int a;
  /*
  a == 1 -> fazer login
  a == 2 -> criar uma nova conta
  a == 181995 -> acessar o perfil do administrador
  */
  while (scanf("%d", &a) == 0 || (a != 1 && a != 2 && a != 181995)){
  printf("Comando inválido. Digite novamente: ");
  setbuf(stdin, NULL);
  }

  if (a == 181995){
    PerfilAdm();
  }

  if (a == 2){
    int k = 0;
    CriarConta(user, k);
    a = 1;
    printf("Pressione a tecla Enter para fazer login\n");
  }
  
  if (a == 1){
    int w;
    w = logar(user);
    if (w == -1){
      printf("Login inválido.\n");
      printf("Por favor, tente mais tarde!\n");
      exit(0);
      
    } else {
      printf("\nSeja bem vindo(a) ao seu perfil!\n");
      int flag = 1;
      do{
        if (flag == 1){
          // -> pagina do perfil pessoal
          PrintaDadosLog(user, w);
          CriaPostLog(user, w);
          PrintaPostsLog(user, w);
          DeletaPostLog(user, w);
          printf("Para fazer logout, tecle 0.\nPara continuar, tecle 1.\n");
          scanf("%d", &flag);
          
          if (flag == 0){
            printf("Até breve!\n");
            exit(0);
          } else {
            flag = 2;
          }  
        }
        if(flag == 2){
          // -> feed
          SeguirLog(user, w);
          PrintaFeedLog(user, w); 
          PararDeSeguir(user, w);
          PrintaFeedLog(user, w);
          flag = 1;
        }
      }while (flag == 1 || flag == 2);   
    }
  }
}

/*  

  CONSTRUÇÃO DAS FILES:


    Dados.txt:
        1
      login1
        2
      login 2
       . . .
        w
      login w


    FILE Nomes.txt:
        1
      nome 1
        2
      nome 2
       . . .
        w
      nome w


    FILE *fdin: (do perfil do usuário)      
      1) int seguindo [50]
      2) nome[32]
      3) login[16]
      4) dia de nascimento [int]
      5) mes de nascimento [int]
      6) ano de nascimento[int]
      7) interesses[128]        
      8) post 1[128]
      9) flag 1
      10) post 2[128]
      11) flag 2  
          . . .            
                  
*/


    