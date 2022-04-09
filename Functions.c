#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int valor;
	struct No* prox;
	struct No* prev;
}node;

typedef node* No;

typedef struct Cabeça {
	struct Node* inicio;
	struct Node* fim;
}cabeça;

typedef cabeça* Head;

No ldlCriaNo(int valor) {
	No novono = malloc(sizeof(No));
	novono->prox = NULL;
	novono->prev = NULL;
	novono->valor = valor;
	return novono;
}

void ldlPrintar(Head head) {
	if (head->inicio == NULL) {
		printf("Lista vazia\n");
		return;
	}

	for (No aux = head->inicio; aux != NULL; aux = aux->prox)
	{
		printf("%d ", aux->valor);
	}
	printf("\n");
}

void ldlInserirFinal(Head head, int valor) {
	No novono = ldlCriaNo(valor);
	if (head->inicio == NULL) {
		head->inicio = novono;
		head->fim = novono;
	}
	else {
		head->fim->prox = novono;
		novono->prev = head->fim;
		head->fim = novono;
	}
}

void ldlInserirInicio(Head head, int valor) {
	if (head->inicio == NULL) {
		No novono = ldlCriaNo(valor);
		head->inicio = novono;
		head->fim = novono;
	}
	else {
		No aux = ldlCriaNo(NULL);
		No novono = ldlCriaNo(valor);

		novono->prox = head->inicio;
		head->inicio = novono;
	}
}

void ldlRemoveFim(Head head) {
	if (head->inicio != NULL) {
		if (head->inicio == head->fim) {
			head->fim = NULL;
			return;
		}
		head->fim = head->fim->prev;
		head->fim->prox = NULL;
	}
	else {
		printf("Lista vazia\n");
	}
}

void ldlRemoveInicio(Head head) {
	if (head->inicio == NULL) {
		printf("Lista vazia\n");
		return;
	}
	head->inicio = head->inicio->prox;
	head->inicio->prev = NULL;
}

void ldlInserirApos(Head head, int index, int valor) {
	No aux = ldlCriaNo(NULL);
	No novono = ldlCriaNo(valor);
	aux = head->inicio;
	while (aux->valor != index) {
		aux = aux->prox;
		if (aux->prox == NULL) {
			printf("Valor não encontrado\n");
			return;
		}
	}
	novono->prox = aux->prox;
	novono->prev = aux;
	aux = aux->prox;
	aux->prev = novono;
	aux = novono->prev;
	aux->prox = novono;
}

void ldlInserirAntes(Head head, int index, int valor) {
	No aux = ldlCriaNo(NULL);
	No novono = ldlCriaNo(valor);
	aux = head->inicio;
	while (aux->valor != index) {
		aux = aux->prox;
		if (aux == NULL) {
			printf("Valor não encontrado\n");
			return;
		}
	}
	novono->prev = aux->prev;
	novono->prox = aux;
	aux->prev = novono;
	aux = novono->prev;
	aux->prox = novono;
}
