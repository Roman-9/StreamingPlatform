#include "Documentar.h"
#include <utility>

Documentar::Documentar(std::string t, std::string g, std::string d, int durata, std::string subiect, int v, std::string cp, std::string lv)
    : ContinutVideo(std::move(t), std::move(g), std::move(d), v, std::move(cp), std::move(lv)), durata(durata), subiect(std::move(subiect)) {}

const std::string& Documentar::getSubiect() const {
    return subiect;
}

int Documentar::getDurata() const {
    return durata;
}

void Documentar::play() {
    std::cout << "[BACKEND] Ruleaza documentarul: '" << titlu << "' (Subiect: " << subiect << ", " << durata << " min).\n";
}

int Documentar::getTimpRamas() const {
    return (notePrimite.empty()) ? durata : 0;
}

int Documentar::getTimpVizionat() const {
    return (notePrimite.empty()) ? 0 : durata;
}

std::shared_ptr<ContinutVideo> Documentar::clone() const {
    return std::make_shared<Documentar>(*this);
}

void Documentar::afisare(std::ostream& os) const {
    os << "[DOCUMENTAR] " << titlu << " (Gen: " << gen << ") | Subiect: " << subiect
       << " | Nota: " << getRating() << " | Durata: " << durata << " min | Varsta Minima: " << varstaMinima << "+\n";
}