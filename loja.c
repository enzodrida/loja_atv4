/******************************************************************************

ATV004-loja:
                    grupo:
                    Enzo Carmargo Vilanova Araujo  RGM: 05006394-4 

*******************************************************************************/
#include <stdio.h> /**/
#include <stdlib.h> /**/
#include <string.h> /**/
#include <ctype.h> /**/

/**/
#define MAX_PRODUTOS 1000
/**/
#define ARQUIVO "produtos.txt"
/**/
#define TEMPORARIO "produtos_temp.txt" 
/**/
#define CSV "produtos.csv"


/*type para identificar quais os itens compõe na lista da loja*/
typedef struct {
    int idProduto;
    /*o valor que está dentro de chaves delimita o uso de caracteres.*/
    char nomeProduto[50];
    char categoriaProduto[50];
    float precoProduto;
    int quantProduto;
    char fornecedorProduto[50];
} Loja;

 /*tipo destinado para realizar ordenação*/
typedef struct {
    Loja produtos[MAX_PRODUTOS];
    int quantidade;
} ProdutosListados;

/*serve para comparar dois textos ignorando maiúsculas e minúsculas*/
int compararTexto(const char a[], const char b[]) {
    int i = 0;
                        /*utilizado como operador AND.*/
    while (a[i] != '\0' && b[i] != '\0') {
        int compararx = tolower((unsigned char)a[i]);
        int comparary = tolower((unsigned char)b[i]);
        if (compararx != comparary) return compararx - comparary;
        i++;
    }
    return tolower((unsigned char)a[i]) - tolower((unsigned char)b[i]);
}

/**/
int lerInteiro(const char mensagem[], int minimo) {
    char entrada[100];
    int valor;
    char extra;
    for (;;) {
        printf("%s", mensagem);
        if (fgets(entrada, sizeof(entrada), stdin) == NULL) return minimo;
        if (sscanf(entrada, " %d %c", &valor, &extra) == 1 && valor >= minimo)
            return valor;
        printf("Digite um numero inteiro valido (minimo %d).\n", minimo);
    }
}

/**/
float lerPreco(const char mensagem[]) {
    char entrada[100];
    float valor;
    char extra;
    for (;;) {
        printf("%s", mensagem);
        if (fgets(entrada, sizeof(entrada), stdin) == NULL) return 0.0f;
        if (sscanf(entrada, " %f %c", &valor, &extra) == 1 && valor >= 0.0f)
            return valor;
        printf("Digite um preco valido, usando ponto para os centavos.\n");
    }
}

/*função: */
void criarArquivo(void) {
    FILE *arquivo = fopen(ARQUIVO, "a");
    if (arquivo == NULL) {
        printf("Erro ao criar ou abrir %s.\n", ARQUIVO);
        exit(EXIT_FAILURE);
    }
    fclose(arquivo);
}

/**/
int carregarProdutos(ProdutosListados *lista) {
    FILE *arquivo = fopen(ARQUIVO, "r");
    char linha[256];
    int maiorId = 0;
    lista->quantidade = 0;
    if (arquivo == NULL) return 1;

    /* Lê e mostra cada linha gravada no arquivo. */
    while (fgets(linha, sizeof(linha), arquivo) != NULL &&
           lista->quantidade < MAX_PRODUTOS) {
        Loja produto = {0};
        int campos = sscanf(linha, "%d|%49[^|]|%49[^|]|%f|%d|%49[^\r\n]",
            &produto.idProduto, produto.nomeProduto, produto.categoriaProduto,
            &produto.precoProduto, &produto.quantProduto, produto.fornecedorProduto);

        if (campos != 6) {
            campos = sscanf(linha,
                "Nome: %49[^|] | Categoria: %49[^|] | Preco: %f | Quantidade: %d | Fornecedor: %49[^\r\n]",
                produto.nomeProduto, produto.categoriaProduto,
                &produto.precoProduto, &produto.quantProduto,
                produto.fornecedorProduto);
            if (campos == 5) produto.idProduto = -1;
        }

        if ((campos == 6 || campos == 5) &&
            produto.precoProduto >= 0.0f && produto.quantProduto >= 0) {
            lista->produtos[lista->quantidade++] = produto;
            if (produto.idProduto > maiorId) maiorId = produto.idProduto;
        }
    }
    fclose(arquivo);

    int i;
    for (i = 0; i < lista->quantidade; i++) {
        if (lista->produtos[i].idProduto < 0)
            lista->produtos[i].idProduto = ++maiorId;
    }
    return 1;
}

