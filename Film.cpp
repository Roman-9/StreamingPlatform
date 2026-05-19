#include "Film.h"

Film::Film(std::string t, std::string g, std::string d, int durata, int v)
    : ContinutVideo(std::move(t), std::move(g), std::move(d), v), durata(durata) {}

int Film::getDurata() const { 
    return durata; 
}
int Film::getTimpRamas() const {
    return durata;
}
int Film::getTimpVizionat() const {
    return durata;
}
void Film::play() const{
    std::cout << "-> Ruleaza filmul: '" << titlu << "' (" << durata << " min). Aseaza-te comod!\n";
}

void Film::afisare(std::ostream& os) const {
    os << "[FILM] " << titlu << " (Gen: " << gen << ") | Nota: " << getRating() 
       << " | Durata: " << durata << " min | Varsta Minima: " << varstaMinima << "+\n";
}