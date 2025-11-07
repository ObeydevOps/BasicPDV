#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <limits.h> 

/*
================================================================
 1. DEFINIÇÃO DAS ESTRUTURAS DE DADOS 
================================================================
*/

// Define um produto no estoque
typedef struct {
    int id;         // Código de barras (ID)
    char nome[100]; // Nome do produto
    float preco;    // Preço unitário
} Produto;

// Define um item dentro do carrinho
typedef struct {
    Produto produto; // O produto que foi comprado
    int quantidade;  // Quantidade que foi comprados
} ItemCarrinho;


/*
================================================================
 2. BANCO DE DADOS E CARRINHO/Variáveis Globais
================================================================
*/

Produto bancoDeDados[200]; 
int totalProdutosNoBanco = 0; // Começa em zero
// Nosso carrinho de compras (começa vazio)
ItemCarrinho carrinho[100];
int totalItensNoCarrinho = 0;


/*
================================================================
 3. FUNÇÕES AUXILIARES E CARREGAMENTO DE DADOS
================================================================
*/

// Funcao para carregar os produtos de um arquivo CSV 
void carregarProdutos(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r"); // Tenta abrir o arquivo para leitura 
    
    if (arquivo == NULL) {
        printf("!! ERRO FATAL: Nao foi possivel abrir o arquivo '%s' !!\n", nomeArquivo);
        printf("!! Verifique se o arquivo existe e esta na mesma pasta do executavel. !!\n");
        exit(1); // Encerra o programa
    }

    char linha[256]; // Buffer para ler cada linha do arquivo
    totalProdutosNoBanco = 0; // Reinicia o contador
    
    // Leitura linha por linha ate o fim do arquivo 
    while (fgets(linha, sizeof(linha), arquivo) != NULL && totalProdutosNoBanco < 200) {
        
        int id;
        char nome[100];
        float preco;
        
        // Tenta extrair: ID (int), Nome (string), Preco (float)
    
        int lidos = sscanf(linha, "%d,%99[^,],%f", &id, nome, &preco);

        if (lidos == 3) { 
            // Copia os dados lidos para o array
            bancoDeDados[totalProdutosNoBanco].id = id;
            strncpy(bancoDeDados[totalProdutosNoBanco].nome, nome, 99);
            bancoDeDados[totalProdutosNoBanco].nome[99] = '\0'; 
            bancoDeDados[totalProdutosNoBanco].preco = preco;
            
            totalProdutosNoBanco++; // Incrementa o contador 
        }
    }

    fclose(arquivo); 
    printf(">> %d produtos carregados do arquivo '%s' com sucesso! <<\n\n", 
           totalProdutosNoBanco, nomeArquivo);
}

// Funcao para limpar a tela (multiplataforma)
void limparTela() {
    #ifdef _WIN32
        system("cls"); // Comando do Windows
    #else
        system("clear"); // Comando do Linux/Mac
    #endif
}

// Funcao para exibir todos os produtos disponiveis no banco de dados
void exibirCatalogo() {
    printf("========= PRODUTOS DISPONIVEIS (%d) =========\n", totalProdutosNoBanco);
    printf("ID   | NOME                     | PRECO\n");
    printf("------------------------------------------\n");
    
    for (int i = 0; i < totalProdutosNoBanco; i++) {
        printf("%-4d | %-24s | R$ %5.2f\n", 
               bancoDeDados[i].id, 
               bancoDeDados[i].nome, 
               bancoDeDados[i].preco);
    }
    printf("============================================\n\n");
}

// Funcao para buscar um produto no banco de dados pelo ID
Produto* buscarProdutoPorId(int id) {
    for (int i = 0; i < totalProdutosNoBanco; i++) {
        if (bancoDeDados[i].id == id) {
            return &bancoDeDados[i];
        }
    }
    return NULL; 
}

