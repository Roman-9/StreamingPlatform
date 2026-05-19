#include "Watchlist.h"
#include <algorithm>

void Watchlist::adauga(const std::shared_ptr<ContinutVideo>& cv) {
    if (cv) {
        lista.push_back(cv);
    }
}

void Watchlist::sterge(const std::shared_ptr<ContinutVideo>& cv) {
    auto it = std::find(lista.begin(), lista.end(), cv);
    if (it != lista.end()) {
        lista.erase(it);
    }
}

const std::vector<std::shared_ptr<ContinutVideo>>& Watchlist::getLista() const {
    return lista;
}

std::ostream& operator<<(std::ostream& os, const Watchlist& w) {
    os << "--- WATCHLIST PERSONAL ---\n";
    if (w.lista.empty()) {
        os << "Lista este goala.\n";
    } else {
        for (const auto& item : w.lista) {
            os << *item; 
        }
    }
    return os << "--------------------------\n";
}