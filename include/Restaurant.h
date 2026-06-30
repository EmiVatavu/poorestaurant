#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "Ingredient.h"
#include "Meniu.h"
#include "Comanda.h"
#include <vector>

class Restaurant {
private:
    std::vector<Ingredient*> inventar;
    Meniu meniu;
    std::vector<Comanda> comenzi;

    static double totalIncasari;

    void elibereazaMemorie();

public:
    Restaurant();
    ~Restaurant();

    Restaurant(const Restaurant&) = delete;
    Restaurant& operator=(const Restaurant&) = delete;

    void initializareDate();

    void adaugaIngredient(const std::string& nume, double cantitate, const std::string& unitate);
    void modificaStocIngredient(const std::string& nume, double delta);
    void afiseazaInventar() const;
    Ingredient* gasesteIngredient(const std::string& nume) const;

    void adaugaProdusInMeniu(Produs* p);
    void stergeProdusDinMeniu(int id);
    void afiseazaMeniu() const;
    const Meniu& getMeniu() const;

    void plaseazaComanda(const std::vector<int>& idsProduse, double bacsis, int varstaClient);
    void afiseazaIstoricComenzi() const;

    static double getTotalIncasari();
    const std::vector<Comanda>& getComenzi() const;
    const std::vector<Ingredient*>& getInventar() const;
};

#endif
