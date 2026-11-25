#ifndef JOC_H
#define JOC_H

#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "FocTabara.h"
#include "Jucator.h"
#include "Resursa.h"
#include "Zi.h"

struct ConfigJoc {
    int nivelFocInitial;
    int maximFoc;
    int bonusVictoriePct;
    int penalizareInfrangerePct;
    int minimFocSupravietuire;
    int nivelMaxUnealta;
    int costLemn12;
    int costBlana12;
    int costLemn23;
    int costBlana23;
    ConfigJucator cfgJucator;
};

class Joc {
public:
    Joc(const std::string& caleConfig,
        const std::string& caleResurse,
        const std::string& caleZile,
        const std::string& numeJucator,
        unsigned int seed);

    void ruleaza();

    friend std::ostream& operator<<(std::ostream& os, const Joc& joc);

private:
    ConfigJoc cfg_;
    FocTabara foc_;
    Jucator jucator_;
    std::vector<Zi> zile_;
    std::size_t indexZiCurenta_ = 0;
    bool jocTerminat_ = false;
    std::mt19937 rng_;

    static ConfigJoc incarcaConfig(const std::string& caleFisier);
    static std::vector<Resursa> incarcaResurse(const std::string& caleFisier);
    static std::vector<Zi> incarcaZile(const std::string& caleFisier);
    static std::string citesteLinieUtila(std::ifstream& fin);

    void afiseazaMeniuZi(const Zi& zi) const;
    void proceseazaNegustor();
};

#endif // JOC_H