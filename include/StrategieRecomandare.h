#pragma once
#include <memory>
#include <vector>
#include <string>
#include "ContinutVideo.h"
#include "ListaGenerica.h"

class StrategieRecomandare {
public:
    virtual ~StrategieRecomandare() = default;
    virtual std::shared_ptr<ContinutVideo> recomanda(
        const std::vector<std::shared_ptr<ContinutVideo>>& catalogGlobal,
        const ListaGenerica<ContinutVideo>& istoricVizionari,
        int varstaUtilizator) const = 0;
};

class RecomandareDupaRating : public StrategieRecomandare {
public:
    std::shared_ptr<ContinutVideo> recomanda(
        const std::vector<std::shared_ptr<ContinutVideo>>& catalogGlobal,
        const ListaGenerica<ContinutVideo>& istoricVizionari,
        int varstaUtilizator) const override;
};

class RecomandareScurta : public StrategieRecomandare {
public:
    std::shared_ptr<ContinutVideo> recomanda(
        const std::vector<std::shared_ptr<ContinutVideo>>& catalogGlobal,
        const ListaGenerica<ContinutVideo>& istoricVizionari,
        int varstaUtilizator) const override;
};
