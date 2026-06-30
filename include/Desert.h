#ifndef DESERT_H
#define DESERT_H

#include "Produs.h"
#include "Ingredient.h"
#include <vector>
#include <utility>

class Desert : public Produs {
private:
    std::vector<std::pair<Ingredient*, double>> ingrediente;
    double grameZahar;
    bool contineAlergeni;

public:
    Desert(int id, const std::string& nume, double pretBaza,
           const std::vector<std::pair<Ingredient*, double>>& ingrediente,
           double grameZahar, bool contineAlergeni);

    double calculeazaPret() const override;
    std::string getTip() const override;
    Produs* clone() const override;
    void afiseaza(std::ostream& os) const override;

    std::vector<std::pair<Ingredient*, double>> getIngredienteNecesare() const override;

    double getGrameZahar() const;
    bool getContineAlergeni() const;
    const std::vector<std::pair<Ingredient*, double>>& getIngrediente() const;
};

#endif