/**/
int salvarProdutos(const ProdutosListados *lista) {
    FILE *arquivo = fopen(TEMPORARIO, "w");
    int i;
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo temporario.\n");
        return 0;
    }
    for (i = 0; i < lista->quantidade; i++) {
        const Loja *produto = &lista->produtos[i];
        if (fprintf(arquivo, "%d|%s|%s|%.2f|%d|%s\n",
            produto->idProduto, produto->nomeProduto, produto->categoriaProduto,
            produto->precoProduto, produto->quantProduto,
            produto->fornecedorProduto) < 0) {
            fclose(arquivo);
            remove(TEMPORARIO);
            printf("Erro ao gravar os produtos.\n");
            return 0;
        }
    }
    if (fclose(arquivo) != 0) {
        remove(TEMPORARIO);
        printf("Erro ao fechar o arquivo temporario.\n");
        return 0;
    }
    if (rename(TEMPORARIO, ARQUIVO) != 0) {
        printf("Erro ao substituir o arquivo original.\n");
        return 0;
    }
    return 1;
}

/*/*/
void imprimirTabela(const ProdutosListados *lista) {
    int i;
    printf("\n%s %s %s %s %s %s\n",
           "ID | ", "Produto | ", "Categoria | ", "Preco | ", "Quantidade | ", "Fornecedor |\n");

    for (i = 0; i < lista->quantidade; i++) {
        const Loja *p = &lista->produtos[i];
        printf("%d %s %s %.2f %d %s\n",
               p->idProduto, p->nomeProduto, p->categoriaProduto,
               p->precoProduto, p->quantProduto, p->fornecedorProduto);
    }
    if (lista->quantidade == 0) printf("Nenhum produto cadastrado.\n");
}
 /**/
void listarRegistros(void) {
    ProdutosListados lista;
    if (!carregarProdutos(&lista)) return;
    printf("\n--- Conteudo da Lista ---\n");
    imprimirTabela(&lista);
}

/**/
int indicePorId(const ProdutosListados *lista, int id) {
    int i;
    for (i = 0; i < lista->quantidade; i++)
        if (lista->produtos[i].idProduto == id) return i;
    return -1;
}

/**/
int indicePorNome(const ProdutosListados *lista, const char nome[], int ignorar) {
    int i;
    for (i = 0; i < lista->quantidade; i++) {
        if (i != ignorar && compararTexto(lista->produtos[i].nomeProduto, nome) == 0)
            return i;
    }
    return -1;
}

/**/
void lerDadosProduto(Loja *produto) {

    printf("Nome do produto: ");
    /**/
    fgets(produto->nomeProduto, 50, stdin);
    produto->nomeProduto[strcspn(produto->nomeProduto, "\n")] = '\0';
    /**/
    printf("Categoria: ");
    fgets(produto->categoriaProduto, 50, stdin);
    produto->categoriaProduto[strcspn(produto->categoriaProduto, "\n")] = '\0';

    produto->precoProduto = lerPreco("Preco R$: ");
    produto->quantProduto = lerInteiro("Quantidade: ", 0);
    /**/
    printf("Fornecedor: ");
    fgets(produto->fornecedorProduto, 50, stdin);
    produto->fornecedorProduto[strcspn(produto->fornecedorProduto, "\n")] = '\0';
}

/**/
void InserirProduto(void) {
    /* A variável produto guarda os dados do produto. */
    Loja produto = {0};
    ProdutosListados lista;
    int i, maiorId = 0;

    if (!carregarProdutos(&lista)) return;
    if (lista.quantidade >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido.\n");
        return;
    }
    printf("\n--- Cadastro de Produto ---\n");
    lerDadosProduto(&produto);
    if (indicePorNome(&lista, produto.nomeProduto, -1) >= 0) {
        printf("Ja existe um produto com esse nome. Cadastro cancelado.\n");
        return;
    }
    for (i = 0; i < lista.quantidade; i++)
        if (lista.produtos[i].idProduto > maiorId) maiorId = lista.produtos[i].idProduto;
    produto.idProduto = maiorId + 1;
    while (indicePorId(&lista, produto.idProduto) >= 0) produto.idProduto++;
    lista.produtos[lista.quantidade++] = produto;
    /* Abre o arquivo para acrescentar o produto no final. */
    if (salvarProdutos(&lista))
        printf("Produto inserido com ID %d.\n", produto.idProduto);
}

