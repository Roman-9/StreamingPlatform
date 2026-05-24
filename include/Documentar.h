#pragma once
#include "Film.h"
#include <string>
#include <memory>

class Documentar : public Film {
private:
    std::string subiect;

protected:
    void do_afisare(std::ostream& os) const override;
public:
    Documentar(std::string t, std::string g, std::string d, int durata, std::string subiect, int v, std::string cp = "", std::string lv = "");

    const std::string& getSubiect() const;

    void play() override;
    std::shared_ptr<ContinutVideo> clone() const override;

    bool matchesFilter(FiltruCatalog filtru) const override;
    std::string getDetaliiSpecifice() const override;
    // cppcheck-suppress unusedFunction
    bool estePremium() const override { return true; }
};