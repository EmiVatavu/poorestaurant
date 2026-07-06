#include "Restaurant.h"
#include "FelPrincipal.h"
#include "Desert.h"
#include "Bautura.h"
#include "RestaurantExceptions.h"
#include <iostream>
#include <iomanip>

double Restaurant::totalIncasari = 0.0;

Restaurant::Restaurant() {}

void Restaurant::elibereazaMemorie() {
    for (Ingredient* ing : inventar) {
        delete ing;
    }
    inventar.clear();
}

Restaurant::~Restaurant() {
    elibereazaMemorie();
}

void Restaurant::initializareDate() {
    adaugaIngredient("Carne de vita", 5000, "g");
    adaugaIngredient("Chifla burger", 20, "buc");
    adaugaIngredient("Cartofi", 10000, "g");
    adaugaIngredient("Rosie", 3000, "g");
    adaugaIngredient("Salata", 1000, "g");
    adaugaIngredient("Ciocolata", 2000, "g");
    adaugaIngredient("Lapte", 5000, "ml");
    adaugaIngredient("Faina", 5000, "g");
    adaugaIngredient("Zahar", 3000, "g");
    adaugaIngredient("Oua", 50, "buc");
    adaugaIngredient("Ulei", 5000, "ml");
    
    adaugaIngredient("Bere Sticla 0.5L", 15, "buc");
    adaugaIngredient("Vin Sticla 0.75L", 10, "buc");
    adaugaIngredient("Coca-Cola Doza", 30, "buc");
    adaugaIngredient("Apa Plata Sticla", 40, "buc");

    std::vector<std::pair<Ingredient*, double>> ingBurger = {
        {gasesteIngredient("Carne de vita"), 150},
        {gasesteIngredient("Chifla burger"), 1},
        {gasesteIngredient("Rosie"), 30},
        {gasesteIngredient("Salata"), 10}
    };
    std::vector<std::pair<Ingredient*, double>> ingCartofi = {
        {gasesteIngredient("Cartofi"), 200},
        {gasesteIngredient("Ulei"), 30}
    };
    std::vector<std::pair<Ingredient*, double>> ingBurgerVeg = {
        {gasesteIngredient("Chifla burger"), 1},
        {gasesteIngredient("Rosie"), 50},
        {gasesteIngredient("Salata"), 20}
    };

    adaugaProdusInMeniu(new FelPrincipal(1, "Burger de Vita", 30.0, ingBurger, 15, false));
    adaugaProdusInMeniu(new FelPrincipal(2, "Portie Cartofi Prajiti", 10.0, ingCartofi, 8, true));
    adaugaProdusInMeniu(new FelPrincipal(3, "Burger Vegetarian", 28.0, ingBurgerVeg, 10, true));

    std::vector<std::pair<Ingredient*, double>> ingLavaCake = {
        {gasesteIngredient("Ciocolata"), 100},
        {gasesteIngredient("Faina"), 30},
        {gasesteIngredient("Zahar"), 40},
        {gasesteIngredient("Oua"), 1}
    };
    std::vector<std::pair<Ingredient*, double>> ingClatite = {
        {gasesteIngredient("Faina"), 50},
        {gasesteIngredient("Lapte"), 100},
        {gasesteIngredient("Oua"), 1},
        {gasesteIngredient("Ciocolata"), 50}
    };

    adaugaProdusInMeniu(new Desert(4, "Chocolate Lava Cake", 20.0, ingLavaCake, 45.0, true));
    adaugaProdusInMeniu(new Desert(5, "Clatite cu Ciocolata", 16.0, ingClatite, 30.0, true));

    adaugaProdusInMeniu(new Bautura(6, "Bere Craft", 12.0, 0.5, true, 5.0, gasesteIngredient("Bere Sticla 0.5L")));
    adaugaProdusInMeniu(new Bautura(7, "Pahar Vin Rosu", 22.0, 0.15, true, 12.5, gasesteIngredient("Vin Sticla 0.75L")));
    adaugaProdusInMeniu(new Bautura(8, "Coca-Cola Doza", 7.0, 0.33, false, 0.0, gasesteIngredient("Coca-Cola Doza")));
    adaugaProdusInMeniu(new Bautura(9, "Apa Plata", 5.0, 0.5, false, 0.0, gasesteIngredient("Apa Plata Sticla")));
}

