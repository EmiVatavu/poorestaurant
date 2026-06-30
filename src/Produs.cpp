#include "Produs.h"
#include "RestaurantExceptions.h"

Produs::Produs(int id, const std::string& nume, double pretBaza)
    : id(id), nume(nume), pretBaza(pretBaza) {
    if (pretBaza < 0) {
        throw PretInvalidException(pretBaza);
    }
}

Produs::~Produs() {
}

int Produs::getId() const {
    return id;
}

std::string Produs::getNume() const {
    return nume;
}

double Produs::getPretBaza() const {
    return pretBaza;
}

void Produs::setPretBaza(double pret) {
    if (pret < 0) {
        throw PretInvalidException(pret);
    }
    pretBaza = pret;
}

void Produs::afiseaza(std::ostream& os) const {
    os << "[" << getTip() << "] ID: " << id << " | " << nume << " | Pret Baza: " << pretBaza << " RON";
}

std::ostream& operator<<(std::ostream& os, const Produs& p) {
    p.afiseaza(os);
    return os;
}
