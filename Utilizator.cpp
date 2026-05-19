#include "Utilizator.h"
#include "Exceptii.h"
#include "Serial.h"
#include <iostream>

Utilizator::Utilizator(std::string n, std::string p, int v) : nume(std::move(n)), plan(std::move(p)), varsta(v) {}

const std::string& Utilizator::getNume() const { return nume; }
const std::string& Utilizator::getPlan() const { return plan; }
int Utilizator::getVarsta() const { return varsta; }
void Utilizator::setPlan(const std::string& planNou) { plan = planNou; }

void Utilizator::adaugaInWatchlist(const std::shared_ptr<ContinutVideo>& cv) {
    if (cv && varsta < cv->getVarstaMinima()) {
        throw LimitaVarstaException(cv->getTitlu(), cv->getVarstaMinima());
    }
    watchlistActiva.adauga(cv);
}

void Utilizator::stergeDinWatchlistDupaTitlu(const std::string& titluCautat) {
    watchlistActiva.stergeDupaTitlu(titluCautat);
}

void Utilizator::marcheazaCaVazut(const std::string& titlu) {
    if (watchlistActiva.mutaInIstoric(titlu, istoricVizionari)) {
        std::cout << "[INFO] '" << titlu << "' a fost mutat in Istoric.\n";
    }
}

void Utilizator::uitaTeLaEpisod(const std::string& titluSerial) {
    auto cv = watchlistActiva.gasesteDupaTitlu(titluSerial);
    if (cv) {
        if (auto serial = std::dynamic_pointer_cast<Serial>(cv)) {
            if (serial->vizioneazaEpisod()) std::cout << "[INFO] Ai vazut un episod nou din " << titluSerial << "\n";
            else std::cout << "[INFO] Ai terminat serialul!\n";
        }
    }
}

void Utilizator::acordaNota(const std::string& titlu, int nota) {
    auto cv = istoricVizionari.gasesteDupaTitlu(titlu);
    if (!cv) cv = watchlistActiva.gasesteDupaTitlu(titlu);
    if (cv) cv->adaugaRecenzie(nota);
}

void Utilizator::afiseazaTimpRamas() const {
    std::cout << "Timp ramas: " << watchlistActiva.calculeazaDurataTotalaRamas() << " minute.\n";
}

void Utilizator::afiseazaStatistici() const {
    std::cout << "Timp pierdut (vizionat): " << istoricVizionari.calculeazaTimpPierdut() << " minute.\n";
}

void Utilizator::cautaGen(const std::string& gen) const {
    watchlistActiva.afiseazaDupaGen(gen);
}

void Utilizator::recomandaTop() const {
    watchlistActiva.afiseazaTopRating();
}

const Watchlist& Utilizator::getWatchlist() const {
    return watchlistActiva;
}

std::ostream& operator<<(std::ostream& os, const Utilizator& user) {
    os << "User: " << user.nume << " | Plan: " << user.plan << "\n";
    return os;
}