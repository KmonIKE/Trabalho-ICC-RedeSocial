#ifndef STRUCT_H
#define STRUCT_H

struct data {
  int dia;
  int mes;
  int ano;
};

typedef struct {
  int seguindo[50]; // Armazena os índices dos perfis que o usuário segue
  char nome[32];
  char login[16];
  struct data nasc;
  char interesses[128];
  char post[50][128]; // 50 posts de tamanho 128 

} dados;

#endif
