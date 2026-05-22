#include "Film.h"
#include <algorithm>

Film::Film(std::string t, std::string g, std::string d, int durata, int v, std::string cp, std::string lv)
    : ContinutVideo(std::move(t), std::move(g), std::move(d), v, std::move(cp), std::move(lv)), durata(durata) {}

int Film::getDurata() const { return durata; }

int Film::getTimpRamas() const {
    // Daca a primit o nota, inseamna ca l-am vazut, deci mai avem 0 minute
    return (notePrimite.empty()) ? durata : 0;
}

int Film::getTimpVizionat() const {
    // Timpul pierdut e 0 daca nu a fost evaluat
    return (notePrimite.empty()) ? 0 : durata;
}

void Film::play() {
    std::cout << "[BACKEND] Ruleaza filmul: '" << titlu << "' (" << durata << " min).\n";
}

std::shared_ptr<ContinutVideo> Film::clone() const {
    return std::make_shared<Film>(*this); 
}

void Film::afisare(std::ostream& os) const {
    os << "[FILM] " << titlu << " (Gen: " << gen << ") | Nota: " << getRating() 
       << " | Durata: " << durata << " min | Varsta Minima: " << varstaMinima << "+\n";
}