#pragma once
#include "PlatformaStreaming.h"
#include <memory> // Pentru std::unique_ptr

namespace sf {
    class RenderWindow;
    class Font;
}

class AplicatieGUI {
private:
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<sf::Font> font;
    PlatformaStreaming& platforma;

public:
    explicit AplicatieGUI(PlatformaStreaming& p);
    ~AplicatieGUI();
    void ruleaza();
    void randeazaCatalog();
};