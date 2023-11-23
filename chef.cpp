#include "chef.h"
#include <iostream>
#include <sstream>
#include <zconf.h>

unsigned int Chef::contador = 0;

Chef::Chef() : id(++contador), nome("") {
    ostringstream onome;
    onome << "ChefeCozinha_" << id;

    nome = onome.str();
    
    ofstream log;
    log.open(nome + ".txt");
    log << nome << endl;
    log.close();

    std::cout << "[LOG][Chef] iniciando log chef " << nome << std::endl;
}

Chef::~Chef() = default;

void Chef::iniciarAtendimento(const unsigned int mesa) {

    std::cout << "[LOG][iniciarAtendimento] chef iniciando atendimento da mesa " << std::endl;

    ofstream log;
    log.open(nome + ".txt", std::ios_base::app);
    log << "" << endl;
    log << "Mesa " << mesa << ":" << endl; 
    log.close();
}

void Chef::preparar(const string &pedido) {
    ofstream log;
    log.open(nome + ".txt", std::ios_base::app);
    log << "    - " << pedido << endl;
    log.close();

    std::cout << "[LOG][preparar] chef " << this->nome << " preparando pedido " << pedido << std::endl;
}

void Chef::finalizarAtendimento() {
    // Implemente seu código aqui...
}

Chef::Atendimento::Atendimento(const unsigned int mesa) {
    // Implemente seu código aqui...
}

Chef::Atendimento::~Atendimento() {
    // Implemente seu código aqui...
}

void Chef::Atendimento::preparar(const string &pedido) {
    // Implemente seu código aqui...
}
