#pragma once
#include "ContinutVideo.h"

class Serial : public ContinutVideo {
private:
    int numarEpisoade;
    int episodCurent;

public:
    explicit Serial(const std::string& t = "Fara titlu", const std::string& g = "Necunoscut",
                    const std::string& d = "Fara descriere", int nrEpisoade = 0, int v = 0);
    ~Serial() override = default;

    [[nodiscard]] int getNumarEpisoade() const;

    void play() override;
    void afiseazaDetalii(std::ostream& os) const override;
};