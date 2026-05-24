#pragma once
#include "ContinutVideo.h"

class Film : public ContinutVideo {
protected:
    int durata;
    void do_afisare(std::ostream& os) const override;
public:
    Film(std::string t, std::string g, std::string d, int durata, int v, std::string cp = "", std::string lv = "");
    int getDurata() const;
    int getTimpRamas() const override;
    int getTimpVizionat() const override;
    void play() override;
    std::shared_ptr<ContinutVideo> clone() const override;

    bool matchesFilter(FiltruCatalog filtru) const override;
    std::string getDetaliiSpecifice() const override;
};