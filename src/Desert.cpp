#include "Desert.h"

Desert::Desert(int id, const std::string& nume, double pretBaza,
               const std::vector<std::pair<Ingredient*, double>>& ingrediente,
               double grameZahar, bool contineAlergeni)
    : Produs(id, nume, pretBaza), ingrediente(ingrediente),
      grameZahar(grameZahar), contineAlergeni(contineAlergeni) {
}

double Desert::calculeazaPret() const {
    return pretBaza;
}

std::string Desert::getTip() const {
    return "Desert";
}

Produs* Desert::clone() const {
    return new Desert(*this);
}

void Desert::afiseaza(std::ostream& os) const {
    Produs::afiseaza(os);
    os << " | Zahar: " << grameZahar << "g | Alergeni: " << (contineAlergeni ? "Da" : "Nu");
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

std::vector<std::pair<Ingredient*, double>> Desert::getIngredienteNecesare() const {
    return ingrediente;
}

double Desert::getGrameZahar() const {
    return grameZahar;
}

bool Desert::getContineAlergeni() const {
    return contineAlergeni;
}

const std::vector<std::pair<Ingredient*, double>>& Desert::getIngrediente() const {
    return ingrediente;
}
