// naLata.cpp :TAREFA DE AVALIAÇÃO PARTE I
// UFCD 5092 
// Este programa é um sistema de gestão de vendas de bebidas energéticas.
// Daniel Silva Pinheiro
// Gicélia Queiroz Mendes
/*
 * __   __                  _  _            _             _            _
 * \ \ / /  ___   _ __     | \| |  __ _    | |     __ _  | |_   __ _  | |
 *  \ V /  / -_) | '  \    | .` | / _` |   | |__  / _` | |  _| / _` | |_|
 *   \_/   \___| |_|_|_|   |_|\_| \__,_|   |____| \__,_|  \__| \__,_| (_)
 *
 */

 //Bibliotecas utilizadas nesse programa
#include <iostream> // cout
#include <iomanip> // setprecision
#include <string> // string
#include <chrono> // chrono
#include <Windows.h> // SetConsoleOutputCP
#include <cstdlib> // srand(números randômicos)
#include <cmath> // round
#include <algorithm> // replace(substitui caracteres)
#include <sstream> // stringstream(apresenta o valor em string como o cout)


// Definições de namespace
using namespace std;
using namespace std::chrono;

// Assinaturas das funções
void produtoEstoque();
void menuPrincipal();
string solicitarEntradaNumerica(const string& mensagem);
void limparTela();
void exibirProdutos();
int buscarProduto(string id);
bool validarNumeros(const string& str);
string fValorMonetario(double valor);
void adicionarProduto();
void eliminarProduto();
void venderProdutos();
void adicionarAoCarrinho(string id, int quantidade);
bool verificarEstoque(string id, int quantidade);
void mostrarCarrinho();
void processarPagamento();
void atualizarEstoque(string id, int quantidade);
void mostrarDataAtualModerno();
void talao();
void detalhesDaVenda();
double stringParaDouble(const std::string& valorStr);
double calcularValorVenda(double precoProduto);
int codigoCliente();
int codigoFatura();

// Variáveis que possuem tamanho constante dentro programa
const int qtdProdutos = 100;
const int atributoProdutos = 5;
const int qtdVendas = 1000;
const int atributoTalao = 10;

//Matrizes
string estoque[qtdProdutos][atributoProdutos];
string vendas[qtdVendas][atributoTalao];

//Variáveis Globais 
int totalProdutos = 0;
double pLiquido, pagamento, troco;
int quantidade;
int itensCarrinho = 0;
double totalCarrinho = 0.0;
double margemPercentual = 30;

int main()
{
    setlocale(LC_ALL, "portuguese");
    setlocale(LC_NUMERIC, "C");

#ifdef _WIN32 // Código para a configuração de acentção seja acessível em Windows
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    srand(time(NULL));

    
    produtoEstoque(); // Inicializa chamada da função para ser utilizada dentro de outras funções no programa

    while (true) // Menu Principal será apresentado após cada interação 
    {
        // Menu boas vindas
        cout << string(40, '*') << endl;
        cout << "*" << string(14, ' ') << "Bem - vindo" << string(13, ' ') << "*" << endl;
        cout << "*" << string(18, ' ') << "ao" << string(18, ' ') << "*" << endl;
        cout << "*" << string(15, ' ') << "Na Lata" << string(16, ' ') << "*" << endl;
        cout << string(40, '*') << endl << endl;

        menuPrincipal();

        
        string opcaoMenu = solicitarEntradaNumerica("Digite a opção desejada: ");
        bool entradaValida = true;
        for (char c : opcaoMenu) 
        {
            if (!isdigit(c))
            {
                entradaValida = false;
                break;
            }
        }

        int menuP = -1; // Valor padrão inválido
        if (entradaValida && !opcaoMenu.empty())
        {
            menuP = stoi(opcaoMenu);
        }

		limparTela();

        switch (menuP) // Switch para o menu principal
        {
        case 1:// Opção de venda
            
            venderProdutos();
            limparTela();
            break;
        case 2:// Opção exibir estoque
            
            exibirProdutos();
            limparTela();
            break;
        case 3:// Opção adicionar produto
            
            adicionarProduto();
            limparTela();
            break;
        case 4://Opção eliminar produto
            
            eliminarProduto();
            limparTela();
            break;
        case 0:
            cout << "Obrigado e até a próxima!" << endl;
            return 0;
        default:
            cout << "Opção inválida! Digite um número entre 0 e 4." << endl;
            limparTela();
            break;
        }
    }
}

