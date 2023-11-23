#ifndef RESTAURANTE_APP_RESTAURANTE_H
#define RESTAURANTE_APP_RESTAURANTE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include "chef.h"

// Caso queira usar uma estrutura para armazenar as informações de um pedido...
struct Pedido {
    unsigned int mesa;
    std::string pedido;
};

class Restaurante {
public:

    /**
     * Cria um objeto Restaurante contendo uma quantidade definida de chefs e de mesas.
     *
     * @param qtdChefs número de chefs
     * @param qtdMesas número de mesas
     */
    Restaurante(unsigned int qtdChefs, unsigned int qtdMesas);

    /**
     * Informa um pedido ao restaurante.
     *
     * @param mesa
     * @param item
     */
    void fazerPedido(unsigned int mesa, const std::string &item);
    void finalizarMesa(unsigned int mesa);
    

private:
    static const unsigned int MAX_CHEFS = 100;

    // ArrayList<Chef> chefs;
    std::vector<Chef> chefs;
    // key (mesa) value (pos chef)
    std::map<unsigned int, Chef*> mesas;

    std::set<Chef*> chefsDisponiveis;

    // Fila das mesas que entraram sem existir chef disponivel
    std::queue<unsigned int> mesaFila;

    // armazeno todos os pedidos da mesa sem atendimento
    std::map<unsigned int, std::vector<std::string>> pedidosFila;

    // Como armazenar as informações das mesas?
    // Como armazenar os pedidos em espera?

    /**
     * Retorna um ponteiro para o Chef que está atendendo a mesa.
     *
     * @param mesa número da mesa
     * @return um ponteiro para o Chef
     */
    Chef *getChef(unsigned int mesa);

    Chef* getChefDisponivel();

    void fazerPedidoFila(unsigned int mesa, const std::string &item);
};

#endif //RESTAURANTE_APP_RESTAURANTE_H
