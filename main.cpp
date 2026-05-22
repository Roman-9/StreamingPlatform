#include <iostream>
#include "PlatformaStreaming.h"

#include "AplicatieGUI.h"

int main() {
    std::cout << "=== INITIALIZARE NETFLIX PLATFORM ===\n\n";

    // 1. Initializam obiectul platformei legat de fisierul bazei de date
    PlatformaStreaming platforma("streaming.db");

    // 2. Lansam interfata grafica
    std::cout << "\n[INFO] Lansam interfata grafica SFML...\n";
    AplicatieGUI app(platforma);
    app.ruleaza();

    return 0;
}