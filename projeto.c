#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
int main() {

    int opcao;
    struct produto *pd;

    do {

        limparTela();

        printf("\n");
        printf("  /\\_/\\     BLACK CAT MERCEARIA\n");
        printf(" ( o.o )\n");
        printf("  > ^ <\n");
        printf("=============================================\n");
        printf("  [1] Cadastrar produto\n");
        printf("  [2] Relatorio em texto (completo)\n");
        printf("  [3] Relatorio em binario (completo)\n");
        printf("  [4] Buscar produto por codigo (indexado)\n");
        printf("  [0] Sair\n");
        printf("=============================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:

                pd = (struct produto *) calloc(1, sizeof(struct produto));

                if (pd == NULL) {
                    printf("Erro: Memoria insuficiente!\n");
                    break;
                }

                printf("--- CADASTRO DE PRODUTO ---\n");
                cadastrarProduto(pd);

                free (pd);
                pd = NULL;

                printf("\nPressione [Enter] para voltar ao menu...");
                while (getchar() != '\n'); 
                getchar();
                break;

            case 2:
                printf("--- PRODUTOS NO ARQUIVO TEXTO (produtos.txt) ---\n");
                relatorioTexto();
                printf("\nPressione [Enter] para voltar ao menu...");
                getchar(); getchar();
                break;
            case 3:
                printf("--- PRODUTOS NO ARQUIVO BINARIO (produtos.bin) ---\n");
                relatorioBinario();
                printf("\nPressione [Enter] para voltar ao menu...");
                getchar(); getchar();
                break;
            case 4:
                printf("--- CONSULTA INDEXADA POR CODIGO ---\n");
                printf("Digite o codigo do produto que deseja buscar:\n");
                buscarProduto();
                printf("\nPressione [Enter] para voltar ao menu...");
                while (getchar() != '\n'); 
                getchar();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n"); 
                printf("\nPressione [Enter] para voltar ao menu...");
                getchar(); getchar();
                break;
        }

    } while (opcao != 0);

    return 0;
}
