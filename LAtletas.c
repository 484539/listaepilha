#include <stdio.h>
#include <stdlib.h>

struct no {
  char nome[30];
  float altura;
  struct no *prox;
};

struct no * inserirNoInicio(struct no *L,char nome[30],float altura){
  struct no *p;

  //Alocar espaco de memoria para o novo no
  p = (struct no *) malloc(sizeof(struct no));
  //Colocar a informacao no novo no
  strcpy(p->nome,nome);
  p->altura = altura;
  //Fazer o encadeamento
  p->prox = L;
  L = p;
  return L;
}//Fim inserirNoInicio()

void mostrarLista(struct no *L){
  struct no *p;

  if (L==NULL){
    printf("Lista Vazia!");
    return;
  }

  p=L; //Aponta p para o primeiro no
  while(p!=NULL){
    printf("(%s,%5.2f)-> ",p->nome,p->altura); //Imprime a informacao
    p = p->prox;  //Avanca o p para o proximo no
  }

}//Fim mostrarLista()

struct no * inserirNoFim(struct no *L,char nome[30],float altura){
  struct no *p,*q;

  //Alocar espaco de memoria para o novo no
  p = (struct no *) malloc(sizeof(struct no));
  //Colocar a informacao no novo no
  strcpy(p->nome,nome);
  p->altura = altura;
  //Coloca NULL no campo prox, pois sera o ultimo
  p->prox = NULL;
  //Fazer o encadeamento
  if (L==NULL){ //Lista Vazia
    return p;
  }
  q=L;
  while (q->prox!=NULL) //Posiciona q no ultimo no da Lista
    q = q->prox;

  q->prox = p;

  return L;
} //Fim inserirNoFim()

int qtdeAtletas(struct no *L){
  struct no *p;
  int cont=0;

  p = L;
  while (p!=NULL){
    cont++;
    p = p->prox;
  }

  return cont;

}//Fim qtdeAtletas()

void exibeMaiores(struct no *L,float alt){
  struct no *p;

  printf("\nAtletas com Altura maior que %3.2f:",alt);
  p = L;
  while(p!=NULL){
    if (p->altura>alt)
      printf("\nNome: %s - Altura: %3.2f",p->nome,p->altura);
    p = p->prox;
  }

}//Fim exibeMaiores()

void dividirLista(struct no *LAtletas,struct no **LMaiores, struct no **LMenores,float alt){
  struct no *p;

  p = LAtletas;
  while (p!=NULL){
    if (p->altura>alt)
      *LMaiores = inserirNoFim(*LMaiores,p->nome,p->altura);
    else
      *LMenores = inserirNoFim(*LMenores,p->nome,p->altura);

    p = p->prox;
  }

} //Fim dividirLista()

void dividirListaInLoco(struct no *LAtletas,struct no **LMaiores, struct no **LMenores,float alt){
  struct no *p, *pmenor, *pmaior;

  *LMaiores=NULL;
  *LMenores=NULL;

  p = LAtletas;
  while (p!=NULL){
    if (p->altura>alt){ //Insere na Maiores
      if (*LMaiores==NULL){
        *LMaiores=p;
        pmaior=p;
      }
      else{
        pmaior->prox = p;
        pmaior = p;
      }
    }else{ //insere na Menores
      if (*LMenores==NULL){
        *LMenores=p;
        pmenor=p;
      }
      else{
        pmenor->prox = p;
        pmenor = p;
      }
    }
    p = p->prox;
  }
  pmaior->prox = NULL;
  pmenor->prox = NULL;
}//Fim dividirListaInLoco()

main(){
  struct no *LAtletas, *LMaiores, *LMenores;
  int opcao,op,retorno;
  char nome[30];
  float altura;

  LAtletas = NULL; //Inicializa (ou cria) a Lista Vazia
  LMaiores = NULL;
  LMenores = NULL;

  do {
    printf("\n\nMenu Lista de Atletas");
    printf("\n1) Inserir no Inicio");
    printf("\n2) Mostrar a Lista");
    printf("\n3) Inserir no Fim");
    printf("\n4) Nro de Atletas na Lista");
    printf("\n5) Exibe Atletas Maiores que uma altura");
    printf("\n6) Dividir Lista - versão criando novas Listas");
    printf("\n7) Dividir Lista - versão in-loco");

    printf("\n0) Sair");

    printf("\n\nOpcao-> ");
    fflush(stdin); scanf("%i",&opcao);

    switch(opcao){
      case 1: //Inserir no inicio da Lista
            printf("\n Digite o Nome: ");
            fflush(stdin); gets(nome);
            printf(" Digite a altura: ");
            fflush(stdin); scanf("%f",&altura);
            LAtletas = inserirNoInicio(LAtletas,nome,altura);
            break;
      case 2: //Mostrar os valores da Lista
            printf("\nLAtleta-> ");
            mostrarLista(LAtletas);
            break;
     case 3: //Inserir no Fim da Lista
            printf("\n Digite o Nome: ");
            fflush(stdin); gets(nome);
            printf(" Digite a altura: ");
            fflush(stdin); scanf("%f",&altura);
            LAtletas = inserirNoFim(LAtletas,nome,altura);
            break;
     case 4: //Retorna a qtde de Atletas na Lista
       printf("\nQtde. de Atletas: %i",qtdeAtletas(LAtletas));
       break;
     case 5: //Exibe os Atletas maiores que uma determinada altura
       printf(" Digite a altura minima: ");
       fflush(stdin); scanf("%f",&altura);
       exibeMaiores(LAtletas,altura);
       break;
      case 6: //Dividir Lista criando novas Listas
       printf(" Digite a altura minima: ");
       fflush(stdin); scanf("%f",&altura);
       dividirLista(LAtletas,&LMaiores,&LMenores,altura);
       printf("\nLAtleta-> ");
       mostrarLista(LAtletas);
       printf("\nLMaiores-> ");
       mostrarLista(LMaiores);
       printf("\nLMenores-> ");
       mostrarLista(LMenores);
       break;
      case 7: //Dividir Lista versao in-loco - sem alocar novos nos
       printf(" Digite a altura minima: ");
       fflush(stdin); scanf("%f",&altura);
       dividirListaInLoco(LAtletas,&LMaiores,&LMenores,altura);
       printf("\nLAtleta-> ");
       mostrarLista(LAtletas);
       printf("\nLMaiores-> ");
       mostrarLista(LMaiores);
       printf("\nLMenores-> ");
       mostrarLista(LMenores);
       break;
    }

  }while (opcao!=0);



}//Fim main
