#pragma once
#include <string>
#include <memory>
#include "ListaGenerica.h"
#include "ContinutVideo.h"
#include "StrategieRecomandare.h"

class Utilizator {
private:
    std::string nume;
    std::string plan;
    int varsta;
    ListaGenerica<ContinutVideo> watchlistActiva;
    ListaGenerica<ContinutVideo> istoricVizionari;
    std::shared_ptr<StrategieRecomandare> strategieRecomandare;

public:
    Utilizator(std::string n, std::string p, int v);
    const std::string& getNume() const;
    const std::string& getPlan() const;
    int getVarsta() const;
    void setPlan(const std::string& planNou);
    void setStrategieRecomandare(std::shared_ptr<StrategieRecomandare> strategie);

    void adaugaInWatchlist(const std::shared_ptr<ContinutVideo>& cv);
    void stergeDinWatchlistDupaTitlu(const std::string& titluCautat);

    void marcheazaCaVazut(const std::shared_ptr<ContinutVideo>& cv);

    void uitaTeLaEpisod(const std::string& titluSerial);
    void acordaNota(const std::string& titlu, int nota);
    int getTimpTotalVizionat() const;
    int getTimpRamasWatchlist() const;
    std::string getTopRecomandare(const std::vector<std::shared_ptr<ContinutVideo>>& catalogGlobal) const;
    const ListaGenerica<ContinutVideo>& getWatchlist() const;

    friend std::ostream& operator<<(std::ostream& os, const Utilizator& user);
    std::shared_ptr<Utilizator> clone() const { return std::make_shared<Utilizator>(*this); }
};