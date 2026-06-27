#ifndef MENU_H
#define MENU_H

struct produto {
    int codigo;
    char nome[50];
    float preco;
    int quantidade;
};
struct index {
    int codigo;
    int posicao;
}; 

void cadastrarProduto(struct produto *pd);
void relatorioTexto();
void relatorioBinario();
void buscarProduto();
void limparTela();
int validarNome(char nome[]);

#endif