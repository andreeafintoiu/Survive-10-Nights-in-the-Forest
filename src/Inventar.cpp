//
// Created by andre on 24.11.2026.
//

#include "Inventar.h"
#include <algorithm>
#include <stdexcept>

Inventar::Inventar(const std::vector<Resursa>& resurseInitiale, const std::vector<Unelte>& unelteInitiale)
    : resurse_(resurseInitiale), unelte_(unelteInitiale) {}

Resursa *Inventar::gasesteResursa(const std::string& numeResursa) {
    for(auto& r : resurse_)
        if(r.getNume() == numeResursa)
            return &r;
    return nullptr;
}

const Resursa *Inventar::gasesteResursa(const std::string &numeResursa) const {
    for(const auto& r : resurse_)
        if(r.getNume() == numeResursa)
            return &r;
    return nullptr;
}

Unelte *Inventar::gasesteUnealta(const std::string &numeUnealta) {
    for(auto& u : unelte_)
        if(u.getNume() == numeUnealta)
            return &u;
    return nullptr;
}

const Unelte *Inventar::gasesteUnealta(const std::string &numeUnealta) const {
    for(const auto& u : unelte_)
        if(u.getNume() == numeUnealta)
            return &u;
    return nullptr;
}

int Inventar::getCantitateResursa(const std::string& numeResursa) const {
    const Resursa* r = gasesteResursa(numeResursa);
    return (r != nullptr) ? r->getCantitate() : 0;
}

int Inventar::getValoareFocResursa(const std::string& numeResursa) const {
    const Resursa* r = gasesteResursa(numeResursa);
    return (r != nullptr) ? r->getValoareFoc() : 0;
}

int Inventar::getNivelUnealta(const std::string& numeUnealta) const {
    const Unelte* u = gasesteUnealta(numeUnealta);
    if(u == nullptr)
        throw std::invalid_argument("Unealta '" + numeUnealta + "' nu exista in inventar.");
    return u->getNivel();
}

int Inventar::getNivelMinimUnelte() const {
    if(unelte_.empty())
        throw std::logic_error("Inventarul nu are unelte.");
    int minNivel = unelte_[0].getNivel();
    for(const auto& u : unelte_)
        minNivel = std::min(minNivel, u.getNivel());
    return minNivel;
}

void Inventar::adaugaResursa(const std::string& numeResursa, int bucati) {
    Resursa* r = gasesteResursa(numeResursa);
    if(r == nullptr)
        throw std::invalid_argument("Resursa '" + numeResursa + "' nu exista in inventar.");
    r->adauga(bucati);
}

bool Inventar::consumaResursa(const std::string& numeResursa, int bucati) {
    Resursa* r = gasesteResursa(numeResursa);
    if(r == nullptr)
        return false;
    return r->consuma(bucati);
}

bool Inventar::alimenteazaFocCuResursa(FocTabara& foc, const std::string &numeResursa, int bucati) {
    Resursa* r = gasesteResursa(numeResursa);
    if(r == nullptr)
        return false;
    return foc.alimentare(*r, bucati);
}


bool Inventar::upgradeUnealta(const std::string& numeUnealta) {
    Unelte* u = gasesteUnealta(numeUnealta);
    if(u == nullptr || !u->poateFiUpgradata())
        return false;
    int costLemn = u->getCostLemnUpgrade();
    int costBlana = u->getCostBlanaUpgrade();

    if(getCantitateResursa("Lemn") < costLemn || getCantitateResursa("Blana") < costBlana)
        return false;

    consumaResursa("Lemn", costLemn);
    consumaResursa("Blana", costBlana);
    return u->upgrade();
}

std::ostream& operator<<(std::ostream& os, const Inventar& inv) {
    os << " Unelte:\n";
    for(const auto& u : inv.unelte_)
        os << "  * " << u << "\n";
    os << " Resurse:\n";
    for(const auto& r : inv.resurse_)
        os << "  - " << r << "\n";
    return os;
}
