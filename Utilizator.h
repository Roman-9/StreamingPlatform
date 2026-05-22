#pragma once
#include <string>
#include <memory>
#include "Watchlist.h"
#include "ContinutVideo.h"

class Utilizator {
private:
    std::string nume;
    std::string plan;
    int varsta;
    Watchlist watchlistActiva;
    Watchlist istoricVizionari;

public:
    Utilizator(std::string n, std::string p, int v);
    const std::string& getNume() const;
    const std::string& getPlan() const;
    int getVarsta() const;
    void setPlan(const std::string& planNou);

    void adaugaInWatchlist(const std::shared_ptr<ContinutVideo>& cv);
    void stergeDinWatchlistDupaTitlu(const std::string& titluCautat);

    void marcheazaCaVazut(const std::shared_ptr<ContinutVideo>& cv);

    void uitaTeLaEpisod(const std::string& titluSerial);
    void acordaNota(const std::string& titlu, int nota);
    int getTimpTotalVizionat() const;
    int getTimpRamasWatchlist() const;
    std::string getTopRecomandare(const std::vector<std::shared_ptr<ContinutVideo>>& catalogGlobal) const;
    const Watchlist& getWatchlist() const;

    friend std::ostream& operator<<(std::ostream& os, const Utilizator& user);
};