#include<stdio.h>
#include <stdlib.h>

int idCount = 0;

//Episódio
typedef struct Ep {
	int id;
	char nome[64];
	char podcast[64];
	int numero;
	//Definir a lista de palavras chave
	struct Episodio* prox;
	struct Episodio* prev;
}episodio;

typedef episodio* Episodio;

//Playlist
typedef struct playlist {
	struct Episodio* inicio;
	struct Episodio* fim;
}playlist;

typedef playlist* Playlist;

//Podcast
typedef struct podcast {
	char nome[64];
	struct Episodio* inicio;
	struct Episodio* fim;
}podcast;

typedef podcast* Podcast;

//Criar episódio
Episodio CriarEp(Podcast podcast) {
	Episodio novoep = malloc(sizeof(Episodio));
	novoep->prev = NULL;
	novoep->prox = NULL;

	//Definir o id
	novoep->id = idCount;
	idCount++;

	//Definir o nome do podcast que pertence
	int PassagemNome = 0;
	while (PassagemNome > sizeof(novoep->podcast)) {
		novoep->podcast[PassagemNome] = podcast->nome[PassagemNome];
	}
	
	char NomeTemp[64];
	Printf("Qual o nome do episódio?\n");
	scanf_s("%s", &NomeTemp);
	PassagemNome = 0;
	while (PassagemNome > sizeof(novoep->nome)) {
		novoep->nome[PassagemNome] = NomeTemp[PassagemNome];
	}

	/*
	* Criar busca para definir automaticamente
	*/
	Printf("Qual o numero do episódio?\n");
	int NumeroTemp;
	scanf_s("%d", &NumeroTemp);
	novoep->numero = NumeroTemp;
}

//Criar podcast
Podcast CriarPodcast() {
	Podcast podcast = malloc(sizeof(Podcast));
	podcast->inicio = NULL;
	podcast->fim = NULL;

	char NomeTemp[64];
	Printf("Qual o nome do Podcast?\n");
	scanf_s("%s", &NomeTemp);

	int PassagemNome = 0;
	while (PassagemNome > sizeof(podcast->nome)) {
		podcast->nome[PassagemNome] = NomeTemp[PassagemNome];
	}

}


