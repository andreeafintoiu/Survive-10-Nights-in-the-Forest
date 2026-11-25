//
// Created by andre on 24.11.2026.
//

#ifndef FOCTABARA_H
#define FOCTABARA_H

#include <iostream>
#include "Resursa.h"

class FocTabara {
public:
    explicit FocTabara(int nivelFocInitial = 60, int maximFoc = 100);

    int getNivelFoc() const;
    bool esteStins() const;

    bool alimentare(Resursa& resursa, int bucati);
    void aplicaScadereNivelFoc(int puncteScadere);
    void aplicaRezultatAtac(bool victorie, int bonusVictoriePct = 20, int penalizareInfrangerePct = 50, int minimSupravietuire = 1);

    friend std::ostream& operator<<(std::ostream& os, const FocTabara& foc);
private:
    int nivelFoc_;
    int maximFoc_;
};

#endif //FOCTABARA_H
