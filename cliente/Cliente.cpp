#include "Cliente.h"
#include "Tarifario.h"

Cliente::Cliente(string nome, unsigned int bi, const Tarifario & tarif):
    nome(nome), bi(bi), esta_no_ginasio(false), hora_guardada(0), tarif(tarif.clone()){

    #if DEBUG_CLIENTE_CONSTRUTOR
        LOG("--- Construtor de cliente ---");
    #endif
}
Cliente::Cliente(const Cliente & obj):
    nome(obj.nome), bi(obj.bi), tarif(obj.tarif->clone()),
    esta_no_ginasio(obj.esta_no_ginasio),hora_guardada(obj.hora_guardada){
    #if DEBUG_CLIENTE_CONSTRUTOR_COPIA
        LOG("--- Construtor por CÓPIA de cliente ---");
    #endif
}
Cliente& Cliente::operator=(const Cliente & obj){
    if(this == &obj)
        return *this;

    Tarifario * tmp = nullptr;

    try { tmp = obj.tarif->clone(); } catch (const bad_alloc & e) {
        throw e;
    }

    nome = obj.nome;
    bi = obj.bi;
    hora_guardada = obj.hora_guardada;
    esta_no_ginasio = obj.esta_no_ginasio;

    delete tarif;
    tarif = tmp;

    #if DEBUG_CLIENTE_OPERATOR_ATRIBUICAO
        LOG("Cliente::operator= ...");
    #endif

    return *this;
}
// getter métodos
string Cliente::obtemNome() const{ return nome; }
int Cliente::obtemBI() const{ return bi; }
bool Cliente::estaNoGinasio() const noexcept{ return esta_no_ginasio; }

double Cliente::obtemValorPagamento() const{
    return tarif->calculaPagamento(false);
}
///

// métodos de gestão de treinos
/// \param hora_inicio
bool Cliente::iniciaTreino(unsigned int hora_inicio){
    if(!esta_no_ginasio) {
        hora_guardada = hora_inicio;
        esta_no_ginasio = true;
        return true;
    }
    return false;
}
bool Cliente::terminaTreino(unsigned int hora_fim){
    if(esta_no_ginasio && hora_fim > hora_guardada) {
        if(!tarif->adicionarTreino((hora_fim-hora_guardada)))
            return false;
        hora_guardada = 0;
        esta_no_ginasio = false;
        return true;
    }

    return false;
}
double Cliente::paga(){
    return tarif->calculaPagamento(true);
}

string Cliente::asString() const{
    ostringstream os;
    os << "Id: '" << bi << "', ";
    os << "N: '" << nome << "', ";

    os << "G: '" << (esta_no_ginasio ? "Y" : "N") << "', ";

    if(esta_no_ginasio)
        os << "GET: '" << hora_guardada << "', ";

    os << "T: '" << tarif->asString(true) << "', ";
    os << "P: '" << tarif->calculaPagamento(false) << "'";

    return os.str();
}
Cliente::~Cliente(){
    #if DEBUG_CLIENTE_DELETE
        LOG("A Destruir o Cliente ...");
    #endif

    delete tarif; /// associação por composição (delete the parts...)
}
///

ostream& operator<<(ostream& out, const Cliente &c) {
    return out << c.asString();
}