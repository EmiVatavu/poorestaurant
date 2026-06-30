#ifndef MENIU_H
#define MENIU_H

#include "Produs.h"
#include <vector>

class Meniu {
private:
    std::vector<Produs*> produse;

    void elibereazaMemorie();
    void copiazaDin(const Meniu& other);

public:
    Meniu();
    
    ~Meniu();
    Meniu(const Meniu& other);
    Meniu& operator=(const Meniu& other);
    Meniu(Meniu&& other) noexcept;
    Meniu& operator=(Meniu&& other) noexcept;

    void adaugaProdus(Produs* p);
    void stergeProdus(int id);
    Produs* gasesteProdus(int id) const;
    void afiseazaMeniu() const;

    const std::vector<Produs*>& getProduse() const;
};

#endif
