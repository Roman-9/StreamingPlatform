#include "CanalTV.h"
#include "Exceptii.h"
#include <utility>

CanalTV::CanalTV(std::string t, std::string g, std::string d, int varsta, std::string program, bool live, std::string cp, std::string lv)
    : ContinutVideo(std::move(t), std::move(g), std::move(d), varsta, std::move(cp), std::move(lv)),
      programCurent(std::move(program)), esteLive(live) {}

void CanalTV::play() {
    std::cout << "[BACKEND] Conectare la stream-ul " << (esteLive ? "LIVE" : "INREGISTRAT") << " pentru canalul: '" << getTitlu() << "' (Program curent: " << programCurent << ").\n";
}

int CanalTV::getTimpRamas() const {
    // Un canal TV este continuu
    return 0;
}

int CanalTV::getTimpVizionat() const {
    // Fara statistici per minut in varianta curenta pentru TV
    return 0;
}

std::shared_ptr<ContinutVideo> CanalTV::clone() const {
    return std::make_shared<CanalTV>(*this);
}

void CanalTV::do_afisare(std::ostream& os) const {
    os << "[CANAL TV] " << getTitlu() << " (Gen: " << getGen() << ") | Program curent: " << programCurent 
       << " | Status: " << (esteLive ? "LIVE" : "INREGISTRAT") << "\n";
}

// cppcheck-suppress unusedFunction
bool CanalTV::matchesFilter(FiltruCatalog filtru) const {
    return filtru == FiltruCatalog::Toate || filtru == FiltruCatalog::CanaleTV;
}

std::string CanalTV::getDetaliiSpecifice() const {
    return (esteLive ? "[LIVE] " : "[REPLAY] ") + programCurent;
}

// cppcheck-suppress unusedFunction
const std::string& CanalTV::getProgramCurent() const {
    return programCurent;
}

// cppcheck-suppress unusedFunction
bool CanalTV::getEsteLive() const {
    return esteLive;
}

// cppcheck-suppress unusedFunction
void CanalTV::setEsteLive(bool status) {
    esteLive = status;
}

// cppcheck-suppress unusedFunction
bool CanalTV::getInregistreazaAcum() const {
    return inregistreazaAcum;
}

// cppcheck-suppress unusedFunction
void CanalTV::inregistreazaProgram() {
    if (!esteLive) {
        throw StreamingException("Acest program este in reluare, nu poate fi inregistrat in direct!");
    }
    inregistreazaAcum = !inregistreazaAcum;
    if (inregistreazaAcum) {
        std::cout << "[DVR] Se inregistreaza transmisia live: '" << programCurent << "'...\n";
    } else {
        std::cout << "[DVR] Inregistrare oprita pentru: '" << programCurent << "'.\n";
    }
}
