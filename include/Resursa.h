#ifndef RESURSA_H
#define RESURSA_H

#include <iostream>
#include <string>

class Resursa {
public:
    Resursa(std::string nume, std::string tip, int valoareFoc, int cantitate = 0);
    Resursa(const Resursa& alta);
    Resursa& operator=(const Resursa& alta);
    ~Resursa();

    const std::string& getNume() const;
    const std::string& getTip() const;
    int getValoareFoc() const;
    int getCantitate() const;
    static int getNrInstante();

    void adauga(int bucati);
    bool consuma(int bucati);

    friend std::ostream& operator<<(std::ostream& os, const Resursa& r);

private:
    std::string nume_;
    std::string tip_;
    int valoareFoc_;
    int cantitate_;
    static int nrInstante_;
};
#endif //RESURSA_H
