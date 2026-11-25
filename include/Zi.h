//
// Created by andre on 25.11.2026.
//

#ifndef ZI_H
#define ZI_H
#include <ostream>
#include "FocTabara.h"
#include "Jucator.h"

enum class RezultatNoapte {
    Supravietuit,
    AtacRespins,
    PrinsDeCerb,
    FocStins,
    InfrangereCultisti
};

class Zi {
public:
    Zi(int numarZi, int scadereFocNoapte, bool atacCultisti, int nivelNecesarCultisti, bool negustorBlanuri);

    int getNumarZi() const;
    int getScadereFocNoapte() const;
    bool areAtacCultisti() const;
    int getNivelNecesarCultisti() const;
    bool areNegustorBlanuri() const;

    RezultatNoapte proceseazaNoaptea(Jucator& jucator, FocTabara& foc, int bonusVictoriePct, int penalizareInfrangerePct, int minimFocSupravieturie) const;

    friend std::ostream& operator<<(std::ostream& os, const Zi& zi);

private:
    int numarZi_;
    int scadereFocNoapte_;
    bool atacCultisti_;
    int nivelNecesarCultisti_;
    bool negustorBlanuri_;
};

#endif //ZI_H
