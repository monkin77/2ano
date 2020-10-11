#include "parque.h"
#include <vector>
#include <algorithm>

using namespace std;

//constructor
ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):lotacao(lot), numMaximoClientes(nMaxCli) {
    vagas = lotacao;
}

unsigned ParqueEstacionamento::getNumLugares() const {
    return this->lotacao;
}

unsigned ParqueEstacionamento::getNumMaximoClientes() const {
    return this->numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string &nome) const {
    for(int idx = 0; idx < clientes.size(); idx++){
        if( clientes[idx].nome == nome ){
            return idx;
        }
    }
    return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string &nome) {
    if(numMaximoClientes == clientes.size()){
        return false;
    }
    InfoCartao newPerson;
    newPerson.nome = nome, newPerson.presente = false;
    clientes.push_back(newPerson);
    return true;
}

bool ParqueEstacionamento::entrar(const string &nome) {
    if(vagas <= 0){
        return false;
    }
    else{
        for(int i = 0; i < clientes.size(); i++){
            if(clientes[i].nome == nome){
                if(clientes[i].presente == false){
                    clientes[i].presente = true;
                    vagas--;
                    return true;
                }
            }
        }
    }
    return false;
}

bool ParqueEstacionamento::retiraCliente(const string &nome) {
    for(int i = 0; i < clientes.size(); i++){
        if(clientes[i].nome == nome){
            if(clientes[i].presente == true){
                return false;
            }
            else {
                clientes.erase(clientes.begin() + i);
                return true;
            }
        }
    }
    return false;
}

bool ParqueEstacionamento::sair(const string &nome) {
    for(int i = 0; i < clientes.size(); i++){
        if(clientes[i].nome == nome){
            if(clientes[i].presente == true){
                clientes[i].presente = false;
                vagas++;
                return true;
            }
        }
    }
    return false;
}

unsigned ParqueEstacionamento::getNumLugaresOcupados() const {
    return lotacao - vagas;
}

unsigned ParqueEstacionamento::getNumClientesAtuais() const {
    return clientes.size();
}