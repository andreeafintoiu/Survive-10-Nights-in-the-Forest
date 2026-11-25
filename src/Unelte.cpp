//
// Created by andre on 24.11.2026.
//

#include "Unelte.h"
#include <stdexcept>
#include <utility>

Unelte::Unelte(std::string nume, int nivel, int nivelMaxim, int costLemn12, int costBlana12, int costLemn23, int costBlana23)
    : nume_(std::move(nume)), nivel_(nivel), nivelMaxim_(nivelMaxim), costLemn12_(costLemn12), costBlana12_(costBlana12), costLemn23_(costLemn23), costBlana23_(costBlana23) {
    if(nivel_ < 1 || nivel_ > nivelMaxim_)
        throw std::invalid_argument("Nivel invalid pentru unealta.");
    if(costLemn12_ < 0 || costBlana12_ < 0 || costLemn23_ < 0 || costBlana23_ < 0)
        throw std::invalid_argument("Costurile de upgare nu pot fi negative.");
}

const std::string& Unelte::getNume() const { return nume_; }
int Unelte::getNivel() const { return nivel_; }
bool Unelte::poateFiUpgradata() const { return nivel_ < nivelMaxim_; }

int Unelte::getCostLemnUpgrade() const {
    if(nivel_ == 1) return costLemn12_;
    if(nivel_ == 2) return costLemn23_;
    return 0;
}

int Unelte::getCostBlanaUpgrade() const {
    if(nivel_ == 1) return costBlana12_;
    if(nivel_ == 2) return costBlana23_;
    return 0;
}

bool Unelte::upgrade() {
    if(!poateFiUpgradata())
        return false;
    ++nivel_;
    return true;
}

std::ostream& operator<<(std::ostream& os, const Unelte& unealta) {
    os << unealta.nume_ << " (Nivel " << unealta.nivel_ << "/" << unealta.nivelMaxim_ << ")";
    if(unealta.poateFiUpgradata())
        os << " [Upgrade: " << unealta.getCostLemnUpgrade() << " Lemn, " << unealta.getCostBlanaUpgrade() << " Blana]";
    else
        os << " [MAX]";
    return os;
}


