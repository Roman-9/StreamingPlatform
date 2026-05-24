#include "Utilizator.h"
#include "Exceptii.h"
#include "Serial.h"
#include <iostream>

Utilizator::Utilizator(std::string n, std::string p, int v) : nume(std::move(n)), plan(std::move(p)), varsta(v) {}

// cppcheck-suppress unusedFunction
const std::string& Utilizator::getNume() const { return nume; }
// cppcheck-suppress unusedFunction
const std::string& Utilizator::getPlan() const { return plan; }
// cppcheck-suppress unusedFunction
int Utilizator::getVarsta() const { return varsta; }
// cppcheck-suppress unusedFunction
void Utilizator::setPlan(const std::string& planNou) { plan = planNou; }

// cppcheck-suppress unusedFunction
void Utilizator::adaugaInWatchlist(const std::shared_ptr<ContinutVideo>& cv) {
    if (cv && varsta < cv->getVarstaMinima()) {
        throw LimitaVarstaException(cv->getTitlu(), cv->getVarstaMinima());
    }
    watchlistActiva.adauga(cv);
}

// cppcheck-suppress unusedFunction
void Utilizator::stergeDinWatchlistDupaTitlu(const std::string& titluCautat) {
    watchlistActiva.stergeDupaTitlu(titluCautat);
}

// cppcheck-suppress unusedFunction
void Utilizator::marcheazaCaVazut(const std::shared_ptr<ContinutVideo>& cv) {
    if (!cv) return;
    try {
        watchlistActiva.stergeDupaTitlu(cv->getTitlu());
    } catch (...) {}

    if (!istoricVizionari.gasesteDupaTitlu(cv->getTitlu())) {
        istoricVizionari.adauga(cv);
        std::cout << "[INFO] '" << cv->getTitlu() << "' a fost mutat in Istoric.\n";
    }
}

// cppcheck-suppress unusedFunction
void Utilizator::uitaTeLaEpisod(const std::string& titluSerial) {
    auto cv = watchlistActiva.gasesteDupaTitlu(titluSerial);
    if (!cv) cv = istoricVizionari.gasesteDupaTitlu(titluSerial);

    if (cv) {
        if (auto serial = std::dynamic_pointer_cast<Serial>(cv)) {
            serial->vizioneazaEpisod();
            serial->play();
        } else {
            cv->play();
        }
    }
}

// cppcheck-suppress unusedFunction
void Utilizator::acordaNota(const std::string& titlu, int nota) {
    auto cv = istoricVizionari.gasesteDupaTitlu(titlu);

    if (!cv) {
        throw RecenzieFaraVizionareException(titlu);
    }

    cv->adaugaRecenzie(nota);
}

// cppcheck-suppress unusedFunction
int Utilizator::getTimpTotalVizionat() const {
    int total = 0;
    // Parcurgem istoricul de vizionari polimorfic
    for (const auto& cv : istoricVizionari.getLista()) {
        total += cv->getTimpVizionat();
    }
    return total;
}

// cppcheck-suppress unusedFunction
int Utilizator::getTimpRamasWatchlist() const {
    int total = 0;
    // Parcurgem elementele din Watchlist pentru a vedea cat timp a mai ramas de vizionat
    for (const auto& cv : getWatchlist().getLista()) {
        total += cv->getTimpRamas();
    }
    return total;
}

// cppcheck-suppress unusedFunction
std::string Utilizator::getTopRecomandare(const std::vector<std::shared_ptr<ContinutVideo>>& catalogGlobal) const {
    std::shared_ptr<ContinutVideo> topPick = nullptr;
    double maxRating = -1.0;

    for (const auto& cv : catalogGlobal) {
        // Algoritm: cautam titlul cu cel mai mare rating pe care utilizatorul NU l-a vazut inca
        if (!istoricVizionari.gasesteDupaTitlu(cv->getTitlu())) {
            if (cv->getRating() > maxRating) {
                maxRating = cv->getRating();
                topPick = cv;
            }
        }
    }

    if (topPick) {
        return topPick->getTitlu() + " (" + topPick->getGen() + ")";
    }
    return "Ai vizionat tot catalogul!";
}


const Watchlist& Utilizator::getWatchlist() const { return watchlistActiva; }

std::ostream& operator<<(std::ostream& os, const Utilizator& user) {
    os << "User: " << user.nume << " | Plan: " << user.plan << "\n";
    return os;
}