// A partir daqui estão as declarações das funções utilizadas

// Função que apresenta o menu 
void menuPrincipal()
{
    cout << string(40, '-') << endl;
    cout << "Selecione a tarefa desejada abaixo: " << endl << endl;
    cout << "[1] - Comprar Bebida" << endl;
    cout << "[2] - Ver Estoque" << endl;
    cout << "[3] - Adicionar Produto" << endl;
    cout << "[4] - Eliminar Produto" << endl;
    cout << "[0] - Sair" << endl;
    cout << string(40, '-') << endl;
}

// Função para apresentar o estoque inicial como solicitado no item 1-c-ii da Tarefa de Avaliação n.º 01
void produtoEstoque()
{
    cout << fixed << setprecision(2);

    //Matriz temporária de inicialização do estoque com as informações solicitadas no item 1-b-i da Tarefa de Avaliação n.º 01
    const string produtos[10][4] =
    {
    {"1", "Monsters Punch", "10", "1.99"},
    {"2", "Monsters Ultra", "10", "2.50"},
    {"3", "Monsters Mango", "10", "1.75"},
    {"4", "Monsters Rehab", "10", "1.80"},
    {"5", "Monsters Rosa", "10", "2.50"},
    {"6", "Monsters Blue", "10", "1.80"},
    {"7", "Monsters Red", "10", "1.99"},
    {"8", "Monsters Gold", "10", "1.75"},
    {"9", "Monsters Black", "10", "1.80"},
    {"10", "Monsters White", "10", "1.99"}
    };

    // Copia para a matriz estoque os dados inseridos
    for (int i = 0; i < 10; i++)
    {
        estoque[i][0] = produtos[i][0]; // ID
        estoque[i][1] = produtos[i][1]; // Nome
        estoque[i][2] = produtos[i][2]; // Quantidade
        estoque[i][3] = produtos[i][3]; // Preço Custo

        // Calcula e armazena o preço de venda
        double precoCusto = stringParaDouble(produtos[i][3]);
        double precoVenda = calcularValorVenda(precoCusto);
        estoque[i][4] = to_string(precoVenda); // Preço Venda

        totalProdutos++;
    }
}

