#include <iostream>
#include <memory>
#include "PlatformaStreaming.h"
#include "Film.h"
#include "Serial.h"
#include "Utilizator.h"
#include "Exceptii.h"

int main() {
    std::cout << "=== NETFLIX PLATFORM ===\n\n";

    PlatformaStreaming platforma("streaming.db");

    try {
        platforma.salveazaFilmInDB("Inception", "SF", "Un hot de vise...", 148, 12);
        platforma.salveazaSerialInDB("Stranger Things", "Sci-Fi", "Un grup de copii...", 34, 14);
        platforma.salveazaFilmInDB("Scream 7", "Horror", "Ghostface se intoarce...", 114, 18);
    } catch (const StreamingException& e) {
        std::cout << "[INFO] " << e.what() << "\n\n";
    }

    platforma.incarcaCatalogDinDB();

    std::cout << "--- CATALOG GLOBAL DIN BAZA DE DATE ---\n";
    for (const auto& continut : platforma.getCatalogGlobal()) {
        std::cout << *continut;
    }
    std::cout << "---------------------------------------\n\n";

    platforma.inregistreazaUtilizator("Andrei", 15);
    Utilizator user = platforma.getUtilizatori().back();
    std::cout << "S-a logat: " << user.getNume() << " (" << user.getVarsta() << " ani)\n\n";

    std::cout << ">>> TEST 1: Adaugare in Watchlist (Testare Varsta) <<<\n";
    try {
        auto film1 = platforma.cautaContinutDupaTitlu("Inception");
        auto serial1 = platforma.cautaContinutDupaTitlu("Stranger Things");
        auto film2 = platforma.cautaContinutDupaTitlu("Scream 7");

        user.adaugaInWatchlist(film1);
        user.adaugaInWatchlist(serial1);
        user.adaugaInWatchlist(film2);
    } catch (const LimitaVarstaException& e) {
        std::cout << "[EXCEPTIE PRINSA] " << e.what() << "\n";
        std::cout << " -> (RECOMANDARE) Uita-te la ce este potrivit pentru varsta ta!\n";
    } catch (const TitluInexistentException& e) {
        std::cout << "[EXCEPTIE PRINSA] " << e.what() << "\n";
    }

    std::cout << "\n" << user << "\n";

    std::cout << ">>> TEST 2: Stergere din Watchlist <<<\n";
    try {
        user.stergeDinWatchlistDupaTitlu("Inception");
        user.stergeDinWatchlistDupaTitlu("Breaking Bad");
    } catch (const TitluInexistentException& e) {
        std::cout << "[EXCEPTIE PRINSA] " << e.what() << "\n";
    }

    std::cout << "\n" << user << "\n";

    std::cout << ">>> TEST 3: Vizionare Continut <<<\n";
    for (const auto& continut : user.getWatchlist().getLista()) {
        continut->play();
    }

    return 0;
}