//
// Created by andre on 24.11.2026.
//

#ifndef JUCATOR_H
#define JUCATOR_H

#include <iostream>
#include <random>
#include <string>
#include "FocTabara.h"
#include "Inventar.h"

struct ConfigJucator {
    int maxActiuniZi;
    int sansaCarbune;
    int sansaCanistra;
    int sansaNimic;
    int dropMinLupi;
    int dropMaxLupi;
    int lemnMin[3];
    int lemnMax[3];
};
enum class TipRezultatActiune {
    FaraActiuni,
    ResursaGasita,
    NimicGasit,
    IntalnireLupi
};
struct RezultatActiune {
    TipRezultatActiune tip;
    std::string numeResursa;
    int cantitate = 0;
};

class Jucator {
public:
    Jucator(std::string nume, Inventar inventarInitial, const ConfigJucator& cfg);

    const std::string& getNume() const;
    int getNivelMinimUnelte() const;
    bool esteInBaza() const;
    int getActiuniRamase() const;

    void reseteazaZi();
    void intoarceInBaza();

    RezultatActiune taieLemne(std::mt19937& rng);
    RezultatActiune exploreazaPadure(std::mt19937& rng);
    bool alimenteazaFoc(FocTabara& foc, const std::string& numeResursa, int bucati);
    bool upgradeUnealta(const std::string& numeUnealta);

    friend std::ostream& operator<<(std::ostream& os, const Jucator& jucator);

private:
    std::string nume_;
    ConfigJucator cfg_;
    bool inBaza_ = true;
    int actiuniRamase_;
    Inventar inventar_;

    bool consumaActiune();
};

#endif //JUCATOR_H
