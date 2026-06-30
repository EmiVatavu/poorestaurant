#include "Restaurant.h"
#include "RestaurantExceptions.h"
#include "FelPrincipal.h"
#include "Desert.h"
#include "Bautura.h"
#include <iostream>
#include <vector>
#include <limits>
#include <string>

void curataInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void afiseazaMeniuOptiuni() {
    std::cout << "\n=================== GESTIUNE RESTAURANT ===================\n";
    std::cout << " 1. Afiseaza Meniul Restaurantului\n";
    std::cout << " 2. Plaseaza o Comanda Noua\n";
    std::cout << " 3. Vizualizeaza Stocul de Ingrediente\n";
    std::cout << " 4. Actualizeaza Stocul (Aprovizionare)\n";
    std::cout << " 5. Administrare Catalog Meniu (Adaugare/Stergere)\n";
    std::cout << " 6. Vizualizeaza Incasari si Istoric Comenzi\n";
    std::cout << " 0. Iesire din Aplicatie\n";
    std::cout << "===========================================================\n";
    std::cout << "Alegeti o optiune: ";
}

int main() {
    std::cout << std::boolalpha;

    Restaurant restaurant;
    
    std::cout << "Se incarca datele restaurantului...\n";
    restaurant.initializareDate();
    std::cout << "Aplicatia a pornit cu succes!\n";

    int optiune = -1;
    while (true) {
        afiseazaMeniuOptiuni();
        if (!(std::cin >> optiune)) {
            std::cout << "Intrare invalida! Va rugam introduceti o cifra corespunzatoare optiunii.\n";
            curataInput();
            continue;
        }

        if (optiune == 0) {
            std::cout << "La revedere! Va mai asteptam la restaurantul nostru.\n";
            break;
        }

        try {
            switch (optiune) {
                case 1: {
                    restaurant.afiseazaMeniu();
                    break;
                }
                case 2: {
                    restaurant.afiseazaMeniu();
                    std::cout << "\n--- PLASARE COMANDA NOUA ---\n";
                    std::vector<int> idsProduse;
                    int id = -1;
                    
                    std::cout << "Introduceti ID-urile produselor dorite (apasati 0 pentru a termina selectia):\n";
                    while (true) {
                        std::cout << "ID Produs: ";
                        if (!(std::cin >> id)) {
                            std::cout << "Eroare: Va rugam sa introduceti un ID valid format din cifre.\n";
                            curataInput();
                            continue;
                        }
                        if (id == 0) break;
                        if (id < 0) {
                            std::cout << "ID-ul nu poate fi negativ!\n";
                            continue;
                        }
                        idsProduse.push_back(id);
                    }

                    if (idsProduse.empty()) {
                        std::cout << "Comanda a fost anulata (niciun produs selectat).\n";
                        break;
                    }

                    double bacsis = 10.0;
                    std::cout << "Introduceti bacsisul procentual (implicit 10%): ";
                    if (!(std::cin >> bacsis)) {
                        std::cout << "Date incorecte! Se va folosi bacsisul implicit de 10%.\n";
                        bacsis = 10.0;
                        curataInput();
                    }

                    int varsta = 18;
                    std::cout << "Introduceti varsta clientului (necesara pentru verificarea alcoolului): ";
                    if (!(std::cin >> varsta)) {
                        std::cout << "Date incorecte! Se va considera varsta implicita de 18 ani.\n";
                        varsta = 18;
                        curataInput();
                    }

                    std::cout << "\nProcesare comanda in curs...\n";
                    restaurant.plaseazaComanda(idsProduse, bacsis, varsta);
                    std::cout << "\nComanda a fost procesata si inregistrata cu succes!\n";
                    break;
                }
                case 3: {
                    restaurant.afiseazaInventar();
                    break;
                }
                case 4: {
                    std::cout << "\n--- ACTUALIZARE STOC INGREDIENT ---\n";
                    std::string nume;
                    double cantitate = 0;
                    std::cout << "Introduceti numele ingredientului: ";
                    std::cin.ignore();
                    std::getline(std::cin, nume);
                    
                    std::cout << "Introduceti cantitatea de adaugat (pozitiva) sau consumat (negativa): ";
                    if (!(std::cin >> cantitate)) {
                        throw InputInvalidException("cantitate stoc");
                    }

                    restaurant.modificaStocIngredient(nume, cantitate);
                    std::cout << "Stocul ingredientului '" << nume << "' a fost actualizat cu succes!\n";
                    break;
                }
                case 5: {
                    std::cout << "\n--- ADMINISTRARE CATALOG MENIU ---\n";
                    std::cout << "1. Adauga un produs nou in meniu\n";
                    std::cout << "2. Sterge un produs din meniu\n";
                    std::cout << "Alegeti sub-optiunea (1 sau 2): ";
                    int subOptiune = 0;
                    if (!(std::cin >> subOptiune)) {
                        curataInput();
                        throw InputInvalidException("subOptiune administrare meniu");
                    }

                    if (subOptiune == 1) {
                        std::cout << "\nTipuri de produs:\n";
                        std::cout << " 1. Fel Principal\n";
                        std::cout << " 2. Desert\n";
                        std::cout << " 3. Bautura\n";
                        std::cout << "Alegeti tipul de produs (1-3): ";
                        int tipProdus = 0;
                        if (!(std::cin >> tipProdus) || tipProdus < 1 || tipProdus > 3) {
                            curataInput();
                            throw InputInvalidException("tip produs");
                        }

                        int newId = 0;
                        std::cout << "Introduceti un ID unic: ";
                        if (!(std::cin >> newId)) {
                            curataInput();
                            throw InputInvalidException("id produs");
                        }

                        std::string numeProdus;
                        std::cout << "Introduceti numele produsului: ";
                        std::cin.ignore();
                        std::getline(std::cin, numeProdus);

                        double pretBaza = 0.0;
                        std::cout << "Introduceti pretul de baza (RON): ";
                        if (!(std::cin >> pretBaza)) {
                            curataInput();
                            throw InputInvalidException("pret baza");
                        }

                        if (tipProdus == 1) {
                            int timpPrep = 0;
                            std::cout << "Timp de preparare (minute): ";
                            if (!(std::cin >> timpPrep)) {
                                curataInput();
                                throw InputInvalidException("timp preparare");
                            }

                            std::string vegInput;
                            std::cout << "Este vegetarian? (da/nu): ";
                            std::cin >> vegInput;
                            bool veg = (vegInput == "da" || vegInput == "DA" || vegInput == "y");

                            std::vector<std::pair<Ingredient*, double>> ingRecipe;
                            restaurant.adaugaProdusInMeniu(new FelPrincipal(newId, numeProdus, pretBaza, ingRecipe, timpPrep, veg));
                        }
                        else if (tipProdus == 2) {
                            double zahar = 0.0;
                            std::cout << "Grame zahar: ";
                            if (!(std::cin >> zahar)) {
                                curataInput();
                                throw InputInvalidException("grame zahar");
                            }

                            std::string algInput;
                            std::cout << "Contine alergeni? (da/nu): ";
                            std::cin >> algInput;
                            bool alg = (algInput == "da" || algInput == "DA" || algInput == "y");

                            std::vector<std::pair<Ingredient*, double>> ingRecipe;
                            restaurant.adaugaProdusInMeniu(new Desert(newId, numeProdus, pretBaza, ingRecipe, zahar, alg));
                        }
                        else if (tipProdus == 3) {
                            double volum = 0.5;
                            std::cout << "Volum (L): ";
                            if (!(std::cin >> volum)) {
                                curataInput();
                                throw InputInvalidException("volum bautura");
                            }

                            std::string alcInput;
                            std::cout << "Contine alcool? (da/nu): ";
                            std::cin >> alcInput;
                            bool alc = (alcInput == "da" || alcInput == "DA" || alcInput == "y");

                            double alcoolemie = 0.0;
                            if (alc) {
                                std::cout << "Procent alcool (%): ";
                                if (!(std::cin >> alcoolemie)) {
                                    curataInput();
                                    throw InputInvalidException("procent alcool");
                                }
                            }

                            Ingredient* stocItem = nullptr;
                            try {
                                stocItem = restaurant.gasesteIngredient(numeProdus);
                            } catch (...) {
                                restaurant.adaugaIngredient(numeProdus, 10, "buc");
                                stocItem = restaurant.gasesteIngredient(numeProdus);
                            }

                            restaurant.adaugaProdusInMeniu(new Bautura(newId, numeProdus, pretBaza, volum, alc, alcoolemie, stocItem));
                        }
                        std::cout << "Produsul a fost adaugat cu succes in meniu!\n";
                    }
                    else if (subOptiune == 2) {
                        int deleteId = 0;
                        std::cout << "Introduceti ID-ul produsului de sters: ";
                        if (!(std::cin >> deleteId)) {
                            curataInput();
                            throw InputInvalidException("id de sters");
                        }
                        restaurant.stergeProdusDinMeniu(deleteId);
                        std::cout << "Produsul a fost sters din meniu!\n";
                    }
                    else {
                        std::cout << "Sub-optiune invalida!\n";
                    }
                    break;
                }
                case 6: {
                    restaurant.afiseazaIstoricComenzi();
                    break;
                }
                default: {
                    std::cout << "Optiune inexistenta! Va rugam sa alegeti o optiune de pe ecran.\n";
                    break;
                }
            }
        } 
        catch (const RestaurantException& e) {
            std::cout << "\n[EROARE SISTEM RESTAURANT]: " << e.what() << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "\n[EROARE NEASTEPTATA]: " << e.what() << "\n";
        }
        catch (...) {
            std::cout << "\n[EROARE FATALA]: A aparut o exceptie necunoscuta!\n";
        }
    }

    return 0;
}
