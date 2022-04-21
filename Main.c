#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int idCount = 0;

typedef struct palavrachave
{
    char palavra[64];
    struct palavrachave *prox;
    struct palavrachave *prev;
} PalavraChave;

typedef struct palavraschave
{
    PalavraChave *inicio;
    PalavraChave *fim;
} PalavrasChave;

// Episódio
typedef struct episodio
{
    char nome[64];
    int numero;
    PalavrasChave *palavraschave;
    struct episodio *prox;
    struct episodio *prev;
} Episodio;

// Playlist
typedef struct episodios
{
    Episodio *inicio;
    Episodio *fim;
} Episodios;

// Podcast
typedef struct podcast
{
    int id;
    char nome[64];
    Episodios *listaEpisodios;
    struct podcast *prev;
    struct podcast *prox;
} Podcast;

// Cabeça do podcast
typedef struct podcasthead
{
    Podcast *inicio;
    Podcast *fim;
} PodcastHead;

typedef struct playlist
{
    Episodio *inicio;
    Episodio *fim;
} Playlist;

void remove_newline_ch(char *line)
{
    int new_line = strlen(line) - 1;

    if (line[new_line] == '\n')
    {
        line[new_line] = '\0';
    }
}

//cria lista de podcast
PodcastHead *CriarPodcastHead()
{
    PodcastHead *newPodcastHead = (PodcastHead *)malloc(sizeof(PodcastHead));

    newPodcastHead->inicio = NULL;
    newPodcastHead->fim = NULL;

    return newPodcastHead;
}

//cria a lista de palavras
PalavrasChave *CriarPalavras()
{
    PalavrasChave *newPalavras = (PalavrasChave *)malloc(sizeof(PalavrasChave));

    newPalavras->inicio = NULL;
    newPalavras->fim = NULL;

    return newPalavras;
}

//lista de episodios
Episodios *CriarEpisodios()
{
    Episodios *newEpisodios = (Episodios *)malloc(sizeof(Episodio));

    newEpisodios->inicio = NULL;
    newEpisodios->fim = NULL;

    return newEpisodios;
}

//cria a palavra em si
PalavraChave *CriarPalavra()
{
    PalavraChave *newPalavra = (PalavraChave *)malloc(sizeof(PalavraChave));

    printf("Palavra-Chave:\n");
    fgets(newPalavra->palavra, 64, stdin);
    remove_newline_ch(newPalavra->palavra);

    newPalavra->prox = NULL;
    newPalavra->prev = NULL;

    return newPalavra;
}

int AdicionaPalavra(PalavrasChave *palavras)
{
    int continuar = 0;

    PalavraChave *newPalavra = CriarPalavra();

    if (palavras->inicio == NULL)
    {
        palavras->inicio = newPalavra;
        palavras->fim = newPalavra;

        printf("Deseja continuar a adicionar: 1-sim  0-nao\n");
        scanf("%d", &continuar);
        getchar();
        fflush (stdin);

        if (continuar == 1)
        {
            return continuar;
        }
        else if(continuar == 0)
        {
            return 0;
        }
    }
    else
    {
        //adiciona a palavra nova no fim da lista de palavras
        palavras->fim->prox = newPalavra;
        newPalavra->prev = palavras->fim;
        palavras->fim = newPalavra;

        printf("Deseja continuar a adicionar: 1-sim  0-nao\n");
        scanf("%d", &continuar);
        getchar();
        fflush (stdin);

        if (continuar == 1)
        {
            return continuar;
        }
        else if (continuar == 0)
        {
            return 0;
        }
    }
}

//cria o episodio em si
Episodio *CriarEpisodio()
{
    Episodio *newEpisodio = (Episodio *)malloc(sizeof(Episodio));

    printf("Nome do Episodio:\n");
    fgets(newEpisodio->nome, 64, stdin);
    remove_newline_ch(newEpisodio->nome);

    printf("Numero do Episodio:\n");
    scanf("%d", &newEpisodio->numero);
    getchar();
    fflush (stdin);

    PalavrasChave *palavras = CriarPalavras();
    newEpisodio->palavraschave = palavras;

    int continuar = AdicionaPalavra(newEpisodio->palavraschave);

    while(continuar)
    {
        continuar = AdicionaPalavra(newEpisodio->palavraschave);

        if(continuar == 0)
            break;
    }

    newEpisodio->prox = NULL;
    newEpisodio->prev = NULL;

    return newEpisodio;
}

