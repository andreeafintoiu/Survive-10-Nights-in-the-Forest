//
// Created by andre on 24.11.2026.
//

#include "Jucator.h"
#include <algorithm>
#include <stdexcept>
#include <utility>

Jucator::Jucator(std::string nume, Inventar inventarInitial, const ConfigJucator& cfg)
    : nume_(std::move(nume)),
      cfg_(cfg),
      actiuniRamase_(cfg.maxActiuniZi),
      inventar_(std::move(inventarInitial)) {
    if (cfg_.maxActiuniZi <= 0)
        throw std::invalid_argument("Numarul maxim de actiuni pe zi trebuie sa fie pozitiv.");
}

const std::string& Jucator::getNume() const { return nume_; }
int Jucator::getNivelMinimUnelte() const { return inventar_.getNivelMinimUnelte(); }
bool Jucator::esteInBaza() const { return inBaza_; }
int Jucator::getActiuniRamase() const { return actiuniRamase_; }

void Jucator::reseteazaZi() {
    actiuniRamase_ = cfg_.maxActiuniZi;
    inBaza_ = true;
}

void Jucator::intoarceInBaza() {
    inBaza_ = true;
}

bool Jucator::consumaActiune() {
    if (actiuniRamase_ <= 0)
        return false;
    --actiuniRamase_;
    inBaza_ = false;
    return true;
}

RezultatActiune Jucator::taieLemne(std::mt19937& rng) {
    if (!consumaActiune())
        return {TipRezultatActiune::FaraActiuni, "", 0};

    int nivelTopor = inventar_.getNivelUnealta("Topor");
    int idx = std::clamp(nivelTopor - 1, 0, 2);

    std::uniform_int_distribution<int> dist(cfg_.lemnMin[idx], cfg_.lemnMax[idx]);
    int gasit = dist(rng);
    inventar_.adaugaResursa("Lemn", gasit);

    return {TipRezultatActiune::ResursaGasita, "Lemn", gasit};
}

RezultatActiune Jucator::exploreazaPadure(std::mt19937& rng) {
    if (!consumaActiune())
        return {TipRezultatActiune::FaraActiuni, "", 0};

    std::uniform_int_distribution<int> sansa(1, 100);
    int roll = sansa(rng);

    int pragCarbune = cfg_.sansaCarbune;
    int pragCanistra = pragCarbune + cfg_.sansaCanistra;
    int pragNimic = pragCanistra + cfg_.sansaNimic;

    if (roll <= pragCarbune) {
        inventar_.adaugaResursa("Carbune", 1);
        return {TipRezultatActiune::ResursaGasita, "Carbune", 1};
    }
    if (roll <= pragCanistra) {
        inventar_.adaugaResursa("Canistra", 1);
        return {TipRezultatActiune::ResursaGasita, "Canistra", 1};
    }
    if (roll <= pragNimic) {
        return {TipRezultatActiune::NimicGasit, "", 0};
    }

    std::uniform_int_distribution<int> dropLupi(cfg_.dropMinLupi, cfg_.dropMaxLupi);
    int blanuri = dropLupi(rng);
    inventar_.adaugaResursa("Blana", blanuri);
    return {TipRezultatActiune::IntalnireLupi, "Blana", blanuri};
}

bool Jucator::alimenteazaFoc(FocTabara& foc, const std::string& numeResursa, int bucati) {
    if (!inventar_.alimenteazaFocCuResursa(foc, numeResursa, bucati))
        return false;
    inBaza_ = true;
    return true;
}

bool Jucator::upgradeUnealta(const std::string& numeUnealta) {
    return inventar_.upgradeUnealta(numeUnealta);
}

std::ostream& operator<<(std::ostream& os, const Jucator& jucator) {
    os << "Jucator: " << jucator.nume_ << " | Locatie: " << (jucator.inBaza_ ? "In baza" : "In padure (PERICOL NOAPTEA)") << " | Actiuni ramase: " << jucator.actiuniRamase_ << "/" << jucator.cfg_.maxActiuniZi << "\n";
    os << jucator.inventar_ << "\n";
    return os;
}