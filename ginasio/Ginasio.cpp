#include "Ginasio.h"
#include "Cliente.h"

/// ---- BEGIN:: Construtores e Operator=
Ginasio::Ginasio():relogio(0), clientes_no_ginasio(0){
    #if DEBUG_GINASIO_CONSTRUTOR
        LOG("Construtor Ginásio ...");
    #endif
}
Ginasio::Ginasio(const Ginasio &obj){
    *this = obj;

    #if DEBUG_GINASIO_CONSTRUTOR_COPIA
        LOG("Construir Ginásio por cópia...");
    #endif
}
Ginasio& Ginasio::operator=(const Ginasio &obj){
    if(this == &obj)
        return *this;

    eliminaClientes();
    relogio = obj.relogio;
    clientes_no_ginasio = obj.clientes_no_ginasio;

    for(auto & el: obj.clientes){
        Cliente * tmp = nullptr;

        try { tmp = el->duplicar(); }
        catch (const bad_alloc & e) {
            eliminaClientes();
            throw e;
        }

        try{ clientes.push_back(tmp); }
        catch (const bad_alloc & e) {
            eliminaClientes();
            throw e;
        }
    }

    #if DEBUG_GINASIO_OPERADOR_ATRIBUICAO
        LOG("Operator= Ginásio ...");
    #endif

    return *this;
}
/// --- end:: ---

void Ginasio::adiantaHoras(unsigned t){
    relogio += t;
}

/// ---- BEGIN::  métodos para a gestão de clientes
pair<bool, string> Ginasio::adicionaCliente(const Cliente *c){
    if(!c)
        return {false, "Cliente em falta!"};

    unsigned c_id = c->obtemBI();

    if(obtemClienteByBI(c_id))
        return {false, "O cliente '" + to_string(c_id) + "' já é um cliente do ginásio."};

    Cliente * tmp = nullptr;
    try { tmp = c->duplicar(); cout << "BI: " << tmp->obtemBI() << endl; } catch (const bad_alloc & e) {
        return {false, "Erro a alocar memória para o novo cliente."};
    }

    try { clientes.push_back(tmp); cout << "sizeof: " << clientes.size() << endl; } catch (const bad_alloc & e) {
        delete tmp;
        return {false, "Erro a alocar memória para o novo cliente."};
    }

    return {true, "O cliente '" + to_string(c_id) + "' foi adicionado com sucesso ao ginásio."};
}
pair<bool, string> Ginasio::removeCliente(unsigned bi){
    auto el = clientes.begin();
    for(; el != clientes.end(); ++el)
        if((*el)->obtemBI() == bi)
            break;

    if(el == clientes.end())
        return {false, "O ginásio não tem um cliente com o BI '" + to_string(bi) + "'."};


    if((*el)->estaNoGinasio())
        return {false, "O cliente '" + to_string(bi) + "' está a treinar. Primeiro tem de terminar."};


    double valor_a_pagar = (*el)->paga(); // diferente de obtemValorPagamento (um remove treinos o outro apenas calcula montante a pagar)
    delete *el;
    clientes.erase(el);

    return {true, "O cliente '" + to_string(bi) + "' anulou a subscrição com sucesso. Tem a pagar: '"
                  + to_string(valor_a_pagar) + "'."};
}
pair<bool, string> Ginasio::clienteEntrar(unsigned bi){
    Cliente * c = obtemClienteByBI(bi);

    if(!c)
        return {false, "O ginásio não tem nenhum cliente com o BI '" + to_string(bi) + "'."};

    if(c->estaNoGinasio())
        return {false, "O cliente '" + to_string(bi) + "' já está no ginásio."};

    if(!c->iniciaTreino(relogio))
        return {false, "Ocorreu um erro a registar a hora de entrada."};

    clientes_no_ginasio++;

    for(auto & el: clientes)
        if(el->estaNoGinasio() && el->obtemBI() != bi)
            el->reageEntrada(this);

    return {true, "O cliente '" + to_string(bi) + "' entrou no ginásio com successo."};
}
pair<bool, string> Ginasio::clienteSair(unsigned bi){
    Cliente * c = obtemClienteByBI(bi);

    if(!c)
        return {false, "O ginásio não tem nenhum cliente com o BI '" + to_string(bi) + "'."};

    if(!c->estaNoGinasio())
        return {false, "O cliente '" + to_string(bi) + "' já saiu do ginásio."};

    if(!c->terminaTreino(relogio))
        return {false, "Ocorreu um erro a registar a hora de entrada."};

    clientes_no_ginasio--;

    for(auto & el: clientes)
        if(el->estaNoGinasio() && c->obtemBI() != bi)
            el->reageSaida(this);

    return {true, "O cliente '" + to_string(bi) + "' saiu do ginásio com successo."};
}
tuple<bool, double, string> Ginasio::PagamentoContaByBi(unsigned bi){
    Cliente * c = obtemClienteByBI(bi);

    if(!c)
        return {false, 0, "O ginásio não tem nenhum cliente com o BI '" + to_string(bi) + "'."};

    if(c->estaNoGinasio())
        return {false, 0, "O cliente '" + to_string(bi) + "' está a treinar. Primeiro tem de sair."};

    double valorPagar = c->paga();

    return {true, valorPagar, ("Cliente '" + to_string(bi) + "' tem a pagar: " + to_string(valorPagar))};
}
/// -- end:: ---

/// ---- BEGIN:: métodos getter
unsigned Ginasio::obtemDuracaoAtual() const{ return relogio; }
size_t Ginasio::obtemNumeroClientes() const{ return clientes.size(); }
size_t Ginasio::obtemNumeroClientesNoGinasio() const{ return clientes_no_ginasio; }

string Ginasio::asString() const{
    ostringstream os;
    size_t size_c = clientes.size();

    os << "G: { Clk: '" << relogio << "', ";
    os << "NC: '" << size_c << "', ";
    os << "NCG: '" << clientes_no_ginasio << "'";

    if(size_c != 0) {
        os << endl << "  CL: " << endl;
        for (size_t i = 0; i < size_c; i++)
            os << "     " << i + 1 << " - " << clientes[i]->asString() << endl;
        os << " }";
    } else
        os << " }";

    return os.str();
}
pair<bool, string> Ginasio::estaNoGinasio(unsigned bi) const{
    auto c = obtemClienteByBI(bi);

    if(!c)
        return {false, "O cliente '" + to_string(bi) + "' não é cliente do ginásio."};

    if(c->estaNoGinasio())
        return {true, "O cliente '" + to_string(bi) + "' está no ginásio."};

    return {false, "O cliente '" + to_string(bi) + "' não está no ginásio."};
}
pair<bool, string> Ginasio::eClienteGinasio(unsigned bi) const{
    auto c = obtemClienteByBI(bi);

    if(!c)
        return {false, "O ginásio não tem nenhum cliente com o BI '" + to_string(bi) + "'."};

    return {true, "O ginásio tem um cliente com o BI '" + to_string(bi) + "'."};
}
/// -- end:: ---

Ginasio::~Ginasio(){
    #if DEBUG_GINASIO_DELETE
        LOG("Destruir ginásio ...");
    #endif

    eliminaClientes();
}
/// ---- BEGIN:: protected métodos
void Ginasio::eliminaClientes(){
    for(const auto & el: clientes)
        delete el;
}
Cliente * Ginasio::obtemClienteByBI(unsigned bi) const{
    for(const auto & el: clientes)
        if(el->obtemBI() == bi)
            return el;

    return nullptr;
}
/// ---end:: ---

ostream &operator<<(ostream &os, const Ginasio &obj) {
    return os << obj.asString();
}