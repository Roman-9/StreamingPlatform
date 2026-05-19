#include "Utilizator.h"

Utilizator::Utilizator(std::string n, int v) : nume(std::move(n)), varsta(v) {}

const std::string& Utilizator::getNume() const { return nume; }
int Utilizator::getVarsta() const { return varsta; }
const Watchlist& Utilizator::getWatchlist() const { return watchlistPersonal; }

void Utilizator::adaugaInWatchlist(const std::shared_ptr<ContinutVideo>& cv) {
    if (!cv) return;
    
    if (varsta < cv->getVarstaMinima()) {
        throw LimitaVarstaException(cv->getTitlu(), cv->getVarstaMinima());
    }
    
    watchlistPersonal.adauga(cv);
    std::cout << "[SUCCESS] '" << cv->getTitlu() << "' a fost adaugat in lista lui " << nume << ".\n";
}

void Utilizator::stergeDinWatchlistDupaTitlu(const std::string& titluCautat) {
    const auto& lista = watchlistPersonal.getLista();
    
    for (const auto& item : lista) {
        if (item->getTitlu() == titluCautat) {
            watchlistPersonal.sterge(item);
            std::cout << "[SUCCESS] '" << titluCautat << "' a fost sters din lista.\n";
            return; 
        }
    }
    
    throw TitluInexistentException(titluCautat);
}

std::ostream& operator<<(std::ostream& os, const Utilizator& u) {
    os << "Utilizator: " << u.nume << " (" << u.varsta << " ani)\n";
    os << u.watchlistPersonal;
    return os;
}