#ifndef RESTAURANT_EXCEPTIONS_H
#define RESTAURANT_EXCEPTIONS_H

#include <stdexcept>
#include <string>

class RestaurantException : public std::runtime_error {
public:
    explicit RestaurantException(const std::string& message)
        : std::runtime_error(message) {}
};

class StocInsuficientException : public RestaurantException {
public:
    explicit StocInsuficientException(const std::string& ingredient, double disponibil, double necesar)
        : RestaurantException("Eroare stoc: Ingredientul '" + ingredient + 
                              "' are stoc insuficient. Disponibil: " + std::to_string(disponibil) + 
                              ", Necesar: " + std::to_string(necesar)) {}
};

class ProdusNegasitException : public RestaurantException {
public:
    explicit ProdusNegasitException(int id)
        : RestaurantException("Eroare meniu: Produsul cu ID-ul " + std::to_string(id) + " nu a fost gasit.") {}
};

class PretInvalidException : public RestaurantException {
public:
    explicit PretInvalidException(double pret)
        : RestaurantException("Eroare date: Pretul introdus (" + std::to_string(pret) + ") este invalid (trebuie sa fie > 0).") {}
};

class VarstaNeautorizataException : public RestaurantException {
public:
    explicit VarstaNeautorizataException(int varsta)
        : RestaurantException("Eroare legalitate: Clientul are varsta de " + std::to_string(varsta) + 
                              " ani. Vanzarea de bauturi alcoolice este interzisa persoanelor sub 18 ani!") {}
};

class InputInvalidException : public RestaurantException {
public:
    explicit InputInvalidException(const std::string& camp)
        : RestaurantException("Eroare date: Valoarea introdusa pentru campul '" + camp + "' este invalida.") {}
};

#endif // RESTAURANT_EXCEPTIONS_H
