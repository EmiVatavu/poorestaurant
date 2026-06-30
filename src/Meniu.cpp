#include "Meniu.h"
#include "RestaurantExceptions.h"
#include <iostream>

Meniu::Meniu() {}

void Meniu::elibereazaMemorie() {
    for (Produs* p : produse) {
        delete p;
    }
    produse.clear();
}

void Meniu::copiazaDin(const Meniu& other) {
    produse.reserve(other.produse.size());
    for (Produs* p : other.produse) {
        produse.push_back(p->clone());
    }
}

Meniu::~Meniu() {
    elibereazaMemorie();
}

Meniu::Meniu(const Meniu& other) {
    copiazaDin(other);
}

Meniu& Meniu::operator=(const Meniu& other) {
    if (this != &other) {
        elibereazaMemorie();
        copiazaDin(other);
    }
    return *this;
}

Meniu::Meniu(Meniu&& other) noexcept : produse(std::move(other.produse)) {
    other.produse.clear();
}

Meniu& Meniu::operator=(Meniu&& other) noexcept {
    if (this != &other) {
        elibereazaMemorie();
        produse = std::move(other.produse);
        other.produse.clear();
    }
    return *this;
}

void Meniu::adaugaProdus(Produs* p) {
    if (p == nullptr) return;
    for (Produs* existing : produse) {
        if (existing->getId() == p->getId()) {
            throw RestaurantException("Eroare adaugare: Exista deja un produs cu ID-ul " + std::to_string(p->getId()) + " in meniu.");
        }
    }
    produse.push_back(p);
}

void Meniu::stergeProdus(int id) {
    for (auto it = produse.begin(); it != produse.end(); ++it) {
        if ((*it)->getId() == id) {
            delete *it;
            produse.erase(it);
            return;
        }
    }
    throw ProdusNegasitException(id);
}

Produs* Meniu::gasesteProdus(int id) const {
    for (Produs* p : produse) {
        if (p->getId() == id) {
            return p;
        }
    }
    throw ProdusNegasitException(id);
}

void Meniu::afiseazaMeniu() const {
    std::cout << "\n=========================== MENIU RESTAURANT ===========================\n";
    if (produse.empty()) {
        std::cout << "Meniul este gol.\n";
    } else {
        for (const Produs* p : produse) {
            std::cout << *p << "\n";
        }
    }
    std::cout << "========================================================================\n";
}

const std::vector<Produs*>& Meniu::getProduse() const {
    return produse;
}
