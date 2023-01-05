#ifndef FT_7_5_GINASIO_H
#define FT_7_5_GINASIO_H

#include "proj_includes.h"
#include <vector>
#include <tuple>

using namespace std;

class Cliente;

class Ginasio {
public:
    /// ---- BEGIN:: Construtores e Operator=
    Ginasio();
    Ginasio(const Ginasio &obj);
    Ginasio& operator=(const Ginasio &obj);
    /// --- end:: ---

    void adiantaHoras(unsigned t);

    /// ---- BEGIN::  métodos para a gestão de clientes
    pair<bool, string> adicionaCliente(const Cliente *c);
    pair<bool, string> removeCliente(unsigned bi);
    pair<bool, string> clienteEntrar(unsigned bi);
    pair<bool, string> clienteSair(unsigned bi);
    tuple<bool, double, string> PagamentoContaByBi(unsigned bi);
    /// -- end:: ---

    /// ---- BEGIN:: métodos getter
    unsigned obtemDuracaoAtual() const;
    size_t obtemNumeroClientes() const;
    size_t obtemNumeroClientesNoGinasio() const;
    string asString() const;
    pair<bool, string> estaNoGinasio(unsigned bi) const;
    pair<bool, string> eClienteGinasio(unsigned bi) const;
    /// -- end:: ---

    ~Ginasio();

private:
    unsigned relogio;
    unsigned clientes_no_ginasio;
    vector<Cliente*> clientes;
    void eliminaClientes();
    Cliente * obtemClienteByBI(unsigned bi) const;
};

ostream &operator<<(ostream &os, const Ginasio &obj);
#endif //FT_7_5_GINASIO_H
