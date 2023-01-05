#include "Sociavel.h"
#include "Ginasio.h"

/// ---- BEGIN:: Construtor e Operator=
Sociavel::Sociavel(string name, unsigned bi, const Tarifario &tarif)
    : Cliente(name, bi, tarif) {
    #if DEBUG_CLIENTE_CONSTRUTOR
        LOG("Construtor (Sociavel) Cliente...");
    #endif

}

Sociavel::Sociavel(const Sociavel &obj)
    :Cliente(obj){

    #if DEBUG_CLIENTE_CONSTRUTOR_COPIA
        LOG("Construtor (Sociavel) Cliente por cópia ...");
    #endif

}

Sociavel& Sociavel::operator=(const Sociavel &obj){
    if(this == &obj)
        return *this;

    Cliente::operator=(obj);

    #if DEBUG_CLIENTE_OPERATOR_ATRIBUICAO
        LOG("(Sociavel) Cliente operator= ...");
    #endif

    return *this;
}
/// --- end:: ---

/// ---- BEGIN:: Virtual methods
/// ---- BEGIN:: Pure virtual methods

void Sociavel::reageEntrada(Ginasio * obj) {
    // não faz nada
    #if DEBUG_CLIENTE_REAGE_ENTRADA
        LOG("(Sociavel) Entrou um cliente... não faço nada...");
    #endif
}
void Sociavel::reageSaida(Ginasio * obj){
    if(obj && estaNoGinasio()) {
        if(obj->obtemNumeroClientes() == 1) {
            auto r = obj->clienteSair(obtemBI());

            #if DEBUG_EXIT_SOCIAVEL
                        LOG("Sociavel - reage saída: " << r.second);
            #endif
        }
    }
}
Sociavel * Sociavel::duplicar() const{
    return new Sociavel(*this);
}
/// --- end:: ---

string Sociavel::asString() const{
    ostringstream os;
    os << "S: { " << Cliente::asString() << " }";
    return os.str();
}

Sociavel::~Sociavel(){
    #if DEBUG_CLIENTE_DELETE
        LOG("Destruir Cliente (Sociável) ...");
    #endif
}

/// --- end:: ---
