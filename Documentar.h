#pragma once
#include "ContinutVideo.h"
#include <string>
#include <memory>

class Documentar : public ContinutVideo {
private:
    int durata;
    std::string subiectPrincipal;

public:
    Documentar(std::string t, std::string g, std::string d, int durata, std::string subiect, int v);
    ~Documentar() override = default;

    void play() const override;
    int getTimpRamas() const override;
    int getTimpVizionat() const override;
    void afisare(std::ostream& os) const override;
    
    [[nodiscard]] std::shared_ptr<ContinutVideo> clone() const override;
    [[nodiscard]] const std::string& getSubiect() const;
};