#include "Zi.h"
#include <stdexcept>

Zi::Zi(int numarZi, int scadereFocNoapte, bool atacCultisti, int nivelNecesarCultisti, bool negustorBlanuri)
    : numarZi_(numarZi), scadereFocNoapte_(scadereFocNoapte),
      atacCultisti_(atacCultisti), nivelNecesarCultisti_(nivelNecesarCultisti),
      negustorBlanuri_(negustorBlanuri) {
    if (numarZi_ <= 0 || scadereFocNoapte_ < 0 || nivelNecesarCultisti_ < 0)
        throw std::invalid_argument("Parametri invalizi pentru configurarea zilei.");
}

int Zi::getNumarZi() const { return numarZi_; }
int Zi::getScadereFocNoapte() const { return scadereFocNoapte_; }
bool Zi::areAtacCultisti() const { return atacCultisti_; }
int Zi::getNivelNecesarCultisti() const { return nivelNecesarCultisti_; }
bool Zi::areNegustorBlanuri() const { return negustorBlanuri_; }

RezultatNoapte Zi::proceseazaNoaptea(Jucator& jucator, FocTabara& foc, int bonusVictoriePct,
                                     int penalizareInfrangerePct, int minimFocSupravietuire) const {
    if (!jucator.esteInBaza())
        return RezultatNoapte::PrinsDeCerb;

    foc.aplicaScadereNivelFoc(scadereFocNoapte_);
    if (foc.esteStins())
        return RezultatNoapte::FocStins;

    if (atacCultisti_) {
        bool victorie = (jucator.getNivelMinimUnelte() >= nivelNecesarCultisti_);
        foc.aplicaRezultatAtac(victorie, bonusVictoriePct, penalizareInfrangerePct, minimFocSupravietuire);
        if (!victorie)
            return RezultatNoapte::InfrangereCultisti;
        return RezultatNoapte::AtacRespins;
    }

    return RezultatNoapte::Supravietuit;
}

std::ostream& operator<<(std::ostream& os, const Zi& zi) {
    os << "Ziua " << zi.numarZi_ << " [Scadere foc noapte: -" << zi.scadereFocNoapte_ << "%";
    if (zi.atacCultisti_)
        os << " | ATAC CULTISTI (Nivel minim unelte: " << zi.nivelNecesarCultisti_ << ")";
    if (zi.negustorBlanuri_)
        os << " | NEGUSTOR DE BLANURI IN TABARA";
    os << "]";
    return os;
}