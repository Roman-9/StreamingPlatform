#include "PlatformaStreaming.h"
#include "ContinutFactory.h"
#include "Exceptii.h"
#include <sqlite3.h>
#include <iostream>
#include <sstream>
#include <algorithm>

PlatformaStreaming::PlatformaStreaming(std::string path) : dbPath(std::move(path)) {}

// cppcheck-suppress unusedFunction
void PlatformaStreaming::adaugaContinutInCatalog(const std::shared_ptr<ContinutVideo>& cv) {
    if (cv) {
        catalogGlobal.adauga(cv);
    }
}

// cppcheck-suppress unusedFunction
void PlatformaStreaming::incarcaCatalogDinDB() {
    sqlite3* db;
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::cerr << "[SQLITE EROARE] Nu s-a putut deschide baza de date: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    const char* sql = "SELECT tip, titlu, gen, descriere, valoare_specifica, varsta_minima, cale_poster, link_vizionare FROM catalog;";
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "[SQLITE EROARE] Eroare la preparare SELECT: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string tip = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string titlu = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string gen = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        std::string descriere = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        std::string valoareSpecifica = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        int varstaMinima = sqlite3_column_int(stmt, 5);

        const char* rawPoster = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        std::string calePoster = rawPoster ? rawPoster : "assets/images/default.jpg";

        const char* rawLink = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
        std::string linkVizionare = rawLink ? rawLink : "https://www.youtube.com";

        if (tip == "FILM") {
            int durata = std::stoi(valoareSpecifica);
            catalogGlobal.adauga(ContinutFactory::creeazaFilm(titlu, gen, descriere, durata, varstaMinima, calePoster, linkVizionare));
        }
        else if (tip == "SERIAL") {
            std::vector<int> vectorDurate;
            std::stringstream ss(valoareSpecifica);
            std::string token;
            while (std::getline(ss, token, ',')) {
                if (!token.empty()) vectorDurate.push_back(std::stoi(token));
            }
            catalogGlobal.adauga(ContinutFactory::creeazaSerial(titlu, gen, descriere, vectorDurate, varstaMinima, calePoster, linkVizionare));
        }
        else if (tip == "DOCUMENTAR") {
            int durata = std::stoi(valoareSpecifica);
            std::string subiect = gen;
            catalogGlobal.adauga(ContinutFactory::creeazaDocumentar(titlu, gen, descriere, durata, subiect, varstaMinima, calePoster, linkVizionare));
        }
        else if (tip == "CANAL_TV") {
            std::string program = "Program Necunoscut";
            bool live = true;
            
            std::stringstream ss(valoareSpecifica);
            std::string token;
            if (std::getline(ss, token, ',')) program = token;
            if (std::getline(ss, token, ',')) live = (token == "1");
            
            catalogGlobal.adauga(ContinutFactory::creeazaCanalTV(titlu, gen, descriere, varstaMinima, program, live, calePoster, linkVizionare));
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
// cppcheck-suppress unusedFunction
void PlatformaStreaming::inregistreazaUtilizator(const std::string& nume, int varsta) {
    utilizatori.adauga(std::make_shared<Utilizator>(nume, "Free", varsta));
}

// cppcheck-suppress unusedFunction
std::shared_ptr<ContinutVideo> PlatformaStreaming::cautaContinutDupaTitlu(const std::string& titlu) const {
    auto cv = gasesteDaca(catalogGlobal, [&titlu](const std::shared_ptr<ContinutVideo>& item) { return item->getTitlu() == titlu; });
    if (cv) return cv;
    throw TitluInexistentException(titlu);
}

// cppcheck-suppress unusedFunction
const ListaGenerica<ContinutVideo>& PlatformaStreaming::getCatalogGlobal() const {
    return catalogGlobal;
}

// cppcheck-suppress unusedFunction
ListaGenerica<Utilizator>& PlatformaStreaming::getUtilizatori() {
    return utilizatori;
}

// cppcheck-suppress unusedFunction
void PlatformaStreaming::stergeContinutDinCatalog(const std::string& titluCautat) {
    try {
        catalogGlobal.stergeDaca([&titluCautat](const std::shared_ptr<ContinutVideo>& cv) {
            return cv->getTitlu() == titluCautat;
        });
    } catch (...) {
        throw TitluInexistentException("Filmul '" + titluCautat + "' nu a fost gasit pentru stergere!");
    }
}

// cppcheck-suppress unusedFunction
std::ostream& operator<<(std::ostream& os, const PlatformaStreaming& ps) {
    os << "Platforma Streaming (Catalog: " << ps.catalogGlobal.size()
       << " titluri, " << ps.utilizatori.size() << " utilizatori)";
    return os;
}