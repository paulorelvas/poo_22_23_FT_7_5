#include "Apressado.h"

Apressado::Apressado() : Tarifario("Apressado") {
#if DEBUG_TARIFARIO_CONSTRUTOR
    LOG("Construtor (Apressado) Tarifário ...");
#endif
}

Apressado::Apressado(const Apressado &obj) : Tarifario(obj) {
#if DEBUG_TARIFARIO_CONSTRUTOR_COPIA
    LOG("Construtor (Apressado) Tarifário por cópia ...");
#endif
}

double Apressado::calculaPagamento(bool remove_treinos) {
    double valorPagar = 0;
    unsigned n_treinos = obtemNumeroTreinos();

    if(n_treinos == 0)
        return valorPagar;

    for(unsigned i = 0; i < n_treinos; i++) {
        int v = obtemTreinoIndex(i);
        if(v != ERROR_INDEX) {
            if (v <= 10)
                valorPagar += 10;
            else if (v >= 11 && v <= 20)
                valorPagar += 15;
            else
                valorPagar += 25;
        }
    }

    if(remove_treinos)
        eliminaTreinos();

    return valorPagar;
}

Apressado * Apressado::clone() const {
    return new Apressado(*this);
}

string Apressado::asString(bool imprime_treinos) const {
    ostringstream oss;
    oss << "A";

    if(imprime_treinos)
        oss << " - " << listarTreinos(true); /// mostra treinos - versão simplificada

    return oss.str();
}

Apressado::~Apressado() {
#if DEBUG_TARIFARIO_DELETE
    LOG("Destrutor (Apressado) Tarifário...");
#endif
}