#include "StrategieRecomandare.h"

std::shared_ptr<ContinutVideo> RecomandareDupaRating::recomanda(
    const std::vector<std::shared_ptr<ContinutVideo>>& catalogGlobal,
    const ListaGenerica<ContinutVideo>& istoricVizionari,
    int varstaUtilizator) const 
{
    std::shared_ptr<ContinutVideo> topPick = nullptr;
    double maxRating = -1.0;

    for (const auto& cv : catalogGlobal) {
        if (cv->getVarstaMinima() > varstaUtilizator) continue;
        if (!gasesteDaca(istoricVizionari, [&cv](const std::shared_ptr<ContinutVideo>& item) { return item->getTitlu() == cv->getTitlu(); })) {
            if (cv->getRating() > maxRating) {
                maxRating = cv->getRating();
                topPick = cv;
            }
        }
    }
    return topPick;
}

std::shared_ptr<ContinutVideo> RecomandareScurta::recomanda(
    const std::vector<std::shared_ptr<ContinutVideo>>& catalogGlobal,
    const ListaGenerica<ContinutVideo>& istoricVizionari,
    int varstaUtilizator) const 
{
    std::shared_ptr<ContinutVideo> topPick = nullptr;
    int minTimp = 999999;

    for (const auto& cv : catalogGlobal) {
        if (cv->getVarstaMinima() > varstaUtilizator) continue;
        if (!gasesteDaca(istoricVizionari, [&cv](const std::shared_ptr<ContinutVideo>& item) { return item->getTitlu() == cv->getTitlu(); })) {
            if (cv->getTimpRamas() < minTimp && cv->getTimpRamas() > 0) {
                minTimp = cv->getTimpRamas();
                topPick = cv;
            }
        }
    }
    return topPick;
}

