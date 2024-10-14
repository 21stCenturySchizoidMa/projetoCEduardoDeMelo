#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 5

typedef struct {
    int codigoLivro;
    char nomeAutor[100];
    char nomeLivro[50];
    int anoLancamento;
    int numeroDePaginas;
    char editora[50];
    int quantidade;
    float preco;
    char edicao[50];
    char descricao[500];
    char disponivel;
} Livro;

typedef struct {
    int id;
    Livro *elementos;
} Lista;

Lista* criarLista();
int inserirElemento(Lista*, Livro);
int inserirElementoID(Lista*, Livro, int);
int inserirElementoInicio(Lista*, Livro);
int removerElemento(Lista*, int);
int atualizarElemento(Lista*, int, Livro);
int buscarElemento(Lista*, int);
int tamanho(Lista*);
void excluirLista(Lista*);
void carregarDados(Lista*, const char*);
void salvarDados(Lista*, const char*);
void listarElementos(Lista*);

int main() {
    Lista *lista = criarLista();


    Livro livro1 = {1, "Júlio Verne", "A Jornada ao Centro da Terra", 1864, 360, "Editora Globo", 15, 89.90, "3ª Edição", "Um dos maiores clássicos da literatura de aventura, com uma viagem épica ao interior da Terra.", 'S'};
    Livro livro2 = {2, "H. G. Wells", "A Máquina do Tempo", 1895, 288, "Companhia das Letras", 8, 74.50, "2ª Edição", "Obra visionária que apresenta um dos primeiros relatos de viagem no tempo.", 'S'};


    inserirElementoInicio(lista, livro1);
    inserirElementoID(lista, livro2, 1);


    printf("Livros na lista:\n");
    listarElementos(lista);


    Livro livro3 = {3, "George Orwell", "1984", 1949, 328, "Companhia das Letras", 20, 59.90, "1ª Edição", "Uma distopia clássica que explora temas de vigilância, totalitarismo e controle social.", 'S'};
    inserirElemento(lista, livro3);


    printf("\nApós adicionar mais um livro:\n");
    listarElementos(lista);


    salvarDados(lista, "Livros.txt");


    excluirLista(lista);

    return 0;
}

Lista* criarLista() {
    Lista *nova = (Lista*)malloc(sizeof(Lista));
    nova->id = 0;
    nova->elementos = (Livro*)malloc(TAM * sizeof(Livro));
    return nova;
}

int inserirElemento(Lista *lista, Livro livro) {
    if (lista == NULL) {
        printf("Lista vazia\n");
        return 0;
    }
    if (lista->id < TAM) {
        lista->elementos[lista->id] = livro;
        lista->id++;
        return 1;
    } else {
        printf("Sem espaço na lista\n");
        return 0;
    }
}

int inserirElementoID(Lista *lista, Livro livro, int posicaoLivro) {
    if (lista == NULL) {
        printf("Lista vazia\n");
        return 0;
    }
    if (lista->id >= TAM) {
        printf("Lista cheia\n");
        return 0;
    }
    if (posicaoLivro < 0 || posicaoLivro > lista->id) {
        printf("Posição inválida\n");
        return 0;
    }

    for (int i = lista->id; i > posicaoLivro; i--) {
        lista->elementos[i] = lista->elementos[i - 1];
    }

    lista->elementos[posicaoLivro] = livro;
    lista->id++;
    return 1;
}

int inserirElementoInicio(Lista *lista, Livro livro) {
    if (lista == NULL) {
        printf("Lista vazia\n");
        return 0;
    } else {
        return inserirElementoID(lista, livro, 0);
    }
}

void listarElementos(Lista *lista) {
    if (lista == NULL) {
        printf("Lista vazia\n");
        return;
    }

    for (int i = 0; i < lista->id; i++) {
        Livro livro = lista->elementos[i];
        printf("Código do Livro: %d\n", livro.codigoLivro);
        printf("Nome do Autor: %s\n", livro.nomeAutor);
        printf("Nome do Livro: %s\n", livro.nomeLivro);
        printf("Ano de Lançamento: %d\n", livro.anoLancamento);
        printf("Número de Páginas: %d\n", livro.numeroDePaginas);
        printf("Editora: %s\n", livro.editora);
        printf("Disponível: %c\n", livro.disponivel);
        printf("Quantidade: %d\n", livro.quantidade);
        printf("Preço: %.2f\n", livro.preco);
        printf("Edição: %s\n", livro.edicao);
        printf("Descrição: %s\n", livro.descricao);
        printf("\n");
    }
}

int removerElemento(Lista *lista, int posicao) {
    if (lista == NULL) {
        printf("Lista vazia\n");
        return 0;
    }
    if (lista->id == 0 || posicao < 0 || posicao >= lista->id) {
        printf("Posição inválida\n");
        return 0;
    }

    for (int i = posicao; i < lista->id - 1; i++) {
        lista->elementos[i] = lista->elementos[i + 1];
    }
    lista->id--;
    return 1;
}

int atualizarElemento(Lista *lista, int posicao, Livro novoLivro) {
    if (lista == NULL) {
        printf("Lista vazia\n");
        return 0;
    }

    if (posicao < 0 || posicao >= lista->id) {
        printf("Posição inválida\n");
        return 0;
    }

    lista->elementos[posicao] = novoLivro;
    return 1;
}

int buscarElemento(Lista *lista, int codigo) {
    for (int i = 0; i < lista->id; i++) {
        if (lista->elementos[i].codigoLivro == codigo) {
            return 1;
        }
    }
    printf("Livro não encontrado\n");
    return -1;
}

int tamanho(Lista *lista) {
    if (lista == NULL) {
        printf("Lista vazia\n");
        return 0;
    }
    return lista->id;
}

void excluirLista(Lista *lista) {
    if (lista == NULL) {
        printf("Lista vazia\n");
        return;
    }
    free(lista->elementos);
    free(lista);
}

void carregarDados(Lista *lista, const char *arquivo) {
    FILE *file = fopen(arquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    while (!feof(file)) {
        Livro livro;
        fscanf(file, "%d %s %s %d %d %s %d %f %s %s %c",
               &livro.codigoLivro, livro.nomeAutor, livro.nomeLivro,
               &livro.anoLancamento, &livro.numeroDePaginas, livro.editora,
               &livro.quantidade, &livro.preco, livro.edicao, livro.descricao, &livro.disponivel);
        inserirElemento(lista, livro);
    }

    fclose(file);
}

void salvarDados(Lista *lista, const char *arquivo) {
    FILE *file = fopen(arquivo, "w");
    if (file == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    for (int i = 0; i < lista->id; i++) {
        Livro livro = lista->elementos[i];
        fprintf(file, "%d %s %s %d %d %s %d %.2f %s %s %c\n",
                livro.codigoLivro, livro.nomeAutor, livro.nomeLivro,
                livro.anoLancamento, livro.numeroDePaginas, livro.editora,
                livro.quantidade, livro.preco, livro.edicao, livro.descricao, livro.disponivel);
    }

    fclose(file);
}