// Funcao para adicionar um produto ao carrinho
void adicionarAoCarrinho(int id, int quantidade) {
    Produto* produtoEncontrado = buscarProdutoPorId(id);

    if (produtoEncontrado == NULL) {
        printf("!! ERRO: Produto com ID %d nao encontrado. !!\n", id);
        return; 
    }

    for (int i = 0; i < totalItensNoCarrinho; i++) {
        if (carrinho[i].produto.id == id) {
            carrinho[i].quantidade += quantidade;
            printf(">> %dx %s adicionado(s). (Quantidade atual: %d) <<\n", 
                   quantidade, produtoEncontrado->nome, carrinho[i].quantidade);
            return; 
        }
    }

    if (totalItensNoCarrinho < 100) { 
        carrinho[totalItensNoCarrinho].produto = *produtoEncontrado; 
        carrinho[totalItensNoCarrinho].quantidade = quantidade;
        totalItensNoCarrinho++; 
        
        printf(">> %dx %s adicionado(s) ao carrinho. <<\n", 
               quantidade, produtoEncontrado->nome);
    } else {
        printf("!! ERRO: Carrinho esta cheio! !!\n");
    }
}

// Funcao para calcular o subtotal de um item (preco * qtd)
float calcularSubtotalItem(ItemCarrinho item) {
    return item.produto.preco * item.quantidade;
}

// Funcao para calcular o total de todos os itens no carrinho
float calcularTotalCarrinho() {
    float total = 0.0;
    for (int i = 0; i < totalItensNoCarrinho; i++) {
        total += calcularSubtotalItem(carrinho[i]);
    }
    return total;
}

// Funcao para exibir o recibo final da compra
void exibirRecibo() {
    printf("\n\n========= CUPOM FISCAL =========\n");
    printf("QTD | UN | PRODUTO                | SUBTOTAL\n");
    printf("------------------------------------------\n");

    for (int i = 0; i < totalItensNoCarrinho; i++) {
        printf("%-3d | %4.2f | %-22s | R$ %6.2f\n",
               carrinho[i].quantidade,
               carrinho[i].produto.preco,
               carrinho[i].produto.nome,
               calcularSubtotalItem(carrinho[i])
        );
    }
    
    float total = calcularTotalCarrinho();
    printf("------------------------------------------\n");
    printf("TOTAL DA COMPRA: R$ %.2f\n", total);
    printf("=================================\n\n");
}

// Funcao para simular o processo de pagamento
void processarPagamento(float total) {
    float valorPago;
    
    do {
        printf("Valor total a pagar: R$ %.2f\n", total);
        printf("Digite o valor pago pelo cliente: R$ ");
        
        
        while (scanf("%f", &valorPago) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer
            printf("Entrada invalida. Digite apenas numeros: R$ ");
        }

        if (valorPago < total) {
            printf("!! Valor insuficiente! Faltam R$ %.2f !!\n\n", total - valorPago);
        }
    } while (valorPago < total);

    float troco = valorPago - total;

    printf("\nValor pago: R$ %.2f\n", valorPago);
    printf("Troco:      R$ %.2f\n", troco);
    printf("\nPagamento processado com sucesso!\n");
}


/*
================================================================
 4. FUNÇÃO PRINCIPAL 
================================================================
*/

int main() {
    // 1. CHAMA A FUNÇÃO DE CARREGAMENTO DE DADOS ANTES DE TUDO!
    carregarProdutos("produtos.csv");

    int idProduto;
    int quantidade;

    while (1) {
        limparTela();
        exibirCatalogo(); 
        
        if(totalItensNoCarrinho > 0) {
            printf("--- Total Parcial: R$ %.2f ---\n", calcularTotalCarrinho());
        }

        printf("Digite o ID do produto (ou 0 para finalizar a compra): ");
        
        // Le a entrada do usuario, garantindo que seja um inteiro
        while (scanf("%d", &idProduto) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer
            printf("Entrada invalida. Digite um ID numerico (ou 0): ");
        }

        if (idProduto == 0) {
            break; 
        }

        printf("Digite a quantidade: ");
        // Le a entrada do usuario, garantindo que seja um inteiro
        while (scanf("%d", &quantidade) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer
            printf("Entrada invalida. Digite uma quantidade numerica: ");
        }

        if (quantidade > 0) {
            adicionarAoCarrinho(idProduto, quantidade);
        } else {
            printf("!! Quantidade invalida. !!\n");
        }
        
        printf("\nPressione Enter para continuar...");
        getchar(); 
        getchar(); 
    }

    limparTela();
    
    if (totalItensNoCarrinho > 0) {
        exibirRecibo();
        float totalAPagar = calcularTotalCarrinho();
        processarPagamento(totalAPagar);
    } else {
        printf("Carrinho vazio. Nenhuma compra realizada.\n");
    }

    printf("\nObrigado por comprar conosco. Volte sempre!\n");

    return 0;
}