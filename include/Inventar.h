//
// Created by andre on 24.11.2026.
//

#ifndef INVENTAR_H
#define INVENTAR_H

#include <iostream>
#include <string>
#include <vector>
#include "Resursa.h"
#include "Unelte.h"
#include "FocTabara.h"

class Inventar {
public:
    Inventar(const std::vector<Resursa>& resurseInitiale, const std::vector<Unelte>& unelteInitiale);

    int getCantitateResursa(const std::string& numeResursa) const;
    int getValoareFocResursa(const std::string& numeResursa) const;
    int getNivelUnealta(const std::string& numeUnealta) const;
    int getNivelMinimUnelte() const;

    void adaugaResursa(const std::string& numeResursa, int bucati);
    bool consumaResursa(const std::string& numeResursa, int bucati);
    bool alimenteazaFocCuResursa(FocTabara& foc, const std::string& numeResursa, int bucati);
    bool upgradeUnealta(const std::string& numeUnealta);

    friend std::ostream& operator<<(std::ostream& os, const Inventar& inv);

private:
    std::vector<Resursa> resurse_;
    std::vector<Unelte> unelte_;

    Resursa* gasesteResursa(const std::string& numeResursa);
    const Resursa* gasesteResursa(const std::string& numeResursa) const;
    Unelte* gasesteUnealta(const std::string& numeUnealta);
    const Unelte* gasesteUnealta(const std::string& numeUnealta) const;
};

#endif //INVENTAR_H
