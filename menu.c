#include <stdio.h>
#include "menu.h"
#include <ctype.h>
#include <stdlib.h>
void cadastrarProduto(struct produto *pd) {

    int cod_duplicado;
    struct index idx;
    FILE *ftxt = fopen("produtos.txt", "a");
    FILE *fbin = fopen("produtos.bin", "ab");
    FILE *findex = fopen("index.bin", "ab");

    if (ftxt == NULL || fbin == NULL || findex == NULL) {
        if (ftxt) fclose(ftxt);
        if (fbin) fclose(fbin);
        if (findex) fclose(findex);
        printf("Erro ao abrir os arquivos\n");

        return;
    }

    printf("Digite o codigo do produto:\n");
    do {
        cod_duplicado = 0;

        if (scanf("%d", &pd->codigo) != 1) {
            printf("Erro: Digite um numero valido para o codigo.\n");
            while (getchar() != '\n');
            pd->codigo = -1; 
            continue;
        }

        if (pd->codigo < 0) {
            printf("Erro: Digite um valor valido\n");
            continue;
        }

        FILE *fcheck = fopen("index.bin", "rb");
        if (fcheck != NULL) {
            struct index temp_idx;
            while (fread(&temp_idx, sizeof(struct index), 1, fcheck) == 1) {
                if (temp_idx.codigo == pd->codigo) {
                    printf("Erro: Este codigo ja esta cadastrado. Tente outro.\n");
                    cod_duplicado = 1;
                    break;
                }
            }
            fclose(fcheck);
        }
    }
    while (pd->codigo < 0 || cod_duplicado);

    printf("Digite o nome do produto:\n");
    do {
        scanf(" %49[^\n]", pd->nome);
        
        if (!validarNome(pd->nome)) {
            printf("Erro: O nome nao pode ser vazio ou conter numeros. Tente novamente.\n");
        }

    } while (!validarNome(pd->nome));

    printf("Digite o preco do produto:\n");
    do {
        if (scanf("%f", &pd->preco) != 1) {
            printf("Erro: Digite um numero valido para o preco.\n");
            while (getchar() != '\n');
            pd->preco = -1; 
            continue;
        }

        if (pd->preco <= 0) 
            printf("Erro: Digite um valor válido\n");
        
    } while (pd->preco <= 0);

    printf("Digite a quantidade de itens desse produto em estoque:\n");
    do {
        if (scanf("%d", &pd->quantidade) != 1) {
            printf("Erro: Digite um numero valido para o quantidade.\n");
            while (getchar() != '\n');
            pd->quantidade = -1; 
            continue;
        }

        if (pd->quantidade < 0) 
            printf("Digite um valor valido\n");
       
    } while (pd->quantidade < 0);

    fprintf(ftxt, "%d;%s;%.2f;%d\n", pd -> codigo, pd -> nome, pd -> preco, pd -> quantidade);
    fseek(fbin, 0, SEEK_END);   
    idx.posicao = ftell(fbin) / sizeof(struct produto); 

    fwrite(pd, sizeof(struct produto), 1, fbin);
    idx.codigo = pd->codigo;
    fwrite(&idx, sizeof(struct index), 1, findex);

    fclose(ftxt); fclose(fbin); fclose(findex);

    printf("Produto cadastrado com sucesso no registro: %d\n", idx.posicao);

}

void relatorioTexto() {

    FILE *ftxt = fopen("produtos.txt", "r");

    if (ftxt == NULL) {
        printf("Arquivo nao encontrado!\n");
        return;
    }

    struct produto pd;

    printf("\n=== RELATORIO EM TEXTO ===\n");

    while (fscanf(ftxt, "%d;%49[^;];%f;%d\n", &pd.codigo, pd.nome, &pd.preco, &pd.quantidade) == 4) {
        printf("Codigo: %d | Nome: %s | Preco: R$ %.2f | Qtd: %d\n", pd.codigo, pd.nome, pd.preco, pd.quantidade);
    }
    fclose(ftxt);
}

void relatorioBinario() {

    FILE *fbin = fopen("produtos.bin", "rb");

    if (fbin == NULL) {
        printf("Arquivo nao encontrado!\n");
        return;
    }

    struct produto pd;

    printf("\n=== RELATORIO EM BINARIO ===\n");

    while (fread(&pd, sizeof(struct produto), 1, fbin) == 1) {
        printf("Codigo: %d | Nome: %s | Preco: R$ %.2f | Qtd: %d\n", pd.codigo, pd.nome, pd.preco, pd.quantidade);
    }
    fclose(fbin);

}

void buscarProduto() {

    FILE *findex = fopen("index.bin", "rb");
    FILE *fbin = fopen("produtos.bin", "rb");

    if (findex == NULL || fbin == NULL) {
        printf("Erro ao abrir arquivos!\n");
        if (findex) fclose(findex);
        if (fbin) fclose(fbin);
        return;
    }

    int codigoB, pos = -1;
    struct index idx;
    struct produto pd;

    if (scanf("%d", &codigoB) != 1) {
        printf("Codigo invalido.\n");
        while (getchar() != '\n');
        fclose(findex); fclose(fbin);
        return;
    }
    
    while (fread(&idx, sizeof(struct index), 1, findex) == 1) {
        if (idx.codigo == codigoB) {
            pos = idx.posicao;
            break;
        }
    }

    fclose(findex);

    if (pos == -1) {
        printf("Produto com o codigo %d nao encontrado no indice.\n", codigoB);
        fclose(fbin);
        return;
    }

    fseek(fbin, pos * sizeof(struct produto), SEEK_SET);
    if (fread(&pd, sizeof(struct produto), 1, fbin) != 1) {
        printf("Erro ao ler o produto.\n");
        fclose(fbin);
        return;
    }

    printf("\nProduto encontrado (registro %d):\n", pos);
    printf("Codigo: %d | Nome: %s | Preco: %.2f | Qtd: %d\n", pd.codigo, pd.nome, pd.preco, pd.quantidade);

    fclose(fbin);
}
int validarNome(char nome[]) {
    int i = 0;

    while (isspace(nome[i])) i++;

    if (nome[i] == '\0') return 0;

    for (i = 0; nome[i] != '\0'; i++) {
        if (isdigit(nome[i])) return 0;
    }
    return 1;
}
void limparTela(){
    #ifdef _WIN32
        system("cls");
    #else 
        system("clear");
    #endif
}