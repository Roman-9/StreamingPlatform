#pragma once
#include <vector>
#include <string>
#include <memory>
#include "ContinutVideo.h"
#include "Utilizator.h"
#include "sqlite3.h"

class PlatformaStreaming {
private:
    std::vector<std::shared_ptr<ContinutVideo>> catalogGlobal;
    std::vector<Utilizator> utilizatori;
    sqlite3* db;

    void creeazaTabele();

public:
    explicit PlatformaStreaming(const std::string& numeFisierDB = "streaming.db");
    ~PlatformaStreaming();

    PlatformaStreaming(const PlatformaStreaming&) = delete;
    PlatformaStreaming& operator=(const PlatformaStreaming&) = delete;

    void incarcaCatalogDinDB();
    void salveazaFilmInDB(const std::string& titlu, const std::string& gen, const std::string& descriere, int durata, int varstaMinima);
    void salveazaSerialInDB(const std::string& titlu, const std::string& gen, const std::string& descriere, int nrEpisoade, int varstaMinima);

    void adaugaContinutInCatalog(const std::shared_ptr<ContinutVideo>& cv);
    void inregistreazaUtilizator(const std::string& nume, int varsta);
    
    [[nodiscard]] std::shared_ptr<ContinutVideo> cautaContinutDupaTitlu(const std::string& titlu) const;
    [[nodiscard]] const std::vector<std::shared_ptr<ContinutVideo>>& getCatalogGlobal() const;
    [[nodiscard]] const std::vector<Utilizator>& getUtilizatori() const;
};