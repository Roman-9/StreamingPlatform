#pragma once
#include <string>
#include <memory>
#include "Watchlist.h"
#include "Exceptii.h"

class Utilizator {
private:
    std::string nume;
    int varsta;
    Watchlist watchlistPersonal;

public:
    explicit Utilizator(std::string n = "Anonim", int v = 0);

    [[nodiscard]] const std::string& getNume() const;
    [[nodiscard]] int getVarsta() const;
    [[nodiscard]] const Watchlist& getWatchlist() const;

    void adaugaInWatchlist(const std::shared_ptr<ContinutVideo>& cv);
    void stergeDinWatchlistDupaTitlu(const std::string& titluCautat);

    friend std::ostream& operator<<(std::ostream& os, const Utilizator& u);
};