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

    Watchlist(const Watchlist& other);
    Watchlist& operator=(Watchlist other);
    ~Watchlist();
    friend void swap(Watchlist& first, Watchlist& second) noexcept;

    void adauga(const std::shared_ptr<ContinutVideo>& cv);
    void stergeDupaTitlu(const std::string& titluCautat);
    std::shared_ptr<ContinutVideo> gasesteDupaTitlu(const std::string& titluCautat) const;
    const std::vector<std::shared_ptr<ContinutVideo>>& getLista() const;

    friend std::ostream& operator<<(std::ostream& os, const Watchlist& wl);
};