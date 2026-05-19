#pragma once
#include <vector>
#include <memory>
#include <string>
#include "ContinutVideo.h"

class Watchlist {
private:
    std::vector<std::shared_ptr<ContinutVideo>> lista;

public:
    Watchlist() = default;
    ~Watchlist() = default;

    void adauga(const std::shared_ptr<ContinutVideo>& cv);
    void stergeDupaTitlu(const std::string& titluCautat);
    [[nodiscard]] std::shared_ptr<ContinutVideo> gasesteDupaTitlu(const std::string& titluCautat) const;

    bool mutaInIstoric(const std::string& titluCautat, Watchlist& istoricDestinatie);
    void afiseazaDupaGen(const std::string& genCautat) const;
    void afiseazaTopRating() const;

    [[nodiscard]] int calculeazaDurataTotalaRamas() const;
    [[nodiscard]] int calculeazaTimpPierdut() const;

    [[nodiscard]] const std::vector<std::shared_ptr<ContinutVideo>>& getLista() const;

    friend std::ostream& operator<<(std::ostream& os, const Watchlist& wl);
};