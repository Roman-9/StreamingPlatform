#pragma once
#include <string>
#include "Watchlist.h"

class Utilizator {
private:
    std::string nume;
    std::string plan;
    int varsta;
    Watchlist watchlistActiva;
    Watchlist istoricVizionari;

public:
    explicit Utilizator(std::string n = "Anonim", std::string p = "Free", int v = 0);

    [[nodiscard]] const std::string& getNume() const;
    [[nodiscard]] const std::string& getPlan() const;
    [[nodiscard]] int getVarsta() const;
    void setPlan(const std::string& planNou);

    void adaugaInWatchlist(const std::shared_ptr<ContinutVideo>& cv);
    void stergeDinWatchlistDupaTitlu(const std::string& titluCautat);

    void marcheazaCaVazut(const std::string& titlu);
    void uitaTeLaEpisod(const std::string& titluSerial);
    void acordaNota(const std::string& titlu, int nota);

    void afiseazaTimpRamas() const;
    void afiseazaStatistici() const;
    void cautaGen(const std::string& gen) const;
    void recomandaTop() const;

    [[nodiscard]] const Watchlist& getWatchlist() const;
    friend std::ostream& operator<<(std::ostream& os, const Utilizator& user);
};