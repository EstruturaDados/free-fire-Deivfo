#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 10 // Número máximo de itens na mochila
#define TAM_NOME 30
#define TAM_TIPO 20

// ----------------------------------------------------------
// Estrutura que representa um item da mochila
// ----------------------------------------------------------
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

// ----------------------------------------------------------
// Protótipos das funções
// ----------------------------------------------------------
void inserirItem(Item mochila[], int *qtd);
void removerItem(Item mochila[], int *qtd);
void listarItens(Item mochila[], int qtd);
void buscarItem(Item mochila[], int qtd);
int buscarPosicao(Item mochila[], int qtd, const char *nome);

// ----------------------------------------------------------
// Função principal (menu principal do sistema)
// ----------------------------------------------------------
int main() {
    Item mochila[TAM_MAX];
    int qtd = 0;
    int opcao;

    do {
        printf("\n=== SISTEMA DE MOCHILA ===\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o '\n' do buffer

        switch (opcao) {
            case 1:
                inserirItem(mochila, &qtd);
                break;
            case 2:
                removerItem(mochila, &qtd);
                break;
            case 3:
                listarItens(mochila, qtd);
                break;
            case 4:
                buscarItem(mochila, qtd);
                break;
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

// ----------------------------------------------------------
// Função: inserirItem
// Objetivo: cadastra um novo item na mochila (até 10 itens).
// ----------------------------------------------------------
void inserirItem(Item mochila[], int *qtd) {
    if (*qtd >= TAM_MAX) {
        printf("Erro: Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novo;

    printf("Digite o nome do item: ");
    fgets(novo.nome, TAM_NOME, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // remove \n

    printf("Digite o tipo do item (ex: arma, municao, cura): ");
    fgets(novo.tipo, TAM_TIPO, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*qtd] = novo;
    (*qtd)++;

    printf("Item \"%s\" cadastrado com sucesso!\n", novo.nome);

    listarItens(mochila, *qtd);
}

// ----------------------------------------------------------
// Função: removerItem
// Objetivo: remove um item da mochila pelo nome.
// ----------------------------------------------------------
void removerItem(Item mochila[], int *qtd) {
    if (*qtd == 0) {
        printf("A mochila esta vazia! Nenhum item para remover.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("Digite o nome do item a remover: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int pos = buscarPosicao(mochila, *qtd, nomeBusca);

    if (pos == -1) {
        printf("Erro: Item \"%s\" nao encontrado.\n", nomeBusca);
        return;
    }

    // Move os itens seguintes uma posição para trás
    for (int i = pos; i < *qtd - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*qtd)--;

    printf("Item \"%s\" removido com sucesso!\n", nomeBusca);

    listarItens(mochila, *qtd);
}

// ----------------------------------------------------------
// Função: listarItens
// Objetivo: exibe todos os itens cadastrados.
// ----------------------------------------------------------
void listarItens(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("\nA mochila esta vazia.\n");
        return;
    }

    printf("\n--- Itens na mochila ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("-------------------------\n");
}

// ----------------------------------------------------------
// Função: buscarItem
// Objetivo: faz busca sequencial por nome e exibe os dados.
// ----------------------------------------------------------
void buscarItem(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("A mochila esta vazia! Nenhum item para buscar.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("Digite o nome do item que deseja buscar: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int pos = buscarPosicao(mochila, qtd, nomeBusca);

    if (pos == -1) {
        printf("Item \"%s\" nao encontrado.\n", nomeBusca);
    } else {
        printf("\nItem encontrado!\n");
        printf("Nome: %s\n", mochila[pos].nome);
        printf("Tipo: %s\n", mochila[pos].tipo);
        printf("Quantidade: %d\n", mochila[pos].quantidade);
    }
}

// ----------------------------------------------------------
// Função: buscarPosicao
// Objetivo: retorna a posição de um item (ou -1 se não achar).
// ----------------------------------------------------------
int buscarPosicao(Item mochila[], int qtd, const char *nome) {
    for (int i = 0; i < qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}