/**/
void alterarProduto(void) {
    ProdutosListados lista;
    Loja alterado;
    int id, indice;
    if (!carregarProdutos(&lista)) return;
    id = lerInteiro("Digite o ID do produto que deseja alterar: ", 1);
    indice = indicePorId(&lista, id);
    if (indice < 0) {
        printf("Produto nao encontrado.\n");
        return;
    }
    printf("Digite os novos dados do produto.\n");
    lerDadosProduto(&alterado);
    if (indicePorNome(&lista, alterado.nomeProduto, indice) >= 0) {
        printf("Ja existe outro produto com esse nome. Alteracao cancelada.\n");
        return;
    }
    alterado.idProduto = id;
    lista.produtos[indice] = alterado;
    if (salvarProdutos(&lista)) printf("Produto alterado.\n");
}

/**/
void excluirProduto(void) {
    ProdutosListados lista;
    int id, indice, i;
    if (!carregarProdutos(&lista)) return;
    id = lerInteiro("Digite o ID do produto que deseja excluir: ", 1);
    indice = indicePorId(&lista, id);
    if (indice < 0) {
        printf("Produto nao encontrado.\n");
        return;
    }
    for (i = indice; i < lista.quantidade - 1; i++)
        lista.produtos[i] = lista.produtos[i + 1];
    lista.quantidade--;
    if (salvarProdutos(&lista)) printf("Produto excluido.\n");
}

/*Bouble sort ordena nome de (A-Z)*/
void ordenarNomeAZ(ProdutosListados *lista) {
    int i, j;
    for (i = 0; i < lista->quantidade - 1; i++) {
        for (j = 0; j < lista->quantidade - i - 1; j++) {
            if (compararTexto(lista->produtos[j].nomeProduto,
                              lista->produtos[j + 1].nomeProduto) > 0) {
                Loja temporario = lista->produtos[j];
                lista->produtos[j] = lista->produtos[j + 1];
                lista->produtos[j + 1] = temporario;
            }
        }
    }
}

/*Bouble sort ordena nome de (Z-A)*/
void ordenarNomeZA(ProdutosListados *lista) {
    int i, j;
    for (i = 0; i < lista->quantidade - 1; i++) {
        for (j = 0; j < lista->quantidade - i - 1; j++) {
            if (compararTexto(lista->produtos[j].nomeProduto,
                              lista->produtos[j + 1].nomeProduto) < 0) {
                Loja temporario = lista->produtos[j];
                lista->produtos[j] = lista->produtos[j + 1];
                lista->produtos[j + 1] = temporario;
            }
        }
    }
}

/*Bouble sort ordena de menor->maior*/
void ordenarPrecoMenorMaior(ProdutosListados *lista) {
    int i, j;
    for (i = 0; i < lista->quantidade - 1; i++) {
        for (j = 0; j < lista->quantidade - i - 1; j++) {
            if (lista->produtos[j].precoProduto >
                lista->produtos[j + 1].precoProduto) {
                Loja temporario = lista->produtos[j];
                lista->produtos[j] = lista->produtos[j + 1];
                lista->produtos[j + 1] = temporario;
            }
        }
    }
}

/*Bouble sort ordena de maior-->menor*/
void ordenarPrecoMaiorMenor(ProdutosListados *lista) {
    int i, j;
    for (i = 0; i < lista->quantidade - 1; i++) {
        for (j = 0; j < lista->quantidade - i - 1; j++) {
            if (lista->produtos[j].precoProduto <
                lista->produtos[j + 1].precoProduto) {
                Loja temporario = lista->produtos[j];
                lista->produtos[j] = lista->produtos[j + 1];
                lista->produtos[j + 1] = temporario;
            }
        }
    }
}

