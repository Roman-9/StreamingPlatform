#pragma once
#include "ContinutVideo.h"
#include <string>
#include <memory>

class Documentar : public ContinutVideo {
private:
    int durata;
    std::string subiect;

public:
    Documentar(std::string t, std::string g, std::string d, int durata, std::string subiect, int v, std::string cp = "", std::string lv = "");

    const std::string& getSubiect() const;
    int getDurata() const;

    void play() override;
    int getTimpRamas() const override;
    int getTimpVizionat() const override;

    std::shared_ptr<ContinutVideo> clone() const override;
    void afisare(std::ostream& os) const override;
};