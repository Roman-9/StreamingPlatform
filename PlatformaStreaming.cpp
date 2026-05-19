#include "PlatformaStreaming.h"
#include "Film.h"
#include "Serial.h"
#include "Exceptii.h"
#include <iostream>

PlatformaStreaming::PlatformaStreaming(const std::string& numeFisierDB) : db(nullptr) {
    if (sqlite3_open(numeFisierDB.c_str(), &db) != SQLITE_OK) {
        std::cout << "[EROARE] Nu s-a putut deschide baza de date!\n";
    } else {
        creeazaTabele();
    }
}

PlatformaStreaming::~PlatformaStreaming() {
    if (db) {
        sqlite3_close(db);
    }
}

void PlatformaStreaming::creeazaTabele() {
    const char* sql = "CREATE TABLE IF NOT EXISTS catalog ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "tip TEXT, "
                      "titlu TEXT UNIQUE, "
                      "gen TEXT, "
                      "descriere TEXT, "
                      "valoare_specifica INTEGER, "
                      "varsta_minima INTEGER);";
    
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        sqlite3_free(errMsg);
    }
}

void PlatformaStreaming::incarcaCatalogDinDB() {
    catalogGlobal.clear();
    const char* sql = "SELECT tip, titlu, gen, descriere, valoare_specifica, varsta_minima FROM catalog;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string tip(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
            std::string titlu(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            std::string gen(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            std::string descriere(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
            int valSpecifica = sqlite3_column_int(stmt, 4);
            int varstaMin = sqlite3_column_int(stmt, 5);

            if (tip == "Film") {
                catalogGlobal.push_back(std::make_shared<Film>(titlu, gen, descriere, valSpecifica, varstaMin));
            } else if (tip == "Serial") {
                catalogGlobal.push_back(std::make_shared<Serial>(titlu, gen, descriere, valSpecifica, varstaMin));
            }
        }
    }
    sqlite3_finalize(stmt);
}

void PlatformaStreaming::salveazaFilmInDB(const std::string& titlu, const std::string& gen, const std::string& descriere, int durata, int varstaMinima) {
    const char* sql = "INSERT INTO catalog (tip, titlu, gen, descriere, valoare_specifica, varsta_minima) VALUES ('Film', ?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, titlu.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, gen.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, descriere.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 4, durata);
        sqlite3_bind_int(stmt, 5, varstaMinima);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            sqlite3_finalize(stmt);
            throw StreamingException("Eroare: Titlul '" + titlu + "' exista deja in baza de date globala!");
        }
    }
    sqlite3_finalize(stmt);
    incarcaCatalogDinDB();
}

void PlatformaStreaming::salveazaSerialInDB(const std::string& titlu, const std::string& gen, const std::string& descriere, int nrEpisoade, int varstaMinima) {
    const char* sql = "INSERT INTO catalog (tip, titlu, gen, descriere, valoare_specifica, varsta_minima) VALUES ('Serial', ?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, titlu.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, gen.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, descriere.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 4, nrEpisoade);
        sqlite3_bind_int(stmt, 5, varstaMinima);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            sqlite3_finalize(stmt);
            throw StreamingException("Eroare: Titlul '" + titlu + "' exista deja in baza de date globala!");
        }
    }
    sqlite3_finalize(stmt);
    incarcaCatalogDinDB();
}

void PlatformaStreaming::adaugaContinutInCatalog(const std::shared_ptr<ContinutVideo>& cv) {
    if (!cv) return;
    for (const auto& item : catalogGlobal) {
        if (item->getTitlu() == cv->getTitlu()) {
            throw StreamingException("Eroare: Titlul '" + cv->getTitlu() + "' exista deja in memoria platformei!");
        }
    }
    catalogGlobal.push_back(cv);
}

void PlatformaStreaming::inregistreazaUtilizator(const std::string& nume, int varsta) {
    utilizatori.emplace_back(nume, varsta);
}

std::shared_ptr<ContinutVideo> PlatformaStreaming::cautaContinutDupaTitlu(const std::string& titlu) const {
    for (const auto& item : catalogGlobal) {
        if (item->getTitlu() == titlu) {
            return item;
        }
    }
    throw TitluInexistentException(titlu);
}

const std::vector<std::shared_ptr<ContinutVideo>>& PlatformaStreaming::getCatalogGlobal() const {
    return catalogGlobal;
}

const std::vector<Utilizator>& PlatformaStreaming::getUtilizatori() const {
    return utilizatori;
}