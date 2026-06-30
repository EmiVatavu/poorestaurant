#ifndef COMANDA_H
#define COMANDA_H

#include "Produs.h"
#include <vector>
#include <iostream>

class Comanda {
private:
    int idComanda;
    std::vector<Produs*> produseComandate;
    std::string status;
    double bacsisProcent;

    static int contorComenzi;

    void elibereazaMemorie();
    void copiazaDin(const Comanda& other);

public:
    explicit Comanda(double bacsisProcent = 10.0);

    ~Comanda();
    Comanda(const Comanda& other);
    Comanda& operator=(const Comanda& other);
    Comanda(Comanda&& other) noexcept;
    Comanda& operator=(Comanda&& other) noexcept;

    void adaugaProdus(const Produs* p);
    
    int getIdComanda() const;
    std::string getStatus() const;
    double getBacsisProcent() const;
    const std::vector<Produs*>& getProduseComandate() const;

    void setStatus(const std::string& status);
    void setBacsisProcent(double procent);

    double calculeazaSubtotal() const;
    double calculeazaTotal() const;
    void proceseazaComanda();
    
    void tiparesteBon(std::ostream& os) const;

    static int getNumarTotalComenzi();
};

#endif
