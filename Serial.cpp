#include "Serial.h"

Serial::Serial(const std::string& t, const std::string& g, const std::string& d, int nrEpisoade, int v)
    : ContinutVideo(t, g, d, v), numarEpisoade(nrEpisoade), episodCurent(1) {}

int Serial::getNumarEpisoade() const { 
    return numarEpisoade; 
}

void Serial::play() {
    if (episodCurent <= numarEpisoade) {
        std::cout << "-> Ruleaza Episodul " << episodCurent << " din '" << titlu << "'.\n";
        episodCurent++;
    } else {
        std::cout << "Ai terminat deja serialul '" << titlu << "'! Felicitari!\n";
    }
}

void Serial::afiseazaDetalii(std::ostream& os) const {
    int afisajEpisod = (episodCurent > numarEpisoade) ? numarEpisoade : episodCurent;
    os << "[SERIAL] " << titlu << " (Gen: " << gen << ") | Nota: " << getRating()
       << " | Progres: Ep. " << afisajEpisod << " / " << numarEpisoade << "\n";
}