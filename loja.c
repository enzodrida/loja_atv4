#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int idProduto;
    char nomeProduto[50];
    char categoriaProduto[50];
    float precoProduto;
    int quantProduto;
    char fornecedorProduto[50];
} Loja;

typedef struct
{
    
} ProdutosListados;



void bubbleSortAZ(char v[], int tamanho) {
    int i, j;
    char temp;
    for (i = 0; i < tamanho - 1; i++) {
        for (j = 0; j < tamanho - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

void bubbleSortZA(char v[], int tamanho) {
    int i, j;
    char temp;
    for (i = 0; i < tamanho - 1; i++) {
        for (j = 0; j < tamanho - i - 1; j++) {
            if (v[j] < v[j + 1]) {
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

void listarRegistros(void) {
    FILE* lista = fopen("produtos.txt", "r");

    if (lista == NULL) {
        printf("Arquivo nao encontrado ou ainda nao foi criado.\n");
        return;
    }

    char linha[256];

    printf("\n--- Conteudo da Lista ---\n");

    /* Lê e mostra cada linha gravada no arquivo. */
    while (fgets(linha, sizeof(linha), lista) != NULL) {
        printf("%s", linha);
    }

    fclose(lista);
}

void InserirProduto(void) {
    /* A variável produto guarda os dados do produto. */
    Loja produto = { 0 };

    printf("\n--- Cadastro de Produto ---\n");

    printf("Nome do produto: ");
    if (scanf(" %49[^\n]", produto.nomeProduto) != 1) {
        printf("Erro ao ler o nome.\n");
        return;
    }

    printf("Categoria: ");
    if (scanf(" %49[^\n]", produto.categoriaProduto) != 1) {
        printf("Erro ao ler a categoria.\n");
        return;
    }

    printf("Preco R$: ");
    if (scanf("%f", &produto.precoProduto) != 1) {
        printf("Preco invalido.\n");
        return;
    }

    printf("Quantidade: ");
    if (scanf("%d", &produto.quantProduto) != 1) {
        printf("Quantidade invalida.\n");
        return;
    }

    printf("Fornecedor: ");
    if (scanf(" %49[^\n]", produto.fornecedorProduto) != 1) {
        printf("Erro ao ler o fornecedor.\n");
        return;
    }
    /* Abre o arquivo para acrescentar o produto no final. */
    FILE* lista = fopen("produtos.txt", "a");

    if (lista == NULL) {
        printf("Erro ao abrir o arquivo para salvar o produto.\n");
        return;
    }

    fprintf(lista,
        "Nome: %s | Categoria: %s | Preco: %.2f | Quantidade: %d | Fornecedor: %s\n",
        produto.nomeProduto,
        produto.categoriaProduto,
        produto.precoProduto,
        produto.quantProduto,
        produto.fornecedorProduto);

    fclose(lista);

    printf("Produto inserido e salvo no arquivo com sucesso!\n\n");
}

int main(void) {
    int selecaoMenu;

    /* Abre um laço de repetição para mostrar o menu novamente. */
    do {
        printf("\n--------------- MENU ----------------\n");
        printf("1 - Inserir produto\n");
        printf("2 - Mostrar a Lista\n");
        printf("3 - Alterar produto\n");
        printf("4 - Excluir produto\n");
        printf("5 - Buscar Produto por Ordenação\n");
        printf("6 - Exportar CSV\n");
        printf("7 - Sair\n");
        printf("--------------------------------------\n");
        printf("Opcao: ");

        if (scanf("%d", &selecaoMenu) != 1) {
            /* Ao receber caracteres em vez de um número, limpa a entrada. */
            while ((selecaoMenu = getchar()) != '\n') {
                /* Descarta os caracteres inválidos. */
            }

            printf("Entrada invalida. Tente novamente.\n");
            continue;
        }

        switch (selecaoMenu) {
        case 1: {
            int inserirMaisItens = 1;

            /* Repete o cadastro enquanto o usuário quiser inserir produtos. */
            do {
                InserirProduto();

                printf("\nDeseja inserir mais algum produto?\n");
                printf("1 - Sim\n");
                printf("2 - Nao\n");
                printf("Opcao: ");

                if (scanf("%d", &inserirMaisItens) != 1) {
                    printf("Entrada invalida. Voltando ao menu.\n");
                    inserirMaisItens = 2;
                }
            } while (inserirMaisItens == 1);

            break;
        }

        case 2:
            listarRegistros();
            break;

        case 3:
            /* Alterar produto será implementado aqui. */
            printf("Opcao ainda nao implementada.\n");
            break;

        case 4:
            /* Excluir produto será implementado aqui. */
            printf("Opcao ainda nao implementada.\n");
            break;

        case 5:
            int buscaLista;
            Loja busca;
            printf("1 - produtos por nome (A–Z)\n");
            printf("2 -produtos por nome (Z–A)\n");
            printf("3 - Ordenar produtos por preço (menor → maior\n");
            printf("4 - Ordenar produtos por preço (maior → menor\n");

            if (scanf("%d", &buscaLista) != 1) {
                /* Ao receber caracteres em vez de um número, limpa a entrada. */
                while ((buscaLista = getchar()) != '\n') {
                    /* Descarta os caracteres inválidos. */
                }
                printf("Entrada invalida. Tente novamente.\n");
                continue;
            }

            switch (buscaLista)
            {
            case 1:
                FILE * lista = fopen("produtos.txt", "r");

                if (lista == NULL) {
                    printf("Arquivo nao encontrado ou ainda nao foi criado.\n");
                    return;
                }

                bubbleSortAZ(v, busca.nomeProduto);
                printf("\nCrescente (A-Z): ");
                for (int i = 0; i < busca.nomeProduto; i++) printf("%s ", v[i]);

                listarRegistros();
                
                break;
            case 2:
                
                FILE * lista = fopen("produtos.txt", "r");

                if (lista == NULL) {
                    printf("Arquivo nao encontrado ou ainda nao foi criado.\n");
                    return;
                }

                bubbleSortZA(v, busca.nomeProduto);
                printf("\nDecrescente (Z-A): ");
                for (int i = 0; i < busca.nomeProduto; i++) printf("%s ", v[i]);
                listarRegistros();
                break;
            case 3:
                /* code */
                break;
            case 4:
                /* code */
                break;
            default:
                break;
            }




            break;

        case 6:
            /* Buscar por categoria será implementado aqui. */
            printf("Opcao ainda nao implementada.\n");
            break;

        case 7:
            printf("Saindo do programa.\n");
            break;

        default:
            printf("Opcao invalida. Escolha de 1 a 9.\n");
            break;
        }
    } while (selecaoMenu != 9);

    return 0;
}
