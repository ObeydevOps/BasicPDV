BasicPDV
Este projeto implementa um Sistema de Ponto de Venda (PDV) em console, desenvolvido na linguagem C.  O programa simula o processo de compra de um caixa, desde o carregamento do estoque até o fechamento da venda. É uma excelente demonstração do uso de estruturas (struct), manipulação de arquivos (FILE*) para carregar dados (CSV), e funções.

Instruções

Sistema de Ponto de Venda (PDV) Básico
Um sistema de ponto de venda (PDV) em console escrito em C. O programa carrega um catálogo de produtos a partir de um arquivo CSV, permite que o usuário adicione itens ao carrinho por ID e quantidade, exibe o recibo e simula o processamento do pagamento e cálculo do troco.

Pré-requisitos
Para compilar e rodar este código, você precisa ter um compilador C instalado no seu sistema.

GCC (GNU Compiler Collection) é o compilador mais comum em sistemas Linux/macOS e é amplamente utilizado no Windows (via MinGW, Cygwin ou WSL).

Estrutura do Projeto
É crucial que você crie um arquivo chamado produtos.csv na mesma pasta do seu código-fonte (.c) para que o programa funcione.

Compilação 
Abra seu terminal ou prompt de comando, navegue até a pasta onde você salvou o arquivo e execute o comando de compilação.

Fluxo de Teste
O programa começará carregando os dados .

Ele exibirá o catálogo de produtos e pedirá o ID do produto.

Digite um ID (ex: 101) e pressione Enter.

Digite a quantidade (ex: 2) e pressione Enter. O item será adicionado ao carrinho.

Pressione Enter para limpar a tela e ver o catálogo novamente com o total parcial.

Para finalizar a compra, digite 0 no prompt do ID do produto.

O programa exibirá o cupom fiscal e solicitará o valor pago para calcular o troco.
