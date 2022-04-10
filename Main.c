#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void remove_newline_ch(char* line)
{
	int new_line = strlen(line) - 1;
	if (line[new_line] == '\n')
		line[new_line] = '\0';
}

int idCount = 0;
Podcast podcasts[20];
Episodio episodios[50];

//Epis�dio
typedef struct Episodio {
	char nome[64];
	int numero;
	struct PodCast* podcast;
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

//Cabe�a do podcast
typedef struct PodcastHead {
	struct PodCast* inicio;
	struct PodCast* fim;
}podcasthead;

typedef podcasthead* PodcastHead;

//Playlist
typedef struct Playlist {
	struct Episodio* inicio;
	struct Episodio* fim;
}playlist;

typedef playlist* Playlist;

//Palavras-Chave
typedef struct Palavraschave {
	char palavra[64];
	struct Palavraschave* prox;
}palavraschave;

typedef palavraschave* PalavrasChave;


//Criar PodcastHead
PodcastHead CriarCabe�aPodcast() {
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

//Criar epis�dio
Episodio CriarNovoEpis�dio(Podcast podcast) {

	int contagem = 0;

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
	printf("Qual o nome do epis�dio?\n");
	fgets(novoep->nome, 64, stdin);
	remove_newline_ch(novoep->nome);

	//Numero
	Episodio epAux = CriarEpVazio();
	epAux = podcast->inicio;

	while (epAux->prox != NULL) {
		contagem++;
		epAux = epAux->prox;
	}

	novoep->numero = contagem;

	//Idendificador do podcast
	novoep->podcast = podcast;

	//PalavrasChave
	int opc = 0;
	int loop = 0;
	printf("Voc� deseja adicionar palavras-chave?\n1 - Sim\n2 - N�o");
	scanf_s("%d", &opc);
	switch (opc) {
		case 1:
			AdicionarPalavras(novoep);
			while (loop != 2) {
				AdicionarPalavras(novoep);
				printf("Voc� deseja adicionar palavras-chave?\n1 - Sim\n2 - N�o");
				canf_s("%d", &loop);
			}
		case 2:
			break;
	}

	return novoep;
}

//Criar epis�dio vazio
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
		printf("\nQual o n�mero do podcast que deseja remover?\n");
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
		printf("N�o h� nenhum epis�dio neste podcast\n");
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

Episodio PrintarEpisodios(Playlist playlist) {
	if (playlist->inicio == NULL) {
		printf("N�o h� nenhum epis�dio nesta playlist\n");
		return 0;
	}
	else {
		Episodio epAux = CriarEpVazio();
		epAux = playlist->inicio;

		while (epAux->prox != NULL) {
			printf("%d %s\n", epAux->numero, epAux->nome);
			epAux = epAux->prox;
		}
		return 1;
	}
}

Podcast PrintarPodcasts(PodcastHead podcasthead) {
	if (podcasthead->inicio == NULL) {
		printf("N�o h� nenhum podcast cadastrado\n");
		return 0;
	}
	else {
		Podcast podcastAux = CriarpodcastVazio();
		podcastAux = podcasthead->inicio;

		while (podcastAux->prox != NULL) {
			printf("%d %s\n", podcastAux->id, podcastAux->nome);
			podcastAux = podcastAux->prox;
		}
		return 1;
	}
}

Playlist CriarPlaylist() {
	Playlist playlist = malloc(sizeof(Playlist));
	playlist->inicio = NULL;
	playlist->fim = NULL;
	return playlist;
}


Podcast EscolherPodcast(int id, PodcastHead podcasthead) {

	Podcast podcastEscolhido = CriarPodcastVazio();
	Podcast podcastAux = CriarPodcastVazio;

	podcastAux = podcasthead->inicio;

	while (podcastAux->id != id) {
		podcastAux = podcastAux->prox;
	}

	if (podcastAux == NULL && podcastAux->id != id) {
		printf("Podcast n�o encontrado\n");
		return;
	}
	else {
		podcastEscolhido = podcastAux;
	}

	return podcastEscolhido;
}

Playlist AdicionarEp(Playlist playlist, Episodio episodio) {
	if (playlist->inicio == NULL) {
		playlist->inicio = episodio;
		playlist->fim = episodio;
	}
	else {
		playlist->fim->prox = episodio;
		episodio->prev = playlist->fim;
		playlist->fim = episodio;

	}
}

Playlist RemoverEp(Playlist playlist, int numero){
	if (PrintarEpisodios(playlist) == 0) {
		return;
	}
	else {
		Episodio epAux = CriarEpVazio();
		epAux = playlist->inicio;

		int opc;
		printf("\nQual o n�mero do epis�dio que deseja remover?\n");
		scanf_s("%d", &opc);

		epAux = epAux = playlist->inicio;
		while (epAux->numero != opc) {
			epAux = epAux->prox;
		}

		epAux->prev->prox = epAux->prox;
		epAux->prox->prev = epAux->prev;
	}
}

Episodio EscolherEpisodio(Podcast podcast, int numero) {
	Episodio episodioEscolhido = CriarEpVazio();
	Episodio epAux = CriarEpVazio();

	epAux = podcast->inicio;

	while (epAux->numero != numero) {
		epAux = epAux->prox;
	}

	if (epAux == NULL && epAux->numero != numero) {
		printf("Epis�dio n�o encontrado\n");
		return;
	}
	else {
		episodioEscolhido = epAux;
	}

	return episodioEscolhido;
}

void main(void) {
	Episodio EpisodioAtual = CriarEpVazio();
	Playlist playlist = CriarPlaylist();
	PodcastHead podcasthead = CriarCabe�aPodcast();

	int opc;
	int pdcopc;
	int epopc;
	bool shuffle = false;
	printf("Bem-vindo!\nEscolha uma das op��es abaixo:\n1 - Criar um novo podcast\n2 - Adicionar um epis�dio ao seu podcast\n3 - Remover um epis�dio ao seu podcast\n4 - Listar todos os epis�dios do seu Podcast\n5 - Adicionar epis�dios � sua playlist\n6 - Remover epis�dios da sua playlist\n7 - Tocar um epis�dio\n8 - Qual epis�dio estou ouvindo?\n9 - Adicionar ep atual � playlist\n10 - Tocar minha playlist\n11 - Tocar pr�ximo da minha playlist\n12 - Ativar o modo aleat�rio na minha playlist\n");
	scanf_s("%d", &opc);
	switch (opc) {
		case 1:
			if (podcasthead->inicio == NULL) {
				Podcast podcast = CriarPodcast();
				podcasthead->inicio = podcast;
				podcasthead->fim = podcast;
			}
			else {
				Podcast podcast = CriarPodcast();
				podcasthead->fim->prox = podcast;
				podcast->prev = podcasthead->fim;
				podcasthead->fim = podcast;
			}
			break;
		case 2:
			PrintarPodcasts(podcasthead);
			printf("Qual o id do podcast que voc� deseja adicionar um Epis�dio?\n");
			scanf_s("%d", &pdcopc);
			
			Podcast podcastEscolhido = EscolherPodcast(pdcopc, podcasthead);

			CriarNovoEpis�dio(podcastEscolhido);

			break;
		case 3:
			PrintarPodcasts(podcasthead);
			printf("Qual o id do podcast que voc� deseja remover um Epis�dio?\n");
			scanf_s("%d", &pdcopc);

			Podcast podcastEscolhido = EscolherPodcast(pdcopc, podcasthead);
			
			RemoverEpisodio(podcastEscolhido);

			break;
		case 4:
			PrintarPodcasts(podcasthead);
			printf("Qual o id do podcast que voc� deseja listar os Epis�dios?\n");
			scanf_s("%d", &pdcopc);

			Podcast podcastEscolhido = EscolherPodcast(pdcopc, podcasthead);

			PrintarEpisodios(podcastEscolhido);
			break;
		case 5:
			PrintarPodcasts(podcasthead);
			printf("Qual o id do podcast que voc� deseja listar os Epis�dios?\n");
			scanf_s("%d", &pdcopc);
			Podcast podcastEscolhido = EscolherPodcast(pdcopc, podcasthead);
			PrintarEpisodios(podcastEscolhido);
			printf("Qual o numero do epis�dio que voc� deseja adicionar � playlist?\n");
			scanf_s("%d", &epopc);
			AdicionarEp(playlist, epopc);
			break;
		case 6:
			PrintarPodcasts(podcasthead);
			printf("Qual o id do podcast que voc� deseja listar os Epis�dios?\n");
			scanf_s("%d", &pdcopc);
			Podcast podcastEscolhido = EscolherPodcast(pdcopc, podcasthead);
			PrintarEpisodios(podcastEscolhido);
			printf("Qual o numero do epis�dio que voc� deseja remover da playlist?\n");
			scanf_s("%d", &epopc);
			removerEp(playlist, epopc);
			break;
		case 7:
			PrintarPodcasts(podcasthead);
			printf("Qual o id do podcast que voc� deseja listar os Epis�dios?\n");
			scanf_s("%d", &pdcopc);
			Podcast podcastEscolhido = EscolherPodcast(pdcopc, podcasthead);
			PrintarEpisodios(podcastEscolhido);
			printf("Qual o numero do epis�dio que voc� deseja ouvir?\n");
			scanf_s("%d", &epopc);
			EpisodioAtual = EscolherEpisodio(podcastEscolhido, epopc);
			printf("Voc� est� ouvindo %d %s do podcast %s\n", EpisodioAtual->numero, EpisodioAtual->nome, EpisodioAtual->podcast->nome);
			break;
		case 8:
			if (EpisodioAtual == NULL) {
				printf("Voc� n�o est� ouvindo nenhum epis�dio\n");
				break;
			}
			else {
				printf("Voc� est� ouvindo %d %s do podcast %s\n", EpisodioAtual->numero, EpisodioAtual->nome, EpisodioAtual->podcast->nome);
				break;
			}
			break;
		case 9:
			if (EpisodioAtual == NULL) {
				printf("Voc� n�o est� ouvindo nenhum epis�dio\n");
				break;
			}
			else {
				AdicionarEp(playlist, EpisodioAtual);
				printf("Epis�dio adicionado � sua playlist\n");
				break;
			}
		case 10:
			if (playlist->inicio != NULL) {
				EpisodioAtual = playlist->inicio;
				printf("Voc� est� ouvindo %d %s do podcast %s\n", EpisodioAtual->numero, EpisodioAtual->nome, EpisodioAtual->podcast->nome);
				break;
			}
			else {
				printf("Playlist vazia");
				break;
			}
		case 11:
			if (shuffle == true) {
				if (playlist->inicio != NULL) {

					srand(time(NULL));
					int aux = rand() % sizeof(playlist) + 1;
					int count = 0;
					while (count != aux) {
						EpisodioAtual = EpisodioAtual->prox;
					}
					printf("Voc� est� ouvindo %d %s do podcast %s\n", EpisodioAtual->numero, EpisodioAtual->nome, EpisodioAtual->podcast->nome);
				}
				else {
					printf("Playlist vazia");
					break;
				}
			}
			else {
				if (EpisodioAtual->prox != NULL) {
					EpisodioAtual = EpisodioAtual->prox;
					printf("Voc� est� ouvindo %d %s do podcast %s\n", EpisodioAtual->numero, EpisodioAtual->nome, EpisodioAtual->podcast->nome);
					break;
				}
				else {
					printf("n�o h� mais epis�dios na sua playlist\n");
					break;
				}
			}
		case 12:
			shuffle = true;
			printf("Ateat�rio ativado!\n");
			break;
	}
}
