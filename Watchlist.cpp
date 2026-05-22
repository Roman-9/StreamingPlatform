#include "Watchlist.h"
#include "Exceptii.h"
#include <iostream>
#include <utility>

Watchlist::Watchlist(const Watchlist& other) {
    for (const auto& cv : other.lista) {
        if (cv) { lista.push_back(cv->clone()); }
    }
}

void swap(Watchlist& first, Watchlist& second) noexcept {
    using std::swap;
    swap(first.lista, second.lista);
}

Watchlist& Watchlist::operator=(Watchlist other) {
    swap(*this, other);
    return *this;
}

Watchlist::~Watchlist() {
    lista.clear();
}

void Watchlist::adauga(const std::shared_ptr<ContinutVideo>& cv) {
    if (cv) lista.push_back(cv);
}

void Watchlist::stergeDupaTitlu(const std::string& titluCautat) {
    for (auto it = lista.begin(); it != lista.end(); ++it) {
        if ((*it)->getTitlu() == titluCautat) {
            lista.erase(it); return;
        }
    }
    throw TitluInexistentException(titluCautat);
}

std::shared_ptr<ContinutVideo> Watchlist::gasesteDupaTitlu(const std::string& titluCautat) const {
    for (const auto& cv : lista) {
        if (cv->getTitlu() == titluCautat) return cv;
    }
    return nullptr;
}

bool Watchlist::mutaInIstoric(const std::string& titluCautat, Watchlist& istoricDestinatie) {
    for (auto it = lista.begin(); it != lista.end(); ++it) {
        if ((*it)->getTitlu() == titluCautat) {
            istoricDestinatie.adauga(*it);
            lista.erase(it); return true;
        }
    }
    return false;
}

void Watchlist::afiseazaDupaGen(const std::string& genCautat) const {
    std::cout << "--- Rezultate pentru genul: " << genCautat << " ---\n";
    bool gasit = false;
    for (const auto& cv : lista) {
        if (cv->getGen() == genCautat) {
            std::cout << *cv << "\n"; gasit = true;
        }
    }
    if (!gasit) std::cout << "Nu s-au gasit elemente din acest gen.\n";
}

void Watchlist::afiseazaTopRating() const {
    double maxRating = -1.0; std::string topTitlu = "";
    for (const auto& cv : lista) {
        if (cv->getRating() > maxRating) {
            maxRating = cv->getRating(); topTitlu = cv->getTitlu();
        }
    }
    if (maxRating != -1.0) {
        std::cout << "[TOP] Cel mai bine cotat titlu este: '" << topTitlu << "' cu nota " << maxRating << "\n";
    } else {
        std::cout << "Lista este goala sau nu exista recenzii.\n";
    }
}

int Watchlist::calculeazaDurataTotalaRamas() const {
    int timp = 0;
    for (const auto& cv : lista) timp += cv->getTimpRamas();
    return timp;
}

int Watchlist::calculeazaTimpPierdut() const {
    int timp = 0;
    for (const auto& cv : lista) timp += cv->getTimpVizionat();
    return timp;
}

const std::vector<std::shared_ptr<ContinutVideo>>& Watchlist::getLista() const { return lista; }

std::ostream& operator<<(std::ostream& os, const Watchlist& wl) {
    if (wl.lista.empty()) { os << "Lista este goala.\n"; return os; }
    for (const auto& cv : wl.lista) os << *cv << "\n";
    return os;
}