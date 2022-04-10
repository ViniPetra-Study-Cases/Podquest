#include<stdio.h>
#include <stdlib.h>

void remove_newline_ch(char* line)
{
	int new_line = strlen(line) - 1;
	if (line[new_line] == '\n')
		line[new_line] = '\0';
}

int idCount = 0;
Podcast podcasts[20];
Episodio episodios[50];

//Episódio
typedef struct Episodio {
	char nome[64];
	int numero;
	struct Podcast* podcast;
	struct PalavrasChave* palavraschave;
	struct Episodio* prox;
	struct Episodio* prev;
}episodio;

typedef episodio* Episodio;

//Podcast
typedef struct PodCast {
	int id;
	char nome[64];
	struct Episodio* inicio;
	struct Episodio* fim;
	struct PodCast* prev;
	struct PodCast* prox;
}podcast;

typedef podcast* Podcast;

//Cabeça do podcast
typedef struct PodcastHead {
	struct Podcast* inicio;
	struct Podcast* fim;
}podcasthead;

typedef podcasthead* PodcastHead;

//Playlist
typedef struct Playlist {
	struct Episodio* ep;
	struct Episodio* inicio;
}playlist;

typedef playlist* Playlist;

//Cabeça da playlist

//Palavras-Chave
typedef struct Palavraschave {
	char palavra[64];
	struct Palavraschave* prox;
}palavraschave;

typedef palavraschave* PalavrasChave;

//Criar PodcastHead
typedef struct PodcastHead {
	Podcast* inicio;
	Podcast* fim;
}podcasthead;

typedef podcasthead* PodcastHead;

//Criar PodcastHead
PodcastHead CriarCabeçaPodcast() {
	PodcastHead podcasthead = malloc(sizeof(PodcastHead));
	return podcasthead;
}

//Criar podcast
Podcast CriarPodcast() {
	Podcast podcast = malloc(sizeof(Podcast));
	
	podcast->inicio = NULL;
	podcast->fim = NULL;
	podcast->prev = NULL;
	podcast->prox = NULL;

	//Definir o id
	podcast->id = idCount;
	podcasts[idCount] = podcast;
	idCount++;

	printf("Qual o nome do Podcast?\n");
	fgets(podcast->nome, 64, stdin);
	remove_newline_ch(podcast->nome);
	return podcast;
}

//Criar episódio
Episodio CriarNovoEpisódio(Podcast podcast) {
	/*
	* 1 - perguntar qual podcast pertence
	* 1.1 - printar podcasts e usar o valor como numero de repetições
	* 1.1.1 - criar funções buscar(podcast) e buscar(podcast, index)
	*/

	Episodio novoep = malloc(sizeof(Episodio));
	
	//Apontamentos
	if (podcast->inicio == NULL) {
		podcast->inicio = novoep;
		podcast->fim = novoep;
	}
	else {
		podcast->fim->prox = novoep;
		novoep->prev = podcast->fim;
		podcast->fim = novoep;
	}

	//Nome
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
	novoep->podcast = podcast;

	//PalavrasChave
	int opc = 0;
	int loop = 0;
	printf("Você deseja adicionar palavras-chave?\n1 - Sim\n2 - Não");
	scanf_s("%d", &opc);
	switch (opc) {
		case 1:
			AdicionarPalavras(novoep);
			while (loop != 2) {
				AdicionarPalavras(novoep);
				printf("Você deseja adicionar palavras-chave?\n1 - Sim\n2 - Não");
				canf_s("%d", &loop);
			}
		case 2:
			break;
	}

	return novoep;
}

//Criar episódio vazio
Episodio CriarEpVazio() {
	Episodio episodio = malloc(sizeof(Episodio));
	episodio->prev = NULL;
	episodio->prox = NULL;
	return episodio;
}

//Criar podcast vazio
Podcast CriarPodcastVazio() {
	Podcast podcast = malloc(sizeof(Podcast));
	podcast->fim = NULL;
	podcast->inicio = NULL;
	podcast->prev = NULL;
	podcast->prox = NULL;
	podcast->id = NULL;
	strcpy(podcast->nome, NULL);
	return podcast;
}

//Palavras - chave
PalavrasChave AdicionarPalavras(Episodio ep) {
	if (ep->palavraschave == NULL) {
		PalavrasChave palavra = malloc(sizeof(PalavrasChave));

		printf("Digite a palavra-chave:\n");
		fgets(palavra->palavra, 64, stdin);
		remove_newline_ch(palavra->palavra);

		palavra->prox = NULL;
	}
	
	PalavrasChave aux = malloc(sizeof(PalavrasChave));
	strcpy(aux->palavra, NULL); //Erro de lvalue 
	aux->prox = NULL;

	aux = ep->palavraschave;

	while (aux->prox != NULL) {
		aux = aux->prox;
	}

	PalavrasChave palavra = malloc(sizeof(PalavrasChave));
	printf("Digite a palavra-chave:\n");
	fgets(palavra->palavra, 64, stdin);
	remove_newline_ch(palavra->palavra);
	aux->prox = palavra;
}

Podcast RemoverEpisodio(Podcast podcast) {
	if (PrintarEpisodios(podcast) == 0) {
		return;
	}
	else {
		Episodio epAux = CriarEpVazio();
		epAux = podcast->inicio;

		int opc;
		printf("\nQual o número do podcast que deseja remover?\n");
		scanf_s("%d", &opc);

		epAux = epAux = podcast->inicio;
		while (epAux->numero != opc) {
			epAux = epAux->prox;
		}

		epAux->prev->prox = epAux->prox;
		epAux->prox->prev = epAux->prev;
	}
}

Episodio PrintarEpisodios(Podcast podcast) {
	if (podcast->inicio == NULL) {
		printf("Não há nenhum episódio neste podcast\n");
		return 0;
	}
	else {
		Episodio epAux = CriarEpVazio();
		epAux = podcast->inicio;

		while (epAux->prox != NULL) {
			printf("%d %s\n", epAux->numero, epAux->nome);
			epAux = epAux->prox;
		}
		return 1;
	}
}

Playlist CriarPlaylist() {
	Playlist playlist = malloc(sizeof(Playlist));
	playlist->ep = NULL;
	playlist->inicio = NULL;
	return playlist;
}

//Imprimir a playlist
Playlist PrintarPlaylist(Playlist playlist) {
	
	if (playlist->inicio == NULL) {
		printf("Playlist vazia\n");
		return;
	}

	Episodio aux = malloc(sizeof(Episodio));

	for (Episodio aux = playlist->inicio; aux != NULL; aux = aux->prox)
	{
		printf("%d\n ", aux->nome);
	}
	printf("\n");
}

Playlist AdicionarEp() {

}

Playlist RemoverEp(){

}

void main(void) {
	PalavrasChave palavra = malloc(sizeof(PalavrasChave));
	int opc;
	printf("Bem-vindo!\nEscolha uma das opções abaixo:\n1 - Criar um novo podcast\n2 - Adicionar um episódio ao seu podcast\n3 - Remover um episódio ao seu podcast\n4 - Listar todos os episódios do seu Podcast\n5 - Adicionar episódios à sua playlist\n");
	
}
