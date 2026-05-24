#include <iostream>
#include "PlatformaStreaming.h"
#include "AplicatieGUI.h"
#include "Exceptii.h"

int main() {
    try {
        std::cout << "=== INITIALIZARE NETFLIX PLATFORM ===\n\n";

        // 1. Initializam obiectul platformei legat de fisierul bazei de date
        PlatformaStreaming platforma("assets/streaming.db");

        // 2. Lansam interfata grafica
        std::cout << "\n[INFO] Lansam interfata grafica SFML...\n";
        AplicatieGUI app(platforma);
        app.ruleaza();
    }
    catch (const StreamingException& e) {
        std::cerr << "[CRITICAL ERROR] Exceptie specifica platformei: " << e.what() << "\n";
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "[CRITICAL ERROR] Exceptie generala: " << e.what() << "\n";
        return 2;
    }
    catch (...) {
        std::cerr << "[CRITICAL ERROR] Exceptie necunoscuta!\n";
        return 3;
    }

    return 0;
}