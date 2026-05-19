#include "ContinutVideo.h"

ContinutVideo::ContinutVideo(std::string t, std::string g, std::string d, int v)
    : titlu(std::move(t)), gen(std::move(g)), descriere(std::move(d)), varstaMinima(v) {}

const std::string& ContinutVideo::getTitlu() const { return titlu; }
const std::string& ContinutVideo::getGen() const { return gen; }
const std::string& ContinutVideo::getDescriere() const { return descriere; }
int ContinutVideo::getVarstaMinima() const { return varstaMinima; }

void ContinutVideo::adaugaRecenzie(int nota) {
    if (nota >= 1 && nota <= 10) {
        notePrimite.push_back(nota);
    } else {
        std::cout << "[Eroare] Nota trebuie sa fie intre 1 si 10!\n";
    }
}

double ContinutVideo::getRating() const {
    if (notePrimite.empty()) return 0.0;
    double suma = 0.0;
    for (size_t i = 0; i < notePrimite.size(); ++i) { 
        suma += notePrimite[i]; 
    }
    return suma / static_cast<double>(notePrimite.size());
}

std::ostream& operator<<(std::ostream& os, const ContinutVideo& cv) {
    cv.afiseazaDetalii(os);
    return os;
}