#include "Resursa.h"
#include <stdexcept>
#include <utility>

int Resursa::nrInstante_ = 0;

Resursa::Resursa(std::string nume, std::string tip, int valoareFoc, int cantitate)
    : nume_(std::move(nume)), tip_(std::move(tip)), valoareFoc_(valoareFoc), cantitate_(cantitate) {
    if (cantitate_ < 0 || valoareFoc_ < 0)
        throw std::invalid_argument("Cantitatea si valoarea focului nu pot fi negative.");
    ++nrInstante_;
}

Resursa::Resursa(const Resursa& alta)
    : nume_(alta.nume_), tip_(alta.tip_), valoareFoc_(alta.valoareFoc_), cantitate_(alta.cantitate_) {
    ++nrInstante_;
}

Resursa& Resursa::operator=(const Resursa& alta) {
    if (this != &alta) {
        nume_ = alta.nume_;
        tip_ = alta.tip_;
        valoareFoc_ = alta.valoareFoc_;
        cantitate_ = alta.cantitate_;
    }
    return *this;
}

Resursa::~Resursa() {
    --nrInstante_;
}

const std::string& Resursa::getNume() const { return nume_; }
const std::string& Resursa::getTip() const { return tip_; }
int Resursa::getValoareFoc() const { return valoareFoc_; }
int Resursa::getCantitate() const { return cantitate_; }
int Resursa::getNrInstante() { return nrInstante_; }

void Resursa::adauga(int bucati) {
    if (bucati > 0)
        cantitate_ += bucati;
}

bool Resursa::consuma(int bucati) {
    if (bucati <= 0 || cantitate_ < bucati)
        return false;
    cantitate_ -= bucati;
    return true;
}

std::ostream& operator<<(std::ostream& os, const Resursa& r) {
    os << r.nume_ << " [" << r.tip_ << "]: " << r.cantitate_ << " buc.";
    if (r.valoareFoc_ > 0)
        os << " (+" << r.valoareFoc_ << "% foc/buc)";
    return os;
}
