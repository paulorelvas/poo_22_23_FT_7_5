#ifndef FT_7_5_TARIFARIO_H
#define FT_7_5_TARIFARIO_H

#include "proj_includes.h"
using namespace std;

class Tarifario {
protected:
    /// -----Begin::TreinoNode class

    // Apenas existe no contexto de class Tarifário e suas derivadas
    // Fora deste contexto não existe
    class TreinoNode {
    public:
        TreinoNode(unsigned duracao);

        unsigned duracao;
        TreinoNode * prox;
    };
    typedef TreinoNode Node;
    /// endregion

public:
    /// -----Begin::Constructor and Operator=
    Tarifario(string design);
    Tarifario(const Tarifario &obj);
    Tarifario& operator=(const Tarifario &obj) = delete;
    /// ---end::---

    /// ---BEGIN:: getter métodos
    string obtemName() const;
    unsigned obtemNumeroTreinos() const;
    string listarTreinos(bool simple = false) const;
    /// ---end::---

    /// ----BEGIN:: Gestão do treino
    bool adicionarTreino(unsigned duracao);
    /// --- end::--

    /// ----BEGIN::virtual functions
    virtual double calculaPagamento(bool remove_treinos = true) = 0;
    virtual Tarifario * clone() const = 0;
    virtual string asString(bool imprime_treinos = false) const = 0;
    virtual ~Tarifario();
    /// ---end::---

protected:
    void eliminaTreinos();
    TreinoNode * obtemTreinos() const ;
    int obtemTreinoIndex(unsigned idx) const;

private:
    string design;
    TreinoNode * inicio;
    TreinoNode * fim;
    unsigned n_treinos;

};
/// Funciona com todos os tipos de filhos de Tarifario (polimorfismo::asString ... )
ostream& operator<<(ostream& out, const Tarifario& t);
#endif //FT_7_5_TARIFARIO_H
