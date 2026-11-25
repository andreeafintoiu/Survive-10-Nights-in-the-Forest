#include "Joc.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

std::string Joc::citesteLinieUtila(std::ifstream& fin) {
    std::string linie;
    while (std::getline(fin, linie)) {
        if (!linie.empty() && linie[0] != '#')
            return linie;
    }
    throw std::runtime_error("Sfarsit neasteptat de fisier la citirea configurarii.");
}

ConfigJoc Joc::incarcaConfig(const std::string& caleFisier) {
    std::ifstream fin(caleFisier);
    if (!fin.is_open())
        throw std::runtime_error("Nu s-a putut deschide fisierul: " + caleFisier);

    ConfigJoc cfg{};

    {
        std::istringstream iss(citesteLinieUtila(fin));
        if (!(iss >> cfg.nivelFocInitial >> cfg.maximFoc >> cfg.bonusVictoriePct
                  >> cfg.penalizareInfrangerePct >> cfg.minimFocSupravietuire))
            throw std::runtime_error("Format invalid pe linia 1 din config.txt");
    }
    {
        std::istringstream iss(citesteLinieUtila(fin));
        if (!(iss >> cfg.cfgJucator.maxActiuniZi >> cfg.cfgJucator.sansaCarbune
                  >> cfg.cfgJucator.sansaCanistra >> cfg.cfgJucator.sansaNimic
                  >> cfg.cfgJucator.dropMinLupi >> cfg.cfgJucator.dropMaxLupi))
            throw std::runtime_error("Format invalid pe linia 2 din config.txt");
    }
    {
        std::istringstream iss(citesteLinieUtila(fin));
        if (!(iss >> cfg.nivelMaxUnealta >> cfg.costLemn12 >> cfg.costBlana12
                  >> cfg.costLemn23 >> cfg.costBlana23))
            throw std::runtime_error("Format invalid pe linia 3 din config.txt");
    }
    {
        std::istringstream iss(citesteLinieUtila(fin));
        if (!(iss >> cfg.cfgJucator.lemnMin[0] >> cfg.cfgJucator.lemnMax[0]
                  >> cfg.cfgJucator.lemnMin[1] >> cfg.cfgJucator.lemnMax[1]
                  >> cfg.cfgJucator.lemnMin[2] >> cfg.cfgJucator.lemnMax[2]))
            throw std::runtime_error("Format invalid pe linia 4 din config.txt");
    }

    return cfg;
}

std::vector<Resursa> Joc::incarcaResurse(const std::string& caleFisier) {
    std::ifstream fin(caleFisier);
    if (!fin.is_open())
        throw std::runtime_error("Nu s-a putut deschide fisierul: " + caleFisier);

    int nrResurse = 0;
    {
        std::istringstream iss(citesteLinieUtila(fin));
        if (!(iss >> nrResurse) || nrResurse <= 0)
            throw std::runtime_error("Numar invalid de resurse in " + caleFisier);
    }

    std::vector<Resursa> resurse;
    resurse.reserve(static_cast<std::size_t>(nrResurse));
    for (int i = 0; i < nrResurse; ++i) {
        std::istringstream iss(citesteLinieUtila(fin));
        std::string nume, tip;
        int valFoc = 0, cantitate = 0;
        if (!(iss >> nume >> tip >> valFoc >> cantitate))
            throw std::runtime_error("Date invalide pentru resursa din " + caleFisier);
        resurse.emplace_back(nume, tip, valFoc, cantitate);
    }
    return resurse;
}

std::vector<Zi> Joc::incarcaZile(const std::string& caleFisier) {
    std::ifstream fin(caleFisier);
    if (!fin.is_open())
        throw std::runtime_error("Nu s-a putut deschide fisierul: " + caleFisier);

    int nrZile = 0;
    {
        std::istringstream iss(citesteLinieUtila(fin));
        if (!(iss >> nrZile) || nrZile <= 0)
            throw std::runtime_error("Numar invalid de zile in " + caleFisier);
    }

    std::vector<Zi> zile;
    zile.reserve(static_cast<std::size_t>(nrZile));
    for (int i = 0; i < nrZile; ++i) {
        std::istringstream iss(citesteLinieUtila(fin));
        int nrZi = 0, scadere = 0, atac = 0, nivelNec = 0, negustor = 0;
        if (!(iss >> nrZi >> scadere >> atac >> nivelNec >> negustor))
            throw std::runtime_error("Date invalide pentru ziua din " + caleFisier);
        zile.emplace_back(nrZi, scadere, atac != 0, nivelNec, negustor != 0);
    }
    return zile;
}

