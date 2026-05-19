#include "Film.h"

Film::Film(const std::string& t, const std::string& g, const std::string& d, int durata, int v)
    : ContinutVideo(t, g, d, v), durata(durata) {}

int Film::getDurata() const { 
    return durata; 
}

void Film::play() {
    std::cout << "-> Ruleaza filmul: '" << titlu << "' (" << durata << " min). Aseaza-te comod!\n";
}

void Film::afiseazaDetalii(std::ostream& os) const {
    os << "[FILM] " << titlu << " (Gen: " << gen << ") | Nota: " << getRating() 
       << " | Durata: " << durata << " min | Varsta Minima: " << varstaMinima << "+\n";
}