#ifndef BAUTURA_H
#define BAUTURA_H

#include "Produs.h"
#include "Ingredient.h"

class Bautura : public Produs {
private:
    double volum;
    bool contineAlcool;
    double procentAlcool;
    Ingredient* stocSticla;

public:
    Bautura(int id, const std::string& nume, double pretBaza,
            double volum, bool contineAlcool, double procentAlcool,
            Ingredient* stocSticla);

    double calculeazaPret() const override;
    std::string getTip() const override;
    Produs* clone() const override;
    void afiseaza(std::ostream& os) const override;

    std::vector<std::pair<Ingredient*, double>> getIngredienteNecesare() const override;

    double getVolum() const;
    bool getContineAlcool() const;
    double getProcentAlcool() const;
    Ingredient* getStocSticla() const;
};

#endif
