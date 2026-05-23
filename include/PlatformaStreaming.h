#pragma once
#include <vector>
#include <memory>
#include <string>
#include "ContinutVideo.h"
#include "Utilizator.h"

class PlatformaStreaming {
private:
    std::string dbPath;
    std::vector<std::shared_ptr<ContinutVideo>> catalogGlobal;
    std::vector<Utilizator> utilizatori;

public:
    explicit PlatformaStreaming(std::string path);
    void adaugaContinutInCatalog(const std::shared_ptr<ContinutVideo>& cv);

    void stergeContinutDinCatalog(const std::string& titluCautat);

    void incarcaCatalogDinDB();
    void inregistreazaUtilizator(const std::string& nume, int varsta);
    std::shared_ptr<ContinutVideo> cautaContinutDupaTitlu(const std::string& titlu) const;
    const std::vector<std::shared_ptr<ContinutVideo>>& getCatalogGlobal() const;
    std::vector<Utilizator>& getUtilizatori();

    friend std::ostream& operator<<(std::ostream& os, const PlatformaStreaming& ps);
};