#ifndef FT_7_5_CLIENTE_H
#define FT_7_5_CLIENTE_H

#include "proj_includes.h"

using namespace std;

class Tarifario;
class Ginasio;

class Cliente {
public:
    /// ----- BEGIN:: construtores e operador=
    Cliente(string nome, unsigned int bi, const Tarifario & tarif);
    Cliente(const Cliente & obj);
    Cliente& operator=(const Cliente & obj);
    /// ---end:: ---

    /// ----- BEGIN:: métodos getters
    string obtemNome() const;
    int obtemBI() const;
    bool estaNoGinasio()const noexcept;
    double obtemValorPagamento() const;
    /// ---end:: ---

    /// ----- BEGIN:: métodos de gestão de treino
    bool iniciaTreino(unsigned int hora_inicio);
    bool terminaTreino(unsigned int hora_fim);
    double paga();
    /// ---end:: ----

    /// ----- BEGIN:: métodos virtuais
    virtual void reageEntrada(Ginasio * obj) = 0;
    virtual void reageSaida(Ginasio * obj) = 0;
    virtual Cliente * duplicar() const = 0;
    virtual string asString() const;
    virtual ~Cliente();
    /// ---end::---
private:
    string nome;
    int bi;
    Tarifario * tarif;
    bool esta_no_ginasio = false;
    unsigned hora_guardada;
};

ostream& operator<<(ostream& out, const Cliente &c);

#endif //FT_7_5_CLIENTE_H
