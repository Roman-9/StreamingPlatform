#include "Film.h"
#include <algorithm>

Film::Film(std::string t, std::string g, std::string d, int durata, int v, std::string cp, std::string lv)
    : ContinutVideo(std::move(t), std::move(g), std::move(d), v, std::move(cp), std::move(lv)), durata(durata) {}

// cppcheck-suppress unusedFunction
int Film::getDurata() const { return durata; }

int Film::getTimpRamas() const {
    // Daca a primit o nota, inseamna ca l-am vazut, deci mai avem 0 minute
    return (aFostEvaluat()) ? 0 : durata;
}

int Film::getTimpVizionat() const {
    // Timpul pierdut e 0 daca nu a fost evaluat
    return (aFostEvaluat()) ? durata : 0;
}

void Film::play() {
    std::cout << "[BACKEND] Ruleaza filmul: '" << getTitlu() << "' (" << durata << " min).\n";
}

std::shared_ptr<ContinutVideo> Film::clone() const {
    return std::make_shared<Film>(*this); 
}

void Film::do_afisare(std::ostream& os) const {
    os << "[FILM] " << getTitlu() << " (Gen: " << getGen() << ") | Nota: " << getRating() 
       << " | Durata: " << durata << " min | Varsta Minima: " << getVarstaMinima() << "+\n";
}

bool Film::matchesFilter(FiltruCatalog filtru) const {
    return filtru == FiltruCatalog::Toate || filtru == FiltruCatalog::Filme;
}

std::string Film::getDetaliiSpecifice() const {
    return "Durata: " + std::to_string(durata) + " min";
}