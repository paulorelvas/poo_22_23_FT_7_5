#include <iostream>

#include "proj_includes.h"
#include "Ginasio.h"
#include "Apressado.h"
#include "Sociavel.h"

using namespace std;

int main() {
    LOG( "---- FT_7_5 ----" );
/*
    Apressado r;

    LOG("=============================================");
    LOG(r.asString());
    LOG("=============================================");
    LOG(r.asString(true));
    LOG("=============================================");

    r.adicionarTreino(5);
    r.adicionarTreino(10);
    r.adicionarTreino(15);
    r.adicionarTreino(25);

    LOG(r.asString());
    LOG("=============================================");
    LOG(r.asString(true));
    LOG("=============================================");

    LOG(r);
    LOG("=============================================");

    LOG(r.obtemNumeroTreinos()); // 4
    LOG("=============================================");

    LOG(r.listarTreinos());
    LOG(r.listarTreinos(true));

    LOG("=============================================");

    LOG("Total a pagar: " << r.calculaPagamento(false)); // 60
    LOG(r.asString(true));

    LOG("=============================================");

    LOG("Total a pagar: " << r.calculaPagamento(true)); // 60 - and clean workouts
    LOG(r.asString(true));

    LOG("=============================================");

    LOG(r);

    LOG("=============================================");

    auto pr = r.clone();

    LOG("=============================================");

    LOG("Clone -> " << *pr);

    LOG("=============================================");

    delete pr;
*/

    Ginasio g;
    Apressado r;

    LOG("=============================================");
    r.adicionarTreino(5);
    r.adicionarTreino(10);
    r.adicionarTreino(15);
    r.adicionarTreino(25);
    LOG(r.asString());
    LOG("=============================================");

    Sociavel s1("S1", 1, r);
    Sociavel s2("S2", 2, r);

    LOG("=================================");
    LOG(g);
    LOG("=================================");

    auto res_ = g.adicionaCliente(&s1);
    LOG("Result: " << res_.second);
    res_ = g.adicionaCliente(&s2);
    LOG("Result: " << res_.second);
    LOG("=================================");
    LOG(g);
    LOG("=================================");

    //g.clienteEntrar(s1.obtemBI());
    //g.clienteEntrar(s2.obtemBI());

    //LOG(g);

    //LOG("=================================");

    g.adiantaHoras(5);

    LOG(g);

    LOG("=================================");
    s1.iniciaTreino(0);
    s1.terminaTreino(5);

    s1.iniciaTreino(7);
    s1.terminaTreino(14);

    s1.iniciaTreino(15);
    s1.terminaTreino(30);

    s1.iniciaTreino(40);
    s1.terminaTreino(63);

    /*LOG("=================================");
    LOG("Is in gym: " << (s1.estaNoGinasio() ? "Yes" : "No") );
    LOG("Name: " << s1.obtemNome());
    LOG("Id: " << s1.obtemBI());
    LOG("Current value to pay: " << s1.obtemValorPagamento());
    LOG("=================================");*/


    auto res = g.clienteSair(s1.obtemBI());
    LOG("Result: " << res.second);

    res = g.clienteSair(s2.obtemBI());
    LOG("Result: " << res.second);          // falha porque o sociável saiu quando está sozinho


    LOG("=================================");

    LOG(g);

    LOG("=================================");


    g.adiantaHoras(1);

    res = g.clienteSair(s1.obtemBI());
    LOG("Result: " << res.second);

    LOG("=================================");



    LOG(g);

    g.adiantaHoras(10);

    LOG("=================================");

    res = g.clienteSair(s1.obtemBI());
    LOG("Result: " << res.second);

    LOG("=================================");
    auto res_2 = g.PagamentoContaByBi(s1.obtemBI());
    LOG("Current value to pay: " << get<2>(res_2) );

    LOG(g);

    LOG("=================================");
    return 0;

}
