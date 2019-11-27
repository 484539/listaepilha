#include <stdio.h>
#include <stdlib.h>

struct no {
  int info;
  struct no *prox;
};

void push(struct no **P,int v){
  struct no *n;

  n = (struct no *) malloc(sizeof(struct no));
  n->info = v;
  n->prox = *P;
  *P = n;

}//Fim push()

int pop(struct no **P){
  struct no *p;
  int v;

  p=*P; //aponta p para o no do TOPO
  v = p->info; //Peguei a informacao do no a ser removido
  *P = p->prox; //Faz o Pilha apontar p/ o proximo no
  free(p); //Libera memoria do no a ser removido
  return v; //retorna o valor do no removido

}//Fim pop()

void mostrarPilha(struct no **Pilha){
  struct no *Paux=NULL;
  int v;

  if (*Pilha==NULL){
    printf("Pilha Vazia!");
    return;
  }
  //O primeiro estou removendo fora do while
  // para ficar na direcao certa quando imprimir
  v=pop(Pilha);  //Retirei da Pilha Original
  printf(" %i\n",v); //Mostrei na tela
  push(&Paux,v); //Guarda na Pilha Auxiliar
  while(*Pilha!=NULL){
    v=pop(Pilha);  //Retirei da Pilha Original
    printf("        %i\n",v); //Mostrei na tela
    push(&Paux,v); //Guarda na Pilha Auxiliar
  }

  while (Paux!=NULL){
    v=pop(&Paux);  //Retira da Pilha Auxiliar
    push(Pilha,v); //Coloca na Pilha Original
  }

}//Fim mostrarPilha()

int QtdeMaioresMedia(struct no **Pilha){
  struct no *Paux=NULL;
  float media;
  int val,soma=0, cont=0;

  while (*Pilha!=NULL){
    val = pop(Pilha); //Remove da Pilha Original
    soma = soma + val;
    cont++;
    push(&Paux,val); //Guarda valor na Pilha Auxiliar
  }
  media = (float) soma/cont;
  cont = 0;
  while (Paux!=NULL){
    val = pop(&Paux); //Remove da Pilha Auxiliar
    if (val > media)  //Verifica se é maior que a media
      cont++;
    push(Pilha,val);  //guarda na Pilha Original
  }

  return cont;
}//Fim QtdeMaioresMedia()

int consultarPosicao(struct no **Pilha,int v){
  struct no *Paux=NULL;
  int posicao=0, achou=0 ;
  int val;

  while ((!achou)&&(*Pilha!=NULL)){
    val = pop(Pilha);
    push(&Paux,val);
    posicao++;
    if (val==v){
      achou = posicao;
    }
  }
  //Voltar elementos para a Pilha original
  while(Paux!=NULL){
    push(Pilha,pop(&Paux)); //Retira da Paux e insere na Pilha
  }

  return achou;

}//Fim consultarPosicao()

int nroItensPilha(struct no **Pilha){
  struct no *Paux=NULL;
  int val, cont=0;

  while(*Pilha!=NULL){
    val = pop(Pilha);
    cont++;
    push(&Paux,val);
  }
  while(Paux!=NULL){
    push(Pilha,pop(&Paux));
  }

  return cont;

}//Fim nroItensPilha()

int main(){
  struct no *Pilha;
  int op, op1, val, ret;

  Pilha = NULL; //Inicializa Pilha Vazia

  do{
    printf("\n\n==== P I L H A =====");
    printf("\n1) Push() - Inserir na Pilha");
    printf("\n2) Pop() - Remover da Pilha");
    printf("\n3) Mostrar Pilha");
    printf("\n4) Ex2) Conta maiores que a media");
    printf("\n5) Ex4) Consultar posicao valor na Pilha");
    printf("\n6) Ex6) Nro. de Itens de uma Pilha");
    printf("\n0) Sair");

    printf("\nOpcao-> ");
    fflush(stdin); scanf("%i",&op);

    switch(op){
        case 1: //push() - Inserir no TOPO da Pilha
            printf("\n Digite o valor: ");
            fflush(stdin); scanf("%i",&val);
            push(&Pilha,val);
            break;
        case 2: //pop() - Remove o valor do TOPO da Pilha
            if(Pilha==NULL)
                  printf("\nPilha Vazia. Impossivel remover.");
            else
                  printf("\nValor Removido: %i", pop(&Pilha));
            break;
        case 3: //Mostra a Pilha
            printf("\nPilha->");
            mostrarPilha(&Pilha);
            break;
        case 4: //conta quantos elementos sao maiores que a media
            printf("\nQtde maiores que a media: %i",QtdeMaioresMedia(&Pilha));
            break;
        case 5: //Consulta se um valor existe na Pilha e retorna sua posicao
          printf("\nDigite o valor a ser Localizado: ");
          fflush(stdin); scanf("%i",&val);
          ret = consultarPosicao(&Pilha,val);
          if (ret==0)
            printf("\nO valor %i NAO foi localizado na Pilha",val);
          else
            printf("\nO valor %i foi localizado na posicao %i da Pilha",val,ret);
          break;
          case 6: //Nro de itens na Pilha
            printf("\nNro de itens na Pilha: %i",nroItensPilha(&Pilha));
            break;
    }

  }while (op!=0);

  return 0;
}//Fim main
