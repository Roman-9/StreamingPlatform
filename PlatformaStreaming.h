#pragma once
#include <string>
#include <vector>
#include <memory>
#include "ContinutVideo.h"
#include "Utilizator.h"

class PlatformaStreaming {
private:
    std::string dbPath;
    std::vector<std::shared_ptr<ContinutVideo>> catalogGlobal;
    std::vector<Utilizator> utilizatori;

public:
    explicit PlatformaStreaming(std::string path);
    ~PlatformaStreaming() = default;

    void adaugaContinutInCatalog(const std::shared_ptr<ContinutVideo>& cv);
    void incarcaCatalogDinDB();
    void inregistreazaUtilizator(const std::string& nume, int varsta);

    [[nodiscard]] std::shared_ptr<ContinutVideo> cautaContinutDupaTitlu(const std::string& titlu) const;
    [[nodiscard]] const std::vector<std::shared_ptr<ContinutVideo>>& getCatalogGlobal() const;
    [[nodiscard]] std::vector<Utilizator>& getUtilizatori();
};