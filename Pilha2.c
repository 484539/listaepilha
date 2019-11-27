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
    printf("         %i\n",v); //Mostrei na tela
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

int esvaziaMenorInsereMaior(struct no **Pilha1, struct no **Pilha2){
  struct no **Pmenor, **Pmaior;
  int tp1, tp2;

  tp1=nroItensPilha(Pilha1); //Pega o tamanho da Pilha1
  tp2=nroItensPilha(Pilha2); //Pega o tamanho da Pilha2

  if (tp1==tp2)
    return 0; //Pilha possuem o mesmo tamanho. Nada a fazer

  //Continua aqui se as pilha possuem tamanhos diferentes
  if (tp1>tp2){
    Pmenor = Pilha2;
    Pmaior = Pilha1;
  }else{
    Pmenor = Pilha1;
    Pmaior = Pilha2;

  }
  //Fazer a transferencia de dados
  while(*Pmenor!=NULL)
      push(Pmaior,pop(Pmenor));

  return 1;
}//Fim esvaziaMenorInsereMaior()

int main(){
  struct no *Pilha1, *Pilha2;
  int op, op1, val, ret;

  Pilha1 = NULL; //Inicializa Pilha Vazia
  Pilha2 = NULL; //Inicializa Pilha Vazia

  do{
    printf("\n\n==== P I L H A =====");
    printf("\n1) Push() - Inserir na Pilha");
    printf("\n2) Pop() - Remover da Pilha");
    printf("\n3) Mostrar Pilha");
    printf("\n4) Ex2) Conta maiores que a media");
    printf("\n5) Ex4) Consultar posicao valor na Pilha");
    printf("\n6) Ex6) Nro. de Itens de uma Pilha");
    printf("\n7) Ex10) Esvazia Pilha Menor e Enche Pilha Maior");
    printf("\n0) Sair");

    printf("\nOpcao-> ");
    fflush(stdin); scanf("%i",&op);

    switch(op){
        case 1: //push() - Inserir no TOPO da Pilha
            printf("\n Digite o valor: ");
            fflush(stdin); scanf("%i",&val);
            printf("\nQual Pilha inserir: (1-Pilha1, 2-Pilha2)? ");
            fflush(stdin); scanf("%i",&op1);
            if (op1==1)
              push(&Pilha1,val);
            else
              push(&Pilha2,val);
            break;
        case 2: //pop() - Remove o valor do TOPO da Pilha
            printf("\nDe qual Pilha inserir: (1-Pilha1, 2-Pilha2)? ");
            fflush(stdin); scanf("%i",&op1);
            if (op1==1)
              if(Pilha1==NULL)
                  printf("\nPilha1 Vazia. Impossivel remover.");
              else
                  printf("\nValor Removido da Pilha1: %i", pop(&Pilha1));
            else
              if(Pilha2==NULL)
                  printf("\nPilha2 Vazia. Impossivel remover.");
              else
                  printf("\nValor Removido da Pilha2: %i", pop(&Pilha2));
            break;
        case 3: //Mostra a Pilha
            printf("\nPilha1->");
            mostrarPilha(&Pilha1);
            printf("\nPilha2->");
            mostrarPilha(&Pilha2);
            break;
        case 4: //conta quantos elementos sao maiores que a media
            printf("\nQtde maiores que a media na Pilha1: %i",QtdeMaioresMedia(&Pilha1));
            printf("\nQtde maiores que a media na Pilha2: %i",QtdeMaioresMedia(&Pilha2));
            break;
        case 5: //Consulta se um valor existe na Pilha e retorna sua posicao
          printf("\nDigite o valor a ser Localizado: ");
          fflush(stdin); scanf("%i",&val);
          ret = consultarPosicao(&Pilha1,val);
          if (ret==0)
            printf("\nO valor %i NAO foi localizado na Pilha1",val);
          else
            printf("\nO valor %i foi localizado na posicao %i da Pilha1",val,ret);
          ret = consultarPosicao(&Pilha2,val);
          if (ret==0)
            printf("\nO valor %i NAO foi localizado na Pilha2",val);
          else
            printf("\nO valor %i foi localizado na posicao %i da Pilha2",val,ret);
          break;
        case 6: //Nro de itens na Pilha
          printf("\nNro de itens na Pilha1: %i",nroItensPilha(&Pilha1));
          printf("\nNro de itens na Pilha2: %i",nroItensPilha(&Pilha2));
          break;
        case 7: //Esvazia Pilha menor e insere itens na Pilha maior
          if (esvaziaMenorInsereMaior(&Pilha1,&Pilha2))
            printf("\nOperação realizada com Sucesso! Mostre as Pilhas para ver o resultado.");
          else
            printf("\nAs pilha possuem o mesmo tamanho. Nada foi feito.");
          break;
    }

  }while (op!=0);

  return 0;
}//Fim main
