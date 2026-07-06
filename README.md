# Proiect Restaurant (Tema 2)

Acesta este un proiect C++ orientat pe obiecte, realizat pentru Tema 2.

## Functionalitati
Proiectul modeleaza functionarea unui restaurant si include:
- Gestionarea meniului (Fel Principal, Desert, Bauturi)
- Plasarea si procesarea comenzilor
- Gestionarea stocului de ingrediente

## Concepte OOP folosite (Tema 2)
- **Incapsulare:** Ascunderea detaliilor de implementare si protejarea datelor prin constructori si metode publice.
- **Mostenire:** O ierarhie de clase plecand de la o clasa de baza abstracta `Produs` din care deriva `FelPrincipal`, `Desert` si `Bautura`.
- **Polimorfism:** Metode virtuale pure (`getIngredienteNecesare`, clone) si suprascrierea acestora (`override`) in clasele derivate.
- **Upcasting & dynamic_cast:** Utilizarea pointerilor la clasa de baza pentru a trata uniform toate produsele si folosirea `dynamic_cast` atunci cand este nevoie de acces la elemente specifice clasei derivate.
- **Memory Management (Regula celor 5):** Constructor de copiere, assignment operator, mutare (move semantics) si destructor implementate corect, in special in clasele ce gestioneaza memorie dinamica (precum `Meniu` / `Comanda`).

## Cum se ruleaza
Pentru a compila si rula acest proiect se foloseste g++:

```bash
g++ -Iinclude src/*.cpp main.cpp -o restaurant.exe
./restaurant.exe
```
