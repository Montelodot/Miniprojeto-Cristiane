# 🐱 Black Cat Mercearia

Sistema de gerenciamento de estoque em C com persistência em arquivos binários e texto, utilizando indexação para busca eficiente.

---

## 📋 Funcionalidades

- **Cadastrar produto** — registra código, nome, preço e quantidade em estoque
- **Relatório em texto** — exibe todos os produtos a partir do arquivo `produtos.txt`
- **Relatório em binário** — exibe todos os produtos a partir do arquivo `produtos.bin`
- **Busca por código (indexada)** — localiza um produto diretamente pelo código usando o arquivo de índice `index.bin`

---

## 🗂️ Estrutura de Arquivos

```
.
├── projeto.c       # Função main — menu principal
├── menu.c          # Implementação das funções
├── menu.h          # Structs e declarações das funções
├── produtos.txt    # Registro dos produtos em texto
├── produtos.bin    # Registro dos produtos em binário
└── index.bin       # Índice de códigos e posições no arquivo binário
```

### Structs utilizadas

```c
struct produto {
    int codigo;
    char nome[50];
    float preco;
    int quantidade;
};

struct index {
    int codigo;
    int posicao; // posição do registro em produtos.bin
};
```

---

## ⚙️ Como Compilar

É necessário ter o **GCC** instalado.

```bash
gcc projeto.c menu.c -o programa
```

---

## ▶️ Como Executar

```bash
./programa        # Linux/Mac
programa.exe      # Windows
```

---

## 🖥️ Menu do Sistema

```
  /\_/\     BLACK CAT MERCEARIA
 ( o.o )
  > ^ <
=============================================
  [1] Cadastrar produto
  [2] Relatorio em texto (completo)
  [3] Relatorio em binario (completo)
  [4] Buscar produto por codigo (indexado)
  [0] Sair
=============================================
```

---

## ✅ Validações

- **Código** — deve ser um número positivo e não pode ser duplicado
- **Nome** — não pode ser vazio nem conter números
- **Preço** — deve ser um valor maior que zero
- **Quantidade** — deve ser zero ou maior

---

## 📌 Observações

- Os arquivos `produtos.txt`, `produtos.bin` e `index.bin` são criados automaticamente na primeira execução.
- A busca por código (opção 4) usa o arquivo `index.bin` para localizar o produto diretamente no arquivo binário, sem percorrer todos os registros.
- O sistema foi desenvolvido para Linux, Mac e Windows — a limpeza de tela é feita automaticamente de acordo com o sistema operacional.
