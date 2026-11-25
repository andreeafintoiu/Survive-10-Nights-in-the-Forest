#include <iostream>
#include <stdexcept>
#include <string>
#include <chrono>
#include "Joc.h"
#include "Resursa.h"

namespace {

    void verificaRegulaCelor3SiExceptii() {
        Resursa r1("Lemn", "mixt", 5, 2);
        Resursa r2(r1);
        Resursa r3("Carbune", "combustibil", 15);
        r3 = r1;
        std::cout << "Instante Resursa active in test: " << Resursa::getNrInstante()
                  << " | Copie: " << r2 << " | Atribuire: " << r3 << "\n";

        try {
            Resursa invalida("Lemn", "mixt", -1);
        } catch (const std::invalid_argument& e) {
            std::cout << "Exceptie prinsa corect: " << e.what() << "\n";
        }
    }

} // namespace

int main() {
    try {
        verificaRegulaCelor3SiExceptii();

        std::string numeJucator;
        unsigned int seed = 999;
        std::cout << "Introdu numele tau si un seed (ex: Jucator 999): ";
        if (!(std::cin >> numeJucator >> seed)) {
            numeJucator = "Supravietuitor";
            seed = 999;
        }
        if (seed == 0)
            seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());

        Joc joc("assets/config.txt", "assets/resurse.txt", "assets/zile.txt", numeJucator, seed);
        std::cout << joc << "\n";
        joc.ruleaza();
    } catch (const std::exception& e) {
        std::cerr << "Eroare critica: " << e.what() << "\n";
        return 1;
    }
    return 0;
}