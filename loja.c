#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

void ArquivoLista() {
    FILE *lista = fopen("produtos.txt", "w");

    if (lista == NULL) {
        printf("Erro ao criar o arquivo.\n");
        exit(1);
    } else {
        fclose(lista);
    }
}

void InserirProduto() {
    // Usando vetores de caracteres para armazenar textos corretamente
    char nomeProduto[50];
    char categoriaProduto[50];
    float precoProduto;
    int quantProduto;
    char fornecedorProduto[50];

    /* Abre o arquivo gerado novamente no modo "a" (adicionar)
    para preservar os registros anteriores*/
    FILE *lista = fopen("produtos.txt", "a");

    if (lista == NULL) {
        printf("Erro ao abrir o arquivo para salvar o produto.\n");
        return;
    }

    printf("--- Cadastro de Produto ---\n");
    printf("ID gerado automaticamente!\n");

    printf("Nome do produto: ");
    scanf("%s", nomeProduto);

    printf("Categoria: ");
    scanf("%s", categoriaProduto);

    printf("Preço R$: ");
    scanf("%.2f", &precoProduto);

    printf("Quantidade: ");
    scanf("%d", &quantProduto);

    printf("Fornecedor: ");
    scanf("%s", fornecedorProduto);

    fprintf(lista, "Nome: %s | Categoria: %s | Preço: %.2f | Quantidade: %d | Fornecedor: %s\n", 
            nomeProduto, categoriaProduto, precoProduto, quantProduto, fornecedorProduto);
    fclose(lista);

    printf("Produto inserido e salvo no arquivo com sucesso!\n\n");
    }

    int main (){
    
    int selecaoMenu;
    int selecaoMenuChar = "%d";    
    selecaoMenuChar = &selecaoMenu;
    do
    {                                   
        printf("\n--------------- MENU ----------------\n");
        printf("1 - Inserir produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Alterar produto\n");
        printf("4 - Excluir produto\n");
        printf("5 - Buscar por nome\n");
        printf("6 - Buscar por categoria\n");
        printf("7 - Ordenar produtos\n");
        printf("8 - Exportar CSV\n");
        printf("9 - Sair\n");
        printf("--------------------------------------\n");

        /*obriga o usuário a esolher a primeira opção
        para que gere o arquivo*/
        if (scanf("%d", &selecaoMenu) != 1){
            /*Limpa os caracteres inválidos do buffer
              pois se carregasse caracteres inválidos
              o laço ia se tornar infito até reinciar
              o programa.*/ 
            while (getchar() != '\n');
            printf("Entrada invalida. Tente novamente.\n");
            continue;
        }

        switch (selecaoMenu){
        case 1:
            InserirProduto();
            break;
        case 2:
            /* code */
            break;
        case 3:
            /* code */
            break;
        case 4:
            /* code */
            break;
        case 5:
            /* code */
            break;
        case 6:
            /* code */
            break;
        case 7:
            /* code */
            break;
        case 8:
            /* code */
            break;
        case 9:
            printf("Saindo do programa.\n");
            break;   
        
        default:
            printf("Opcao invalida. Escolha de 1 a 9.\n");
            break;
    }
    } while (selecaoMenu != 9);
    return 0;
}
