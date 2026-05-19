#pragma once
#include "ContinutVideo.h"

class Film : public ContinutVideo {
private:
    int durata;

public:
    explicit Film(const std::string& t = "Fara titlu", const std::string& g = "Necunoscut",
                  const std::string& d = "Fara descriere", int durata = 0, int v = 0);
    ~Film() override = default;

    [[nodiscard]] int getDurata() const;

    void play() override;
    void afiseazaDetalii(std::ostream& os) const override;
};