#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CriaPostLog.h"

void CriaPostLog(dados user, int w){
  
  int cria; // flag para fazer posts (cria = 1 para criar e cria = 2 para não criar)
  int i; // contador do número de posts feitos
  int flag = 1; // (flag = 1 para post existente e flag = 0 para post deletado)
   
  do{

    i = 0;
    
    while (i < 50){
      
      printf("Para fazer um post, digite 1. Caso contrário, digite 2.\n");
      while (scanf("%d", &cria) == 0 || (cria != 1 && cria != 2)){
        printf("Comando inválido. Digite novamente: ");
        setbuf(stdin, NULL);
      }
      getchar();
      if (cria == 2){
        break;
      }

      FILE *fdin; // Abrir a FILE do perfil do usuário para escrever o post  
      char strbin[32];
      sprintf(strbin, "Perfil%d", w); 
      fdin = fopen (strbin, "a");
      if (fdin == NULL){
        printf("Não foi possível abrir o arquivo do perfil desejado.\n");
        exit(0);
      }

      printf("Digite o post: ");      
      fgets(user.post[i], 128, stdin);
      fwrite(user.post[i], sizeof(char), 128, fdin);
      fwrite(&flag, sizeof(int), 1, fdin);

      fclose(fdin);

      i++;
            
    }

  } while (cria == 1);
 
}
  