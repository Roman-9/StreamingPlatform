#include <iostream>
#include "PlatformaStreaming.h"
#include "Teste.h"
#include "AplicatieGUI.h"

int main() {
    std::cout << "=== INITIALIZARE NETFLIX PLATFORM ===\n\n";

    // 1. Initializare si Baza de Date
    PlatformaStreaming platforma("streaming.db");
    platforma.incarcaCatalogDinDB();

    // 2. Rulam toate testele de backend in consola
    ruleazaTesteConsole(platforma);

    // 3. LANSAM INTERFATA GRAFICA
    std::cout << "\n[INFO] Lansam interfata grafica SFML...\n";
    AplicatieGUI app(platforma);
    app.ruleaza();

    return 0;
}