#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>
#include <iostream>

class Ingredient {
private:
    std::string nume;
    double cantitateStoc;
    std::string unitateMasura;

public:
    Ingredient(const std::string& nume, double cantitateStoc, const std::string& unitateMasura);

    std::string getNume() const;
    double getCantitateStoc() const;
    std::string getUnitateMasura() const;

    void adaugaStoc(double cantitate);
    void consumaStoc(double cantitate);

    friend std::ostream& operator<<(std::ostream& os, const Ingredient& ing);
};

#endif