/*nova lista apresentada no botão 5 quando utilizamos essa função*/
void ordenarProdutos(void) {
    ProdutosListados lista;
    int menuBotao5;
    int opcao;
    if (!carregarProdutos(&lista)) return;
    printf("\n--- Ordenar produtos ---\n");
    printf("1 - Produtos por nome (A-Z)\n");
    printf("2 - Produtos por nome (Z-A)\n");
    printf("3 - Produtos por preco (menor para maior)\n");
    printf("4 - Produtos por preco (maior para menor)\n");
    opcao = lerInteiro("Opcao: ", 1);

    /**/
    if (scanf("%d", &menuBotao5) != 1) {
            /* Ao receber caracteres em vez de um número, limpa a entrada. */
            while ((menuBotao5 = getchar()) != '\n') {
                /* Descarta os caracteres inválidos. */
            }
            system("cls");
            printf("Entrada invalida. Tente novamente.\n");
        }

    /**/
    switch (opcao) {
        /**/
        case 1:
            ordenarNomeAZ(&lista);
            break;
        /**/
        case 2:
            ordenarNomeZA(&lista);
            break;
        /**/
        case 3:
            ordenarPrecoMenorMaior(&lista);
            break;
        /**/
        case 4:
            ordenarPrecoMaiorMenor(&lista);
            break;
        /*Envia  para a tela*/
        default:
            printf("Opcao invalida.\n");
            return;
    }
    /**/
    imprimirTabela(&lista);
}

/**/
void escreverCampoCSV(FILE *arquivo, const char campo[]) {
    int i;
    fputc('"', arquivo);
    for (i = 0; campo[i] != '\0'; i++) {
        if (campo[i] == '"') fputc('"', arquivo);
        fputc(campo[i], arquivo);
    }
    fputc('"', arquivo);
}

/**/
void exportarCSV(void) {
    ProdutosListados lista;
    FILE *arquivo;
    int i;
    if (!carregarProdutos(&lista)) return;
    arquivo = fopen(CSV, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o CSV.\n");
        return;
    }
    fprintf(arquivo, "ID,Produto,Categoria,Preco,Quantidade,Fornecedor\n");
    for (i = 0; i < lista.quantidade; i++) {
        Loja *p = &lista.produtos[i];
        fprintf(arquivo, "%d,", p->idProduto);
        escreverCampoCSV(arquivo, p->nomeProduto);
        fputc(',', arquivo);
        escreverCampoCSV(arquivo, p->categoriaProduto);
        fprintf(arquivo, ",%.2f,%d,", p->precoProduto, p->quantProduto);
        escreverCampoCSV(arquivo, p->fornecedorProduto);
        fputc('\n', arquivo);
    }
    fclose(arquivo);
    printf("Dados exportados para %s.\n", CSV);
}

/*inicio do codigo*/
int main(void) {
    int selecaoMenu;
    criarArquivo();

    /* Abre um laço de repetição para mostrar o menu novamente. */
    do {
        printf("\n--------------- MENU ----------------\n");
        printf("1 - Inserir produto\n");
        printf("2 - Mostrar a lista\n");
        printf("3 - Alterar produto\n");
        printf("4 - Excluir produto\n");
        printf("5 - Ordenar produtos\n");
        printf("6 - Exportar CSV\n");
        printf("7 - Sair\n");
        printf("--------------------------------------\n");
        printf("Opcao: ");

        if (scanf("%d", &selecaoMenu) != 1) {
            /* Ao receber caracteres em vez de um número, limpa a entrada. */
            while ((selecaoMenu = getchar()) != '\n') {
                /* Descarta os caracteres inválidos. */
            }
            system("cls");
            printf("Entrada invalida. Tente novamente.\n");
            
            continue;
        }

        switch (selecaoMenu) {
            case 1: {
                int inserirMais = 1;
                /* Repete o cadastro enquanto o usuário quiser inserir produtos. */
                do {
                    InserirProduto();
                    inserirMais = lerInteiro("Deseja inserir outro produto? (1-Sim, 2-Nao): ", 1);
                } while (inserirMais == 1);
                break;
            }
            case 2:
                listarRegistros();
                break;
            case 3:
                alterarProduto();
                break;
            case 4:
                excluirProduto();
                break;
            case 5:
                ordenarProdutos();
                break;
            case 6:
                exportarCSV();
                break;
            case 7:
                printf("Saindo do programa.\n");
                break;
            default:
                system("cls");
                printf("Opcao invalida. Escolha de 1 a 7.\n");
                break;
        }
        /*faça enquanto for maior ou igual a 1 ou menor ou igual a 7*/
        /*"||" é utilizado como operador OU.*/
    } while (selecaoMenu >= 1 || selecaoMenu <= 7);

    return 0;
}
