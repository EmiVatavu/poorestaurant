#include "FelPrincipal.h"
#include <iomanip>

FelPrincipal::FelPrincipal(int id, const std::string& nume, double pretBaza,
                             const std::vector<std::pair<Ingredient*, double>>& ingrediente,
                             int timpPreparare, bool esteVegetarian)
    : Produs(id, nume, pretBaza), ingrediente(ingrediente),
      timpPreparare(timpPreparare), esteVegetarian(esteVegetarian) {
}

double FelPrincipal::calculeazaPret() const {
    return pretBaza + (timpPreparare * 0.2);
}

std::string FelPrincipal::getTip() const {
    return "Fel Principal";
}

Produs* FelPrincipal::clone() const {
    return new FelPrincipal(*this);
}

void FelPrincipal::afiseaza(std::ostream& os) const {
    Produs::afiseaza(os);
    os << " | Timp prep: " << timpPreparare << " min | Veg: " << (esteVegetarian ? "Da" : "Nu");
    os << "\n   Ingrediente: ";
    if (ingrediente.empty()) {
        os << "Niciunul (pre-ambalat)";
    } else {
        for (size_t i = 0; i < ingrediente.size(); ++i) {
            os << ingrediente[i].first->getNume() << " (" << ingrediente[i].second << " " << ingrediente[i].first->getUnitateMasura() << ")";
            if (i < ingrediente.size() - 1) os << ", ";
        }
    }
}

std::vector<std::pair<Ingredient*, double>> FelPrincipal::getIngredienteNecesare() const {
    return ingrediente;
}

int FelPrincipal::getTimpPreparare() const {
    return timpPreparare;
}

bool FelPrincipal::getEsteVegetarian() const {
    return esteVegetarian;
}

const std::vector<std::pair<Ingredient*, double>>& FelPrincipal::getIngrediente() const {
    return ingrediente;
}
