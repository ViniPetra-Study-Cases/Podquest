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


typedef struct podcast {
	struct Episodio* inicio;
	struct Episodio* fim;
}podcast;

typedef podcast* Podcast;




