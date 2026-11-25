#include <iostream>
#include <stdexcept>
#include <string>
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
        unsigned int seed = 42;
        if (!(std::cin >> numeJucator >> seed)) {
            numeJucator = "Supravietuitor";
        }

        Joc joc("assets/config.txt", "assets/resurse.txt", "assets/zile.txt", numeJucator, seed);
        std::cout << joc << "\n";
        joc.ruleaza();
    } catch (const std::exception& e) {
        std::cerr << "Eroare critica: " << e.what() << "\n";
        return 1;
    }
    return 0;
}