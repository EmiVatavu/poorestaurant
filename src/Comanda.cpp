#include "Comanda.h"
#include "FelPrincipal.h"
#include "Desert.h"
#include "Bautura.h"
#include "RestaurantExceptions.h"
#include "Ingredient.h"
#include <iomanip>
#include <map>

int Comanda::contorComenzi = 0;

Comanda::Comanda(double bacsisProcent)
    : idComanda(++contorComenzi), status("In preparare"), bacsisProcent(bacsisProcent) {
    if (bacsisProcent < 0) {
        this->bacsisProcent = 0;
    }
}

void Comanda::elibereazaMemorie() {
    for (Produs* p : produseComandate) {
        delete p;
    }
    produseComandate.clear();
}

void Comanda::copiazaDin(const Comanda& other) {
    produseComandate.reserve(other.produseComandate.size());
    for (Produs* p : other.produseComandate) {
        produseComandate.push_back(p->clone());
    }
}

Comanda::~Comanda() {
    elibereazaMemorie();
}

Comanda::Comanda(const Comanda& other)
    : idComanda(other.idComanda), status(other.status), bacsisProcent(other.bacsisProcent) {
    copiazaDin(other);
}

Comanda& Comanda::operator=(const Comanda& other) {
    if (this != &other) {
        elibereazaMemorie();
        idComanda = other.idComanda;
        status = other.status;
        bacsisProcent = other.bacsisProcent;
        copiazaDin(other);
    }
    return *this;
}

Comanda::Comanda(Comanda&& other) noexcept
    : idComanda(other.idComanda), produseComandate(std::move(other.produseComandate)),
      status(std::move(other.status)), bacsisProcent(other.bacsisProcent) {
    other.produseComandate.clear();
}

Comanda& Comanda::operator=(Comanda&& other) noexcept {
    if (this != &other) {
        elibereazaMemorie();
        idComanda = other.idComanda;
        produseComandate = std::move(other.produseComandate);
        status = std::move(other.status);
        bacsisProcent = other.bacsisProcent;
        other.produseComandate.clear();
    }
    return *this;
}

void Comanda::adaugaProdus(const Produs* p) {
    if (p == nullptr) return;
    produseComandate.push_back(p->clone());
}

int Comanda::getIdComanda() const {
    return idComanda;
}

std::string Comanda::getStatus() const {
    return status;
}

double Comanda::getBacsisProcent() const {
    return bacsisProcent;
}

const std::vector<Produs*>& Comanda::getProduseComandate() const {
    return produseComandate;
}

void Comanda::setStatus(const std::string& status) {
    this->status = status;
}

void Comanda::setBacsisProcent(double procent) {
    if (procent >= 0) {
        bacsisProcent = procent;
    }
}

double Comanda::calculeazaSubtotal() const {
    double subtotal = 0;
    for (const Produs* p : produseComandate) {
        double pretProdus = p->calculeazaPret();
        
        const Desert* desertPtr = dynamic_cast<const Desert*>(p);
        if (desertPtr != nullptr) {
            pretProdus *= 0.90;
        }
        
        subtotal += pretProdus;
    }
    return subtotal;
}

double Comanda::calculeazaTotal() const {
    double totalCuTVA = 0;
    for (const Produs* p : produseComandate) {
        double pretProdus = p->calculeazaPret();
        
        const Desert* desertPtr = dynamic_cast<const Desert*>(p);
        if (desertPtr != nullptr) {
            pretProdus *= 0.90;
        }

        double tvaProcent = 0.09;
        const Bautura* bauturaPtr = dynamic_cast<const Bautura*>(p);
        if (bauturaPtr != nullptr && bauturaPtr->getContineAlcool()) {
            tvaProcent = 0.19;
        }

        totalCuTVA += pretProdus * (1.0 + tvaProcent);
    }
    
    double totalFinal = totalCuTVA * (1.0 + (bacsisProcent / 100.0));
    return totalFinal;
}

