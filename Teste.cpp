#include "Teste.h"
#include <iostream>
#include <memory>
#include "Film.h"
#include "Serial.h"
#include "Utilizator.h"
#include "Exceptii.h"
#include "Documentar.h"

void ruleazaTesteConsole(PlatformaStreaming& platforma) {
    // 2. Testam adaugarea manuala in catalog
    auto filmNou = std::make_shared<Film>("Dune: Part Two", "Sci-Fi", "O calatorie mitica...", 166, 12);
    auto serialNou = std::make_shared<Serial>("Shogun", "Drama", "In Japonia feudala...", std::vector<int>{55, 60, 58}, 16);
    platforma.adaugaContinutInCatalog(filmNou);
    platforma.adaugaContinutInCatalog(serialNou);

    // 3. Testam serial
    std::cout << "Test conversie Serial pentru DB: " << serialNou->getDurateAsConversieString() << "\n\n";

    // 4. Inregistram utilizatori
    platforma.inregistreazaUtilizator("Andrei", 25);
    platforma.inregistreazaUtilizator("Matei", 14); // Utilizator minor pentru a testa exceptiile

    // Preluam utilizatorii
    Utilizator& user1 = platforma.getUtilizatori()[0];

    // Testam setter si getteri pentru Utilizator
    user1.setPlan("Premium");
    std::cout << "Profil: " << user1.getNume() << " | Varsta: " << user1.getVarsta()
              << " | Plan: " << user1.getPlan() << "\n\n";

    // 5. Verificam intregul catalog
    std::cout << "=== CATALOG DISPONIBIL ===\n";
    for (const auto& continut : platforma.getCatalogGlobal()) {
        std::cout << "- " << continut->getTitlu() << " (" << continut->getGen() << ") | 1"
                  << continut->getVarstaMinima() << "+\n";
        std::cout << "  Descriere: " << continut->getDescriere() << "\n";

        if (auto f = std::dynamic_pointer_cast<Film>(continut)) {
            std::cout << "  [Tip: Film] Durata totala: " << f->getDurata() << " min\n";
        } else if (auto s = std::dynamic_pointer_cast<Serial>(continut)) {
            std::cout << "  [Tip: Serial] Episoade: " << s->getNumarEpisoade()
                      << " (Primul ep: " << s->getDurateEpisoade().front() << " min)\n";
        }
    }
    std::cout << "==========================\n\n";

    // 6. Testam adaugarea in Watchlist cu tratarea Exceptiilor
    std::cout << "=== TESTARE ADAUGARE IN LISTE (CU EXCEPTII) ===\n";
    try {
        // User-ul adult adauga cu succes
        user1.adaugaInWatchlist(platforma.cautaContinutDupaTitlu("Dune: Part Two"));
        user1.adaugaInWatchlist(platforma.cautaContinutDupaTitlu("Shogun"));

        // User-ul copil incearca sa adauge un serial 16+
        Utilizator& userCopil = platforma.getUtilizatori()[1];
        userCopil.adaugaInWatchlist(platforma.cautaContinutDupaTitlu("Shogun"));
    } catch (const LimitaVarstaException& e) {
        std::cout << "[EROARE PRINSA] Matei: " << e.what() << "\n";
    } catch (const TitluInexistentException& e) {
        std::cout << "[EROARE PRINSA] " << e.what() << "\n";
    }

    try {
        // Cautam ceva ce nu exista
        user1.adaugaInWatchlist(platforma.cautaContinutDupaTitlu("Film Care Nu Exista"));
    } catch (const StreamingException& e) {
        std::cout << "[EROARE PRINSA] Andrei: " << e.what() << "\n";
    }

    // 7. Testam functionalitatile din lista de vizionare
    std::cout << "\n=== LISTA LUI " << user1.getNume() << " ===\n";
    std::cout << user1; // Apeleaza operatorul <<

    std::cout << "\n>>> PLAY TEST<<<\n";
    for (const auto& cv : user1.getWatchlist().getLista()) {
        cv->play();
    }

    std::cout << "\n>>> VIZIONARE SERIAL <<< \n";
    user1.uitaTeLaEpisod("Shogun"); // Vede episodul 1
    user1.uitaTeLaEpisod("Shogun"); // Vede episodul 2

    // 8. Timp, Note, Istoric
    std::cout << "\n>>> STATISTICI INAINTE DE A TERMINA FILMUL <<<\n";
    user1.afiseazaTimpRamas();

    // Andrei termina "Dune: Part Two" si da nota
    user1.acordaNota("Dune: Part Two", 10);
    user1.marcheazaCaVazut("Dune: Part Two");

    std::cout << "\n>>> STATISTICI DUPA CE A VAZUT FILMUL <<<\n";
    user1.afiseazaTimpRamas();
    user1.afiseazaStatistici();

    // 9. Stergere din lista
    user1.stergeDinWatchlistDupaTitlu("Shogun");

    // 10. Filtre si Cautari
    std::cout << "\n>>> RECOMANDARI SI CAUTARI <<<\n";
    user1.adaugaInWatchlist(filmNou);
    user1.acordaNota("Dune: Part Two", 9);

    user1.cautaGen("Sci-Fi");
    user1.cautaGen("Horror"); // Nu va gasi nimic
    user1.recomandaTop();

    // 11. Testare documentar
    std::cout << "\n>>> TESTAARE DOCUMENTAR <<<\n";
    auto doc1 = std::make_shared<Documentar>("Planet Earth", "Natura", "BBC", 50, "Animale", 0);
    std::cout << "Subiect documentar: " << doc1->getSubiect() << "\n";

    // 12. Testam Clone (Constructor Virtual)
    auto docClonat = doc1->clone();
    std::cout << "Am clonat cu succes: " << docClonat->getTitlu() << "\n";

    // 13. Testam Atributul Static
    std::cout << "Pana acum s-au creat in memorie " << ContinutVideo::getNumarTotalContinut() << " obiecte video.\n";
}