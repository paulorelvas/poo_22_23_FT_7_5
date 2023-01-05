#ifndef FT_7_5_APRESSADO_H
#define FT_7_5_APRESSADO_H

#include "Tarifario.h"
using namespace  std;

class Apressado:public Tarifario {
public:
    /// -----Begin::Constructor and operator=
    Apressado();
    Apressado(const Apressado &obj);
    /// end::---

    /// ----BEGIN::Virtual functions
    double calculaPagamento(bool remove_treinos = true) override;
    Apressado * clone() const override;
    string asString(bool imprime_treinos = false) const override;

    ~Apressado();
    /// ----end::---
};


#endif //FT_7_5_APRESSADO_H