void Restaurant::adaugaIngredient(const std::string& nume, double cantitate, const std::string& unitate) {
    for (Ingredient* ing : inventar) {
        if (ing->getNume() == nume) {
            ing->adaugaStoc(cantitate);
            return;
        }
    }
    inventar.push_back(new Ingredient(nume, cantitate, unitate));
}

void Restaurant::modificaStocIngredient(const std::string& nume, double delta) {
    Ingredient* ing = gasesteIngredient(nume);
    if (delta > 0) {
        ing->adaugaStoc(delta);
    } else {
        ing->consumaStoc(-delta);
    }
}

Ingredient* Restaurant::gasesteIngredient(const std::string& nume) const {
    for (Ingredient* ing : inventar) {
        if (ing->getNume() == nume) {
            return ing;
        }
    }
    throw RestaurantException("Eroare stoc: Ingredientul '" + nume + "' nu exista in inventar.");
}

void Restaurant::afiseazaInventar() const {
    if (inventar.empty()) {
        std::cout << "Inventarul este gol.\n";
    } else {
        for (const Ingredient* ing : inventar) {
            std::cout << " * " << *ing << "\n";
        }
    }
}

void Restaurant::adaugaProdusInMeniu(Produs* p) {
    meniu.adaugaProdus(p);
}

void Restaurant::stergeProdusDinMeniu(int id) {
    meniu.stergeProdus(id);
}

void Restaurant::afiseazaMeniu() const {
    meniu.afiseazaMeniu();
}

const Meniu& Restaurant::getMeniu() const {
    return meniu;
}

void Restaurant::plaseazaComanda(const std::vector<int>& idsProduse, double bacsis, int varstaClient) {
    if (idsProduse.empty()) {
        throw RestaurantException("Eroare comanda: Nu se poate plasa o comanda vida.");
    }

    Comanda comanda(bacsis);

    for (int id : idsProduse) {
        Produs* p = meniu.gasesteProdus(id);
        
        Bautura* b = dynamic_cast<Bautura*>(p);
        if (b != nullptr && b->getContineAlcool() && varstaClient < 18) {
            throw VarstaNeautorizataException(varstaClient);
        }

        comanda.adaugaProdus(p);
    }

    comanda.proceseazaComanda();

    comanda.tiparesteBon(std::cout);

    comenzi.push_back(comanda);

    totalIncasari += comanda.calculeazaTotal();
}

void Restaurant::afiseazaIstoricComenzi() const {
    if (comenzi.empty()) {
        std::cout << "Nu s-a inregistrat nicio comanda finalizata pana acum.\n";
    } else {
        std::cout << " Total comenzi inregistrate: " << comenzi.size() << "\n";
        std::cout << " Total incasari restaurant:  " << std::fixed << std::setprecision(2) << totalIncasari << " RON\n";
        std::cout << "------------------------------------------------------------------------\n";
        for (const Comanda& c : comenzi) {
            std::cout << " Comanda #" << c.getIdComanda() << " | Status: " << c.getStatus() 
                      << " | Produse: " << c.getProduseComandate().size()
                      << " | Total: " << c.calculeazaTotal() << " RON\n";
        }
    }
}

double Restaurant::getTotalIncasari() {
    return totalIncasari;
}

const std::vector<Comanda>& Restaurant::getComenzi() const {
    return comenzi;
}

const std::vector<Ingredient*>& Restaurant::getInventar() const {
    return inventar;
}
