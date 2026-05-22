#pragma once
#include "ContinutVideo.h"

class Film : public ContinutVideo {
private:
    int durata;
public:
    Film(std::string t, std::string g, std::string d, int durata, int v, std::string cp = "", std::string lv = "");
    int getDurata() const;
    int getTimpRamas() const override;
    int getTimpVizionat() const override;
    void play() override;
    std::shared_ptr<ContinutVideo> clone() const override;
    void afisare(std::ostream& os) const override;
};