Joc::Joc(const std::string& caleConfig,
         const std::string& caleResurse,
         const std::string& caleZile,
         const std::string& numeJucator,
         unsigned int seed)
    : cfg_(incarcaConfig(caleConfig)),
      foc_(cfg_.nivelFocInitial, cfg_.maximFoc),
      jucator_(
          numeJucator,
          Inventar(
              incarcaResurse(caleResurse),
              {
                  Unelte("Topor", 1, cfg_.nivelMaxUnealta, cfg_.costLemn12, cfg_.costBlana12, cfg_.costLemn23, cfg_.costBlana23),
                  Unelte("Pusca", 1, cfg_.nivelMaxUnealta, cfg_.costLemn12, cfg_.costBlana12, cfg_.costLemn23, cfg_.costBlana23)
              }),
          cfg_.cfgJucator),
      zile_(incarcaZile(caleZile)),
      rng_(seed) {}

void Joc::afiseazaMeniuZi(const Zi& zi) const {
    std::cout << "\n========================================\n";
    std::cout << zi << "\n";
    std::cout << foc_ << "\n";
    std::cout << jucator_;
    std::cout << "----------------------------------------\n";
    std::cout << "1. Taie lemne langa baza (costa 1 actiune, iesi in padure)\n";
    std::cout << "2. Exploreaza adancul padurii (costa 1 actiune, risc lupi)\n";
    std::cout << "3. Alimenteaza focul de tabara (te intoarce in baza)\n";
    std::cout << "4. Intoarce-te in baza (fara consum de actiune)\n";
    if (zi.areNegustorBlanuri())
        std::cout << "5. Viziteaza Negustorul de Blanuri (upgrade unelte)\n";
    std::cout << "0. Incheie ziua si treci la noapte\n";
    std::cout << "Alege optiunea: ";
}

void Joc::proceseazaNegustor() {
    jucator_.intoarceInBaza();
    std::cout << "\n--- NEGUSTORUL DE BLANURI ---\n";
    std::cout << "1. Upgrade Topor\n";
    std::cout << "2. Upgrade Pusca\n";
    std::cout << "0. Inapoi\n";
    std::cout << "Alegere: ";

    int opt = 0;
    if (!(std::cin >> opt)) {
        jocTerminat_ = true;
        return;
    }

    if (opt == 1) {
        std::cout << (jucator_.upgradeUnealta("Topor")
                          ? "Toporul a fost upgradat cu succes!\n"
                          : "Resurse insuficiente sau nivel maxim atins!\n");
    } else if (opt == 2) {
        std::cout << (jucator_.upgradeUnealta("Pusca")
                          ? "Pusca a fost upgradata cu succes!\n"
                          : "Resurse insuficiente sau nivel maxim atins!\n");
    }
}

