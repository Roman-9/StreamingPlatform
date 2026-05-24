#include "Serial.h"
#include <sstream>
#include <algorithm>

Serial::Serial(std::string t, std::string g, std::string d, std::vector<int> durate, int v, std::string cp, std::string lv)
    : ContinutVideo(std::move(t), std::move(g), std::move(d), v, std::move(cp), std::move(lv)), durateEpisoade(std::move(durate)), episodCurent(0) {}

void Serial::play() {
    if (vizioneazaEpisod()) {
        std::cout << "[BACKEND] Ai vazut episodul " << episodCurent << " din " << getTitlu() << "!\n";
    } else {
        std::cout << "[BACKEND] Ai terminat deja acest serial!\n";
    }
}

bool Serial::vizioneazaEpisod() {
    if (static_cast<size_t>(episodCurent) < durateEpisoade.size()) {
        episodCurent++; return true;
    }
    return false;
}

// cppcheck-suppress unusedFunction
int Serial::getEpisodCurent() const { return episodCurent; }

// cppcheck-suppress unusedFunction
void Serial::setEpisodCurent(int ep) {
    if (ep >= 0 && ep <= static_cast<int>(durateEpisoade.size())) {
        episodCurent = ep;
    }
}

int Serial::getTimpRamas() const {
    int timp = 0;
    for (size_t i = episodCurent; i < durateEpisoade.size(); ++i) timp += durateEpisoade[i];
    return timp;
}

int Serial::getTimpVizionat() const {
    int timp = 0;
    for (size_t i = 0; i < static_cast<size_t>(episodCurent); ++i) timp += durateEpisoade[i];
    return timp;
}

// cppcheck-suppress unusedFunction
int Serial::getNumarEpisoade() const { return static_cast<int>(durateEpisoade.size()); }

// cppcheck-suppress unusedFunction
const std::vector<int>& Serial::getDurateEpisoade() const { return durateEpisoade; }

void Serial::do_afisare(std::ostream& os) const {
    os << "[SERIAL] " << getTitlu() << " (gen: " << getGen() << ") | Nota: " << getRating()
       << " | Progres: Ep. " << episodCurent << " din " << durateEpisoade.size() << "\n";
}
std::shared_ptr<ContinutVideo> Serial::clone() const {
    return std::make_shared<Serial>(*this);
}

bool Serial::matchesFilter(FiltruCatalog filtru) const {
    return filtru == FiltruCatalog::Toate || filtru == FiltruCatalog::Seriale;
}

std::string Serial::getDetaliiSpecifice() const {
    return "Ghid Episoade (" + std::to_string(getNumarEpisoade()) + " episoade)";
}