int AdicionaEpisodio(Episodios *episodios)
{
    int continuar = 0;

    Episodio *newEpisodio = CriarEpisodio();

    if (episodios->inicio == NULL)
    {
        episodios->inicio = newEpisodio;
        episodios->fim = newEpisodio;

        printf("Deseja continuar a adicionar: 1-sim  0-nao\n");
        scanf("%d", &continuar);
        getchar();
        fflush (stdin);

        if (continuar == 1)
        {
            return continuar;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        episodios->fim->prox = newEpisodio;
        newEpisodio->prev = episodios->fim;
        episodios->fim = newEpisodio;

        printf("Deseja continuar a adicionar: 1-sim  0-nao\n");
        scanf("%d", &continuar);
        getchar();
        fflush (stdin);

        if (continuar == 1)
        {
            return continuar;
        }
        else
        {
            return 0;
        }
    }
}

//cria o podcast em si
Podcast *CriarPodcast(int id)
{
    Podcast *newPodcast = (Podcast *)malloc(sizeof(Podcast));

    idCount++;
    newPodcast->id = idCount;

    printf("Nome do Podcast:\n");
    fgets(newPodcast->nome, 64, stdin);
    remove_newline_ch(newPodcast->nome);

    Episodios *episodios = CriarEpisodios();
    newPodcast->listaEpisodios = episodios;

    int continuar = AdicionaEpisodio(newPodcast->listaEpisodios);

    while(continuar)
    {
        continuar = AdicionaEpisodio(newPodcast->listaEpisodios);

        if (continuar == 0)
            break;
    }

    newPodcast->prox = NULL;
    newPodcast->prev = NULL;

    return newPodcast;
}

void AdicionaPodcast(PodcastHead *podcasthead)
{
    Podcast *newPodcast = CriarPodcast(idCount);

    if (podcasthead->inicio == NULL)
    {
        podcasthead->inicio = newPodcast;
        podcasthead->fim = newPodcast;

        return;
    }
    else
    {
        podcasthead->fim->prox = newPodcast;
        newPodcast->prev = podcasthead->fim;
        podcasthead->fim = newPodcast;
    }
}

void Printar(PodcastHead *podcasthead)
{
    for(Podcast *aux = podcasthead->inicio; aux != NULL; aux = aux->prox)
    {
        printf("Id: %d\n", aux->id);
        printf("Nome: %s\n", aux->nome);
        printf("Episodios:\n");
        for(Episodio *aux1 = aux->listaEpisodios->inicio; aux1 != NULL; aux1 = aux1->prox)
        {
            printf("Nome: %s\n", aux1->nome);
            printf("Numero: %d\n", aux1->numero);
            printf("Palavras-Chave:\n");
            for(PalavraChave *aux2 = aux1->palavraschave->inicio; aux2 != NULL; aux2 = aux2->prox)
            {
                printf("%s\n", aux2->palavra);
            }
        }
    }
}



Playlist *CriarPlaylist(){
    Playlist *playlist = (Playlist *)malloc(sizeof(Playlist));
    playlist->inicio = NULL;
    playlist->fim = NULL;
    return playlist;
}

Podcast* EscolherPodcast(PodcastHead* podcastHead){
    int id;
    Printar(podcastHead);
    printf("Qual o id do podcast que deseja modificar?\n");
    scanf("%d", &id);
    fflush(stdin);

    for(Podcast *aux = podcastHead->inicio; aux != NULL; aux = aux->prox) {
        if (aux->id == id) {
            return aux;
        }
        printf("Podcast não encontrado\n");
    }
}

Episodio * EscolherEpisodio(PodcastHead* podcastHead, Episodios * episodios){
    int id;
    printf("Qual o id do episodio que deseja modificar?\n");
    scanf("%d", &id);
    fflush(stdin);

    for(Episodio *aux = episodios->inicio; aux != NULL; aux = aux->prox){
        if(aux->numero == id) {
            return aux;
        }
        printf("Episodio não encontrado\n");
    }
}

void RemoverEpisodio(Episodio* episodio) {
    if(episodio->prox == NULL && episodio->prev != NULL){
        episodio->prev->prox = NULL;
    }else if(episodio->prev == NULL && episodio->prox ==NULL){
        printf("Função não implementada para Podcasts com apenas um episódio!\nCrie outro episódio para remover este\n");
    }else if(episodio->prev != NULL && episodio->prox != NULL){
        episodio->prev->prox = episodio->prox;
        episodio->prox->prev = episodio->prev;
        printf("Episodio removido\n");
    }
}

Episodio *TocarEpisodio(Episodio* episodio){
    printf("Tocando episódio: %s", episodio->nome);
    return episodio;
}

void AdicionaEp(Playlist *playlist, Episodio* episodio)
{

    if (playlist->inicio == NULL){
        playlist->inicio = episodio;
        playlist->fim = episodio;
        printf("Episódio adicionado\n");
        return;
    }
    else
    {
        playlist->fim->prox = episodio;
        episodio->prev = playlist->fim;
        playlist->fim = episodio;
        printf("Episódio adicionado\n");
    }
}

void RemoverEp(Episodio* episodio) {
    if(episodio->prox == NULL && episodio->prev != NULL){
        episodio->prev->prox = NULL;
    }else if(episodio->prev == NULL && episodio->prox ==NULL){
        printf("Função não implementada para Podcasts com apenas um episódio!\nCrie outro episódio para remover este\n");
    }else if(episodio->prev != NULL && episodio->prox != NULL){
        episodio->prev->prox = episodio->prox;
        episodio->prox->prev = episodio->prev;
        printf("Episodio removido\n");
    }
}

int main(void)
{
    PodcastHead *podcasthead = CriarPodcastHead();
    Playlist *playlist = CriarPlaylist();
    Podcast* podcastEscolhido;
    Episodio * episodioEscolhido;
    Episodio * episodioAtual;
    Playlist *playlistBackup;
    bool shuffle = false;

    int opc;
    bool rodando = true;
    while (rodando == true) {
    printf("Bem-vindo!\nEscolha uma das opções abaixo:\n1 - Criar um novo "
           "podcast\n2 - Adicionar um episódio ao seu podcast\n3 - Remover um "
           "episódio ao seu podcast\n4 - Listar todos os episódios do seu "
           "Podcast\n5 - Adicionar episódios à sua playlist\n6 - Remover "
           "episódios da sua playlist\n7 - Tocar um episódio\n8 - Qual episódio "
           "estou ouvindo?\n9 - Adicionar ep atual à playlist\n10 - Tocar minha "
           "playlist\n11 - Tocar próximo da minha playlist\n12 - Ativar o modo "
           "aleatório na minha playlist\n13- Sair\n");
    scanf("%d", &opc);
    fflush(stdin);
        switch (opc) {
            case 1:
                AdicionaPodcast(podcasthead);
                break;
            case 2:
                podcastEscolhido = EscolherPodcast(podcasthead);
                AdicionaEpisodio(podcastEscolhido->listaEpisodios);
                break;
            case 3:
                podcastEscolhido = EscolherPodcast(podcasthead);
                episodioEscolhido = EscolherEpisodio(podcasthead, podcastEscolhido->listaEpisodios);
                RemoverEpisodio(episodioEscolhido);
                break;
            case 4:
                Printar(podcasthead);
                break;
            case 5:
                if(shuffle == false) {
                    podcastEscolhido = EscolherPodcast(podcasthead);
                    episodioEscolhido = EscolherEpisodio(podcasthead, podcastEscolhido->listaEpisodios);
                    AdicionaEp(playlist, episodioEscolhido);
                    break;
                } else if(shuffle == true){
                    printf("Desative o aleatório para adicionar episódios\n");
                }
                break;
            case 6:
                podcastEscolhido = EscolherPodcast(podcasthead);
                episodioEscolhido = EscolherEpisodio(podcasthead, podcastEscolhido->listaEpisodios);
                RemoverEp(episodioEscolhido);
                break;
            case 7:
                podcastEscolhido = EscolherPodcast(podcasthead);
                episodioEscolhido = EscolherEpisodio(podcasthead, podcastEscolhido->listaEpisodios);
                episodioAtual = TocarEpisodio(episodioEscolhido);
                break;
            case 8:
                if(episodioAtual->numero =! NULL){
                    printf("Você está ouvindo ao episódio:\n%d %s\n", episodioAtual->numero, episodioAtual->nome);
                }else{
                    printf("Você não está ouvindo a nenhum episódio\n");
                }
                break;
            case 9:
                if(shuffle == false) {
                    AdicionaEp(playlist, episodioAtual);
                    break;
                } else if(shuffle == true){
                    printf("Desative o aleatório para adicionar episódios\n");
                }
                break;
            case 10:
                episodioAtual = TocarEpisodio(playlist->inicio);
                break;
            case 11:
                if(shuffle == false) {
                    if (episodioAtual->prox != NULL) {
                        episodioAtual = TocarEpisodio(episodioAtual->prox);
                    } else {
                        printf("Sua playlist acabou, estou voltando ao primeiro episódio\n");
                        episodioAtual = TocarEpisodio(playlist->inicio);
                    }
                    break;
                }else if(shuffle == true){
                    int val = rand() % 101;
                    for(int i = 0; i!= val; i++){
                        episodioAtual = episodioAtual->prox;
                    }
                    TocarEpisodio((episodioAtual));
                }
            case 12:
                playlistBackup = playlist;

                if(shuffle == false){
                    shuffle = true;
                    playlist->fim = playlist->inicio;
                    printf("Modo aleatório ativado!\n");
                    break;
                } else if(shuffle == true){
                    shuffle = false;
                    playlist = playlistBackup;
                    printf("Modo aleatório desativado!\n");
                }
                break;
            case 13:
                rodando = false;
                break;
        }
    }


    return 0;
}