void Comanda::proceseazaComanda() {
    if (status == "Finalizata") {
        throw RestaurantException("Eroare comanda: Comanda este deja finalizata.");
    }
    if (status == "Anulata") {
        throw RestaurantException("Eroare comanda: Comanda este anulata si nu poate fi procesata.");
    }
    if (produseComandate.empty()) {
        throw RestaurantException("Eroare comanda: Nu se poate procesa o comanda fara produse.");
    }

    std::map<Ingredient*, double> totalNecesare;
    for (const Produs* p : produseComandate) {
        auto necesareProdus = p->getIngredienteNecesare();
        for (const auto& pair : necesareProdus) {
            Ingredient* ing = pair.first;
            double cantitate = pair.second;
            totalNecesare[ing] += cantitate;
        }
    }

    for (const auto& pair : totalNecesare) {
        Ingredient* ing = pair.first;
        double necesar = pair.second;
        if (ing->getCantitateStoc() < necesar) {
            throw StocInsuficientException(ing->getNume(), ing->getCantitateStoc(), necesar);
        }
    }

    for (const auto& pair : totalNecesare) {
        Ingredient* ing = pair.first;
        double necesar = pair.second;
        ing->consumaStoc(necesar);
    }

    status = "Finalizata";
}

void Comanda::tiparesteBon(std::ostream& os) const {
    os << "\n========================================= BON FISCAL =========================================\n";
    os << " Comanda ID: " << idComanda << " | Status: " << status << "\n";
    os << "-----------------------------------------------------------------------------------------------\n";
    
    os << std::fixed << std::setprecision(2);
    double subtotalTotal = 0;
    double tvaTotal = 0;

    for (const Produs* p : produseComandate) {
        double pretProdus = p->calculeazaPret();
        double discount = 0;

        const Desert* desertPtr = dynamic_cast<const Desert*>(p);
        if (desertPtr != nullptr) {
            discount = pretProdus * 0.10;
            pretProdus *= 0.90;
        }

        double tvaProcent = 0.09;
        const Bautura* bauturaPtr = dynamic_cast<const Bautura*>(p);
        if (bauturaPtr != nullptr && bauturaPtr->getContineAlcool()) {
            tvaProcent = 0.19;
        }

        double valoareTVA = pretProdus * tvaProcent;
        subtotalTotal += pretProdus;
        tvaTotal += valoareTVA;

        os << " " << std::left << std::setw(25) << p->getNume()
           << " | Tip: " << std::setw(13) << p->getTip()
           << " | Pret: " << std::right << std::setw(6) << (pretProdus + discount) << " RON";
        
        if (discount > 0) {
            os << " (Discount HH: -" << discount << " RON)";
        } else {
            os << "                      ";
        }
        
        os << " | TVA (" << std::setw(2) << (int)(tvaProcent * 100) << "%): " << std::setw(5) << valoareTVA << " RON\n";
    }

    os << "-----------------------------------------------------------------------------------------------\n";
    os << " Subtotal (fara TVA, cu discount): " << std::right << std::setw(8) << subtotalTotal << " RON\n";
    os << " Total TVA:                        " << std::right << std::setw(8) << tvaTotal << " RON\n";
    os << " Total (cu TVA):                   " << std::right << std::setw(8) << (subtotalTotal + tvaTotal) << " RON\n";
    os << " Bacsis (" << (int)bacsisProcent << "%):                      " << std::right << std::setw(8) << ((subtotalTotal + tvaTotal) * (bacsisProcent / 100.0)) << " RON\n";
    os << "-----------------------------------------------------------------------------------------------\n";
    os << " TOTAL GENERAL:                    " << std::right << std::setw(8) << calculeazaTotal() << " RON\n";
    os << "===============================================================================================\n";
}

int Comanda::getNumarTotalComenzi() {
    return contorComenzi;
}
