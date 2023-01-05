#include "Tarifario.h"


// Class TreinoNode
Tarifario::TreinoNode::TreinoNode(unsigned valor)
    : duracao(valor), prox(nullptr) {}

Tarifario::Tarifario(string design)
    :design(design), inicio(nullptr),fim(nullptr), n_treinos(0){
    #if DEBUG_TARIFARIO_CONSTRUTOR
        LOG("A construir Tarifário ...");
    #endif
}
Tarifario::Tarifario(const Tarifario &obj)
    :design(obj.design), inicio(nullptr),fim(nullptr), n_treinos(0){

    Node * p = obj.inicio;

    while(p != nullptr) {
        TreinoNode * n_node = new TreinoNode(p->duracao);

        if(!n_node) {
            eliminaTreinos();
            throw bad_alloc();
        }

        if(inicio == nullptr) {
            inicio = n_node;
            fim = n_node;
        } else {
            fim->prox = n_node;
            fim = n_node;
        }

        n_treinos++;
        p = p->prox;
    }
    #if DEBUG_TARIFARIO_CONSTRUTOR_COPIA
        LOG("A construir Tarifário por cópia ...");
    #endif
}

string Tarifario::obtemName() const{
    return design;
}
unsigned Tarifario::obtemNumeroTreinos() const{
    return n_treinos;
}
string Tarifario::listarTreinos(bool simple) const{
    if(!inicio)
        return "Não existem treinos!";

    bool f = false;
    unsigned c = 1;
    ostringstream oss;

    if(!simple) {
        for(const Node * p_t = inicio; p_t != nullptr; p_t = p_t->prox) {
            if(!f) {
                oss << "Lista de Treinos:" << endl;
                f = true;
            }
            oss << "   Treino " << c++ << " - " << p_t->duracao << " minutos" << endl;
        }
    } else {
        for(const Node * p_t = inicio; p_t != nullptr; p_t = p_t->prox) {
            if(!f) {
                oss << "Treinos: ";
                f = true;
            }

            if(p_t != fim)
                oss << p_t->duracao << "; ";
            else
                oss << p_t->duracao;
        }
    }
    return oss.str();
}

// Adicionar novo treino
bool Tarifario::adicionarTreino(unsigned int hora) {
    if(hora == 0)
        return false;

    Node * n_node = new Node(hora);

    if(!n_node) return false;

    if(inicio == nullptr) {
        inicio = n_node;
        fim = n_node;
    } else {
        fim->prox = n_node;
        fim = n_node;
    }

    n_treinos++;
    return true;
}
///

// métodos virtuais
Tarifario::~Tarifario() {
    eliminaTreinos();

    #if DEBUG_TARIFARIO_DELETE
        LOG("A Destrutuir Tarifário ...");
    #endif
}
///

// Protected métodos

void Tarifario::eliminaTreinos() {
    Node * aux = nullptr;

    while(inicio != nullptr){
        aux = inicio;
        inicio = inicio->prox;
        delete aux;
    }

    fim = nullptr;
    n_treinos = 0;
}

Tarifario::TreinoNode * Tarifario::obtemTreinos() const { return inicio; }

int Tarifario::obtemTreinoIndex(unsigned int idx) const {
    if(n_treinos == 0)
        return ERROR_INDEX;

    if(idx >= n_treinos)
        return ERROR_INDEX;

    unsigned i = 0;
    Node * p = inicio;

    while(p != nullptr){
        if(i == idx)
            return p->duracao;

        p = p->prox;
        i++;
    }
    return ERROR_INDEX;
}
///


ostream& operator<<(ostream& out, const Tarifario& t) {
    return out << t.asString(true);
}
