#include "Serial.h"
#include <sstream>
#include <algorithm>

Serial::Serial(std::string t, std::string g, std::string d, std::vector<int> durate, int v, std::string cp, std::string lv)
    : ContinutVideo(std::move(t), std::move(g), std::move(d), v, std::move(cp), std::move(lv)), durateEpisoade(std::move(durate)), episodCurent(0) {}

void Serial::play() {
    if (vizioneazaEpisod()) {
        std::cout << "[BACKEND] Ai vazut episodul " << episodCurent << " din " << titlu << "!\n";
    } else {
        std::cout << "[BACKEND] Ai terminat deja acest serial!\n";
    }
}

bool Serial::vizioneazaEpisod() {
    if (episodCurent < durateEpisoade.size()) {
        episodCurent++; return true;
    }
    return false;
}

int Serial::getEpisodCurent() const { return episodCurent; }

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

int Serial::getNumarEpisoade() const { return static_cast<int>(durateEpisoade.size()); }

const std::vector<int>& Serial::getDurateEpisoade() const { return durateEpisoade; }

void Serial::afisare(std::ostream& os) const {
    os << "[SERIAL] " << titlu << " (gen: " << gen << ") | Nota: " << getRating()
       << " | Progres: Ep. " << episodCurent << " din " << durateEpisoade.size() << "\n";
}

std::string Serial::getDurateAsConversieString() const {
    std::stringstream ss;
    for (size_t i = 0; i < durateEpisoade.size(); ++i) {
        ss << durateEpisoade[i];
        if (i < durateEpisoade.size() - 1) ss << ",";
    }
    return ss.str();
}

std::shared_ptr<ContinutVideo> Serial::clone() const {
    return std::make_shared<Serial>(*this);
}