#include "Utilizator.h"
#include "Exceptii.h"
#include "Serial.h"
#include <iostream>

Utilizator::Utilizator(std::string n, std::string p, int v) : nume(std::move(n)), plan(std::move(p)), varsta(v) {
    strategieRecomandare = std::make_shared<RecomandareDupaRating>();
}

// cppcheck-suppress unusedFunction
const std::string& Utilizator::getNume() const { return nume; }
// cppcheck-suppress unusedFunction
const std::string& Utilizator::getPlan() const { return plan; }
// cppcheck-suppress unusedFunction
int Utilizator::getVarsta() const { return varsta; }
// cppcheck-suppress unusedFunction
void Utilizator::setPlan(const std::string& planNou) { plan = planNou; }

void Utilizator::setStrategieRecomandare(std::shared_ptr<StrategieRecomandare> strategie) {
    if (strategie) {
        strategieRecomandare = strategie;
    }
}

// cppcheck-suppress unusedFunction
void Utilizator::adaugaInWatchlist(const std::shared_ptr<ContinutVideo>& cv) {
    if (cv && varsta < cv->getVarstaMinima()) {
        throw LimitaVarstaException(cv->getTitlu(), cv->getVarstaMinima());
    }
    watchlistActiva.adauga(cv);
}

// cppcheck-suppress unusedFunction
void Utilizator::stergeDinWatchlistDupaTitlu(const std::string& titluCautat) {
    watchlistActiva.stergeDaca([&titluCautat](const std::shared_ptr<ContinutVideo>& cv) {
        return cv->getTitlu() == titluCautat;
    });
}

// cppcheck-suppress unusedFunction
void Utilizator::marcheazaCaVazut(const std::shared_ptr<ContinutVideo>& cv) {
    if (!cv) return;
    try {
        watchlistActiva.stergeDaca([&cv](const std::shared_ptr<ContinutVideo>& item) {
            return item->getTitlu() == cv->getTitlu();
        });
    } catch (...) {}

    if (!gasesteDaca(istoricVizionari, [&cv](const std::shared_ptr<ContinutVideo>& item) { return item->getTitlu() == cv->getTitlu(); })) {
        istoricVizionari.adauga(cv);
        std::cout << "[INFO] '" << cv->getTitlu() << "' a fost mutat in Istoric.\n";
    }
}

// cppcheck-suppress unusedFunction
void Utilizator::uitaTeLaEpisod(const std::string& titluSerial) {
    auto cv = gasesteDaca(watchlistActiva, [&titluSerial](const std::shared_ptr<ContinutVideo>& item) { return item->getTitlu() == titluSerial; });
    if (!cv) cv = gasesteDaca(istoricVizionari, [&titluSerial](const std::shared_ptr<ContinutVideo>& item) { return item->getTitlu() == titluSerial; });

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
    auto cv = gasesteDaca(istoricVizionari, [&titlu](const std::shared_ptr<ContinutVideo>& item) { return item->getTitlu() == titlu; });

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
    if (!strategieRecomandare) {
        return "Nicio strategie de recomandare setata!";
    }

    auto topPick = strategieRecomandare->recomanda(catalogGlobal, istoricVizionari, varsta);

    if (topPick) {
        return topPick->getTitlu() + " (" + topPick->getGen() + ")";
    }
    return "Ai vizionat tot catalogul!";
}


const ListaGenerica<ContinutVideo>& Utilizator::getWatchlist() const { return watchlistActiva; }

std::ostream& operator<<(std::ostream& os, const Utilizator& user) {
    os << "User: " << user.nume << " | Plan: " << user.plan << "\n";
    return os;
}