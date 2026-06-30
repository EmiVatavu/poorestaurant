#ifndef FEL_PRINCIPAL_H
#define FEL_PRINCIPAL_H

#include "Produs.h"
#include "Ingredient.h"
#include <vector>
#include <utility>

class FelPrincipal : public Produs {
private:
    std::vector<std::pair<Ingredient*, double>> ingrediente;
    int timpPreparare;
    bool esteVegetarian;

public:
    FelPrincipal(int id, const std::string& nume, double pretBaza,
                 const std::vector<std::pair<Ingredient*, double>>& ingrediente,
                 int timpPreparare, bool esteVegetarian);

    double calculeazaPret() const override;
    std::string getTip() const override;
    Produs* clone() const override;
    void afiseaza(std::ostream& os) const override;

    std::vector<std::pair<Ingredient*, double>> getIngredienteNecesare() const override;

    int getTimpPreparare() const;
    bool getEsteVegetarian() const;
    const std::vector<std::pair<Ingredient*, double>>& getIngrediente() const;
};

#endif
