#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "ContinutVideo.h"

class Watchlist {
private:
    std::vector<std::shared_ptr<ContinutVideo>> lista;

public:
    Watchlist() = default;

    void adauga(const std::shared_ptr<ContinutVideo>& cv);
    void sterge(const std::shared_ptr<ContinutVideo>& cv);

    [[nodiscard]] const std::vector<std::shared_ptr<ContinutVideo>>& getLista() const;

    friend std::ostream& operator<<(std::ostream& os, const Watchlist& w);
};