void Joc::ruleaza() {
    std::cout << "=== SURVIVE " << zile_.size() << " NIGHTS IN THE FOREST ===\n";

    for (indexZiCurenta_ = 0; indexZiCurenta_ < zile_.size() && !jocTerminat_; ++indexZiCurenta_) {
        const Zi& zi = zile_[indexZiCurenta_];
        jucator_.reseteazaZi();

        bool ziIncheiata = false;
        while (!ziIncheiata && !jocTerminat_) {
            afiseazaMeniuZi(zi);
            int opt = 0;
            if (!(std::cin >> opt)) {
                jocTerminat_ = true;
                break;
            }

            if (opt == 1) {
                RezultatActiune rez = jucator_.taieLemne(rng_);
                if (rez.tip == TipRezultatActiune::FaraActiuni)
                    std::cout << "Nu mai ai actiuni de scavenge disponibile astazi!\n";
                else
                    std::cout << "Ai taiat lemne si ai obtinut " << rez.cantitate << " buc. de " << rez.numeResursa << ".\n";
            } else if (opt == 2) {
                RezultatActiune rez = jucator_.exploreazaPadure(rng_);
                if (rez.tip == TipRezultatActiune::FaraActiuni)
                    std::cout << "Nu mai ai actiuni de scavenge disponibile astazi!\n";
                else if (rez.tip == TipRezultatActiune::ResursaGasita)
                    std::cout << "Ai explorat padurea si ai gasit " << rez.cantitate << "x " << rez.numeResursa << "!\n";
                else if (rez.tip == TipRezultatActiune::NimicGasit)
                    std::cout << "Ai cautat prin padure, dar nu ai gasit nimic.\n";
                else if (rez.tip == TipRezultatActiune::IntalnireLupi)
                    if(rez.cantitate > 0)
                        std::cout << "RANDOM EVENT: Ai invins lupii si ai obtinut " << rez.cantitate << "x " << rez.numeResursa << "!\n";
                    else
                        std::cout << "RANDOM EVENT: Ai scapat cu greu de lupi, si nu ai reusit sa iei nicio blana.\n";
            } else if (opt == 3) {
                std::cout << "Ce resursa folosesti? (Lemn / Carbune / Canistra) si cate bucati: ";
                std::string res;
                int buc = 0;
                if (std::cin >> res >> buc) {
                    if (jucator_.alimenteazaFoc(foc_, res, buc))
                        std::cout << "Ai alimentat focul cu " << buc << "x " << res << "! " << foc_ << "\n";
                    else
                        std::cout << "Nu ai destule resurse sau resursa nu este combustibil!\n";
                }
            } else if (opt == 4) {
                jucator_.intoarceInBaza();
                std::cout << "Te-ai intors in siguranta in baza.\n";
            } else if (opt == 5) {
                if (zi.areNegustorBlanuri())
                    proceseazaNegustor();
                else
                    std::cout << "Negustorul nu este disponibil astazi!\n";
            } else if (opt == 0) {
                ziIncheiata = true;
            } else {
                std::cout << "Optiune invalida!\n";
            }
        }

        if (!jocTerminat_) {
            std::cout << "\n--- SE LASA NOAPTEA (" << zi.getNumarZi() << ") ---\n";
            RezultatNoapte rezNoapte = zi.proceseazaNoaptea(
                jucator_, foc_, cfg_.bonusVictoriePct, cfg_.penalizareInfrangerePct, cfg_.minimFocSupravietuire);

            if (rezNoapte == RezultatNoapte::PrinsDeCerb) {
                std::cout << "[GAME OVER] Ai ramas in padure dupa lasarea noptii! Cerbul mutant te-a prins!\n";
                jocTerminat_ = true;
            } else if (rezNoapte == RezultatNoapte::FocStins) {
                std::cout << "[GAME OVER] Focul de tabara s-a stins!\n";
                jocTerminat_ = true;
            } else if (rezNoapte == RezultatNoapte::InfrangereCultisti) {
                std::cout << "[GAME OVER] Cultistii au atacat si uneltele tale (nivel minim "
                          << jucator_.getNivelMinimUnelte() << ") nu au facut fata (necesar: "
                          << zi.getNivelNecesarCultisti() << ")!\n";
                jocTerminat_ = true;
            } else if (rezNoapte == RezultatNoapte::AtacRespins) {
                std::cout << "Ai respins atacul cultistilor! " << foc_ << "\n";
            } else {
                std::cout << "Ai supravietuit noptii! " << foc_ << "\n";
            }
        }
    }

    if (!jocTerminat_) {
        std::cout << "\n========================================\n";
        std::cout << "[VICTORIE!] Ai supravietuit tuturor celor " << zile_.size() << " nopti! Ai primit [Medalionul Supravietuitorului]! \n";
    }
}

std::ostream& operator<<(std::ostream& os, const Joc& joc) {
    os << "[Stare Joc - Ziua " << (joc.indexZiCurenta_ + 1) << "/" << joc.zile_.size() << "]\n"
       << joc.foc_ << "\n"
       << joc.jucator_;
    return os;
}