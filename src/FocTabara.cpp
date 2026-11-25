//
// Created by andre on 24.11.2026.
//

#include "FocTabara.h"
#include <algorithm>
#include <stdexcept>

FocTabara::FocTabara(int nivelFocInitial, int maximFoc)
    : nivelFoc_(nivelFocInitial), maximFoc_(maximFoc) {
    if(maximFoc_ <= 0 || nivelFoc_ <= 0 || nivelFoc_ > maximFoc_)
        throw std::invalid_argument("Parametrii invalizi pentru FocTabara.");
}

int FocTabara::getNivelFoc() const { return nivelFoc_; }
bool FocTabara::esteStins() const { return nivelFoc_ <= 0; }

bool FocTabara::alimentare(Resursa& resursa, int bucati) {
    if(bucati <= 0 || resursa.getValoareFoc() <= 0 || !resursa.consuma(bucati))
        return false;
    const long long nou = static_cast<long long>(nivelFoc_) + static_cast<long long>(resursa.getValoareFoc()) * bucati;
    nivelFoc_ = static_cast<int>(std::min<long long>(maximFoc_, nou));
    return true;
}

void FocTabara::aplicaScadereNivelFoc(int puncteScadere) {
   if (puncteScadere > 0)
       nivelFoc_ = std::max(0, nivelFoc_ - puncteScadere);
}

void FocTabara::aplicaRezultatAtac(bool victorie, int bonusVictoriePct, int penalizareInfrangerePct, int minimSupravietuire) {
    if (esteStins())
        return; // un foc stins nu mai poate fi schimbat de un atac
    if (victorie) {
        nivelFoc_ = std::min(maximFoc_, nivelFoc_ + (nivelFoc_ * bonusVictoriePct) / 100);
    } else {
        const int nou = std::max(minimSupravietuire, nivelFoc_ - (nivelFoc_ * penalizareInfrangerePct) / 100 + 1);
        nivelFoc_ = std::min(nivelFoc_, nou); // infrangerea nu poate creste focul
    }
}

std::ostream& operator<<(std::ostream& os, const FocTabara& foc) {
    os << "Foc de Tabara: " << foc.nivelFoc_ << "% / " << foc.maximFoc_ << "%";
    return os;
}
