#include "restaurante.h"


Restaurante::Restaurante(unsigned int qtdChefs, unsigned int qtdMesas) : chefs() {
    if (qtdChefs > MAX_CHEFS) {
        throw std::invalid_argument("Quantidade inválida de chefs: " + std::to_string(qtdChefs));
    } else if (qtdMesas < qtdChefs || qtdMesas > qtdChefs * 4) {
        throw std::invalid_argument("Quantidade inválida de mesas: " + std::to_string(qtdMesas));
    }

    // Instancia <qtdChefs> objetos Chef
    for (int i = 0; i < qtdChefs; i++) {
        chefs.emplace_back();
    }  

    for(int i = 0 ; i < qtdChefs; i++) {
        chefsDisponiveis.insert(&(chefs.at(i)));
    }

    for(auto ci = chefsDisponiveis.begin(); ci != chefsDisponiveis.end(); ci++) {
        std::cout << "[LOG][Restaurante] chef disponivel " << (*ci)->getID() << std::endl;
    }
}

Chef *Restaurante::getChef(unsigned int mesa) {
    // Implemente seu código aqui...
    auto iter = mesas.find(mesa);

    if(iter != mesas.end()) {
        return iter->second;
    }

    return nullptr;
}

Chef *Restaurante::getChefDisponivel() {

    if(chefsDisponiveis.size() > 0) {
        auto iter = chefsDisponiveis.begin();

        std::cout << "[LOG][getChefDisponivel] chef_id " << (*iter) << std::endl;

        return *iter;
    }

    return nullptr;
}

void Restaurante::fazerPedido(unsigned int mesa, const std::string &item) {

    auto chef = getChef(mesa);

    if(chef == nullptr) {

        chef = getChefDisponivel();

        if(chef == nullptr) {
            fazerPedidoFila(mesa, item);

            std::cout << "[LOG][fazerPedido] mesa " << mesa << " com pedido " << item << " aguardanndo chef " << std::endl;
            return;
        } else {
            
            std::cout << "[LOG][fazerPedido] chef_id " << chef->getID() << " nome " << chef->getNome() << std::endl;

            chef->iniciarAtendimento(mesa);
            chefsDisponiveis.erase(chef);
            mesas[mesa] = chef;
        }
    }

    std::cout << "[LOG][fazerPedido] chef id " << chef->getID() << " preparando pedido " << item << " para mesa " << mesa << std::endl;

    chef->preparar(item);
}

void Restaurante::finalizarMesa(unsigned int mesa) {

    auto chef = this->getChef(mesa);

    if (chef == nullptr) {
        fazerPedidoFila(mesa, "FIM");
        return;
    }
    
    chef->finalizarAtendimento();

    // torna o chef disponivel
    chefsDisponiveis.insert(chef);

    // verifica se tem mesa aguardando chef
    if(!mesaFila.empty()) {

        // torna o chef insdiponivel novamente
        chefsDisponiveis.erase(chef);

        // recupera a mesa da fila
        unsigned int proxima_mesa = mesaFila.front();

        // remove mesa da fila
        mesaFila.pop();

        // iniciar atendimento da proxima mesa
        mesas[proxima_mesa] = chef;
        chef->iniciarAtendimento(proxima_mesa);

        // processa todos os pedidos que a mesa estava aguardando
        auto iter = pedidosFila.find(proxima_mesa);

        for(int i = 0; i < iter->second.size(); i++) {

            std::cout << "[LOG][finalizarMesa] item " << iter->second.at(i) << std::endl;

            if(iter->second.at(i) == "FIM"){
                finalizarMesa(proxima_mesa);
            } else {
                chef->preparar(iter->second.at(i));
            }
        }

    }

    mesas[mesa] = nullptr;
    // limpa os pedidos da mesa
    auto it = pedidosFila.find(mesa);
    
    if(it != pedidosFila.end()){
        pedidosFila.erase(mesa);
    }
}

void Restaurante::fazerPedidoFila(unsigned int mesa, const std::string &item){ 

    auto iter = pedidosFila.find(mesa);

    if(iter != pedidosFila.end()) {
        // inserindo mais pedidos na mesa
        iter->second.push_back(item);
    } else {

        // inserindo a mesa na fila para processamento apos chefe ficar disponivel
        mesaFila.push(mesa);

        // inserindo o primeiro pedido na mesa
        std::vector<std::string> pedidos;
        pedidos.push_back(item);
        pedidosFila[mesa] = pedidos;
    }
}