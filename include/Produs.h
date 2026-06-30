#ifndef PRODUS_H
#define PRODUS_H

#include <string>
#include <iostream>
#include <vector>
#include <utility>

class Produs {
protected:
    int id;
    std::string nume;
    double pretBaza;

public:
    Produs(int id, const std::string& nume, double pretBaza);
    virtual ~Produs();

    int getId() const;
    std::string getNume() const;
    double getPretBaza() const;
    void setPretBaza(double pret);

    virtual double calculeazaPret() const = 0;
    virtual std::string getTip() const = 0;
    virtual Produs* clone() const = 0;
    virtual std::vector<std::pair<class Ingredient*, double>> getIngredienteNecesare() const = 0;

    virtual void afiseaza(std::ostream& os) const;

    friend std::ostream& operator<<(std::ostream& os, const Produs& p);
};

#endif
