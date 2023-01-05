#ifndef FT_7_5_SOCIAVEL_H
#define FT_7_5_SOCIAVEL_H

#include "Cliente.h"

using namespace std;

class Sociavel:public Cliente {

public:
    /// ---- BEGIN:: Construtor e Operator=
    Sociavel(string name, unsigned bi, const Tarifario &tarif);
    Sociavel(const Sociavel &obj);
    Sociavel& operator=(const Sociavel &obj);
    /// --- end:: ---

    /// ---- BEGIN:: Virtual methods
    /// ---- BEGIN:: Pure virtual methods
    void reageEntrada(Ginasio * obj) override;
    void reageSaida(Ginasio * obj) override;
    Sociavel * duplicar() const override;
    /// --- end:: ---

    string asString() const override;

    ~Sociavel();

    /// --- end:: ---
};


#endif //FT_7_5_SOCIAVEL_H
