#include "Ingredient.h"
#include "RestaurantExceptions.h"

Ingredient::Ingredient(const std::string& nume, double cantitateStoc, const std::string& unitateMasura)
    : nume(nume), cantitateStoc(cantitateStoc), unitateMasura(unitateMasura) {
    if (cantitateStoc < 0) {
        this->cantitateStoc = 0;
    }
}

std::string Ingredient::getNume() const {
    return nume;
}

double Ingredient::getCantitateStoc() const {
    return cantitateStoc;
}

std::string Ingredient::getUnitateMasura() const {
    return unitateMasura;
}

void Ingredient::adaugaStoc(double cantitate) {
    if (cantitate > 0) {
        cantitateStoc += cantitate;
    }
}

void Ingredient::consumaStoc(double cantitate) {
    if (cantitate <= 0) return;
    if (cantitateStoc < cantitate) {
        throw StocInsuficientException(nume, cantitateStoc, cantitate);
    }
    cantitateStoc -= cantitate;
}

std::ostream& operator<<(std::ostream& os, const Ingredient& ing) {
    os << ing.nume << ": " << ing.cantitateStoc << " " << ing.unitateMasura;
    return os;
}
