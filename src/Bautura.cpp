#include "Bautura.h"

Bautura::Bautura(int id, const std::string& nume, double pretBaza,
                 double volum, bool contineAlcool, double procentAlcool,
                 Ingredient* stocSticla)
    : Produs(id, nume, pretBaza), volum(volum),
      contineAlcool(contineAlcool), procentAlcool(contineAlcool ? procentAlcool : 0.0),
      stocSticla(stocSticla) {
}

double Bautura::calculeazaPret() const {
    if (contineAlcool) {
        return pretBaza * 1.20;
    }
    return pretBaza;
}

std::string Bautura::getTip() const {
    return "Bautura";
}

Produs* Bautura::clone() const {
    return new Bautura(*this);
}

void Bautura::afiseaza(std::ostream& os) const {
    Produs::afiseaza(os);
    os << " | Volum: " << volum << "L | Alcool: ";
    if (contineAlcool) {
        os << procentAlcool << "%";
    } else {
        os << "Fara alcool";
    }
    if (stocSticla != nullptr) {
        os << " | Stoc: " << stocSticla->getCantitateStoc() << " buc";
    } else {
        os << " | Stoc: Indisponibil";
    }
}

std::vector<std::pair<Ingredient*, double>> Bautura::getIngredienteNecesare() const {
    std::vector<std::pair<Ingredient*, double>> necesare;
    if (stocSticla != nullptr) {
        necesare.push_back({stocSticla, 1.0});
    }
    return necesare;
}

double Bautura::getVolum() const {
    return volum;
}

bool Bautura::getContineAlcool() const {
    return contineAlcool;
}

double Bautura::getProcentAlcool() const {
    return procentAlcool;
}

Ingredient* Bautura::getStocSticla() const {
    return stocSticla;
}
