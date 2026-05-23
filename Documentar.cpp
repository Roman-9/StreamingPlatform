#include "Documentar.h"
#include <utility>

Documentar::Documentar(std::string t, std::string g, std::string d, int durata, std::string subiect, int v, std::string cp, std::string lv)
    : ContinutVideo(std::move(t), std::move(g), std::move(d), v, std::move(cp), std::move(lv)), durata(durata), subiect(std::move(subiect)) {}

// cppcheck-suppress unusedFunction
const std::string& Documentar::getSubiect() const {
    return subiect;
}

// cppcheck-suppress unusedFunction
int Documentar::getDurata() const {
    return durata;
}

void Documentar::play() {
    std::cout << "[BACKEND] Ruleaza documentarul: '" << getTitlu() << "' (Subiect: " << subiect << ", " << durata << " min).\n";
}

int Documentar::getTimpRamas() const {
    return (aFostEvaluat()) ? 0 : durata;
}

int Documentar::getTimpVizionat() const {
    return (aFostEvaluat()) ? durata : 0;
}

std::shared_ptr<ContinutVideo> Documentar::clone() const {
    return std::make_shared<Documentar>(*this);
}

void Documentar::do_afisare(std::ostream& os) const {
    os << "[DOCUMENTAR] " << getTitlu() << " (Gen: " << getGen() << ") | Subiect: " << subiect
       << " | Nota: " << getRating() << " | Durata: " << durata << " min | Varsta Minima: " << getVarstaMinima() << "+\n";
}