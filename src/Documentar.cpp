#include "Documentar.h"
#include <utility>

Documentar::Documentar(std::string t, std::string g, std::string d, int durata, std::string subiect, int v, std::string cp, std::string lv)
    : Film(std::move(t), std::move(g), std::move(d), durata, v, std::move(cp), std::move(lv)), subiect(std::move(subiect)) {}

// cppcheck-suppress unusedFunction
const std::string& Documentar::getSubiect() const {
    return subiect;
}

void Documentar::play() {
    std::cout << "[BACKEND] Ruleaza documentarul: '" << getTitlu() << "' (Subiect: " << subiect << ", " << durata << " min).\n";
}

std::shared_ptr<ContinutVideo> Documentar::clone() const {
    return std::make_shared<Documentar>(*this);
}

void Documentar::do_afisare(std::ostream& os) const {
    os << "[DOCUMENTAR] " << getTitlu() << " (Gen: " << getGen() << ") | Subiect: " << subiect
       << " | Nota: " << getRating() << " | Durata: " << durata << " min | Varsta Minima: " << getVarstaMinima() << "+\n";
}

bool Documentar::matchesFilter(FiltruCatalog filtru) const {
    return filtru == FiltruCatalog::Toate || filtru == FiltruCatalog::Documentare;
}

std::string Documentar::getDetaliiSpecifice() const {
    return "Subiect: " + subiect + "  |  Durata: " + std::to_string(durata) + " min";
}