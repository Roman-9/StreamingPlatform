#pragma once
#include <SFML/Graphics.hpp>
#include "PlatformaStreaming.h"


class AplicatieGUI {
private:
    sf::RenderWindow window;
    PlatformaStreaming& platforma;

    sf::Font font;

public:
    explicit AplicatieGUI(PlatformaStreaming& p);
    void ruleaza();
    void randeazaCatalog();
};