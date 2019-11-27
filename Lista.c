#include <stdio.h>
#include <stdlib.h>

struct no {
  int info;
  struct no *prox;
};

struct no * inserirNoInicio(struct no *L, int v){
struct no *p;

//Aloca espaço de memoria para o novo no
p = (struct no *) malloc(sizeof(struct no));

p->info = v; //Coloca a informacao no novo noh

p->prox = L; //Faz o encadeamento do novo noh no inicio da Lista

L = p; //Faz a Lista apontar para o novo noh, o qual passa a ser o primeiro

return L; //Retorna o endereco do novo noh para atualizar a Lista no prog. principal

}//Fim inserirNoInicio()

void imprimirLista(struct no *L){
  struct no *p;

  if(L==NULL){  //Tratamento de Caso de Lista Vazia
    printf("Lista Vazia!");
    return;
  }

  p = L; //Aponta p para o primeiro noh da Lista
  while (p != NULL){
    printf("%i->",p->info);
    p = p->prox;
  }

}//Fim imprimirLista()

struct no * inserirNoFim(struct no *L, int v){
  struct no *p, *n;

  n = (struct no *) malloc(sizeof(struct no)); //Aloca memoria
  n->info = v; //coloca a informacao no novo noh
  n->prox = NULL; //Como será o ultimo noh, colocal NULL no seu prox

  if (L==NULL){ //Tratamento de Lista Vazia.
    return n;
  }

  //Localizar o ultimo noh da Lista
  p=L; //Aponta p para o primeiro
  while(p->prox!=NULL)
    p = p->prox; //Anda o p até o ultimo noh

  p->prox = n; //Faz o encadeamento do ultimo noh com o novo noh

  return L;
}//Fim inserirNoFim()

struct no *removerDoInicio(struct no *L,int *v){
  struct no *p;

  p = L; //Aponta p para o primeiro noh, o qual será removido
  *v = p->info; //Coloca em val (através de v) a informacao do noh removido

  L=p->prox; //aponta L para o segundo noh, o qual passara a ser o primeiro
  free(p); //Libera espaço de memoria usada pelo noh removido

  return L;

}//Fim removerDoInicio()

struct no *removerDoFim(struct no *L,int *v){
  struct no *p, *q;

  p = L;
  while (p->prox!=NULL) //Posiciona p no ultimo noh
    p = p->prox;

  if (L->prox!=NULL){ //Lista tem mais de 1 noh
    q = L;
    while (q->prox!=p) //Posiciona q no noh anterior ao p
      q = q->prox;

    q->prox = NULL; //Finaliza a Lista no penultimo noh
  }
  else{ //Lista só tem 1 noh
    L = NULL;
  }

  *v = p->info; //Pega a informacao no noh que será removido
  free(p); //Libera memoria do noh removido

  return L;
}//Fim removerDoFim()

int comprimentoLista(struct no *L){
  struct no *p;
  int cont=0;

  p = L;
  while (p!=NULL){
    cont++;
    p = p->prox;
  }

  return cont;

}//Fim comprimentoLista()

int existe(struct no *L,int v){
  struct no *p;
  int achou;

  p = L;
  achou=0;
  while ((!achou)&&(p!=NULL)){
    if (p->info==v) //Encontrou um noh que tem o valor procurado
      achou = 1;
    p = p->prox;
  }
  return achou;
}//Fim existe()

struct no *localizaRemove(struct no *L,int v){
  struct no *p, *q;

  if (!existe(L,v)){
    printf("\nO valor solicitado NAO existe na Lista.");
    return L;
  }

  p = L;
  while (p->info!=v) //Posicionar p no noh que contém a
    p = p->prox;    // primeira ocorencia do valor procurado

  if (p==L){ //O noh a ser removido eh o primeiro noh da Lista
    L = p->prox; //Faz L apontar para o o segundo noh, que será o primeiro
  }else{ //O noh a ser removido eh do fim ou "do meio" da Lista
    q=L;
    while (q->prox!=p)  //Posiciona q no noh anterior ao p
      q = q->prox;

    q->prox = p->prox; //Faz o encadeamento
  }
  free(p);
  printf("\n Noh removido com sucesso.");
  return L;

}//Fim localizaRemove()

int main(){
struct no *Lista;
int op, val;

Lista = NULL; //Cria a Lista Vazia

do{
  printf("\n======================================");
  printf("\n== 1) Inserir no Inicio da Lista    ==");
  printf("\n== 2) Imprimir a Lista              ==");
  printf("\n== 3) Inserir no FIM da Lista       ==");
  printf("\n== 4) Remover do Inicio da Lista    ==");
  printf("\n== 5) Remover do Fim da Lista       ==");
  printf("\n== 55) Localizar e Remover          ==");
  printf("\n== 6) Exa) Comprimento da Lista     ==");
  printf("\n== 7) Exb) Existe valor na Lista    ==");
  printf("\n== 0) Sair                          ==");
  printf("\n==                                  ==");
  printf("\n== Opcao-> ");

  fflush(stdin); scanf("%i",&op);
  switch(op){
  case 1: //Insere um novo noh no Inicio da Lista
    printf("Digite o valor: ");
    fflush(stdin); scanf("%i",&val);
    Lista = inserirNoInicio(Lista,val);
    break;
  case 2: //Imprimir os elementos da Lista
    printf("\nLista -> ");
    imprimirLista(Lista);
    break;
  case 3: //Insere um novo noh no FIM da Lista
    printf("Digite o valor: ");
    fflush(stdin); scanf("%i",&val);
    Lista = inserirNoFim(Lista,val);
    break;
  case 4: //Remover o noh do Incicio da Lista, retornando a informacao do noh
    if (Lista==NULL){
      printf("\nLista Vazia. Impossivel remover!");
    }else {
      Lista = removerDoInicio(Lista,&val);
      printf("\nValor removido: %i",val);
    }
    break;
  case 5: //Remover o noh do FIM da Lista, retornando a informacao do noh
    if (Lista==NULL){
      printf("\nLista Vazia. Impossivel remover!");
    }else {
      Lista = removerDoFim(Lista,&val);
      printf("\nValor removido: %i",val);
    }
    break;
  case 55:  //Remover o nó que contém a primeira ocorrência de uma
            //determinada informação
    printf("Digite o valor a ser Localizado e Removido: ");
    fflush(stdin); scanf("%i",&val);
    Lista = localizaRemove(Lista,val);
    break;
  case 6: //Comprimento da Lista - Nro. de nós da Lista
    printf("\nComprimento da Lista: %i",comprimentoLista(Lista));
    break;
  case 7: //Verifica se um determinado valor existe na Lista
    printf("Digite o valor a ser Verificado: ");
    fflush(stdin); scanf("%i",&val);
    if (existe(Lista,val))
      printf("\nO Valor %i EXISTE na Lista",val);
    else
      printf("\nO Valor %i NAO existe na Lista",val);
    break;
  }


}while (op!=0);


  return 0;
}//Fim main()
