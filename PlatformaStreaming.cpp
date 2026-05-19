#include "PlatformaStreaming.h"
#include "Film.h"
#include "Serial.h"
#include "Exceptii.h"
#include <sqlite3.h>
#include <iostream>
#include <sstream>

PlatformaStreaming::PlatformaStreaming(std::string path) : dbPath(std::move(path)) {}

void PlatformaStreaming::adaugaContinutInCatalog(const std::shared_ptr<ContinutVideo>& cv) {
    if (cv) {
        catalogGlobal.push_back(cv);
    }
}

void PlatformaStreaming::incarcaCatalogDinDB() {
    sqlite3* db;
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::cerr << "[SQLITE EROARE] Nu s-a putut deschide baza de date: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    const char* sql = "SELECT tip, titlu, gen, descriere, valoare_specifica, varsta_minima FROM catalog;";
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

        if (tip == "FILM") {
            int durata = std::stoi(valoareSpecifica);
            catalogGlobal.push_back(std::make_shared<Film>(titlu, gen, descriere, durata, varstaMinima));
        }
        else if (tip == "SERIAL") {
            std::vector<int> vectorDurate;
            std::stringstream ss(valoareSpecifica);
            std::string token;

            while (std::getline(ss, token, ',')) {
                if (!token.empty()) {
                    vectorDurate.push_back(std::stoi(token));
                }
            }

            catalogGlobal.push_back(std::make_shared<Serial>(titlu, gen, descriere, vectorDurate, varstaMinima));
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void PlatformaStreaming::inregistreazaUtilizator(const std::string& nume, int varsta) {
    utilizatori.push_back(Utilizator(nume, "Free", varsta));
}

std::shared_ptr<ContinutVideo> PlatformaStreaming::cautaContinutDupaTitlu(const std::string& titlu) const {
    for (const auto& cv : catalogGlobal) {
        if (cv->getTitlu() == titlu) {
            return cv;
        }
    }
    // Daca titlul nu exista in catalog, aruncam exceptia custom prinsa in main
    throw TitluInexistentException(titlu);
}

const std::vector<std::shared_ptr<ContinutVideo>>& PlatformaStreaming::getCatalogGlobal() const {
    return catalogGlobal;
}

std::vector<Utilizator>& PlatformaStreaming::getUtilizatori() {
    return utilizatori;
}