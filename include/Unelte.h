//
// Created by andre on 24.11.2026.
//

#ifndef UNELTE_H
#define UNELTE_H

#include <iostream>
#include <string>

class Unelte {
public:
    explicit Unelte(std::string nume, int nivel = 1, int nivelMaxim = 3, int costLemn12 = 3, int costBlana12 = 2, int costLemn23 = 5, int costBlana23 = 4);

    const std::string& getNume() const;
    int getNivel() const;
    bool poateFiUpgradata() const;
    int getCostLemnUpgrade() const;
    int getCostBlanaUpgrade() const;

    bool upgrade();
    friend std::ostream& operator<<(std::ostream& os, const Unelte& unealta);

private:
    std::string nume_;
    int nivel_;
    int nivelMaxim_;
    int costLemn12_;
    int costBlana12_;
    int costLemn23_;
    int costBlana23_;
};

#endif //UNELTE_H
