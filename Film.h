#pragma once
#include "ContinutVideo.h"

class Film : public ContinutVideo {
private:
    int durata;

public:
    Film(std::string t, std::string g, std::string d, int durata, int v);
    ~Film() override = default;

    void play() const override;
    int getTimpRamas() const override;
    int getTimpVizionat() const override;
    void afisare(std::ostream& os) const override;

    [[nodiscard]] int getDurata() const;
};