#include "Documentar.h"

Documentar::Documentar(std::string t, std::string g, std::string d, int durata, std::string subiect, int v)
    : ContinutVideo(std::move(t), std::move(g), std::move(d), v), durata(durata), subiectPrincipal(std::move(subiect)) {}

void Documentar::play() const {
    std::cout << "[PLAY DOCUMENTAR] Invatam despre: " << subiectPrincipal << "\n";
}
int Documentar::getTimpRamas() const {
    return durata;
}
int Documentar::getTimpVizionat() const {
    return durata;
}

void Documentar::afisare(std::ostream& os) const {
    os << "[DOCUMENTAR] " << titlu << " | Subiect: " << subiectPrincipal << " | Durata: " << durata << "min\n";
}

std::shared_ptr<ContinutVideo> Documentar::clone() const {
    return std::make_shared<Documentar>(*this);
}

const std::string& Documentar::getSubiect() const { return subiectPrincipal; }