//Limpa a tela depois do Enter, assim que terminar uma ação
void limparTela()
{
    cout << "\nPressione Enter para continuar...";
    cin.ignore();
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

//Exibe todos os produtos cadastrados no estoque
void exibirProdutos()
{
    cout << fixed << setprecision(2);
    cout << "Produtos em Estoque:" << endl << endl;
    for (int i = 0; i < totalProdutos; i++)
    {
        double precoVenda = stringParaDouble(estoque[i][4]);
        cout << "ID: " << estoque[i][0] << "  | Nome: " << estoque[i][1] << " | Quantidade: " << estoque[i][2] << " | Preço: € " << estoque[i][3]
            << " | Preço Venda: € " << precoVenda << endl;

        cout << string(90, '-') << endl << endl;
    }
}

// Valida se o campo numérico recebe apenas números e não aceita números negativos
bool validarNumeros(const string& str)
{
    if (str.empty() || str[0] == '-') 
    {
        return false; // Rejeita vazios e negativos
    }

    int pontos = 0; // Contador de pontos decimais

    for (char c : str) 
    {
        if (c == '.') 
        {
            pontos++;
            if (pontos > 1) return false; // Mais de um ponto é inválido
        }
        else if (!isdigit(c)) 
        {
            return false; // Rejeita caracteres não numéricos
        }
    }
    return true;
   
}

// Somente irá aceitar números positivos para isso recebe a função validarNumeros
string solicitarEntradaNumerica(const string& mensagem)
{
    string entrada;
    while (true)
    {
        cout << mensagem;
        getline(cin, entrada);

        if (validarNumeros(entrada)) 
        {
            return entrada;
        }
        cout << "Entrada inválida! Por favor, use apenas números.\n";
    }
}

// Adiciona o produto ao estoque, verificando se já existe ou não, conforme solicitado no item 1-a-ii-1 da Tarefa de Avaliação n.º 01
void adicionarProduto()
{
    cout << "Adicionar um produto:"<<endl;
    string id = solicitarEntradaNumerica("Digite o ID do produto: ");
    int indice = buscarProduto(id);

    if (indice != -1)
    {
        cout << "\nProduto já cadastrado: " << estoque[indice][1] << endl;
        cout << "Quantidade atual: " << estoque[indice][2] << endl;

        string qtdAtualizar = solicitarEntradaNumerica("Digite a quantidade a adicionar: ");

        int qtdAdicional = stoi(qtdAtualizar);
        int qtdAtual = stoi(estoque[indice][2]);
        estoque[indice][2] = to_string(qtdAtual + qtdAdicional);
        cout << "Quantidade atualizada com sucesso! Total: " << estoque[indice][2] << endl;
    }
    else
    {
        estoque[totalProdutos][0] = id;
        cout << "Digite o nome do produto: ";
        getline(cin, estoque[totalProdutos][1]);

        estoque[totalProdutos][2] = solicitarEntradaNumerica("Digite a quantidade do produto: ");

        string precoCustoStr;

        while (true)
        {
            precoCustoStr = solicitarEntradaNumerica("Digite o preço de custo: € ");
           
            if (validarNumeros(precoCustoStr))
            {
                double precoCusto = stringParaDouble(precoCustoStr);
                if (precoCusto > 0)
                {
                    estoque[totalProdutos][3] = precoCustoStr;
                    break;
                }
            }
            cout << "Erro: Digite um valor monetário válido!\n";
        }

        // Calcula e armazena o preço de venda
        double precoVenda = calcularValorVenda(stringParaDouble(precoCustoStr));
        estoque[totalProdutos][4] = to_string(precoVenda);

        cout << "Preço de venda calculado: € " << fixed << setprecision(2) << precoVenda << endl;
        cout << "Produto adicionado com sucesso!" << endl;

        totalProdutos++;
    }
}

// Elimina um produto do estoque, verificando se existe ou não, conforme solicitado no item 1-a-ii-2 da Tarefa de Avaliação n.º 01
void eliminarProduto()
{
    cout << "Eliminar o Produto Desejado:" << endl;
    string idProduto = solicitarEntradaNumerica("Digite o ID do produto a ser eliminado: ");

    for (int i = 0; i < totalProdutos; i++)
    {
        if (estoque[i][0] == idProduto)
        {
            for (int j = i; j < totalProdutos - 1; j++)
            {
                estoque[j][0] = estoque[j + 1][0];
                estoque[j][1] = estoque[j + 1][1];
                estoque[j][2] = estoque[j + 1][2];
                estoque[j][3] = estoque[j + 1][3];
            }
            totalProdutos--;
            cout << "Produto eliminado com sucesso!" << endl << endl;
            cout << string(40, '-') << endl;
            return;
        }
    }
    cout << "Produto não encontrado!" << endl << endl;
}

// Efetua a venda do produto conforme solicitado no item 1-a-i-1/2/3/4 da Tarefa de Avaliação n.º 01
void venderProdutos()
{
    string idProduto;
    string strQuantidade;
    char continuar = 's';// Variável para controlar se o usuário deseja continuar comprando

    // Reinicializa o carrinho
    itensCarrinho = 0;
    totalCarrinho = 0.0;

    while (continuar == 's' || continuar == 'S')// Estrutura de repetição para verificar se o usuário deseja continuar comprando
    {
        cout << string(35, '=') << " VENDA DE PRODUTOS " << string(35, '=') << endl;
        exibirProdutos();

        idProduto = solicitarEntradaNumerica("Digite o ID do produto: ");
        int indice = buscarProduto(idProduto);

        if (indice == -1)
        {
            cout << "Produto não encontrado!" << endl;
        }
        else
        {
            int quantidadeDisponivel = stoi(estoque[indice][2]);
            if (quantidadeDisponivel == 0) 
            {
                cout << "Produto esgotado!" << endl;
                cout << "Deseja escolher outro ? (s / n) : ";
                //char opcao;
                cin >> continuar;
                cin.ignore();

                if (continuar == 's' || continuar == 'S') 
                {
                    continuar = 's';
                    continue;
                }
                else 
                {
                    continuar = 'n';
                    break;
                }
            }
            int quantidadeDesejada;
            bool quantidadeValida = false;

            do 
            {
                strQuantidade = solicitarEntradaNumerica("Quantidade (disponível: " + to_string(quantidadeDisponivel) + "): ");
                quantidadeDesejada = stoi(strQuantidade);

                if (quantidadeDesejada <= 0) 
                {
                    cout << "Erro: A quantidade deve ser maior que zero!" << endl;
                }
                else if (quantidadeDesejada > quantidadeDisponivel) 
                {
                    cout << "Quantidade indisponível! Máximo disponível: " << quantidadeDisponivel << endl;
                }
                else 
                {
                    quantidadeValida = true;
                }
            } while (!quantidadeValida);

            if (verificarEstoque(idProduto, quantidadeDesejada))
            {
                adicionarAoCarrinho(idProduto, quantidadeDesejada);
                atualizarEstoque(idProduto, quantidadeDesejada);
                cout << "Produto adicionado ao carrinho!" << endl;
            }
        }

        cout << string(60, '-') << endl;

        do
        {
            cout << "Deseja adicionar outro produto? (s/n): ";
            cin >> continuar;
            cin.ignore();
        } while (continuar != 'n' && continuar != 'N' && continuar != 's' && continuar != 'S');
    }

    if (itensCarrinho > 0)
    {
        limparTela();
        mostrarCarrinho();
    }

}

// Registra os dados da venda no carrinho
void adicionarAoCarrinho(string id, int quantidade)
{
    for (int i = 0; i < itensCarrinho; i++) 
    {
        if (vendas[i][0] == id) 
        {  // Compara o ID do produto
            // Produto encontrado no carrinho - atualiza a quantidade
            int qtdExistente = stoi(vendas[i][2]);
            vendas[i][2] = to_string(qtdExistente + quantidade);

            // Atualiza os valores monetários
            double precoVenda = stringParaDouble(vendas[i][3]);
            double novoSubtotal = (qtdExistente + quantidade) * precoVenda;
            double novoImposto = novoSubtotal * 0.23;
            double novoTotal = novoSubtotal + novoImposto;

            vendas[i][4] = fValorMonetario(novoTotal);
            vendas[i][5] = fValorMonetario(novoImposto);

            // Atualiza o total do carrinho
            totalCarrinho += (quantidade * precoVenda) * 1.23;

            cout << "Quantidade atualizada no carrinho!" << endl;
            return;
        }
    }

    int indice = buscarProduto(id);
    if (indice != -1)
    {
        double precoCusto = stringParaDouble(estoque[indice][3]);
        double precoVenda = calcularValorVenda(precoCusto);
        double subtotal = quantidade * precoVenda; // Preço * quantidade
        double imposto = subtotal * 0.23; // Calcula o imposto (IVA)
        double pTotal = subtotal + imposto; // Adiciona % de IVA

        // Registrar no carrinho 
        vendas[itensCarrinho][0] = id;
        vendas[itensCarrinho][1] = estoque[indice][1];
        vendas[itensCarrinho][2] = to_string(quantidade);
        vendas[itensCarrinho][3] = fValorMonetario(precoVenda);
        vendas[itensCarrinho][4] = fValorMonetario(pTotal);
        vendas[itensCarrinho][5] = fValorMonetario(imposto);

        itensCarrinho++;
        totalCarrinho += pTotal;
    }
}

// Apresenta os itens do carrinho de compras conforme solicitado no item 1-a-i-3 da Tarefa de Avaliação n.º 01
void mostrarCarrinho()
{
    cout << string(19, '=') << " CARRINHO DE COMPRAS " << string(19, '=') << endl;
    cout << string(60, '-') << endl;

    for (int i = 0; i < itensCarrinho; i++)
    {
        double pVenda = stringParaDouble(vendas[i][3]);
        double vTotal = stringParaDouble(vendas[i][4]);

        cout << vendas[i][1] << " | Qtd: " << vendas[i][2]
            << " | Preço: € " << fValorMonetario(pVenda)
            << " | Total: € " << fValorMonetario(vTotal) << endl;
    }

    cout << string(60, '-') << endl;
    double subtotal = totalCarrinho / 1.23;
    double iva = totalCarrinho - subtotal;
    cout << "SUBTOTAL: € " << fValorMonetario(subtotal) << endl;
    cout << "IVA (23%): € " << fValorMonetario(iva) << endl;
    cout << "TOTAL: € " << fValorMonetario(totalCarrinho) << endl;

    // Opção para cancelar ou prosseguir compra
    char opcao;
    bool entradaValida = false;

    do 
    {
        cout << "\n[1] Finalizar compra\n[2] Cancelar e voltar ao menu\nEscolha: ";
        string input;
        getline(cin, input);

        if (input.empty()) 
        {
            cout << "Erro: Você deve digitar 1 ou 2!" << endl;
			continue;
        }

        // Pega apenas o primeiro caractere digitado
        opcao = input[0];

        if (opcao == '1') 
        {
            int sorteio = rand() % 2;
            bool compraGratis = (sorteio == 0);

            if (compraGratis) 
            {
                cout << "# Parabéns! A sua compra é totalmente GRÁTIS!# " << endl;
                totalCarrinho = 0.0;
                pagamento = 0.0;
                troco = 0.0;
                processarPagamento();
            }
            else 
            {
                cout << "\nTotal a pagar (com IVA): € " << fValorMonetario(totalCarrinho) << endl;

                bool valorValido = false;
                string input;

                while (!valorValido)
                {
                    cout << "Valor entregue (ou 0 para cancelar): € ";
                    getline(cin, input);

                    if (input == "0") 
                    {
                        cout << "Compra cancelada!" << endl;
                        limparTela();
                        return;  // Volta ao menu principal
                    }

                    pagamento = stringParaDouble(input);

                    if (pagamento == 0.0 && input != "0" && input != "0,00" && input != "0.00") 
                    {
                        cout << "Valor inválido! Use números com até 2 casas decimais." << endl;
                    }
                    else if (pagamento < totalCarrinho) 
                    {
                        cout << endl << "Valor insuficiente! Digite um valor igual ou maior que € " << fValorMonetario(totalCarrinho) << endl;
                    }
                    else 
                    {
                        valorValido = true;
                    }
                }
                processarPagamento();
            }
            entradaValida = true;
        }
        else if (opcao == '2') 
        {
            cout << "Compra cancelada! Retornando ao menu principal..." << endl;
            // Reseta o carrinho
            itensCarrinho = 0;
            totalCarrinho = 0.0;
            limparTela();
            return;  // Volta ao menu principal
        }
        else 
        {
            cout << "Opção inválida! Digite 1 ou 2." << endl;
        }
    } while (!entradaValida );
}

// Fará o processamento do pagamento conforme solicitado no item 1-a-i-4 da Tarefa de Avaliação n.º 01
void processarPagamento()
{
    if (totalCarrinho > 0) 
    {
        troco = pagamento - totalCarrinho;

        if (itensCarrinho < qtdVendas) 
        {
            vendas[itensCarrinho][5] = fValorMonetario(totalCarrinho);
            vendas[itensCarrinho][6] = fValorMonetario(pagamento);
            vendas[itensCarrinho][7] = fValorMonetario(troco);
        }
    }

    cout << "\nProcessando pagamento..." << endl;
    cout << "Pagamento realizado com sucesso!" << endl;

    if (troco > 0) 
    {
        cout << "Troco: € " << fValorMonetario(troco) << endl;
    }

    cout << string(40, '-') << endl;
    limparTela();
    talao();
}

// Função para converter string com vírgula/ponto para double
double stringParaDouble(const string& valorStr)
{
    string copia = valorStr;

    // Substitui vírgula por ponto
    replace(copia.begin(), copia.end(), ',', '.');

    // Verifica se é um número válido
    bool pontoDecimalEncontrado = false;
    bool caracterValido = true;

    for (size_t i = 0; i < copia.size() && caracterValido; ++i)
    {
        char c = copia[i];

        // Permite sinal negativo apenas no início
        if (i == 0 && c == '-') 
        {
            continue;
        }

        // Verifica caracteres válidos
        if (!isdigit(c))  
        {
            if (c == '.' && !pontoDecimalEncontrado) 
            {
                pontoDecimalEncontrado = true;
            }
            else 
            {
                caracterValido = false;
                break;
            }
        }
    }
    if (!caracterValido || copia.empty() || copia == "." || copia == "-") 
    {
        return 0.0;
    }

    // Converte para double usando strtod
    char* endptr;
    double valor = strtod(copia.c_str(), &endptr);

    // Verifica se a conversão foi completa
    if (*endptr != '\0') 
    {
        return 0.0;
    }

    return valor; 
}

// Função para formatar valores monetários
string fValorMonetario(double valor)
{
    valor = round(valor * 100) / 100;

    // Converte para string com 2 casas decimais
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%.2f", valor);

    string valorStr(buffer);
    replace(valorStr.begin(), valorStr.end(), '.', ',');

    return valorStr;
}

// Verifica quantidade do produto no estoque pelo id
bool verificarEstoque(string id, int quantidade)
{
    int indice = buscarProduto(id);
    if (indice != -1)
    {
        return stoi(estoque[indice][2]) >= quantidade;
    }
    return false;
}
// Atualiza quantidade no estoque
void atualizarEstoque(string id, int quantidade)
{
    int indice = buscarProduto(id);
    if (indice != -1)
    {
        int novoEstoque = stoi(estoque[indice][2]) - quantidade;
        estoque[indice][2] = to_string(novoEstoque);
    }
}

//Verifica se o produto esxiste pelo id
int buscarProduto(string id)
{
    for (int i = 0; i < totalProdutos; i++)
    {
        if (estoque[i][0] == id)
        {
            return i;
        }
    }
    return -1;
}

// Mostra a data do dia da compra conforme solicitado no item 1-c-i da Tarefa de Avaliação n.º 01
void mostrarDataAtualModerno()
{
    // Obter a data atual  
    auto agora = system_clock::now();
    time_t tempo = system_clock::to_time_t(agora);

    // Converter para formato local  
    tm dataLocal;
    localtime_s(&dataLocal, &tempo);

    // Exibir formatado  
    cout << "Data atual: " << put_time(&dataLocal, "%d/%m/%Y");
}

// Gera de modo randômico do cliente
int codigoCliente()
{
    unsigned int seed = time(0);

    srand(seed);
    cout << 1 + rand() % 1000; // Gera um número aleatório entre 1 - 1000

    return 0;
}

// Gera de modo randômico da fatura
int codigoFatura()
{
    unsigned int seed = time(0);

    srand(seed);
    cout << rand(); // Gera um número aleatório entre 0 - 32767

    return 0;
}

// Resumo da venda apresentado no talão 
void detalhesDaVenda()
{
    for (int i = 0; i < itensCarrinho; i++)
    {
        cout << "   ID do produto: " << vendas[i][0] << endl;
        cout << "   Produto: " << vendas[i][1] << endl;
        cout << "   Quantidade: " << vendas[i][2] << endl;

        // Formatando valores monetários
        string pLucro = vendas[i][3];
        double pVenda = stringParaDouble(pLucro); // Preço de venda, calculado na função vVenda
        fValorMonetario(pVenda);
        cout << "   Preço de Venda: € " << fixed << setprecision(2) << pVenda << endl;

        string IVA = vendas[i][5];
        double pIVA = stringParaDouble(IVA); // Preço de venda, calculado na função vVenda
        fValorMonetario(pIVA);
        cout << "   IVA: € " << fixed << setprecision(2) << pIVA << endl;

        string pTotal = vendas[i][4];
        double vTotal = stringParaDouble(pTotal); // Valor total da compra
        fValorMonetario(vTotal);
        cout << "   Total: € " << fixed << setprecision(2) << vTotal << endl;

        cout << string(40, '-') << endl;
    }
}

// Calcula o preço de venda com base no preço de custo e na margem percentual
double calcularValorVenda(double precoProduto)
{
    double valorVenda = precoProduto * (1 + margemPercentual / 100);

    stringstream sDecimal;
    sDecimal << fixed << setprecision(2) << valorVenda;
    string valorFormatado = sDecimal.str();

    return stod(valorFormatado);
}

// Função para gerar o talão de compra conforme solicitado no item 1-b-ii da Tarefa de Avaliação n.º 01
void talao()
{
    cin.ignore();
    cout << string(40, '*') << endl;
    cout << "*" << string(17, ' ') << "Talão" << string(16, ' ') << "*" << endl;
    cout << string(40, '*') << endl;
    cout << "*" << string(15, ' ') << " Na Lata" << string(15, ' ') << "*" << endl;
    cout << string(40, '*') << endl;
    cout << "*" << string(8, ' ');
    mostrarDataAtualModerno();
    cout << string(8, ' ') << "*" << endl;
    cout << string(40, '*') << endl;
    cout << "   Número da fatura: ";
    codigoFatura();
    cout << endl;
    cout << "   Número do cliente: ";
    codigoCliente();
    cout << endl;
    cout << string(40, '-') << endl;
    detalhesDaVenda();
    cout << string(40, '-') << endl;
    cout << "   Total: €" << fixed << setprecision(2) << totalCarrinho << endl;
    cout << "   Pagamento: €" << fixed << setprecision(2) << pagamento << endl;
    cout << "   Troco: €" << fixed << setprecision(2) << troco << endl;
    cout << string(40, '-') << endl;
    cout << "|" << string(5, ' ') << "Só Na Lata mata sua sede : )" << string(5, ' ') << "|" << endl;
    cout << "|" << string(6, ' ') << "Obrigado pela sua compra!" << string(7, ' ') << "|" << endl;
    cout << string(40, '-') << endl;	
}

