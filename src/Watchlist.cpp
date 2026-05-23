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
const std::vector<std::shared_ptr<ContinutVideo>>& Watchlist::getLista() const { return lista; }

std::ostream& operator<<(std::ostream& os, const Watchlist& wl) {
    if (wl.lista.empty()) { os << "Lista este goala.\n"; return os; }
    for (const auto& cv : wl.lista) os << *cv << "\n";
    return os;
}