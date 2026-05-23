#include "ContinutVideo.h"
#include "Exceptii.h"

int ContinutVideo::numarTotalContinut = 0;

ContinutVideo::ContinutVideo(std::string t, std::string g, std::string d, int v, std::string cp, std::string lv)
    : titlu(std::move(t)), gen(std::move(g)), descriere(std::move(d)), varstaMinima(v),
      calePoster(std::move(cp)), linkVizionare(std::move(lv)) {
    numarTotalContinut++;
}

ContinutVideo::ContinutVideo(const ContinutVideo& other)
    : titlu(other.titlu), gen(other.gen), descriere(other.descriere), varstaMinima(other.varstaMinima),
      calePoster(other.calePoster), linkVizionare(other.linkVizionare), notePrimite(other.notePrimite) {
    numarTotalContinut++;
}

ContinutVideo::~ContinutVideo() {
    numarTotalContinut--;
}

const std::string& ContinutVideo::getTitlu() const { return titlu; }
const std::string& ContinutVideo::getGen() const { return gen; }
// cppcheck-suppress unusedFunction
const std::string& ContinutVideo::getDescriere() const { return descriere; }
int ContinutVideo::getVarstaMinima() const { return varstaMinima; }
// cppcheck-suppress unusedFunction
int ContinutVideo::getNumarTotalContinut() { return numarTotalContinut; }

void ContinutVideo::adaugaRecenzie(int nota) {
    if (nota >= 1 && nota <= 10) {
        notePrimite.push_back(nota);
    } else {
        throw NotaInvalidaException(nota);
    }
}

double ContinutVideo::getRating() const {
    if (notePrimite.empty()) return 0.0;
    double suma = 0.0;
    for (int nota : notePrimite) suma += nota;
    return suma / static_cast<double>(notePrimite.size());
}

bool ContinutVideo::aFostEvaluat() const {
    return !notePrimite.empty();
}

void ContinutVideo::afisare(std::ostream& os) const {
    do_afisare(os);
}

std::ostream& operator<<(std::ostream& os, const ContinutVideo& cv) {
    cv.afisare(os);
    return os;
}