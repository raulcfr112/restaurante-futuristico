#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <sstream>
#include "restaurante.h"
#include "chef.h"

using namespace std;

/**
 * Função para testar a execução dos Chefs.
 */
void testarChefs() {
    Chef c1, c2;

    sleep(2);
    c1.iniciarAtendimento(4);
    c1.preparar("bife com batatas fritas");
    sleep(4);
    c1.preparar("bolo de chocolate");
    c1.finalizarAtendimento();
    sleep(1);
}

bool encerrar(std::string &comando) {
    std::transform(comando.begin(), comando.end(), comando.begin(), ::toupper);
    return (comando == "FIM");
}

/**
 * Função que processa a entrada da aplicação
 *
 * @param entrada um stream de entrada, seja o terminal ou um arquivo de texto
 */
int processarEntrada(std::istream &entrada) {
    unsigned int qtdChefs, qtdMesas;
    entrada >> qtdChefs >> qtdMesas;
    std::cin.ignore();

    try {
        Restaurante restaurante(qtdChefs, qtdMesas);

        while (true) {
            std::string linha;
            std::getline(entrada, linha);
            if (encerrar(linha)) break;

            int mesa;
            std::string pedido;
            std::istringstream stream(linha);

            stream >> mesa;
            stream.ignore();
            std::getline(stream, pedido);

            if (encerrar(pedido)) {
                std::cout << "[LOG][processarEntrada] Finalizando Mesa " << mesa << std::endl;
                restaurante.finalizarMesa(mesa);
            } else {
                std::cout << "[LOG][processarEntrada] Mesa " << mesa << " Pedido: " << pedido << std::endl;
                restaurante.fazerPedido(mesa, pedido);
            }
        }

    } catch (exception &ex) {
        std::cerr << ex.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/**
 * Função principal chamada para inicializar a aplicação.
 *
 * @param argc - tamanho do vetor com os parâmetros de inicialização
 * @param argv - vetor com os parâmetros de inicialização
 *
 * @return  0 (EXIT_SUCCESS) quando a aplicação finaliza com sucesso;
 *          1 (EXIT_FAILURE) quando a aplicação é encerrada devido a uma falha.
 */
int main() {

    return processarEntrada(std::cin);
}
