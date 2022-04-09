#include<stdio.h>
#include <stdlib.h>

void remove_newline_ch(char* line)
{
	int new_line = strlen(line) - 1;
	if (line[new_line] == '\n')
		line[new_line] = '\0';
}

int idCount = 0;

//Episódio
typedef struct Episodio {
	char nome[64];
	char podcast[64];
	int numero;
	struct PalavrasChave* palavraschave;
	struct Episodio* prox;
	struct Episodio* prev;
}episodio;

typedef episodio* Episodio;

//Playlist
typedef struct Playlist {
	struct Episodio* inicio;
	struct Episodio* fim;
}playlist;

typedef playlist* Playlist;

//Podcast
typedef struct Podcast {
	int id;
	char nome[64];
	struct Episodio* inicio;
	struct Episodio* fim;
}podcast;

typedef podcast* Podcast;

//Palavras-Chave
typedef struct PalavrasChave {
	char palavra[64];
	struct PalavrasChave* prox;
}palavraschave;

typedef palavraschave* PalavrasChave;

typedef struct ListaPalavrasChave {
	struct PalavrasChave* inicio;
	struct PalavrasChave* fim;
}listapalavraschave;

typedef listapalavraschave* ListaPalavrasChave;

//Criar episódio
Episodio CriarEp(Podcast podcast) {
	Episodio novoep = malloc(sizeof(Episodio));
	novoep->prev = NULL;
	novoep->prox = NULL;

	printf("Qual o nome do episódio?\n");
	fgets(novoep->nome, 64, stdin);
	remove_newline_ch(novoep->nome);

	/*
	* Criar busca para definir automaticamente
	*/
	printf("Qual o numero do episódio?\n");
	int NumeroTemp;
	scanf_s("%d", &NumeroTemp);
	getchar();
	novoep->numero = NumeroTemp;


	//Idendificador do podcast
	int PassagemNome = 0;
	while (PassagemNome > sizeof(podcast->nome)) {
		novoep->podcast[PassagemNome] = podcast->nome[PassagemNome];
	}
	//Palavras chave
	return novoep;
}

//Criar podcast
Podcast CriarPodcast() {
	Podcast podcast = malloc(sizeof(Podcast));
	podcast->inicio = NULL;
	podcast->fim = NULL;	
	
	//Definir o id
	podcast->id = idCount;
	idCount++;

	printf("Qual o nome do Podcast?\n");
	fgets(podcast->nome, 64, stdin);
	remove_newline_ch(podcast->nome);
	return podcast;
}

//Adicionar Episódio
Podcast NovoEpisodio(Podcast podcast) {
	
	Episodio novoep = CriarEp(podcast);
	
	if (podcast->inicio == NULL) {
		podcast->inicio = novoep;
		podcast->fim = novoep;
	}
	else {
		podcast->fim->prox = novoep;
		novoep->prev = podcast->fim;
		podcast->fim = novoep;
	}
	return novoep;
}

Podcast RemoverEpisodio(Podcast podcast) {

}


void main(void) {
	Podcast podcast = CriarPodcast();
	NovoEpisodio(podcast);
	NovoEpisodio(podcast);
}
